/*
 * max11801_ts.c - Driver for MAXI MAX11801 - A Resistive touch screen
 * controller with i2c interface
 *
 * Copyright (C) 2011 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 */

/* This driver is aim for support the serial of MAXI touch chips
 * max11801-max11803, the main different of this 4 chips can get from
 * this table
 * ----------------------------------------------
 * | CHIP     |	 AUTO MODE SUPPORT | INTERFACE	|
 * |--------------------------------------------|
 * | max11800 |	 YES		   |   SPI	|
 * | max11801 |	 YES		   |   I2C	|
 * | max11802 |	 NO		   |   SPI	|
 * | max11803 |	 NO		   |   I2C	|
 * ----------------------------------------------
 *
 * Currently, this driver only support max11801.
 * */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/interrupt.h>
#include <linux/input.h>
#include <linux/irq.h>
#include <linux/slab.h>
#include <linux/bitops.h>
#include <linux/delay.h>

/* Register Address define */
#define GENERNAL_STATUS_REG		0x00
#define GENERNAL_CONF_REG		0x01
#define MESURE_RES_CONF_REG		0x02
#define MESURE_AVER_CONF_REG		0x03
#define ADC_SAMPLE_TIME_CONF_REG	0x04
#define PANEL_SETUPTIME_CONF_REG	0x05
#define DELAY_CONVERSION_CONF_REG	0x06
#define TOUCH_DETECT_PULLUP_CONF_REG	0x07
#define AUTO_MODE_TIME_CONF_REG		0x08 /* only for max11800/max11801 */
#define APERTURE_CONF_REG		0x09 /* only for max11800/max11801 */
#define AUX_MESURE_CONF_REG		0x0a
#define OP_MODE_CONF_REG		0x0b

#define FIFO_RD_CMD			(0x50 << 1)
#define MAX11801_FIFO_INT		(1 << 2)
#define MAX11801_FIFO_OVERFLOW		(1 << 3)

#define READ_BUFFER_XYZ1Z2_SIZE		16
#define XY_BUFSIZE			4

#define MAX11801_MAX_XC			0xfff
#define MAX11801_MAX_YC			0xfff

#define MEASURE_TAG_OFFSET		2
#define MEASURE_TAG_MASK		(3 << MEASURE_TAG_OFFSET)
#define EVENT_TAG_OFFSET		0
#define EVENT_TAG_MASK			(3 << EVENT_TAG_OFFSET)
#define EVENT_X_TAG			(0 << MEASURE_TAG_OFFSET)
#define EVENT_Y_TAG			(1 << MEASURE_TAG_OFFSET)

enum {
	EVENT_INIT,
	EVENT_MIDDLE,
	EVENT_RELEASE,
	EVENT_FIFO_END
};

#ifdef CALIBRATION
/**
 * calibration array refers to
 * (delta_x[0], delta_x[1], delta_x[2], delta_y[0], delta_y[1],
 * delta_y[2], delta).
 * Which generated by calibration service.
 * In this driver when we got touch pointer (x', y') from PMIC ADC,
 * we calculate the display pointer (x,y) by:
 * x = (delta_x[0] * x' + delta_x[1] * y' + delta_x[2]) / delta;
 * y = (delta_y[0] * x' + delta_y[1] * y' + delta_y[2]) / delta;
 */
static int calibration[7];
module_param_array(calibration, int, NULL, S_IRUGO | S_IWUSR);
#endif

struct max11801_data {
	struct i2c_client		*client;
	struct input_dev		*input_dev;
	struct delayed_work		work;
	struct workqueue_struct		*workq;
};

static u8 read_register(struct i2c_client *client, int addr)
{
	/* This chip ignore LSB of register address */
	return i2c_smbus_read_byte_data(client, addr << 1);
}

static int max11801_write_reg(struct i2c_client *client, int addr, int data)
{
	/* This chip ignore LSB of register address */
	return i2c_smbus_write_byte_data(client, addr << 1, data);
}

#ifdef CALIBRATION
static void calibration_pointer(int *x_orig, int *y_orig)
{
	int x, y;
	if (calibration[6] == 0)
		return;
	x = calibration[0] * (*x_orig) +
		calibration[1] * (*y_orig) +
		calibration[2];
	x /= calibration[6];
	if (x < 0)
		x = 0;
	y = calibration[3] * (*x_orig) +
		calibration[4] * (*y_orig) +
		calibration[5];
	y /= calibration[6];
	if (y < 0)
		y = 0;

	*x_orig = x;
	*y_orig = y;
}
#else
static void calibration_pointer(int *x_orig, int *y_orig)
{
	int  y;
	y = MAX11801_MAX_YC - *y_orig;
	*y_orig = y;
}
#endif

static void maxi_ts_work(struct work_struct *work)
{
	struct max11801_data *data = container_of(to_delayed_work(work),
						  struct max11801_data, work);
	struct i2c_client *client = data->client;
	unsigned int x, y;
	int status, i, ret;
	u8 buf[XY_BUFSIZE];

	status = read_register(data->client, GENERNAL_STATUS_REG);
	while (status & (MAX11801_FIFO_INT | MAX11801_FIFO_OVERFLOW)) {

		status = read_register(data->client, GENERNAL_STATUS_REG);

		ret = i2c_smbus_read_i2c_block_data(client, FIFO_RD_CMD,
						    XY_BUFSIZE, buf);
		if (ret < 4) {
			dev_err(&client->dev, "event not enough\n");
			continue;
		}

		for (i = 0; i < XY_BUFSIZE; i += 2) {
			if ((buf[i+1] & MEASURE_TAG_MASK) == EVENT_X_TAG)
				x = (buf[i] << 4) + (buf[i+1] >> 4);
			else if ((buf[i+1] & MEASURE_TAG_MASK) == EVENT_Y_TAG)
				y = (buf[i] << 4) + (buf[i+1] >> 4);
		}

		if ((buf[1] & EVENT_TAG_MASK) != (buf[3] & EVENT_TAG_MASK))
			continue;

		switch (buf[1] & EVENT_TAG_MASK) {
		case EVENT_INIT:
		case EVENT_MIDDLE:
			dev_dbg(&client->dev, "before cali: x :%d y: %d\n",
				x, y);
			calibration_pointer(&x, &y);
			dev_dbg(&client->dev, "after cali: x :%d y: %d\n",
				x, y);
			input_report_abs(data->input_dev, ABS_X, x);
			input_report_abs(data->input_dev, ABS_Y, y);
			input_report_abs(data->input_dev, ABS_PRESSURE, 1);
			input_event(data->input_dev, EV_KEY, BTN_TOUCH, 1);
			input_sync(data->input_dev);
			break;
		case EVENT_RELEASE:
			input_report_abs(data->input_dev, ABS_PRESSURE, 0);
			input_event(data->input_dev, EV_KEY, BTN_TOUCH, 0);
			input_sync(data->input_dev);
			break;
		case EVENT_FIFO_END:
			break;
		}
	}
	enable_irq(client->irq);
}

static void max11801_ts_phy_init(struct max11801_data *data)
{
	struct i2c_client *client = data->client;

	/* Average X,Y, take 16 samples, average eight media sample */
	max11801_write_reg(client, MESURE_AVER_CONF_REG, 0xff);
	/* X,Y panel setup time set to 20us */
	max11801_write_reg(client, PANEL_SETUPTIME_CONF_REG, 0x11);
	/* Rough pullup time (2uS), Fine pullup time (10us)  */
	max11801_write_reg(client, TOUCH_DETECT_PULLUP_CONF_REG, 0x10);
	/* Auto mode init period = 5ms , scan period = 5ms*/
	max11801_write_reg(client, AUTO_MODE_TIME_CONF_REG, 0xaa);
	/* Aperture X,Y set to +- 4LSB */
	max11801_write_reg(client, APERTURE_CONF_REG, 0x33);
	/* Enable Power, enable Automode, enable Aperture, enable Average X,Y */
	max11801_write_reg(client, OP_MODE_CONF_REG, 0x36);
}

static irqreturn_t max11801_irq(int irq, void *dev)
{
	struct max11801_data *data = dev;
	disable_irq_nosync(irq);
	queue_delayed_work(data->workq, &data->work, 0);
	return IRQ_HANDLED;
}

static int __devinit max11801_ts_probe(struct i2c_client *client,
				       const struct i2c_device_id *id)
{
	struct max11801_data *data;
	struct input_dev *input_dev;
	int ret;

	data = kzalloc(sizeof(struct max11801_data), GFP_KERNEL);
	if (!data) {
		dev_err(&client->dev, "Failed to allocate memory\n");
		return -ENOMEM;
	}

#ifdef CALIBRATION
	memset(calibration, 0, sizeof(calibration));
#endif

	input_dev = input_allocate_device();
	if (!input_dev) {
		dev_err(&client->dev, "Failed to allocate memory\n");
		ret = -ENOMEM;
		goto err_free_mem;
	}

	data->client = client;
	data->input_dev = input_dev;
	max11801_ts_phy_init(data);
	INIT_DELAYED_WORK(&data->work, maxi_ts_work);
	data->workq = create_singlethread_workqueue("max11801_ts");
	if (!data->workq) {
		dev_err(&client->dev, "Failed to create workqueue\n");
		ret = -ENOMEM;
		goto err_free_wq;
	}

	input_dev->name = "max11801_ts";
	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.parent = &client->dev;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);
	__set_bit(ABS_X, input_dev->absbit);
	__set_bit(ABS_Y, input_dev->absbit);
	__set_bit(ABS_PRESSURE, input_dev->absbit);
#ifndef CALIBRATION
	input_set_abs_params(input_dev, ABS_X, 0, MAX11801_MAX_XC, 0, 0);
	input_set_abs_params(input_dev, ABS_Y, 0, MAX11801_MAX_YC, 0, 0);
#endif
	input_set_drvdata(input_dev, data);

	ret = request_irq(client->irq, max11801_irq,
				   IRQF_TRIGGER_LOW, "max11801_ts", data);
	if (ret < 0) {
		dev_err(&client->dev, "Failed to register interrupt\n");
		goto err_free_dev;
	}

	ret = input_register_device(data->input_dev);
	if (ret < 0)
		goto err_free_irq;
	i2c_set_clientdata(client, data);
	return 0;

err_free_irq:
	free_irq(client->irq, data);
err_free_wq:
	destroy_workqueue(data->workq);
err_free_dev:
	input_free_device(input_dev);
err_free_mem:
	kfree(data);
	return ret;
}

static __devexit int max11801_ts_remove(struct i2c_client *client)
{
	struct max11801_data *data = i2c_get_clientdata(client);

	free_irq(client->irq, data);
	cancel_delayed_work_sync(&data->work);
	destroy_workqueue(data->workq);
	input_unregister_device(data->input_dev);
	input_free_device(data->input_dev);
	kfree(data);

	return 0;
}

static const struct i2c_device_id max11801_ts_id[] = {
	{"max11801", 0},
	{ }
};
MODULE_DEVICE_TABLE(i2c, max11801_ts_id);

static struct i2c_driver max11801_ts_driver = {
	.probe		= max11801_ts_probe,
	.remove		= __devexit_p(max11801_ts_remove),
	.driver = {
		.name = "max11801_ts",
	},
	.id_table	= max11801_ts_id,
};

static int __init max11801_ts_init(void)
{
	return i2c_add_driver(&max11801_ts_driver);
}

static void __exit max11801_ts_exit(void)
{
	i2c_del_driver(&max11801_ts_driver);
}

module_init(max11801_ts_init);
module_exit(max11801_ts_exit);

MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_DESCRIPTION("Touchscreen driver for MAXI MAX11801 controller");
MODULE_LICENSE("GPL");
