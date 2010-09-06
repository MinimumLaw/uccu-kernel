/*
 * Freescale POWER Register Definitions
 *
 * Copyright 2008-2010 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright 2008 Embedded Alley Solutions, Inc All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 * This file is created by xml file. Don't Edit it.
 *
 * Xml Revision: 1.0
 * Template revision: 26195
 */

#ifndef __ARCH_ARM___POWER_H
#define __ARCH_ARM___POWER_H

#include <mach/mx23.h>

#define REGS_POWER_BASE IO_ADDRESS(POWER_PHYS_ADDR)
#define REGS_POWER_PHYS (0x80044000)
#define REGS_POWER_SIZE 0x00002000

#define HW_POWER_CTRL	(0x00000000)
#define HW_POWER_CTRL_SET	(0x00000004)
#define HW_POWER_CTRL_CLR	(0x00000008)
#define HW_POWER_CTRL_TOG	(0x0000000c)

#define BM_POWER_CTRL_RSRVD3	0x80000000
#define BM_POWER_CTRL_CLKGATE	0x40000000
#define BP_POWER_CTRL_RSRVD2	28
#define BM_POWER_CTRL_RSRVD2	0x30000000
#define BF_POWER_CTRL_RSRVD2(v)  \
		(((v) << 28) & BM_POWER_CTRL_RSRVD2)
#define BM_POWER_CTRL_PSWITCH_MID_TRAN	0x08000000
#define BP_POWER_CTRL_RSRVD1	25
#define BM_POWER_CTRL_RSRVD1	0x06000000
#define BF_POWER_CTRL_RSRVD1(v)  \
		(((v) << 25) & BM_POWER_CTRL_RSRVD1)
#define BM_POWER_CTRL_DCDC4P2_BO_IRQ	0x01000000
#define BM_POWER_CTRL_ENIRQ_DCDC4P2_BO	0x00800000
#define BM_POWER_CTRL_VDD5V_DROOP_IRQ	0x00400000
#define BM_POWER_CTRL_ENIRQ_VDD5V_DROOP	0x00200000
#define BM_POWER_CTRL_PSWITCH_IRQ	0x00100000
#define BM_POWER_CTRL_PSWITCH_IRQ_SRC	0x00080000
#define BM_POWER_CTRL_POLARITY_PSWITCH	0x00040000
#define BM_POWER_CTRL_ENIRQ_PSWITCH	0x00020000
#define BM_POWER_CTRL_POLARITY_DC_OK	0x00010000
#define BM_POWER_CTRL_DC_OK_IRQ	0x00008000
#define BM_POWER_CTRL_ENIRQ_DC_OK	0x00004000
#define BM_POWER_CTRL_BATT_BO_IRQ	0x00002000
#define BM_POWER_CTRL_ENIRQBATT_BO	0x00001000
#define BM_POWER_CTRL_VDDIO_BO_IRQ	0x00000800
#define BM_POWER_CTRL_ENIRQ_VDDIO_BO	0x00000400
#define BM_POWER_CTRL_VDDA_BO_IRQ	0x00000200
#define BM_POWER_CTRL_ENIRQ_VDDA_BO	0x00000100
#define BM_POWER_CTRL_VDDD_BO_IRQ	0x00000080
#define BM_POWER_CTRL_ENIRQ_VDDD_BO	0x00000040
#define BM_POWER_CTRL_POLARITY_VBUSVALID	0x00000020
#define BM_POWER_CTRL_VBUSVALID_IRQ	0x00000010
#define BM_POWER_CTRL_ENIRQ_VBUS_VALID	0x00000008
#define BM_POWER_CTRL_POLARITY_VDD5V_GT_VDDIO	0x00000004
#define BM_POWER_CTRL_VDD5V_GT_VDDIO_IRQ	0x00000002
#define BM_POWER_CTRL_ENIRQ_VDD5V_GT_VDDIO	0x00000001

#define HW_POWER_5VCTRL	(0x00000010)
#define HW_POWER_5VCTRL_SET	(0x00000014)
#define HW_POWER_5VCTRL_CLR	(0x00000018)
#define HW_POWER_5VCTRL_TOG	(0x0000001c)

#define BP_POWER_5VCTRL_RSRVD6	30
#define BM_POWER_5VCTRL_RSRVD6	0xC0000000
#define BF_POWER_5VCTRL_RSRVD6(v) \
		(((v) << 30) & BM_POWER_5VCTRL_RSRVD6)
#define BP_POWER_5VCTRL_VBUSDROOP_TRSH	28
#define BM_POWER_5VCTRL_VBUSDROOP_TRSH	0x30000000
#define BF_POWER_5VCTRL_VBUSDROOP_TRSH(v)  \
		(((v) << 28) & BM_POWER_5VCTRL_VBUSDROOP_TRSH)
#define BM_POWER_5VCTRL_RSRVD5	0x08000000
#define BP_POWER_5VCTRL_HEADROOM_ADJ	24
#define BM_POWER_5VCTRL_HEADROOM_ADJ	0x07000000
#define BF_POWER_5VCTRL_HEADROOM_ADJ(v)  \
		(((v) << 24) & BM_POWER_5VCTRL_HEADROOM_ADJ)
#define BP_POWER_5VCTRL_RSRVD4	21
#define BM_POWER_5VCTRL_RSRVD4	0x00E00000
#define BF_POWER_5VCTRL_RSRVD4(v)  \
		(((v) << 21) & BM_POWER_5VCTRL_RSRVD4)
#define BM_POWER_5VCTRL_PWD_CHARGE_4P2	0x00100000
#define BP_POWER_5VCTRL_RSRVD3	18
#define BM_POWER_5VCTRL_RSRVD3	0x000C0000
#define BF_POWER_5VCTRL_RSRVD3(v)  \
		(((v) << 18) & BM_POWER_5VCTRL_RSRVD3)
#define BP_POWER_5VCTRL_CHARGE_4P2_ILIMIT	12
#define BM_POWER_5VCTRL_CHARGE_4P2_ILIMIT	0x0003F000
#define BF_POWER_5VCTRL_CHARGE_4P2_ILIMIT(v)  \
		(((v) << 12) & BM_POWER_5VCTRL_CHARGE_4P2_ILIMIT)
#define BM_POWER_5VCTRL_RSRVD2	0x00000800
#define BP_POWER_5VCTRL_VBUSVALID_TRSH	8
#define BM_POWER_5VCTRL_VBUSVALID_TRSH	0x00000700
#define BF_POWER_5VCTRL_VBUSVALID_TRSH(v)  \
		(((v) << 8) & BM_POWER_5VCTRL_VBUSVALID_TRSH)
#define BM_POWER_5VCTRL_PWDN_5VBRNOUT	0x00000080
#define BM_POWER_5VCTRL_ENABLE_LINREG_ILIMIT	0x00000040
#define BM_POWER_5VCTRL_DCDC_XFER	0x00000020
#define BM_POWER_5VCTRL_VBUSVALID_5VDETECT	0x00000010
#define BM_POWER_5VCTRL_VBUSVALID_TO_B	0x00000008
#define BM_POWER_5VCTRL_ILIMIT_EQ_ZERO	0x00000004
#define BM_POWER_5VCTRL_PWRUP_VBUS_CMPS	0x00000002
#define BM_POWER_5VCTRL_ENABLE_DCDC	0x00000001

#define HW_POWER_MINPWR	(0x00000020)
#define HW_POWER_MINPWR_SET	(0x00000024)
#define HW_POWER_MINPWR_CLR	(0x00000028)
#define HW_POWER_MINPWR_TOG	(0x0000002c)

#define BP_POWER_MINPWR_RSRVD1	15
#define BM_POWER_MINPWR_RSRVD1	0xFFFF8000
#define BF_POWER_MINPWR_RSRVD1(v) \
		(((v) << 15) & BM_POWER_MINPWR_RSRVD1)
#define BM_POWER_MINPWR_LOWPWR_4P2	0x00004000
#define BM_POWER_MINPWR_VDAC_DUMP_CTRL	0x00002000
#define BM_POWER_MINPWR_PWD_BO	0x00001000
#define BM_POWER_MINPWR_USE_VDDXTAL_VBG	0x00000800
#define BM_POWER_MINPWR_PWD_ANA_CMPS	0x00000400
#define BM_POWER_MINPWR_ENABLE_OSC	0x00000200
#define BM_POWER_MINPWR_SELECT_OSC	0x00000100
#define BM_POWER_MINPWR_VBG_OFF	0x00000080
#define BM_POWER_MINPWR_DOUBLE_FETS	0x00000040
#define BM_POWER_MINPWR_HALF_FETS	0x00000020
#define BM_POWER_MINPWR_LESSANA_I	0x00000010
#define BM_POWER_MINPWR_PWD_XTAL24	0x00000008
#define BM_POWER_MINPWR_DC_STOPCLK	0x00000004
#define BM_POWER_MINPWR_EN_DC_PFM	0x00000002
#define BM_POWER_MINPWR_DC_HALFCLK	0x00000001

#define HW_POWER_CHARGE	(0x00000030)
#define HW_POWER_CHARGE_SET	(0x00000034)
#define HW_POWER_CHARGE_CLR	(0x00000038)
#define HW_POWER_CHARGE_TOG	(0x0000003c)

#define BP_POWER_CHARGE_RSRVD4	27
#define BM_POWER_CHARGE_RSRVD4	0xF8000000
#define BF_POWER_CHARGE_RSRVD4(v) \
		(((v) << 27) & BM_POWER_CHARGE_RSRVD4)
#define BP_POWER_CHARGE_ADJ_VOLT	24
#define BM_POWER_CHARGE_ADJ_VOLT	0x07000000
#define BF_POWER_CHARGE_ADJ_VOLT(v)  \
		(((v) << 24) & BM_POWER_CHARGE_ADJ_VOLT)
#define BM_POWER_CHARGE_RSRVD3	0x00800000
#define BM_POWER_CHARGE_ENABLE_LOAD	0x00400000
#define BM_POWER_CHARGE_ENABLE_CHARGER_RESISTORS	0x00200000
#define BM_POWER_CHARGE_ENABLE_FAULT_DETECT	0x00100000
#define BM_POWER_CHARGE_CHRG_STS_OFF	0x00080000
#define BM_POWER_CHARGE_LIION_4P1	0x00040000
#define BM_POWER_CHARGE_USE_EXTERN_R	0x00020000
#define BM_POWER_CHARGE_PWD_BATTCHRG	0x00010000
#define BP_POWER_CHARGE_RSRVD2	12
#define BM_POWER_CHARGE_RSRVD2	0x0000F000
#define BF_POWER_CHARGE_RSRVD2(v)  \
		(((v) << 12) & BM_POWER_CHARGE_RSRVD2)
#define BP_POWER_CHARGE_STOP_ILIMIT	8
#define BM_POWER_CHARGE_STOP_ILIMIT	0x00000F00
#define BF_POWER_CHARGE_STOP_ILIMIT(v)  \
		(((v) << 8) & BM_POWER_CHARGE_STOP_ILIMIT)
#define BP_POWER_CHARGE_RSRVD1	6
#define BM_POWER_CHARGE_RSRVD1	0x000000C0
#define BF_POWER_CHARGE_RSRVD1(v)  \
		(((v) << 6) & BM_POWER_CHARGE_RSRVD1)
#define BP_POWER_CHARGE_BATTCHRG_I	0
#define BM_POWER_CHARGE_BATTCHRG_I	0x0000003F
#define BF_POWER_CHARGE_BATTCHRG_I(v)  \
		(((v) << 0) & BM_POWER_CHARGE_BATTCHRG_I)

#define HW_POWER_VDDDCTRL	(0x00000040)

#define BP_POWER_VDDDCTRL_ADJTN	28
#define BM_POWER_VDDDCTRL_ADJTN	0xF0000000
#define BF_POWER_VDDDCTRL_ADJTN(v) \
		(((v) << 28) & BM_POWER_VDDDCTRL_ADJTN)
#define BP_POWER_VDDDCTRL_RSRVD4	24
#define BM_POWER_VDDDCTRL_RSRVD4	0x0F000000
#define BF_POWER_VDDDCTRL_RSRVD4(v)  \
		(((v) << 24) & BM_POWER_VDDDCTRL_RSRVD4)
#define BM_POWER_VDDDCTRL_PWDN_BRNOUT	0x00800000
#define BM_POWER_VDDDCTRL_DISABLE_STEPPING	0x00400000
#define BM_POWER_VDDDCTRL_ENABLE_LINREG	0x00200000
#define BM_POWER_VDDDCTRL_DISABLE_FET	0x00100000
#define BP_POWER_VDDDCTRL_RSRVD3	18
#define BM_POWER_VDDDCTRL_RSRVD3	0x000C0000
#define BF_POWER_VDDDCTRL_RSRVD3(v)  \
		(((v) << 18) & BM_POWER_VDDDCTRL_RSRVD3)
#define BP_POWER_VDDDCTRL_LINREG_OFFSET	16
#define BM_POWER_VDDDCTRL_LINREG_OFFSET	0x00030000
#define BF_POWER_VDDDCTRL_LINREG_OFFSET(v)  \
		(((v) << 16) & BM_POWER_VDDDCTRL_LINREG_OFFSET)
#define BP_POWER_VDDDCTRL_RSRVD2	11
#define BM_POWER_VDDDCTRL_RSRVD2	0x0000F800
#define BF_POWER_VDDDCTRL_RSRVD2(v)  \
		(((v) << 11) & BM_POWER_VDDDCTRL_RSRVD2)
#define BP_POWER_VDDDCTRL_BO_OFFSET	8
#define BM_POWER_VDDDCTRL_BO_OFFSET	0x00000700
#define BF_POWER_VDDDCTRL_BO_OFFSET(v)  \
		(((v) << 8) & BM_POWER_VDDDCTRL_BO_OFFSET)
#define BP_POWER_VDDDCTRL_RSRVD1	5
#define BM_POWER_VDDDCTRL_RSRVD1	0x000000E0
#define BF_POWER_VDDDCTRL_RSRVD1(v)  \
		(((v) << 5) & BM_POWER_VDDDCTRL_RSRVD1)
#define BP_POWER_VDDDCTRL_TRG	0
#define BM_POWER_VDDDCTRL_TRG	0x0000001F
#define BF_POWER_VDDDCTRL_TRG(v)  \
		(((v) << 0) & BM_POWER_VDDDCTRL_TRG)

#define HW_POWER_VDDACTRL	(0x00000050)

#define BP_POWER_VDDACTRL_RSRVD4	20
#define BM_POWER_VDDACTRL_RSRVD4	0xFFF00000
#define BF_POWER_VDDACTRL_RSRVD4(v) \
		(((v) << 20) & BM_POWER_VDDACTRL_RSRVD4)
#define BM_POWER_VDDACTRL_PWDN_BRNOUT	0x00080000
#define BM_POWER_VDDACTRL_DISABLE_STEPPING	0x00040000
#define BM_POWER_VDDACTRL_ENABLE_LINREG	0x00020000
#define BM_POWER_VDDACTRL_DISABLE_FET	0x00010000
#define BP_POWER_VDDACTRL_RSRVD3	14
#define BM_POWER_VDDACTRL_RSRVD3	0x0000C000
#define BF_POWER_VDDACTRL_RSRVD3(v)  \
		(((v) << 14) & BM_POWER_VDDACTRL_RSRVD3)
#define BP_POWER_VDDACTRL_LINREG_OFFSET	12
#define BM_POWER_VDDACTRL_LINREG_OFFSET	0x00003000
#define BF_POWER_VDDACTRL_LINREG_OFFSET(v)  \
		(((v) << 12) & BM_POWER_VDDACTRL_LINREG_OFFSET)
#define BM_POWER_VDDACTRL_RSRVD2	0x00000800
#define BP_POWER_VDDACTRL_BO_OFFSET	8
#define BM_POWER_VDDACTRL_BO_OFFSET	0x00000700
#define BF_POWER_VDDACTRL_BO_OFFSET(v)  \
		(((v) << 8) & BM_POWER_VDDACTRL_BO_OFFSET)
#define BP_POWER_VDDACTRL_RSRVD1	5
#define BM_POWER_VDDACTRL_RSRVD1	0x000000E0
#define BF_POWER_VDDACTRL_RSRVD1(v)  \
		(((v) << 5) & BM_POWER_VDDACTRL_RSRVD1)
#define BP_POWER_VDDACTRL_TRG	0
#define BM_POWER_VDDACTRL_TRG	0x0000001F
#define BF_POWER_VDDACTRL_TRG(v)  \
		(((v) << 0) & BM_POWER_VDDACTRL_TRG)

#define HW_POWER_VDDIOCTRL	(0x00000060)

#define BP_POWER_VDDIOCTRL_RSRVD5	24
#define BM_POWER_VDDIOCTRL_RSRVD5	0xFF000000
#define BF_POWER_VDDIOCTRL_RSRVD5(v) \
		(((v) << 24) & BM_POWER_VDDIOCTRL_RSRVD5)
#define BP_POWER_VDDIOCTRL_ADJTN	20
#define BM_POWER_VDDIOCTRL_ADJTN	0x00F00000
#define BF_POWER_VDDIOCTRL_ADJTN(v)  \
		(((v) << 20) & BM_POWER_VDDIOCTRL_ADJTN)
#define BM_POWER_VDDIOCTRL_RSRVD4	0x00080000
#define BM_POWER_VDDIOCTRL_PWDN_BRNOUT	0x00040000
#define BM_POWER_VDDIOCTRL_DISABLE_STEPPING	0x00020000
#define BM_POWER_VDDIOCTRL_DISABLE_FET	0x00010000
#define BP_POWER_VDDIOCTRL_RSRVD3	14
#define BM_POWER_VDDIOCTRL_RSRVD3	0x0000C000
#define BF_POWER_VDDIOCTRL_RSRVD3(v)  \
		(((v) << 14) & BM_POWER_VDDIOCTRL_RSRVD3)
#define BP_POWER_VDDIOCTRL_LINREG_OFFSET	12
#define BM_POWER_VDDIOCTRL_LINREG_OFFSET	0x00003000
#define BF_POWER_VDDIOCTRL_LINREG_OFFSET(v)  \
		(((v) << 12) & BM_POWER_VDDIOCTRL_LINREG_OFFSET)
#define BM_POWER_VDDIOCTRL_RSRVD2	0x00000800
#define BP_POWER_VDDIOCTRL_BO_OFFSET	8
#define BM_POWER_VDDIOCTRL_BO_OFFSET	0x00000700
#define BF_POWER_VDDIOCTRL_BO_OFFSET(v)  \
		(((v) << 8) & BM_POWER_VDDIOCTRL_BO_OFFSET)
#define BP_POWER_VDDIOCTRL_RSRVD1	5
#define BM_POWER_VDDIOCTRL_RSRVD1	0x000000E0
#define BF_POWER_VDDIOCTRL_RSRVD1(v)  \
		(((v) << 5) & BM_POWER_VDDIOCTRL_RSRVD1)
#define BP_POWER_VDDIOCTRL_TRG	0
#define BM_POWER_VDDIOCTRL_TRG	0x0000001F
#define BF_POWER_VDDIOCTRL_TRG(v)  \
		(((v) << 0) & BM_POWER_VDDIOCTRL_TRG)

#define HW_POWER_VDDMEMCTRL	(0x00000070)

#define BP_POWER_VDDMEMCTRL_RSRVD2	11
#define BM_POWER_VDDMEMCTRL_RSRVD2	0xFFFFF800
#define BF_POWER_VDDMEMCTRL_RSRVD2(v) \
		(((v) << 11) & BM_POWER_VDDMEMCTRL_RSRVD2)
#define BM_POWER_VDDMEMCTRL_PULLDOWN_ACTIVE	0x00000400
#define BM_POWER_VDDMEMCTRL_ENABLE_ILIMIT	0x00000200
#define BM_POWER_VDDMEMCTRL_ENABLE_LINREG	0x00000100
#define BP_POWER_VDDMEMCTRL_RSRVD1	5
#define BM_POWER_VDDMEMCTRL_RSRVD1	0x000000E0
#define BF_POWER_VDDMEMCTRL_RSRVD1(v)  \
		(((v) << 5) & BM_POWER_VDDMEMCTRL_RSRVD1)
#define BP_POWER_VDDMEMCTRL_TRG	0
#define BM_POWER_VDDMEMCTRL_TRG	0x0000001F
#define BF_POWER_VDDMEMCTRL_TRG(v)  \
		(((v) << 0) & BM_POWER_VDDMEMCTRL_TRG)

#define HW_POWER_DCDC4P2	(0x00000080)

#define BP_POWER_DCDC4P2_DROPOUT_CTRL	28
#define BM_POWER_DCDC4P2_DROPOUT_CTRL	0xF0000000
#define BF_POWER_DCDC4P2_DROPOUT_CTRL(v) \
		(((v) << 28) & BM_POWER_DCDC4P2_DROPOUT_CTRL)
#define BP_POWER_DCDC4P2_RSRVD5	26
#define BM_POWER_DCDC4P2_RSRVD5	0x0C000000
#define BF_POWER_DCDC4P2_RSRVD5(v)  \
		(((v) << 26) & BM_POWER_DCDC4P2_RSRVD5)
#define BP_POWER_DCDC4P2_ISTEAL_THRESH	24
#define BM_POWER_DCDC4P2_ISTEAL_THRESH	0x03000000
#define BF_POWER_DCDC4P2_ISTEAL_THRESH(v)  \
		(((v) << 24) & BM_POWER_DCDC4P2_ISTEAL_THRESH)
#define BM_POWER_DCDC4P2_ENABLE_4P2	0x00800000
#define BM_POWER_DCDC4P2_ENABLE_DCDC	0x00400000
#define BM_POWER_DCDC4P2_HYST_DIR	0x00200000
#define BM_POWER_DCDC4P2_HYST_THRESH	0x00100000
#define BM_POWER_DCDC4P2_RSRVD3	0x00080000
#define BP_POWER_DCDC4P2_TRG	16
#define BM_POWER_DCDC4P2_TRG	0x00070000
#define BF_POWER_DCDC4P2_TRG(v)  \
		(((v) << 16) & BM_POWER_DCDC4P2_TRG)
#define BP_POWER_DCDC4P2_RSRVD2	13
#define BM_POWER_DCDC4P2_RSRVD2	0x0000E000
#define BF_POWER_DCDC4P2_RSRVD2(v)  \
		(((v) << 13) & BM_POWER_DCDC4P2_RSRVD2)
#define BP_POWER_DCDC4P2_BO	8
#define BM_POWER_DCDC4P2_BO	0x00001F00
#define BF_POWER_DCDC4P2_BO(v)  \
		(((v) << 8) & BM_POWER_DCDC4P2_BO)
#define BP_POWER_DCDC4P2_RSRVD1	5
#define BM_POWER_DCDC4P2_RSRVD1	0x000000E0
#define BF_POWER_DCDC4P2_RSRVD1(v)  \
		(((v) << 5) & BM_POWER_DCDC4P2_RSRVD1)
#define BP_POWER_DCDC4P2_CMPTRIP	0
#define BM_POWER_DCDC4P2_CMPTRIP	0x0000001F
#define BF_POWER_DCDC4P2_CMPTRIP(v)  \
		(((v) << 0) & BM_POWER_DCDC4P2_CMPTRIP)

#define HW_POWER_MISC	(0x00000090)

#define BP_POWER_MISC_RSRVD2	7
#define BM_POWER_MISC_RSRVD2	0xFFFFFF80
#define BF_POWER_MISC_RSRVD2(v) \
		(((v) << 7) & BM_POWER_MISC_RSRVD2)
#define BP_POWER_MISC_FREQSEL	4
#define BM_POWER_MISC_FREQSEL	0x00000070
#define BF_POWER_MISC_FREQSEL(v)  \
		(((v) << 4) & BM_POWER_MISC_FREQSEL)
#define BM_POWER_MISC_RSRVD1	0x00000008
#define BM_POWER_MISC_DELAY_TIMING	0x00000004
#define BM_POWER_MISC_TEST	0x00000002
#define BM_POWER_MISC_SEL_PLLCLK	0x00000001

#define HW_POWER_DCLIMITS	(0x000000a0)

#define BP_POWER_DCLIMITS_RSRVD3	16
#define BM_POWER_DCLIMITS_RSRVD3	0xFFFF0000
#define BF_POWER_DCLIMITS_RSRVD3(v) \
		(((v) << 16) & BM_POWER_DCLIMITS_RSRVD3)
#define BM_POWER_DCLIMITS_RSRVD2	0x00008000
#define BP_POWER_DCLIMITS_POSLIMIT_BUCK	8
#define BM_POWER_DCLIMITS_POSLIMIT_BUCK	0x00007F00
#define BF_POWER_DCLIMITS_POSLIMIT_BUCK(v)  \
		(((v) << 8) & BM_POWER_DCLIMITS_POSLIMIT_BUCK)
#define BM_POWER_DCLIMITS_RSRVD1	0x00000080
#define BP_POWER_DCLIMITS_NEGLIMIT	0
#define BM_POWER_DCLIMITS_NEGLIMIT	0x0000007F
#define BF_POWER_DCLIMITS_NEGLIMIT(v)  \
		(((v) << 0) & BM_POWER_DCLIMITS_NEGLIMIT)

#define HW_POWER_LOOPCTRL	(0x000000b0)
#define HW_POWER_LOOPCTRL_SET	(0x000000b4)
#define HW_POWER_LOOPCTRL_CLR	(0x000000b8)
#define HW_POWER_LOOPCTRL_TOG	(0x000000bc)

#define BP_POWER_LOOPCTRL_RSRVD3	21
#define BM_POWER_LOOPCTRL_RSRVD3	0xFFE00000
#define BF_POWER_LOOPCTRL_RSRVD3(v) \
		(((v) << 21) & BM_POWER_LOOPCTRL_RSRVD3)
#define BM_POWER_LOOPCTRL_TOGGLE_DIF	0x00100000
#define BM_POWER_LOOPCTRL_HYST_SIGN	0x00080000
#define BM_POWER_LOOPCTRL_EN_CM_HYST	0x00040000
#define BM_POWER_LOOPCTRL_EN_DF_HYST	0x00020000
#define BM_POWER_LOOPCTRL_CM_HYST_THRESH	0x00010000
#define BM_POWER_LOOPCTRL_DF_HYST_THRESH	0x00008000
#define BM_POWER_LOOPCTRL_RCSCALE_THRESH	0x00004000
#define BP_POWER_LOOPCTRL_EN_RCSCALE	12
#define BM_POWER_LOOPCTRL_EN_RCSCALE	0x00003000
#define BF_POWER_LOOPCTRL_EN_RCSCALE(v)  \
		(((v) << 12) & BM_POWER_LOOPCTRL_EN_RCSCALE)
#define BM_POWER_LOOPCTRL_RSRVD2	0x00000800
#define BP_POWER_LOOPCTRL_DC_FF	8
#define BM_POWER_LOOPCTRL_DC_FF	0x00000700
#define BF_POWER_LOOPCTRL_DC_FF(v)  \
		(((v) << 8) & BM_POWER_LOOPCTRL_DC_FF)
#define BP_POWER_LOOPCTRL_DC_R	4
#define BM_POWER_LOOPCTRL_DC_R	0x000000F0
#define BF_POWER_LOOPCTRL_DC_R(v)  \
		(((v) << 4) & BM_POWER_LOOPCTRL_DC_R)
#define BP_POWER_LOOPCTRL_RSRVD1	2
#define BM_POWER_LOOPCTRL_RSRVD1	0x0000000C
#define BF_POWER_LOOPCTRL_RSRVD1(v)  \
		(((v) << 2) & BM_POWER_LOOPCTRL_RSRVD1)
#define BP_POWER_LOOPCTRL_DC_C	0
#define BM_POWER_LOOPCTRL_DC_C	0x00000003
#define BF_POWER_LOOPCTRL_DC_C(v)  \
		(((v) << 0) & BM_POWER_LOOPCTRL_DC_C)

#define HW_POWER_STS	(0x000000c0)

#define BP_POWER_STS_RSRVD3	30
#define BM_POWER_STS_RSRVD3	0xC0000000
#define BF_POWER_STS_RSRVD3(v) \
		(((v) << 30) & BM_POWER_STS_RSRVD3)
#define BP_POWER_STS_PWRUP_SOURCE	24
#define BM_POWER_STS_PWRUP_SOURCE	0x3F000000
#define BF_POWER_STS_PWRUP_SOURCE(v)  \
		(((v) << 24) & BM_POWER_STS_PWRUP_SOURCE)
#define BP_POWER_STS_RSRVD2	22
#define BM_POWER_STS_RSRVD2	0x00C00000
#define BF_POWER_STS_RSRVD2(v)  \
		(((v) << 22) & BM_POWER_STS_RSRVD2)
#define BP_POWER_STS_PSWITCH	20
#define BM_POWER_STS_PSWITCH	0x00300000
#define BF_POWER_STS_PSWITCH(v)  \
		(((v) << 20) & BM_POWER_STS_PSWITCH)
#define BP_POWER_STS_RSRVD1	18
#define BM_POWER_STS_RSRVD1	0x000C0000
#define BF_POWER_STS_RSRVD1(v)  \
		(((v) << 18) & BM_POWER_STS_RSRVD1)
#define BM_POWER_STS_AVALID_STATUS	0x00020000
#define BM_POWER_STS_BVALID_STATUS	0x00010000
#define BM_POWER_STS_VBUSVALID_STATUS	0x00008000
#define BM_POWER_STS_SESSEND_STATUS	0x00004000
#define BM_POWER_STS_BATT_BO	0x00002000
#define BM_POWER_STS_VDD5V_FAULT	0x00001000
#define BM_POWER_STS_CHRGSTS	0x00000800
#define BM_POWER_STS_DCDC_4P2_BO	0x00000400
#define BM_POWER_STS_DC_OK	0x00000200
#define BM_POWER_STS_VDDIO_BO	0x00000100
#define BM_POWER_STS_VDDA_BO	0x00000080
#define BM_POWER_STS_VDDD_BO	0x00000040
#define BM_POWER_STS_VDD5V_GT_VDDIO	0x00000020
#define BM_POWER_STS_VDD5V_DROOP	0x00000010
#define BM_POWER_STS_AVALID	0x00000008
#define BM_POWER_STS_BVALID	0x00000004
#define BM_POWER_STS_VBUSVALID	0x00000002
#define BM_POWER_STS_SESSEND	0x00000001

#define HW_POWER_SPEED	(0x000000d0)
#define HW_POWER_SPEED_SET	(0x000000d4)
#define HW_POWER_SPEED_CLR	(0x000000d8)
#define HW_POWER_SPEED_TOG	(0x000000dc)

#define BP_POWER_SPEED_RSRVD1	24
#define BM_POWER_SPEED_RSRVD1	0xFF000000
#define BF_POWER_SPEED_RSRVD1(v) \
		(((v) << 24) & BM_POWER_SPEED_RSRVD1)
#define BP_POWER_SPEED_STATUS	16
#define BM_POWER_SPEED_STATUS	0x00FF0000
#define BF_POWER_SPEED_STATUS(v)  \
		(((v) << 16) & BM_POWER_SPEED_STATUS)
#define BP_POWER_SPEED_RSRVD0	2
#define BM_POWER_SPEED_RSRVD0	0x0000FFFC
#define BF_POWER_SPEED_RSRVD0(v)  \
		(((v) << 2) & BM_POWER_SPEED_RSRVD0)
#define BP_POWER_SPEED_CTRL	0
#define BM_POWER_SPEED_CTRL	0x00000003
#define BF_POWER_SPEED_CTRL(v)  \
		(((v) << 0) & BM_POWER_SPEED_CTRL)

#define HW_POWER_BATTMONITOR	(0x000000e0)

#define BP_POWER_BATTMONITOR_RSRVD3	26
#define BM_POWER_BATTMONITOR_RSRVD3	0xFC000000
#define BF_POWER_BATTMONITOR_RSRVD3(v) \
		(((v) << 26) & BM_POWER_BATTMONITOR_RSRVD3)
#define BP_POWER_BATTMONITOR_BATT_VAL	16
#define BM_POWER_BATTMONITOR_BATT_VAL	0x03FF0000
#define BF_POWER_BATTMONITOR_BATT_VAL(v)  \
		(((v) << 16) & BM_POWER_BATTMONITOR_BATT_VAL)
#define BP_POWER_BATTMONITOR_RSRVD2	11
#define BM_POWER_BATTMONITOR_RSRVD2	0x0000F800
#define BF_POWER_BATTMONITOR_RSRVD2(v)  \
		(((v) << 11) & BM_POWER_BATTMONITOR_RSRVD2)
#define BM_POWER_BATTMONITOR_EN_BATADJ	0x00000400
#define BM_POWER_BATTMONITOR_PWDN_BATTBRNOUT	0x00000200
#define BM_POWER_BATTMONITOR_BRWNOUT_PWD	0x00000100
#define BP_POWER_BATTMONITOR_RSRVD1	5
#define BM_POWER_BATTMONITOR_RSRVD1	0x000000E0
#define BF_POWER_BATTMONITOR_RSRVD1(v)  \
		(((v) << 5) & BM_POWER_BATTMONITOR_RSRVD1)
#define BP_POWER_BATTMONITOR_BRWNOUT_LVL	0
#define BM_POWER_BATTMONITOR_BRWNOUT_LVL	0x0000001F
#define BF_POWER_BATTMONITOR_BRWNOUT_LVL(v)  \
		(((v) << 0) & BM_POWER_BATTMONITOR_BRWNOUT_LVL)

#define HW_POWER_RESET	(0x00000100)
#define HW_POWER_RESET_SET	(0x00000104)
#define HW_POWER_RESET_CLR	(0x00000108)
#define HW_POWER_RESET_TOG	(0x0000010c)

#define BP_POWER_RESET_UNLOCK	16
#define BM_POWER_RESET_UNLOCK	0xFFFF0000
#define BF_POWER_RESET_UNLOCK(v) \
		(((v) << 16) & BM_POWER_RESET_UNLOCK)
#define BV_POWER_RESET_UNLOCK__KEY 0x3E77
#define BP_POWER_RESET_RSRVD1	2
#define BM_POWER_RESET_RSRVD1	0x0000FFFC
#define BF_POWER_RESET_RSRVD1(v)  \
		(((v) << 2) & BM_POWER_RESET_RSRVD1)
#define BM_POWER_RESET_PWD_OFF	0x00000002
#define BM_POWER_RESET_PWD	0x00000001

#define HW_POWER_DEBUG	(0x00000110)
#define HW_POWER_DEBUG_SET	(0x00000114)
#define HW_POWER_DEBUG_CLR	(0x00000118)
#define HW_POWER_DEBUG_TOG	(0x0000011c)

#define BP_POWER_DEBUG_RSRVD0	4
#define BM_POWER_DEBUG_RSRVD0	0xFFFFFFF0
#define BF_POWER_DEBUG_RSRVD0(v) \
		(((v) << 4) & BM_POWER_DEBUG_RSRVD0)
#define BM_POWER_DEBUG_VBUSVALIDPIOLOCK	0x00000008
#define BM_POWER_DEBUG_AVALIDPIOLOCK	0x00000004
#define BM_POWER_DEBUG_BVALIDPIOLOCK	0x00000002
#define BM_POWER_DEBUG_SESSENDPIOLOCK	0x00000001

#define HW_POWER_SPECIAL	(0x00000120)
#define HW_POWER_SPECIAL_SET	(0x00000124)
#define HW_POWER_SPECIAL_CLR	(0x00000128)
#define HW_POWER_SPECIAL_TOG	(0x0000012c)

#define BP_POWER_SPECIAL_TEST	0
#define BM_POWER_SPECIAL_TEST	0xFFFFFFFF
#define BF_POWER_SPECIAL_TEST(v)	(v)

#define HW_POWER_VERSION	(0x00000130)

#define BP_POWER_VERSION_MAJOR	24
#define BM_POWER_VERSION_MAJOR	0xFF000000
#define BF_POWER_VERSION_MAJOR(v) \
		(((v) << 24) & BM_POWER_VERSION_MAJOR)
#define BP_POWER_VERSION_MINOR	16
#define BM_POWER_VERSION_MINOR	0x00FF0000
#define BF_POWER_VERSION_MINOR(v)  \
		(((v) << 16) & BM_POWER_VERSION_MINOR)
#define BP_POWER_VERSION_STEP	0
#define BM_POWER_VERSION_STEP	0x0000FFFF
#define BF_POWER_VERSION_STEP(v)  \
		(((v) << 0) & BM_POWER_VERSION_STEP)
#endif /* __ARCH_ARM___POWER_H */
