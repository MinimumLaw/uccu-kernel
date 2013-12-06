/*
 * Copyright 2009-2010 Freescale Semiconductor, Inc. All Rights Reserved.
 */

/*
 * The code contained herein is licensed under the GNU General Public
 * License. You may obtain a copy of the GNU General Public License
 * Version 2 or later at the following locations:
 *
 * http://www.opensource.org/licenses/gpl-license.html
 * http://www.gnu.org/copyleft/gpl.html
 */

#include <linux/slab.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/pm.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/init.h>
#include <linux/clk.h>
#include <linux/platform_device.h>
#include <linux/fsl_devices.h>
#include <linux/spi/spi.h>
#include <linux/i2c.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/map.h>
#include <linux/mtd/partitions.h>
#include <linux/regulator/consumer.h>
#include <linux/pmic_external.h>
#include <linux/pmic_status.h>
#include <linux/ipu.h>
#include <linux/mxcfb.h>
#include <linux/gpio.h>
#include <linux/gpio_keys.h>
#include <linux/pwm_backlight.h>
#include <linux/can/platform/mcp251x.h>
#include <mach/common.h>
#include <mach/hardware.h>
#include <asm/setup.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/time.h>
#include <asm/mach/keypad.h>
#include <asm/mach/flash.h>
#include <mach/gpio.h>
#include <mach/mmc.h>
#include <mach/mxc_dvfs.h>
#include <mach/mxc_edid.h>
#include <mach/iomux-mx51.h>
#include <mach/i2c.h>

#include "devices.h"
#include "crm_regs.h"
#include "usb.h"

/*!
 * @file mach-mx51/mx51_babbage.c
 *
 * @brief This file contains the board specific initialization routines.
 *
 * @ingroup MSL_MX51
 */

#define BABBAGE_SD1_CD			(0*32 + 0)	/* GPIO_1_0 */
#define BABBAGE_SW12V_EN		(0*32 + 1)	/* GPIO_1_1 */
#define BABBAGE_WDOG_B			(0*32 + 4)	/* GPIO_1_4 */
#define BABBAGE_SD2_WP			(0*32 + 5)	/* GPIO_1_5 */
#define BABBAGE_SD2_CD			(0*32 + 6)	/* GPIO_1_6 */
#define BABBAGE_USBH1_HUB_RST_B		(0*32 + 7)	/* GPIO_1_7 */
#define BABBAGE_PMIC_INT		(0*32 + 8)	/* GPIO_1_8 */

#define BABBAGE_GPO_3			(1*32 + 1)	/* GPIO_2_1 */
#define BABBAGE_GPI_0			(1*32 + 2)	/* GPIO_2_2 */
#define BABBAGE_GPI_1			(1*32 + 4)	/* GPIO_2_4 */
#define BABBAGE_USB_PHY_RESET_B		(1*32 + 5)	/* GPIO_2_5 */
#define BABBAGE_GPI_2			(1*32 + 6)	/* GPIO_2_6 */
#define BABBAGE_GPI_3			(1*32 + 7)	/* GPIO_2_7 */
#define BABBAGE_GPO_0			(1*32 + 12)	/* GPIO_2_12 */
#define BABBAGE_GPO_1			(1*32 + 13)	/* GPIO_2_13 */
#define BABBAGE_FEC_PHY_RESET_B		(1*32 + 14)	/* GPIO_2_14 */
#define BABBAGE_BT_ENABLE		(1*32 + 15)	/* GPIO_2_15 */
#define BABBAGE_WL_ENABLE		(1*32 + 16)	/* GPIO_2_16 */
#define BABBAGE_GPO_2			(1*32 + 17)	/* GPIO_2_17 */
#define BABBAGE_CAN_RESET_B		(1*32 + 18)	/* GPIO_2_18 */
#define BABBAGE_WIRELESS_IRQ		(1*32 + 19)	/* GPIO_2_19 */
#define BABBAGE_CAN_IRQ			(1*32 + 20)	/* GPIO_2_20 */
#define BABBAGE_POWER_KEY		(1*32 + 21)	/* GPIO_2_21 */
#define BABBAGE_EIM_RESET		(1*32 + 26)	/* GPIO_2_26 */
#define BABBAGE_EIM_IRQ			(1*32 + 31)	/* GPIO_2_31 */

#define BABBAGE_26M_OSC_EN		(2*32 + 1)	/* GPIO_3_1 */
#define BABBAGE_LVDS_POWER_DOWN_B	(2*32 + 3)	/* GPIO_3_3 */
#define BABBAGE_VDAC_POWER_DOWN_B	(2*32 + 8)	/* GPIO_3_8 */
#define BABBAGE_HEADPHONE_DET		(2*32 + 26)	/* GPIO_3_26 */

#define BABBAGE_VADC_RESET_B		(3*32 + 11)	/* GPIO_4_11 */
#define BABBAGE_VADC_POWER_DOWN_B	(3*32 + 12)	/* GPIO_4_12 */
#define BABBAGE_USB_CLK_EN_B		(3*32 + 13)	/* GPIO_4_13 */
#define BABBAGE_3V3_ON			(3*32 + 15)	/* GPIO_4_15 */
#define BABBAGE_CSPI1_SS0_GPIO		(3*32 + 24)	/* GPIO_4_24 */
#define BABBAGE_AUDIO_CLK_EN_B		(3*32 + 26)	/* GPIO_4_26 */

extern int __init mx51_babbage_init_mc13892(void);
extern struct cpu_wp *(*get_cpu_wp)(int *wp);
extern void (*set_num_cpu_wp)(int num);
static int num_cpu_wp = 3;

static iomux_v3_cfg_t mx51babbage_pads[] = {
	/* UART1 */
	MX51_PAD_UART1_RXD__UART1_RXD,
	MX51_PAD_UART1_TXD__UART1_TXD,
	MX51_PAD_UART1_RTS__UART1_RTS,
	MX51_PAD_UART1_CTS__UART1_CTS,
	MX51_PAD_UART3_RXD__UART1_DTR,
	MX51_PAD_UART3_TXD__UART1_DSR,
	MX51_PAD_KEY_COL4__UART1_RI,
	MX51_PAD_KEY_COL5__UART1_DCD,

	/* UART 2 */
	MX51_PAD_UART2_RXD__UART2_RXD,
	MX51_PAD_UART2_TXD__UART2_TXD,

	/* UART 3 */
	MX51_PAD_EIM_D24__UART3_CTS,
	MX51_PAD_EIM_D25__UART3_RXD,
	MX51_PAD_EIM_D26__UART3_TXD,
	MX51_PAD_EIM_D27__UART3_RTS,

	/* USB HOST1 */
	MX51_PAD_USBH1_STP__USBH1_STP,
	MX51_PAD_USBH1_CLK__USBH1_CLK,
	MX51_PAD_USBH1_DIR__USBH1_DIR,
	MX51_PAD_USBH1_NXT__USBH1_NXT,
	MX51_PAD_USBH1_DATA0__USBH1_DATA0,
	MX51_PAD_USBH1_DATA1__USBH1_DATA1,
	MX51_PAD_USBH1_DATA2__USBH1_DATA2,
	MX51_PAD_USBH1_DATA3__USBH1_DATA3,
	MX51_PAD_USBH1_DATA4__USBH1_DATA4,
	MX51_PAD_USBH1_DATA5__USBH1_DATA5,
	MX51_PAD_USBH1_DATA6__USBH1_DATA6,
	MX51_PAD_USBH1_DATA7__USBH1_DATA7,
	MX51_PAD_CSI2_VSYNC__GPIO4_13, /* SION required */ /* USB CLK Enable pin */

	MX51_PAD_CSI2_D18__GPIO4_11, /* SION required */ /* VADC Reset pin */

	MX51_PAD_GPIO1_0__GPIO1_0,
	MX51_PAD_GPIO1_1__GPIO1_1, /* SION required */
	MX51_PAD_GPIO1_4__GPIO1_4,
	MX51_PAD_GPIO1_5__GPIO1_5,
	MX51_PAD_GPIO1_6__GPIO1_6,
	MX51_PAD_GPIO1_7__GPIO1_7, /* SION required */
	MX51_PAD_GPIO1_8__GPIO1_8,

	MX51_PAD_EIM_D17__GPIO2_1, /* SION required */
	MX51_PAD_EIM_D18__GPIO2_2,
	MX51_PAD_EIM_D20__GPIO2_4,
	MX51_PAD_EIM_D21__GPIO2_5, /* SION required */
	MX51_PAD_EIM_D22__GPIO2_6,
	MX51_PAD_EIM_D23__GPIO2_7,
	MX51_PAD_EIM_A17__GPIO2_11,
	MX51_PAD_EIM_A18__GPIO2_12, /* SION required */
	MX51_PAD_EIM_A19__GPIO2_13, /* SION required */
	MX51_PAD_EIM_A20__GPIO2_14, /* SION required */
	MX51_PAD_EIM_A21__GPIO2_15,
	MX51_PAD_EIM_A22__GPIO2_16,
	MX51_PAD_EIM_A23__GPIO2_17, /* SION required */
	MX51_PAD_EIM_A25__GPIO2_19,
	MX51_PAD_EIM_A26__GPIO2_20,
	MX51_PAD_EIM_A27__GPIO2_21,
	MX51_PAD_EIM_DTACK__GPIO2_31,
	MX51_PAD_EIM_LBA__EIM_LBA,

	MX51_PAD_DI1_D0_CS__GPIO3_3, /* SION required */
	MX51_PAD_DISPB2_SER_DIN__GPIO3_5,
	MX51_PAD_DISPB2_SER_DIO__GPIO3_6,
	/* MX51_PAD_NANDF_CS0__GPIO3_16,  TO DO for NJM */
	MX51_PAD_NANDF_CS1__GPIO3_17,
	MX51_PAD_NANDF_D14__GPIO3_26,
	MX51_PAD_NANDF_D12__GPIO3_28,

	MX51_PAD_CSI2_D12__GPIO4_9,
	MX51_PAD_CSI2_D13__GPIO4_10,
	MX51_PAD_CSI2_D19__GPIO4_12,
	MX51_PAD_CSPI1_RDY__GPIO4_26, /* SION required */

	/* FEC */
	MX51_PAD_EIM_EB2__FEC_MDIO,
	MX51_PAD_NANDF_D9__FEC_RDATA0,
	MX51_PAD_EIM_EB3__FEC_RDATA1,
	MX51_PAD_EIM_CS2__FEC_RDATA2,
	MX51_PAD_EIM_CS3__FEC_RDATA3,
	MX51_PAD_EIM_CS4__FEC_RX_ER,
	MX51_PAD_EIM_CS5__FEC_CRS,
	MX51_PAD_NANDF_RB2__FEC_COL,
	MX51_PAD_NANDF_RB3__FEC_RX_CLK,
	MX51_PAD_NANDF_CS2__FEC_TX_ER,
	MX51_PAD_NANDF_CS3__FEC_MDC,
	MX51_PAD_NANDF_D8__FEC_TDATA0,
	MX51_PAD_NANDF_CS4__FEC_TDATA1,
	MX51_PAD_NANDF_CS5__FEC_TDATA2,
	MX51_PAD_NANDF_CS6__FEC_TDATA3,
	MX51_PAD_NANDF_CS7__FEC_TX_EN,
	MX51_PAD_NANDF_RDY_INT__FEC_TX_CLK,
	MX51_PAD_NANDF_D11__FEC_RX_DV,

	MX51_PAD_EIM_CS1__GPIO2_26, /* SION required */
	MX51_PAD_GPIO_NAND__PATA_INTRQ,

	MX51_PAD_DI_GP4__DI2_PIN15,
#ifdef CONFIG_FB_MXC_CLAA_WVGA_SYNC_PANEL
	MX51_PAD_DISP1_DAT22__DISP2_DAT16,
	MX51_PAD_DISP1_DAT23__DISP2_DAT17,

	MX51_PAD_DI1_D1_CS__GPIO3_4,
#endif
//	FixMe: What is it? Separete interface?
//	MX51_PAD_I2C1_CLK__HSI2C_CLK,
//	MX51_PAD_I2C1_DAT__HSI2C_DAT,
	MX51_PAD_EIM_D16__I2C1_SDA,
	MX51_PAD_EIM_D19__I2C1_SCL,

	MX51_PAD_GPIO1_2__PWM1_PWMO,

	MX51_PAD_KEY_COL5__I2C2_SDA,
	MX51_PAD_KEY_COL4__I2C2_SCL,

	MX51_PAD_SD1_CMD__SD1_CMD,
	MX51_PAD_SD1_CLK__SD1_CLK,
	MX51_PAD_SD1_DATA0__SD1_DATA0,
	MX51_PAD_SD1_DATA1__SD1_DATA1,
	MX51_PAD_SD1_DATA2__SD1_DATA2,
	MX51_PAD_SD1_DATA3__SD1_DATA3,

	MX51_PAD_AUD3_BB_TXD__AUD3_TXD,
	MX51_PAD_AUD3_BB_RXD__AUD3_RXD,
	MX51_PAD_AUD3_BB_CK__AUD3_TXC,
	MX51_PAD_AUD3_BB_FS__AUD3_TXFS,

	MX51_PAD_CSPI1_SS1__ECSPI1_SS1,
	MX51_PAD_DI1_PIN11__ECSPI1_SS2,

	MX51_PAD_DI_GP3__CSI1_DATA_EN,
	MX51_PAD_CSI1_D10__CSI1_D10,
	MX51_PAD_CSI1_D11__CSI1_D11,
	MX51_PAD_CSI1_D12__CSI1_D12,
	MX51_PAD_CSI1_D13__CSI1_D13,
	MX51_PAD_CSI1_D14__CSI1_D14,
	MX51_PAD_CSI1_D15__CSI1_D15,
	MX51_PAD_CSI1_D16__CSI1_D16,
	MX51_PAD_CSI1_D17__CSI1_D17,
	MX51_PAD_CSI1_D18__CSI1_D18,
	MX51_PAD_CSI1_D19__CSI1_D19,
	MX51_PAD_CSI1_VSYNC__CSI1_VSYNC,
	MX51_PAD_CSI1_HSYNC__CSI1_HSYNC,

	MX51_PAD_OWIRE_LINE__OWIRE_LINE,

	/* CAN */
	MX51_PAD_EIM_A24__GPIO2_18, /* SION required */
//	FixMe: What is it? No this pin mode in iomux?
//	MX51_PAD_EIM_A26__CAN_IRQ,

	MX51_PAD_DI1_PIN12__GPIO3_1, /* SION required */
	MX51_PAD_DI1_D0_CS__GPIO3_3, /* SION required */     /* LVDS power down */
	MX51_PAD_DISPB2_SER_RS__GPIO3_8, /* SION required */ /* Video DAC power down */
};

static iomux_v3_cfg_t mx51_sd2_as_sd2_pads[] = {
	MX51_PAD_SD2_CMD__SD2_CMD,
	MX51_PAD_SD2_CLK__SD2_CLK,
	MX51_PAD_SD2_DATA0__SD2_DATA0,
	MX51_PAD_SD2_DATA1__SD2_DATA1,
	MX51_PAD_SD2_DATA2__SD2_DATA2,
	MX51_PAD_SD2_DATA3__SD2_DATA3,
};

static iomux_v3_cfg_t mx51_sd2_as_spi_pads[] = {
	MX51_PAD_SD2_CMD__CSPI_MOSI,
	MX51_PAD_SD2_CLK__CSPI_SCLK,
	MX51_PAD_SD2_DATA0__CSPI_MISO,
	MX51_PAD_SD2_DATA3__CSPI_SS2,
};

/* working point(wp): 0 - 800MHz; 1 - 166.25MHz; */
static struct cpu_wp cpu_wp_auto[] = {
	{
	 .pll_rate = 1000000000,
	 .cpu_rate = 1000000000,
	 .pdf = 0,
	 .mfi = 10,
	 .mfd = 11,
	 .mfn = 5,
	 .cpu_podf = 0,
	 .cpu_voltage = 1175000,},
	{
	 .pll_rate = 800000000,
	 .cpu_rate = 800000000,
	 .pdf = 0,
	 .mfi = 8,
	 .mfd = 2,
	 .mfn = 1,
	 .cpu_podf = 0,
	 .cpu_voltage = 1100000,},
	{
	 .pll_rate = 800000000,
	 .cpu_rate = 166250000,
	 .pdf = 4,
	 .mfi = 8,
	 .mfd = 2,
	 .mfn = 1,
	 .cpu_podf = 4,
	 .cpu_voltage = 850000,},
};

static struct fb_videomode video_modes[] = {
	{
	 /* NTSC TV output */
	 "TV-NTSC", 60, 720, 480, 74074,
	 122, 15,
	 18, 26,
	 1, 1,
	 FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT | FB_SYNC_EXT,
	 FB_VMODE_INTERLACED,
	 0,},
	{
	 /* PAL TV output */
	 "TV-PAL", 50, 720, 576, 74074,
	 132, 11,
	 22, 26,
	 1, 1,
	 FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT | FB_SYNC_EXT,
	 FB_VMODE_INTERLACED | FB_VMODE_ODD_FLD_FIRST,
	 0,},
	{
	 /* 720p60 TV output */
	 "720P60", 60, 1280, 720, 13468,
	 260, 109,
	 25, 4,
	 1, 1,
	 FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT |
			FB_SYNC_EXT,
	 FB_VMODE_NONINTERLACED,
	 0,},
	{
	 /*MITSUBISHI LVDS panel */
	 "XGA", 60, 1024, 768, 15385,
	 220, 40,
	 21, 7,
	 60, 10,
	 0,
	 FB_VMODE_NONINTERLACED,
	 0,},
	{
	 /* 800x480 @ 57 Hz , pixel clk @ 27MHz */
	 "CLAA-WVGA", 57, 800, 480, 37037, 40, 60, 10, 10, 20, 10,
	 FB_SYNC_CLK_LAT_FALL,
	 FB_VMODE_NONINTERLACED,
	 0,},
};

struct cpu_wp *mx51_babbage_get_cpu_wp(int *wp)
{
	*wp = num_cpu_wp;
	return cpu_wp_auto;
}

void mx51_babbage_set_num_cpu_wp(int num)
{
	num_cpu_wp = num;
	return;
}

static struct mxc_w1_config mxc_w1_data = {
	.search_rom_accelerator = 1,
};

static u16 keymapping[16] = {
	KEY_UP, KEY_DOWN, KEY_MENU, KEY_BACK,
	KEY_RIGHT, KEY_LEFT, KEY_SELECT, KEY_ENTER,
	KEY_F1, KEY_F3, KEY_1, KEY_3,
	KEY_F2, KEY_F4, KEY_2, KEY_4,
};

static struct keypad_data keypad_plat_data = {
	.rowmax = 4,
	.colmax = 4,
	.learning = 0,
	.delay = 2,
	.matrix = keymapping,
};

static struct platform_pwm_backlight_data mxc_pwm_backlight_data = {
	.pwm_id = 0,
	.max_brightness = 255,
	.dft_brightness = 128,
	.pwm_period_ns = 78770,
};

extern void mx5_ipu_reset(void);
static struct mxc_ipu_config mxc_ipu_data = {
	.rev = 2,
	.reset = mx5_ipu_reset,
};

extern void mx5_vpu_reset(void);
static struct mxc_vpu_platform_data mxc_vpu_data = {
	.reset = mx5_vpu_reset,
};

/* workaround for ecspi chipselect pin may not keep correct level when idle */
static void mx51_babbage_gpio_ecspi_chipselect_active(int cspi_mode, int status,
					     int chipselect)
{
	switch (cspi_mode) {
	case 1:
		switch (chipselect) {
		case 0x1:
			{
			mxc_iomux_v3_setup_pad(MX51_PAD_CSPI1_SS0__ECSPI1_SS0);
			break;
			}
		case 0x2:
		case 0x3:
			{
			mxc_iomux_v3_setup_pad(MX51_PAD_CSPI1_SS0__GPIO4_24);
			gpio_request(BABBAGE_CSPI1_SS0_GPIO, "cspi1-gpio");
			gpio_direction_output(BABBAGE_CSPI1_SS0_GPIO, 0);
			//gpio_set_value(BABBAGE_CSPI1_SS0_GPIO, 1 & (~status));
			break;
			}
		default:
			break;
		}
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
}

static void mx51_babbage_gpio_ecspi_chipselect_inactive(int cspi_mode, int status,
					       int chipselect)
{
	switch (cspi_mode) {
	case 1:
		switch (chipselect) {
		case 0x1:
			break;
		case 0x2:
		case 0x3:
			gpio_free(BABBAGE_CSPI1_SS0_GPIO);
			break;

		default:
			break;
		}
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
}

static void mx51_babbage_cspi_chipselect_active(int cspi_mode, int status,
					     int chipselect)
{
	//pr_info("DIMAS: CS act\n");
}

static void mx51_babbage_cspi_chipselect_inactive(int cspi_mode, int status,
					       int chipselect)
{
	//pr_info("DIMAS: CS inact\n");
}

static struct mxc_spi_master mxcspi1_data = {
	.maxchipselect = 4,
	.spi_version = 23,
	.chipselect_active = mx51_babbage_gpio_ecspi_chipselect_active,
	.chipselect_inactive = mx51_babbage_gpio_ecspi_chipselect_inactive,
};

static struct mxc_spi_master mxcspi3_data = {
	.maxchipselect = 4,
	.spi_version = 7,
	.chipselect_active = mx51_babbage_cspi_chipselect_active,
	.chipselect_inactive = mx51_babbage_cspi_chipselect_inactive,
};

static struct imxi2c_platform_data mxci2c_data = {
	.bitrate = 100000,
};

static struct mxc_i2c_platform_data mxci2c_hs_data = {
	.i2c_clk = 400000,
};

/* FixMe: removed for build 
static struct mxc_srtc_platform_data srtc_data = {
	.srtc_sec_mode_addr = 0x83F98840,
}; */

static struct tve_platform_data tve_data = {
	.dac_reg = "VVIDEO",
};

static struct mxc_dvfs_platform_data dvfs_core_data = {
	.reg_id = "SW1",
	.clk1_id = "cpu_clk",
	.clk2_id = "gpc_dvfs_clk",
	.gpc_cntr_offset = MXC_GPC_CNTR_OFFSET,
	.gpc_vcr_offset = MXC_GPC_VCR_OFFSET,
	.ccm_cdcr_offset = MXC_CCM_CDCR_OFFSET,
	.ccm_cacrr_offset = MXC_CCM_CACRR_OFFSET,
	.ccm_cdhipr_offset = MXC_CCM_CDHIPR_OFFSET,
	.prediv_mask = 0x1F800,
	.prediv_offset = 11,
	.prediv_val = 3,
	.div3ck_mask = 0xE0000000,
	.div3ck_offset = 29,
	.div3ck_val = 2,
	.emac_val = 0x08,
	.upthr_val = 25,
	.dnthr_val = 9,
	.pncthr_val = 33,
	.upcnt_val = 10,
	.dncnt_val = 10,
	.delay_time = 30,
/* FixMe: removed
	.num_wp = 3, */
};

static struct mxc_dvfsper_data dvfs_per_data = {
	.reg_id = "SW2",
	.clk_id = "gpc_dvfs_clk",
	.gpc_cntr_reg_addr = MXC_GPC_CNTR,
	.gpc_vcr_reg_addr = MXC_GPC_VCR,
	.gpc_adu = 0x0,
	.vai_mask = MXC_DVFSPMCR0_FSVAI_MASK,
	.vai_offset = MXC_DVFSPMCR0_FSVAI_OFFSET,
	.dvfs_enable_bit = MXC_DVFSPMCR0_DVFEN,
	.irq_mask = MXC_DVFSPMCR0_FSVAIM,
	.div3_offset = 0,
	.div3_mask = 0x7,
	.div3_div = 2,
	.lp_high = 1250000,
	.lp_low = 1250000,
};

static struct mxc_spdif_platform_data mxc_spdif_data = {
	.spdif_tx = 1,
	.spdif_rx = 0,
	.spdif_clk_44100 = 0,	/* spdif_ext_clk source for 44.1KHz */
	.spdif_clk_48000 = 7,	/* audio osc source */
	.spdif_clkid = 0,
	.spdif_clk = NULL,	/* spdif bus clk */
};

/* NAND Flash Partitions */
#ifdef CONFIG_MTD_PARTITIONS

static struct mtd_partition nand_flash_partitions[] = {
	{
	 .name = "resque",
	 .offset = 0,
	 .size = 50 * 1024 * 1024},
	{
	 .name = "restore",
	 .offset = MTDPART_OFS_APPEND,
	 .size = 450 * 1024 * 1024},
	{
	 .name = "reserved",
	 .offset = MTDPART_OFS_APPEND,
	 .size = MTDPART_SIZ_FULL},
};

#endif

extern void gpio_nand_active(void);
extern void gpio_nand_inactive(void);

static int nand_init(void)
{
	/* Configure the pins */
	gpio_nand_active();
	return 0;
}

static void nand_exit(void)
{
	/* Free the pins */
	gpio_nand_inactive();
}

static struct flash_platform_data mxc_nand_data = {
	#ifdef CONFIG_MTD_PARTITIONS
		.parts = nand_flash_partitions,
		.nr_parts = ARRAY_SIZE(nand_flash_partitions),
	#endif
	.width = 1,
	.init = nand_init,
	.exit = nand_exit,
};

/* i.MX MTD NAND Flash Controller */

#if defined(CONFIG_MTD_NAND_IMX_NFC) || defined(CONFIG_MTD_NAND_IMX_NFC_MODULE)

/*
 * Platform-specific information about this device. Some of the details depend
 * on the SoC. See imx_init_nfc() below for code that fills in the rest.
 */

static struct imx_nfc_platform_data imx_nfc_platform_data = {
	.nfc_major_version  = 3,
	.nfc_minor_version  = 2,
	.force_ce           = false,
	.target_cycle_in_ns = 30,
	.clock_name         = "nfc_clk",
	.set_page_size      = 0,
	.interleave         = false,
	#ifdef CONFIG_MTD_PARTITIONS
		.partitions      = nand_flash_partitions,
		.partition_count = ARRAY_SIZE(nand_flash_partitions),
	#endif
};

#endif /* i.MX MTD NAND Flash Controller */

static struct resource mxcfb_resources[] = {
	[0] = {
	       .flags = IORESOURCE_MEM,
	       },
};

static struct mxc_fb_platform_data fb_data[] = {
	{
	 .interface_pix_fmt = IPU_PIX_FMT_RGB24,
	 .mode_str = "1024x768M-16@60",
	 .mode = video_modes,
	 .num_modes = ARRAY_SIZE(video_modes),
	 },
	{
	 .interface_pix_fmt = IPU_PIX_FMT_RGB565,
	 .mode_str = "CLAA-WVGA",
	 .mode = video_modes,
	 .num_modes = ARRAY_SIZE(video_modes),
	 },
};

extern int primary_di;
static int __init mxc_init_fb(void)
{
	if (!machine_is_mx51_babbage())
		return 0;

	if (primary_di) {
		printk(KERN_INFO "DI1 is primary\n");

		/* DI1 -> DP-BG channel: */
		mxc_fb_devices[1].num_resources = ARRAY_SIZE(mxcfb_resources);
		mxc_fb_devices[1].resource = mxcfb_resources;
		mxc_register_device(&mxc_fb_devices[1], &fb_data[1]);

		/* DI0 -> DC channel: */
		mxc_register_device(&mxc_fb_devices[0], &fb_data[0]);
	} else {
		printk(KERN_INFO "DI0 is primary\n");

		/* DI0 -> DP-BG channel: */
		mxc_fb_devices[0].num_resources = ARRAY_SIZE(mxcfb_resources);
		mxc_fb_devices[0].resource = mxcfb_resources;
		mxc_register_device(&mxc_fb_devices[0], &fb_data[0]);

		/* DI1 -> DC channel: */
		mxc_register_device(&mxc_fb_devices[1], &fb_data[1]);
	}

	/*
	 * DI0/1 DP-FG channel:
	 */
	mxc_register_device(&mxc_fb_devices[2], NULL);

	return 0;
}
device_initcall(mxc_init_fb);

static int handle_edid(int *pixclk)
{
#if 0
	int err = 0;
	int dvi = 0;
	int fb0 = 0;
	int fb1 = 1;
	struct fb_var_screeninfo screeninfo;
	struct i2c_adapter *adp;

	memset(&screeninfo, 0, sizeof(screeninfo));

	adp = i2c_get_adapter(1);

	if (cpu_is_mx51_rev(CHIP_REV_3_0) > 0) {
		gpio_set_value(IOMUX_TO_GPIO(MX51_PIN_CSI2_HSYNC), 1);
		msleep(1);
	}
	err = read_edid(adp, &screeninfo, &dvi);
	if (cpu_is_mx51_rev(CHIP_REV_3_0) > 0)
		gpio_set_value(IOMUX_TO_GPIO(MX51_PIN_CSI2_HSYNC), 0);

	if (!err) {
		printk(KERN_INFO " EDID read\n");
		if (!dvi) {
			enable_vga = 1;
			fb0 = 1; /* fb0 will be VGA */
			fb1 = 0; /* fb1 will be DVI or TV */
		}

		/* Handle TV modes */
		/* This logic is fairly complex yet still doesn't handle all
		   possibilities.  Once a customer knows the platform
		   configuration, this should be simplified to what is desired.
		 */
		if (screeninfo.xres == 1920 && screeninfo.yres != 1200) {
			/* MX51 can't handle clock speeds for anything larger.*/
			if (!enable_tv)
				enable_tv = 1;
			if (enable_vga || enable_wvga || enable_tv == 2)
				enable_tv = 2;
			fb_data[0].mode = &(video_modes[0]);
			if (!enable_wvga)
				fb_data[1].mode_str = "800x600M-16@60";
		} else if (screeninfo.xres > 1280 && screeninfo.yres > 1024) {
			if (!enable_wvga) {
				fb_data[fb0].mode_str = "1280x1024M-16@60";
				fb_data[fb1].mode_str = NULL;
			} else {
				/* WVGA is preset so the DVI can't be > this. */
				fb_data[0].mode_str = "1024x768M-16@60";
			}
		} else if (screeninfo.xres > 0 && screeninfo.yres > 0) {
			if (!enable_wvga) {
				fb_data[fb0].mode =
					kzalloc(sizeof(struct fb_videomode),
							GFP_KERNEL);
				fb_var_to_videomode(fb_data[fb0].mode,
						    &screeninfo);
				fb_data[fb0].mode_str = NULL;
				if (screeninfo.xres >= 1280 &&
						screeninfo.yres > 720)
					fb_data[fb1].mode_str = NULL;
				else if (screeninfo.xres > 1024 &&
						screeninfo.yres > 768)
					fb_data[fb1].mode_str =
						"800x600M-16@60";
				else if (screeninfo.xres > 800 &&
						screeninfo.yres > 600)
					fb_data[fb1].mode_str =
						"1024x768M-16@60";
			} else {
				/* A WVGA panel was specified and an EDID was
				   read thus there is a DVI monitor attached. */
				if (screeninfo.xres >= 1024)
					fb_data[0].mode_str = "1024x768M-16@60";
				else if (screeninfo.xres >= 800)
					fb_data[0].mode_str = "800x600M-16@60";
				else
					fb_data[0].mode_str = "640x480M-16@60";
			}
		}
	}
#endif
	return 0;
}

static int mxc_mcp251x_setup(struct spi_device* sdev)
{
	return 0;
}

static int mxc_mcp251x_power_enable(int enable)
{
	if(enable)
		gpio_set_value(BABBAGE_CAN_RESET_B, 1);
	else
		gpio_set_value(BABBAGE_CAN_RESET_B, 0);
	return 0;
}

static struct mxc_camera_platform_data camera_data = {
	.io_regulator = "SW4",
	.analog_regulator = "VIOHI",
	.mclk = 24000000,
	.csi = 0,
};

static struct i2c_board_info mxc_i2c0_board_info[] __initdata = {
	{
	.type = "ov3640",
	.addr = 0x3C,
	.platform_data = (void *)&camera_data,
	},
	{
	 .type = "ds2782",
	 .addr = 0x34,
	},
};

static struct mxc_lightsensor_platform_data ls_data = {
	.vdd_reg = "VIOHI",
	.rext = 100,
};

static void adv7180_pwdn(int pwdn)
{
	if(pwdn)
		gpio_direction_output(BABBAGE_VADC_POWER_DOWN_B, 0);
	else
		gpio_direction_output(BABBAGE_VADC_POWER_DOWN_B, 1);
		
}
static struct mxc_tvin_platform_data adv7180_data = {
	.dvddio_reg = NULL,
	.dvdd_reg = NULL,
	.avdd_reg = NULL,
	.pvdd_reg = NULL,
	.pwdn = adv7180_pwdn,
	.reset = NULL,
};
static struct i2c_board_info mxc_i2c1_board_info[] __initdata = {
	{
	 .type = "sgtl5000-i2c",
	 .addr = 0x0a,
	 },
	{
	 .type = "adv7180",
	 .addr = 0x20,
	 .platform_data = &adv7180_data,
	 },
};

static struct mtd_partition mxc_spi_nor_partitions[] = {
	{
	 .name = "bootloader",
	 .offset = 0,
	 .size = 0x00040000,},
	{
	 .name = "kernel",
	 .offset = MTDPART_OFS_APPEND,
	 .size = MTDPART_SIZ_FULL,},

};

static struct mtd_partition mxc_dataflash_partitions[] = {
	{
	 .name = "u-boot",
	 .offset = 0,
	 .size = 768 * 1024,},
	{
	 .name = "u-boot-env",
	 .offset = MTDPART_OFS_APPEND,
	 .size = 256 * 1024,},
	{
	 .name = "reserved",
	 .offset = MTDPART_OFS_APPEND,
	 .size = MTDPART_SIZ_FULL,},
};

static struct flash_platform_data mxc_spi_flash_data[] = {
	{
	 .name = "mxc_spi_nor",
	 .parts = mxc_spi_nor_partitions,
	 .nr_parts = ARRAY_SIZE(mxc_spi_nor_partitions),
	 .type = "sst25vf016b",},
	{
	 .name = "mxc_dataflash",
	 .parts = mxc_dataflash_partitions,
	 .nr_parts = ARRAY_SIZE(mxc_dataflash_partitions),
	 .type = "at45db321d",}
};

static struct mcp251x_platform_data mxc_mcp251x_pdata = {
	.oscillator_frequency 	= 16000000,
	.board_specific_setup	= mxc_mcp251x_setup,
	.model			= CAN_MCP251X_MCP2515,
	.power_enable		= mxc_mcp251x_power_enable,
};

static struct spi_board_info mxc_spi_nor_device[] __initdata = {
	{
	 .modalias = "mxc_spi_nor",
	 .max_speed_hz = 25000000,	/* max spi clock (SCK) speed in HZ */
	 .bus_num = 1,
	 .chip_select = 1,
	 .platform_data = &mxc_spi_flash_data[0],
	},
};

static struct spi_board_info mxc_dataflash_device[] __initdata = {
	{
	 .modalias = "mxc_dataflash",
	 .max_speed_hz = 25000000,	/* max spi clock (SCK) speed in HZ */
	 .bus_num = 1,
	 .chip_select = 1,
	 .platform_data = &mxc_spi_flash_data[1],
	},
};

static struct spi_board_info mxc_mcp2515x_device[] __initdata = {
	{
	 .modalias = "mcp251x",
	 .max_speed_hz = 10000000,	/* max spi clock (SCK) speed in HZ */
	 .mode = SPI_MODE_0,
	 .bus_num = 1,
	 .chip_select = 2,
/* FixMe: removed
	 .irq = IOMUX_TO_IRQ_V3(BABBAGE_CAN_IRQ), */
	 .platform_data = &mxc_mcp251x_pdata,
	},
};

static struct spi_board_info mxc_sagrad_device[] __initdata = {
	{
	 .modalias = "cx3110x",
	 .max_speed_hz = 13000000,	/* max spi clock (SCK) speed in HZ */
	 .mode = SPI_MODE_0,
	 .bus_num = 3,
	 .chip_select = 2,
	},
};

static int sdhc_write_protect(struct device *dev)
{
	/* DIMAS: No write protection bit on micro SD card */
	return 0;
}

static unsigned int sdhc_get_card_det_status(struct device *dev)
{
	int ret;

	/* read the det pin for SDHC1/2 */
	if (to_platform_device(dev)->id == 0)
		ret = gpio_get_value(BABBAGE_SD1_CD);
	else
	{
		/* TiWi card inserted, if WP==1 && CD==0 for UTSVU board */

		if(gpio_get_value(BABBAGE_SD2_WP))
			ret = gpio_get_value(BABBAGE_SD2_CD);
		else
			ret = 1;
	}
	return ret;
}

static struct mxc_mmc_platform_data mmc1_data = {
	.ocr_mask = MMC_VDD_27_28 | MMC_VDD_28_29 | MMC_VDD_29_30 |
	    MMC_VDD_31_32,
	.caps = MMC_CAP_4_BIT_DATA,
	.min_clk = 150000,
	.max_clk = 52000000,
	.card_inserted_state = 0,
	.status = sdhc_get_card_det_status,
	.wp_status = sdhc_write_protect,
	.clock_mmc = "esdhc_clk",
	.power_mmc = NULL,
};

static struct mxc_mmc_platform_data mmc2_data = {
	.ocr_mask = MMC_VDD_27_28 | MMC_VDD_28_29 | MMC_VDD_29_30 |
	    MMC_VDD_31_32,
	.caps = MMC_CAP_4_BIT_DATA,
	.min_clk = 150000,
	.max_clk = 26000000,
	.card_inserted_state = 0,
	.status = sdhc_get_card_det_status,
	.wp_status = sdhc_write_protect,
	.clock_mmc = "esdhc_clk",
};

static int mxc_sgtl5000_amp_enable(int enable)
{
	return 0;
}

static int mxc_sgtl5000_clock_enable(int enable)
{
	gpio_set_value(BABBAGE_AUDIO_CLK_EN_B, !enable);
	return 0;
}

static int headphone_det_status(void)
{
	return (gpio_get_value(BABBAGE_HEADPHONE_DET) == 0);
}

static struct mxc_audio_platform_data sgtl5000_data = {
	.ssi_num = 1,
	.src_port = 2,
	.ext_port = 3,
/* FixMe: removed
	.hp_irq = IOMUX_TO_IRQ_V3(BABBAGE_HEADPHONE_DET), */
	.hp_status = headphone_det_status,
	.amp_enable = mxc_sgtl5000_amp_enable,
	.clock_enable = mxc_sgtl5000_clock_enable,
	.sysclk = 12288000,
};

static struct platform_device mxc_sgtl5000_device = {
	.name = "imx-3stack-sgtl5000",
};

static int __initdata enable_w1 = { 0 };
static int __init w1_setup(char *__unused)
{
	enable_w1 = 1;
	return cpu_is_mx51();
}

__setup("w1", w1_setup);

/*!
 * Board specific fixup function. It is called by \b setup_arch() in
 * setup.c file very early on during kernel starts. It allows the user to
 * statically fill in the proper values for the passed-in parameters. None of
 * the parameters is used currently.
 *
 * @param  desc         pointer to \b struct \b machine_desc
 * @param  tags         pointer to \b struct \b tag
 * @param  cmdline      pointer to the command line
 * @param  mi           pointer to \b struct \b meminfo
 */
static void __init fixup_mxc_board(struct machine_desc *desc, struct tag *tags,
				   char **cmdline, struct meminfo *mi)
{
	char *str;
	struct tag *t;
	struct tag *mem_tag = 0;
	int total_mem = SZ_512M;
	int left_mem = 0;
	int gpu_mem = SZ_64M;
	int fb_mem = SZ_32M;

	mxc_set_cpu_type(MXC_CPU_MX51);

	get_cpu_wp = mx51_babbage_get_cpu_wp;
	set_num_cpu_wp = mx51_babbage_set_num_cpu_wp;

	for_each_tag(mem_tag, tags) {
		if (mem_tag->hdr.tag == ATAG_MEM) {
			total_mem = mem_tag->u.mem.size;
			left_mem = total_mem - gpu_mem - fb_mem;
			break;
		}
	}

	for_each_tag(t, tags) {
		if (t->hdr.tag == ATAG_CMDLINE) {
			str = t->u.cmdline.cmdline;
			str = strstr(str, "mem=");
			if (str != NULL) {
				str += 4;
				left_mem = memparse(str, &str);
				if (left_mem == 0 || left_mem > total_mem)
					left_mem = total_mem - gpu_mem - fb_mem;
			}

			str = t->u.cmdline.cmdline;
			str = strstr(str, "gpu_memory=");
			if (str != NULL) {
				str += 11;
				gpu_mem = memparse(str, &str);
			}

			break;
		}
	}

	if (mem_tag) {
		fb_mem = total_mem - left_mem - gpu_mem;
		if (fb_mem < 0) {
			gpu_mem = total_mem - left_mem;
			fb_mem = 0;
		}
		mem_tag->u.mem.size = left_mem;

		/*reserve memory for gpu*/
		gpu_device.resource[5].start =
				mem_tag->u.mem.start + left_mem;
		gpu_device.resource[5].end =
				gpu_device.resource[5].start + gpu_mem - 1;
#if defined(CONFIG_FB_MXC_SYNC_PANEL) || \
	defined(CONFIG_FB_MXC_SYNC_PANEL_MODULE)
		if (fb_mem) {
			mxcfb_resources[0].start =
				gpu_device.resource[5].end + 1;
			mxcfb_resources[0].end =
				mxcfb_resources[0].start + fb_mem - 1;
		} else {
			mxcfb_resources[0].start = 0;
			mxcfb_resources[0].end = 0;
		}
#endif
	}
}

/*
 *   We need SPI1 interface pins placed in reset state for
 * correctly boot form SPI interface after watchdog reset.
 */
static  iomux_v3_cfg_t mx51_spi1_boot[] = {
	IOMUX_PAD(0x600, 0x210, 0x03, 0, 0, 0xA5), // MOSI
	IOMUX_PAD(0x604, 0x214, 0x03, 0, 0, 0x85), // MISO
	IOMUX_PAD(0x608, 0x218, 0x03, 0, 0, 0x85), // SS0
	IOMUX_PAD(0x60c, 0x21c, 0x03, 0, 0, 0x85), // SS1
	IOMUX_PAD(0x610, 0x220, 0x03, 0, 0, 0x80), // RDY
	IOMUX_PAD(0x614, 0x224, 0x03, 0, 0, 0xA5), // SCLK

};

#define ARRAY_AND_SIZE(x)       (x), ARRAY_SIZE(x)

static void mxc_restart(char mode, const char* cmd)
{
	mxc_iomux_v3_setup_multiple_pads(
	    ARRAY_AND_SIZE(mx51_spi1_boot));
	arm_machine_restart(mode, cmd);
}

#define PWGT1SPIEN (1<<15)
#define PWGT2SPIEN (1<<16)
#define USEROFFSPI (1<<3)

static void mxc_power_off(void)
{
	/* We can do power down one of two ways:
	   Set the power gating
	   Set USEROFFSPI */

	/* Set the power gate bits to power down */
	pmic_write_reg(REG_POWER_MISC, (PWGT1SPIEN|PWGT2SPIEN),
		(PWGT1SPIEN|PWGT2SPIEN));
}

static struct gpio_keys_button babbage_buttons[] = {
	{
	 .gpio = BABBAGE_POWER_KEY,
	 .code = KEY_POWER,
	 .desc = "PWR",
	 .active_low = 1,
	 .debounce_interval = 100,
	 .wakeup = 1,
	},
};

static struct gpio_keys_platform_data babbage_button_data = {
	.buttons = babbage_buttons,
	.nbuttons = 1,
};

static struct platform_device babbage_button_device = {
	.name = "gpio-keys",
	.id = -1,
	.num_resources = 0,
	.dev = {
		.platform_data = &babbage_button_data,
	},
};

static inline void babbage_init_keyboard_gpio( void ) {
	mxc_register_device(&babbage_button_device, &babbage_button_data);
};

static void __init mx51_babbage_io_init(void)
{
	mxc_iomux_v3_setup_multiple_pads(mx51babbage_pads,
					ARRAY_SIZE(mx51babbage_pads));

	gpio_request(BABBAGE_PMIC_INT, "pmic-int");
	gpio_request(BABBAGE_SD1_CD, "sd1-cd");

	gpio_direction_input(BABBAGE_PMIC_INT);
	gpio_direction_input(BABBAGE_SD1_CD);

	/* SD2 CD for BB2.5 */
	gpio_request(BABBAGE_SD2_CD, "sd2-cd");
	gpio_direction_input(BABBAGE_SD2_CD);

	gpio_request(BABBAGE_SD2_WP, "sd2-wp");
	gpio_direction_input(BABBAGE_SD2_WP);

	/* reset usbh1 hub */
	gpio_request(BABBAGE_USBH1_HUB_RST_B, "usb-hub-rst_n");
	gpio_direction_output(BABBAGE_USBH1_HUB_RST_B, 0);
	gpio_set_value(BABBAGE_USBH1_HUB_RST_B, 0);
	msleep(1);
	gpio_set_value(BABBAGE_USBH1_HUB_RST_B, 1);

	/* reset FEC PHY */
	gpio_request(BABBAGE_FEC_PHY_RESET_B, "fec-phy-reset_n");
	gpio_direction_output(BABBAGE_FEC_PHY_RESET_B, 0);
	msleep(1);
	gpio_set_value(BABBAGE_FEC_PHY_RESET_B, 1);

	/* Drive 26M_OSC_EN line high */
	gpio_request(BABBAGE_26M_OSC_EN, "26m-osc-en");
	gpio_direction_output(BABBAGE_26M_OSC_EN, 1);

	/* reset USB PHY */
	gpio_request(BABBAGE_USB_PHY_RESET_B, "usb-phy-reset_n");
	gpio_direction_output(BABBAGE_USB_PHY_RESET_B, 0);
	msleep(1);
	gpio_direction_output(BABBAGE_USB_PHY_RESET_B, 1);

	/* hphone_det_b */
	gpio_request(BABBAGE_HEADPHONE_DET, "hphone-det");
	gpio_direction_input(BABBAGE_HEADPHONE_DET);

	/* audio_clk_en_b */
	gpio_request(BABBAGE_AUDIO_CLK_EN_B, "audio-clk-en_n");
	gpio_direction_output(BABBAGE_AUDIO_CLK_EN_B, 0);

	/* usb_clk_en_b */
	gpio_request(BABBAGE_USB_CLK_EN_B, "usb-clk-en_n");
	gpio_direction_output(BABBAGE_USB_CLK_EN_B, 0);

	babbage_init_keyboard_gpio();

	/* VGA power down */
	gpio_request(BABBAGE_VDAC_POWER_DOWN_B, "vdac-power-down_n");
	gpio_direction_output(BABBAGE_VDAC_POWER_DOWN_B, 1);

	/* LVDS power down */
	gpio_request(BABBAGE_LVDS_POWER_DOWN_B, "lvds-power-down_n");
	gpio_direction_output(BABBAGE_LVDS_POWER_DOWN_B, 1);

	/* Video ADC reset and power down */
	gpio_request(BABBAGE_VADC_POWER_DOWN_B, "vadc-power-down_n");
	gpio_request(BABBAGE_VADC_RESET_B, "vadc-reset_n");
	gpio_direction_output(BABBAGE_VADC_RESET_B, 0);
	gpio_set_value(BABBAGE_VADC_RESET_B, 0);
	msleep(1);
	gpio_set_value(BABBAGE_VADC_RESET_B, 1);
	gpio_direction_output(BABBAGE_VADC_POWER_DOWN_B, 0);

	/* EIM IRQ */
	gpio_request(BABBAGE_EIM_IRQ, "eim-irq");
	gpio_direction_input(BABBAGE_EIM_IRQ);

	/* EIM Reset */
	gpio_request(BABBAGE_EIM_RESET, "eim-reset");
	gpio_direction_output(BABBAGE_EIM_RESET, 1);
	gpio_set_value(BABBAGE_EIM_RESET, 1);
	msleep(1);
	gpio_set_value(BABBAGE_EIM_RESET, 0);

	/* Bluetooth enable */
	gpio_request(BABBAGE_BT_ENABLE, "bt-en");
	gpio_direction_output(BABBAGE_BT_ENABLE, 1);

	/* GPI_0 */
	gpio_request(BABBAGE_GPI_0, "gpi-0");
	gpio_direction_input(BABBAGE_GPI_0);

	/* GPI_1 */
	gpio_request(BABBAGE_GPI_1, "gpi-1");
	gpio_direction_input(BABBAGE_GPI_1);

	/* GPI_2 */
	gpio_request(BABBAGE_GPI_2, "gpi-2");
	gpio_direction_input(BABBAGE_GPI_2);

	/* GPI_3 */
	gpio_request(BABBAGE_GPI_3, "gpi-3");
	gpio_direction_input(BABBAGE_GPI_3);

	/* GPO_0 */
	gpio_request(BABBAGE_GPO_0, "gpo-0");
	gpio_direction_output(BABBAGE_GPO_0, 0);

	/* GPO_1 */
	gpio_request(BABBAGE_GPO_1, "gpo-1");
	gpio_direction_output(BABBAGE_GPO_1, 0);

	/* GPO_2 */
	gpio_request(BABBAGE_GPO_2, "gpo-2");
	gpio_direction_output(BABBAGE_GPO_2, 0);

	/* GPO_3 */
	gpio_request(BABBAGE_GPO_3, "gpo-3");
	gpio_direction_output(BABBAGE_GPO_3, 0);

	if (enable_w1) {
		/* OneWire */
		mxc_iomux_v3_setup_pad(MX51_PAD_OWIRE_LINE__OWIRE_LINE);
	}
}

/*   Board UTSVU specific initialization 
 *   Added by Dmitry Tarasov, Prosoft-Spb 2012 
 */

static void __init mx51_utsvu_mcp251x_init(void)
{
	if( (gpio_request(BABBAGE_CAN_IRQ, "MCP 251x CAN INT") == 0) && (gpio_direction_input(BABBAGE_CAN_IRQ) == 0) )
	{
		gpio_export(BABBAGE_CAN_IRQ, 0);
/* FixMe: removed
		set_irq_type(IOMUX_TO_IRQ_V3(BABBAGE_CAN_IRQ), IRQ_TYPE_EDGE_FALLING); */
	}
	else
	{
		pr_info("could not obtain GPIO for MCP251x CAN bus interrupt.\n");
	}
}

static void __init mx51_utsvu_wireless_for_tiwi_init(void)
{
	/* Wireless enable */
	gpio_request(BABBAGE_WL_ENABLE, "wl-en");
	gpio_direction_output(BABBAGE_WL_ENABLE, 1);

	if( (gpio_request(BABBAGE_WIRELESS_IRQ, "WIRELESS INT") == 0) && (gpio_direction_input(BABBAGE_WIRELESS_IRQ) == 0) )
	{
		gpio_export(BABBAGE_WIRELESS_IRQ, 0);
/* FixMe: removed
		set_irq_type(IOMUX_TO_IRQ_V3(BABBAGE_WIRELESS_IRQ), IRQ_TYPE_EDGE_RISING); */
	}
	else
	{
		pr_info("could not obtain GPIO for wireless interrupt.\n");
	} 
}

static iomux_v3_cfg_t mx51_utsvu_pads[] = {

	MX51_PAD_GPIO1_2__I2C2_SCL,
	MX51_PAD_GPIO1_3__I2C2_SDA,

	MX51_PAD_KEY_COL4__UART1_RI,
	MX51_PAD_KEY_COL5__UART1_DCD,

	MX51_PAD_CSI2_PIXCLK__GPIO4_15, /* 3.3 V ON */
};

typedef enum sd2card_type {
	CARD_NONE = 0,
	CARD_SAGRAD,
	CARD_TIWI
} sd2card_type_t;

static void __init mx51_utsvu_io_init(void)
{
	mxc_iomux_v3_setup_multiple_pads(mx51_utsvu_pads,
					ARRAY_SIZE(mx51_utsvu_pads));

	/* GPIO 1_4 as POWER OFF pin */
	gpio_request(BABBAGE_WDOG_B, "power-off");
	gpio_direction_output(BABBAGE_WDOG_B, 1);

	/* GPIO 4_15 (power on 3.3 V) */
	gpio_request(BABBAGE_3V3_ON, "3v3-on");
	gpio_direction_output(BABBAGE_3V3_ON, 1);

	/* Switch 12 V */
	gpio_request(BABBAGE_SW12V_EN, "sw12v-en");
	gpio_direction_output(BABBAGE_SW12V_EN, 0);

	/* CAN Reset */
	gpio_request(BABBAGE_CAN_RESET_B, "can-rst_n");
	gpio_direction_output(BABBAGE_CAN_RESET_B, 0);
	gpio_set_value(BABBAGE_CAN_RESET_B, 0);
	msleep(5);
	gpio_set_value(BABBAGE_CAN_RESET_B, 1);
}

/*!
 * Board specific initialization.
 */
extern unsigned int system_rev;
static void __init mxc_board_init(void)
{
	sd2card_type_t sd2_device_type;

	mxc_ipu_data.di_clk[0] = clk_get(NULL, "ipu_di0_clk");
	mxc_ipu_data.di_clk[1] = clk_get(NULL, "ipu_di1_clk");
	mxc_ipu_data.csi_clk[0] = clk_get(NULL, "csi_mclk1");
	mxc_ipu_data.csi_clk[1] = clk_get(NULL, "csi_mclk2");

	mxc_spdif_data.spdif_core_clk = clk_get(NULL, "spdif_xtal_clk");
	clk_put(mxc_spdif_data.spdif_core_clk);
	/* SD card detect irqs */
/* FixMe: removed
	mxcsdhc2_device.resource[2].start = IOMUX_TO_IRQ_V3(BABBAGE_SD2_CD);
	mxcsdhc2_device.resource[2].end = IOMUX_TO_IRQ_V3(BABBAGE_SD2_CD);
	mxcsdhc1_device.resource[2].start = IOMUX_TO_IRQ_V3(BABBAGE_SD1_CD);
	mxcsdhc1_device.resource[2].end = IOMUX_TO_IRQ_V3(BABBAGE_SD1_CD); */

	mxc_cpu_common_init();
	mx51_babbage_io_init();

	// NJM: Special I/O init for Avionika UTSVU board
	mx51_utsvu_io_init();

	/* DIMAS: detect SD2 card inserted */
	sd2_device_type = CARD_NONE;
	if((gpio_get_value(BABBAGE_SD2_CD) == 0) && (gpio_get_value(BABBAGE_SD2_WP) == 0))
		sd2_device_type = CARD_SAGRAD;
	else
	if((gpio_get_value(BABBAGE_SD2_CD) == 0) && gpio_get_value(BABBAGE_SD2_WP))
		sd2_device_type = CARD_TIWI;

	switch(sd2_device_type)
	{
		case CARD_SAGRAD:
			mxc_iomux_v3_setup_multiple_pads(mx51_sd2_as_spi_pads, ARRAY_SIZE(mx51_sd2_as_spi_pads));
			break;
		case CARD_TIWI:
			mxc_iomux_v3_setup_multiple_pads(mx51_sd2_as_sd2_pads, ARRAY_SIZE(mx51_sd2_as_sd2_pads));
			break;
		default:
			break;
	};
	mxc_register_device(&mxc_dma_device, NULL);
	mxc_register_device(&mxc_wdt_device, NULL);
	mxc_register_device(&mxcspi1_device, &mxcspi1_data);
	mxc_register_device(&mxcspi3_device, &mxcspi3_data);
	mxc_register_device(&mxci2c_devices[0], &mxci2c_data);
	mxc_register_device(&mxci2c_devices[1], &mxci2c_data);
	mxc_register_device(&mxci2c_hs_device, &mxci2c_hs_data);
	mxc_register_device(&mxc_rtc_device, NULL); // See FixMe: above &srtc_data);
	mxc_register_device(&mxc_w1_master_device, &mxc_w1_data);
	mxc_register_device(&mxc_ipu_device, &mxc_ipu_data);
	mxc_register_device(&mxc_tve_device, &tve_data);
	mxc_register_device(&mxcvpu_device, &mxc_vpu_data);
	mxc_register_device(&gpu_device, NULL);
	mxc_register_device(&mxcscc_device, NULL);
	mxc_register_device(&mx51_lpmode_device, NULL);
	mxc_register_device(&busfreq_device, NULL);
	mxc_register_device(&sdram_autogating_device, NULL);
	mxc_register_device(&mxc_dvfs_core_device, &dvfs_core_data);
	mxc_register_device(&mxc_dvfs_per_device, &dvfs_per_data);
	mxc_register_device(&mxc_iim_device, NULL);
	mxc_register_device(&mxc_pwm1_device, NULL);
	mxc_register_device(&mxc_pwm1_backlight_device,
		&mxc_pwm_backlight_data);
	mxc_register_device(&mxc_keypad_device, &keypad_plat_data);
	mxc_register_device(&mxcsdhc1_device, &mmc1_data);
	mxc_register_device(&mxc_ssi1_device, NULL);
	mxc_register_device(&mxc_ssi2_device, NULL);
	mxc_register_device(&mxc_ssi3_device, NULL);
	mxc_register_device(&mxc_alsa_spdif_device, &mxc_spdif_data);
	mxc_register_device(&mxc_fec_device, NULL);
	mxc_register_device(&mxc_v4l2_device, NULL);
	mxc_register_device(&mxc_v4l2out_device, NULL);

#if defined(CONFIG_MTD_NAND_IMX_NFC) || defined(CONFIG_MTD_NAND_IMX_NFC_MODULE)
	mxc_register_device(&imx_nfc_device, &imx_nfc_platform_data);
#else
	mxc_register_device(&mxc_nandv2_mtd_device, &mxc_nand_data);
#endif

	mx51_babbage_init_mc13892();

	//if (board_is_rev(BOARD_REV_2))
		/* BB2.5 */
		spi_register_board_info(mxc_dataflash_device,
					ARRAY_SIZE(mxc_dataflash_device));
	//else
		/* BB2.0 */
	//	spi_register_board_info(mxc_spi_nor_device,
	//				ARRAY_SIZE(mxc_spi_nor_device));

	pr_info("DIMAS: board revision: %X\n", system_rev);

	/* DIMAS: CAN init */
	mx51_utsvu_mcp251x_init();

	/* DIMAS: SAGRAD and TiWi init */
	switch(sd2_device_type)
	{
		case CARD_SAGRAD:
			pr_info("DIMAS: Sagrad card inserted.\n");
			spi_register_board_info(mxc_sagrad_device, ARRAY_SIZE(mxc_sagrad_device));
			break;
		case CARD_TIWI:
			pr_info("DIMAS: TiWi card inserted.\n");
			mx51_utsvu_wireless_for_tiwi_init();
			mxc_register_device(&mxcsdhc2_device, &mmc2_data);
			break;
		default:
			pr_info("DIMAS: No card inserted.\n");
			break;
	};

	spi_register_board_info(mxc_mcp2515x_device, ARRAY_SIZE(mxc_mcp2515x_device));

	i2c_register_board_info(0, mxc_i2c0_board_info,
				ARRAY_SIZE(mxc_i2c0_board_info));
	i2c_register_board_info(1, mxc_i2c1_board_info,
				ARRAY_SIZE(mxc_i2c1_board_info));

	pm_power_off	= mxc_power_off;
	arm_pm_restart	= mxc_restart;

	sgtl5000_data.sysclk = 26000000;

	mxc_register_device(&mxc_sgtl5000_device, &sgtl5000_data);

	mx5_usb_dr_init();
	mx5_usbh1_init();
}

static void __init mx51_babbage_timer_init(void)
{
	struct clk *uart_clk;

	/* Change the CPU voltages for TO2*/
	if (mx51_revision() == IMX_CHIP_REVISION_2_0) {
		cpu_wp_auto[0].cpu_voltage = 1175000;
		cpu_wp_auto[1].cpu_voltage = 1100000;
		cpu_wp_auto[2].cpu_voltage = 1000000;
	}

	mx51_clocks_init(32768, 24000000, 22579200, 24576000);

	uart_clk = clk_get_sys("mxcintuart.0", NULL);
	early_console_setup(UART1_BASE_ADDR, uart_clk);
}

static struct sys_timer mxc_timer = {
	.init	= mx51_babbage_timer_init,
};

/*
 * The following uses standard kernel macros define in arch.h in order to
 * initialize __mach_desc_MX51_BABBAGE data structure.
 */
/* *INDENT-OFF* */
MACHINE_START(MX51_BABBAGE, "Dolomant/Freescale MX51 RAVION UTSVU (UCCU) Board")
	/* Maintainer: Freescale Semiconductor, Inc. */
	.phys_io	= AIPS1_BASE_ADDR,
	.io_pg_offst	= ((AIPS1_BASE_ADDR_VIRT) >> 18) & 0xfffc,
	.fixup = fixup_mxc_board,
	.map_io = mx5_map_io,
	.init_irq = mx5_init_irq,
	.init_machine = mxc_board_init,
	.timer = &mxc_timer,
MACHINE_END
