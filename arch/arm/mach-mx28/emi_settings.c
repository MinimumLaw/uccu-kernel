/*
 * Copyright (C) 2009-2010 Freescale Semiconductor, Inc. All Rights Reserved.
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
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/irq.h>
#include <linux/clk.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/input.h>
#include <linux/platform_device.h>
#include <linux/mmc/host.h>
#include <linux/phy.h>

#include <asm/mach/map.h>

#include <mach/mx28.h>
#include <mach/clock.h>
#include "emi_settings.h"

static unsigned int DRAM_REG[MX28_DRAMCTRLREGNUM];
unsigned int *get_current_emidata()
{
	return DRAM_REG;
}

void test_emi_change()
{
	struct mxs_emi_scaling_data emi;
	void (*f) (struct mxs_emi_scaling_data *, unsigned int *);
	f = (void *)MX28_OCRAM_BASE;
	memcpy(f, mxs_ram_freq_scale,
	       (unsigned int)mxs_ram_freq_scale_end -
	       (unsigned int)mxs_ram_freq_scale);

	pr_debug("start change emi frequency test\n");
	pr_debug("begin change 133\n");
	emi.emi_div = 3;	/* 130Mhz */
	emi.frac_div = 22;	/* 392Mhz */
	emi.new_freq = 133;
	DDR2EmiController_EDE1116_133MHz();
	f(&emi, get_current_emidata());
	pr_debug("end change 133\n");

	pr_debug("begin change 166\n");
	emi.emi_div = 2;	/* 160Mhz */
	emi.frac_div = 27;	/* 320Mhz */
	emi.new_freq = 166;
	DDR2EmiController_EDE1116_166MHz();
	f(&emi, get_current_emidata());
	pr_debug("end change 166\n");

	pr_debug("begin change 200\n");
	emi.emi_div = 2;	/* 192Mhz */
	emi.frac_div = 22;	/* 392Mhz */
	emi.new_freq = 200;
	DDR2EmiController_EDE1116_200MHz();
	f(&emi, get_current_emidata());
	pr_debug("end change 200\n");

	pr_debug("begin change 166\n");
	emi.emi_div = 2;	/* 166Mhz */
	emi.frac_div = 26;	/* 332Mhz */
	emi.new_freq = 166;
	DDR2EmiController_EDE1116_166MHz();
	f(&emi, get_current_emidata());
	pr_debug("end change 166\n");

	pr_debug("begin change 133\n");
	emi.emi_div = 3;	/* 130Mhz */
	emi.frac_div = 22;	/* 392Mhz */
	emi.new_freq = 133;
	DDR2EmiController_EDE1116_133MHz();
	f(&emi, get_current_emidata());
	pr_debug("end change 133\n");
	pr_debug("finish change emi frequency test\n");
}

void DDR2EmiController_EDE1116_133MHz(void)
{
	DRAM_REG[0] = 0x00000000;
	DRAM_REG[1] = 0x00000000;
	DRAM_REG[2] = 0x00000000;
	DRAM_REG[3] = 0x00000000;
	DRAM_REG[4] = 0x00000000;
	DRAM_REG[5] = 0x00000000;
	DRAM_REG[6] = 0x00000000;
	DRAM_REG[7] = 0x00000000;
	DRAM_REG[8] = 0x00000000;
	DRAM_REG[9] = 0x00000000;
	DRAM_REG[10] = 0x00000000;
	DRAM_REG[11] = 0x00000000;
	DRAM_REG[12] = 0x00000000;
	DRAM_REG[13] = 0x00000000;
	DRAM_REG[14] = 0x00000000;
	DRAM_REG[15] = 0x00000000;
	DRAM_REG[16] = 0x00000000;
	DRAM_REG[17] = 0x00000100;
	DRAM_REG[18] = 0x00000000;
	DRAM_REG[19] = 0x00000000;
	DRAM_REG[20] = 0x00000000;
	DRAM_REG[21] = 0x00000000;
	DRAM_REG[22] = 0x00000000;
	DRAM_REG[23] = 0x00000000;
	DRAM_REG[24] = 0x00000000;
	DRAM_REG[25] = 0x00000000;
	DRAM_REG[26] = 0x00010101;
	DRAM_REG[27] = 0x01010101;
	DRAM_REG[28] = 0x000f0f01;
	DRAM_REG[29] = 0x0f02020a;
	DRAM_REG[30] = 0x00000000;
	DRAM_REG[31] = 0x00010101;
	DRAM_REG[32] = 0x00000100;
	DRAM_REG[33] = 0x00000100;
	DRAM_REG[34] = 0x00000000;
	DRAM_REG[35] = 0x00000002;
	DRAM_REG[36] = 0x01010000;
	DRAM_REG[37] = 0x07080403;
	DRAM_REG[38] = 0x04003603;
	DRAM_REG[39] = 0x070000c8;
	DRAM_REG[40] = 0x0200682b;
	DRAM_REG[41] = 0x00020208;
	DRAM_REG[42] = 0x00246c06;
	DRAM_REG[43] = 0x02110409;
	DRAM_REG[44] = 0x01020202;
	DRAM_REG[45] = 0x00c80013;
	DRAM_REG[46] = 0x00000000;
	DRAM_REG[47] = 0x00000000;
	DRAM_REG[48] = 0x00012100;
	DRAM_REG[49] = 0xffff0303;
	DRAM_REG[50] = 0x00012100;
	DRAM_REG[51] = 0xffff0303;
	DRAM_REG[52] = 0x00012100;
	DRAM_REG[53] = 0xffff0303;
	DRAM_REG[54] = 0x00012100;
	DRAM_REG[55] = 0xffff0303;
	DRAM_REG[56] = 0x00000003;
	DRAM_REG[57] = 0x00000000;
	DRAM_REG[58] = 0x00000000;
	DRAM_REG[59] = 0x00000000;
	DRAM_REG[60] = 0x00000000;
	DRAM_REG[61] = 0x00000000;
	DRAM_REG[62] = 0x00000000;
	DRAM_REG[63] = 0x00000000;
	DRAM_REG[64] = 0x00000000;
	DRAM_REG[65] = 0x00000000;
	DRAM_REG[66] = 0x00000409;
	DRAM_REG[67] = 0x01000f02;
	DRAM_REG[68] = 0x04090409;
	DRAM_REG[69] = 0x00000200;
	DRAM_REG[70] = 0x00020006;
	DRAM_REG[71] = 0xf4004a27;
	DRAM_REG[72] = 0xf4004a27;
	DRAM_REG[73] = 0xf4004a27;
	DRAM_REG[74] = 0xf4004a27;
	DRAM_REG[75] = 0x07000300;
	DRAM_REG[76] = 0x07000300;
	DRAM_REG[77] = 0x07400300;
	DRAM_REG[78] = 0x07400300;
	DRAM_REG[79] = 0x00000005;
	DRAM_REG[80] = 0x00000000;
	DRAM_REG[81] = 0x00000000;
	DRAM_REG[82] = 0x01000000;
	DRAM_REG[83] = 0x01020408;
	DRAM_REG[84] = 0x08040201;
	DRAM_REG[85] = 0x000f1133;
	DRAM_REG[86] = 0x00000000;
	DRAM_REG[87] = 0x00001f04;
	DRAM_REG[88] = 0x00001f04;
	DRAM_REG[89] = 0x00001f04;
	DRAM_REG[90] = 0x00001f04;
	DRAM_REG[91] = 0x00001f04;
	DRAM_REG[92] = 0x00001f04;
	DRAM_REG[93] = 0x00001f04;
	DRAM_REG[94] = 0x00001f04;
	DRAM_REG[95] = 0x00000000;
	DRAM_REG[96] = 0x00000000;
	DRAM_REG[97] = 0x00000000;
	DRAM_REG[98] = 0x00000000;
	DRAM_REG[99] = 0x00000000;
	DRAM_REG[100] = 0x00000000;
	DRAM_REG[101] = 0x00000000;
	DRAM_REG[102] = 0x00000000;
	DRAM_REG[103] = 0x00000000;
	DRAM_REG[104] = 0x00000000;
	DRAM_REG[105] = 0x00000000;
	DRAM_REG[106] = 0x00000000;
	DRAM_REG[107] = 0x00000000;
	DRAM_REG[108] = 0x00000000;
	DRAM_REG[109] = 0x00000000;
	DRAM_REG[110] = 0x00000000;
	DRAM_REG[111] = 0x00000000;
	DRAM_REG[112] = 0x00000000;
	DRAM_REG[113] = 0x00000000;
	DRAM_REG[114] = 0x00000000;
	DRAM_REG[115] = 0x00000000;
	DRAM_REG[116] = 0x00000000;
	DRAM_REG[117] = 0x00000000;
	DRAM_REG[118] = 0x00000000;
	DRAM_REG[119] = 0x00000000;
	DRAM_REG[120] = 0x00000000;
	DRAM_REG[121] = 0x00000000;
	DRAM_REG[122] = 0x00000000;
	DRAM_REG[123] = 0x00000000;
	DRAM_REG[124] = 0x00000000;
	DRAM_REG[125] = 0x00000000;
	DRAM_REG[126] = 0x00000000;
	DRAM_REG[127] = 0x00000000;
	DRAM_REG[128] = 0x00000000;
	DRAM_REG[129] = 0x00000000;
	DRAM_REG[130] = 0x00000000;
	DRAM_REG[131] = 0x00000000;
	DRAM_REG[132] = 0x00000000;
	DRAM_REG[133] = 0x00000000;
	DRAM_REG[134] = 0x00000000;
	DRAM_REG[135] = 0x00000000;
	DRAM_REG[136] = 0x00000000;
	DRAM_REG[137] = 0x00000000;
	DRAM_REG[138] = 0x00000000;
	DRAM_REG[139] = 0x00000000;
	DRAM_REG[140] = 0x00000000;
	DRAM_REG[141] = 0x00000000;
	DRAM_REG[142] = 0x00000000;
	DRAM_REG[143] = 0x00000000;
	DRAM_REG[144] = 0x00000000;
	DRAM_REG[145] = 0x00000000;
	DRAM_REG[146] = 0x00000000;
	DRAM_REG[147] = 0x00000000;
	DRAM_REG[148] = 0x00000000;
	DRAM_REG[149] = 0x00000000;
	DRAM_REG[150] = 0x00000000;
	DRAM_REG[151] = 0x00000000;
	DRAM_REG[152] = 0x00000000;
	DRAM_REG[153] = 0x00000000;
	DRAM_REG[154] = 0x00000000;
	DRAM_REG[155] = 0x00000000;
	DRAM_REG[156] = 0x00000000;
	DRAM_REG[157] = 0x00000000;
	DRAM_REG[158] = 0x00000000;
	DRAM_REG[159] = 0x00000000;
	DRAM_REG[160] = 0x00000000;
	DRAM_REG[161] = 0x00000000;
	DRAM_REG[162] = 0x00010000;
	DRAM_REG[163] = 0x00030404;
	DRAM_REG[164] = 0x00000002;
	DRAM_REG[165] = 0x00000000;
	DRAM_REG[166] = 0x00000000;
	DRAM_REG[167] = 0x00000000;
	DRAM_REG[168] = 0x00000000;
	DRAM_REG[169] = 0x00000000;
	DRAM_REG[170] = 0x00000000;
	DRAM_REG[171] = 0x01010000;
	DRAM_REG[172] = 0x01000000;
	DRAM_REG[173] = 0x03030000;
	DRAM_REG[174] = 0x00010303;
	DRAM_REG[175] = 0x01020202;
	DRAM_REG[176] = 0x00000000;
	DRAM_REG[177] = 0x02030303;
	DRAM_REG[178] = 0x21002103;
	DRAM_REG[179] = 0x00040900;
	DRAM_REG[180] = 0x04090409;
	DRAM_REG[181] = 0x02420242;
	DRAM_REG[182] = 0x02420242;
	DRAM_REG[183] = 0x00040004;
	DRAM_REG[184] = 0x00040004;
	DRAM_REG[185] = 0x00000000;
	DRAM_REG[186] = 0x00000000;
	DRAM_REG[187] = 0x00000000;
	DRAM_REG[188] = 0x00000000;
	DRAM_REG[189] = 0xffffffff;

}

void DDR2EmiController_EDE1116_166MHz(void)
{

	DRAM_REG[0] = 0x00000000;
	DRAM_REG[1] = 0x00000000;
	DRAM_REG[2] = 0x00000000;
	DRAM_REG[3] = 0x00000000;
	DRAM_REG[4] = 0x00000000;
	DRAM_REG[5] = 0x00000000;
	DRAM_REG[6] = 0x00000000;
	DRAM_REG[7] = 0x00000000;
	DRAM_REG[8] = 0x00000000;
	DRAM_REG[9] = 0x00000000;
	DRAM_REG[10] = 0x00000000;
	DRAM_REG[11] = 0x00000000;
	DRAM_REG[12] = 0x00000000;
	DRAM_REG[13] = 0x00000000;
	DRAM_REG[14] = 0x00000000;
	DRAM_REG[15] = 0x00000000;
	DRAM_REG[16] = 0x00000000;
	DRAM_REG[17] = 0x00000100;
	DRAM_REG[18] = 0x00000000;
	DRAM_REG[19] = 0x00000000;
	DRAM_REG[20] = 0x00000000;
	DRAM_REG[21] = 0x00000000;
	DRAM_REG[22] = 0x00000000;
	DRAM_REG[23] = 0x00000000;
	DRAM_REG[24] = 0x00000000;
	DRAM_REG[25] = 0x00000000;
	DRAM_REG[26] = 0x00010101;
	DRAM_REG[27] = 0x01010101;
	DRAM_REG[28] = 0x000f0f01;
	DRAM_REG[29] = 0x0f02020a;
	DRAM_REG[30] = 0x00000000;
	DRAM_REG[31] = 0x00010101;
	DRAM_REG[32] = 0x00000100;
	DRAM_REG[33] = 0x00000100;
	DRAM_REG[34] = 0x00000000;
	DRAM_REG[35] = 0x00000002;
	DRAM_REG[36] = 0x01010000;
	DRAM_REG[37] = 0x07080403;
	DRAM_REG[38] = 0x06004303;
	DRAM_REG[39] = 0x090000c8;
	DRAM_REG[40] = 0x02008236;
	DRAM_REG[41] = 0x0002030a;
	DRAM_REG[42] = 0x002d8908;
	DRAM_REG[43] = 0x0316050e;
	DRAM_REG[44] = 0x02030202;
	DRAM_REG[45] = 0x00c80017;
	DRAM_REG[46] = 0x00000000;
	DRAM_REG[47] = 0x00000000;
	DRAM_REG[48] = 0x00012100;
	DRAM_REG[49] = 0xffff0303;
	DRAM_REG[50] = 0x00012100;
	DRAM_REG[51] = 0xff000303;
	DRAM_REG[52] = 0x00012100;
	DRAM_REG[53] = 0xffff0303;
	DRAM_REG[54] = 0x00012100;
	DRAM_REG[55] = 0xffff0303;
	DRAM_REG[56] = 0x00000003;
	DRAM_REG[57] = 0x00000000;
	DRAM_REG[58] = 0x00000000;
	DRAM_REG[59] = 0x00000000;
	DRAM_REG[60] = 0x00000000;
	DRAM_REG[61] = 0x00000000;
	DRAM_REG[62] = 0x00000000;
	DRAM_REG[63] = 0x00000000;
	DRAM_REG[64] = 0x00000000;
	DRAM_REG[65] = 0x00000000;
	DRAM_REG[66] = 0x0000050e;
	DRAM_REG[67] = 0x01000f02;
	DRAM_REG[68] = 0x050e050e;
	DRAM_REG[69] = 0x00000200;
	DRAM_REG[70] = 0x00020007;
	DRAM_REG[71] = 0xf5004a27;
	DRAM_REG[72] = 0xf5004a27;
	DRAM_REG[73] = 0xf5004a27;
	DRAM_REG[74] = 0xf5004a27;
	DRAM_REG[75] = 0x07000300;
	DRAM_REG[76] = 0x07000300;
	DRAM_REG[77] = 0x07400300;
	DRAM_REG[78] = 0x07400300;
	DRAM_REG[79] = 0x00000006;
	DRAM_REG[80] = 0x00000000;
	DRAM_REG[81] = 0x00000000;
	DRAM_REG[82] = 0x01000000;
	DRAM_REG[83] = 0x01020408;
	DRAM_REG[84] = 0x08040201;
	DRAM_REG[85] = 0x000f1133;
	DRAM_REG[86] = 0x00000000;
	DRAM_REG[87] = 0x00001f04;
	DRAM_REG[88] = 0x00001f04;
	DRAM_REG[89] = 0x00001f04;
	DRAM_REG[90] = 0x00001f04;
	DRAM_REG[91] = 0x00001f04;
	DRAM_REG[92] = 0x00001f04;
	DRAM_REG[93] = 0x00001f04;
	DRAM_REG[94] = 0x00001f04;
	DRAM_REG[95] = 0x00000000;
	DRAM_REG[96] = 0x00000000;
	DRAM_REG[97] = 0x00000000;
	DRAM_REG[98] = 0x00000000;
	DRAM_REG[99] = 0x00000000;
	DRAM_REG[100] = 0x00000000;
	DRAM_REG[101] = 0x00000000;
	DRAM_REG[102] = 0x00000000;
	DRAM_REG[103] = 0x00000000;
	DRAM_REG[104] = 0x00000000;
	DRAM_REG[105] = 0x00000000;
	DRAM_REG[106] = 0x00000000;
	DRAM_REG[107] = 0x00000000;
	DRAM_REG[108] = 0x00000000;
	DRAM_REG[109] = 0x00000000;
	DRAM_REG[110] = 0x00000000;
	DRAM_REG[111] = 0x00000000;
	DRAM_REG[112] = 0x00000000;
	DRAM_REG[113] = 0x00000000;
	DRAM_REG[114] = 0x00000000;
	DRAM_REG[115] = 0x00000000;
	DRAM_REG[116] = 0x00000000;
	DRAM_REG[117] = 0x00000000;
	DRAM_REG[118] = 0x00000000;
	DRAM_REG[119] = 0x00000000;
	DRAM_REG[120] = 0x00000000;
	DRAM_REG[121] = 0x00000000;
	DRAM_REG[122] = 0x00000000;
	DRAM_REG[123] = 0x00000000;
	DRAM_REG[124] = 0x00000000;
	DRAM_REG[125] = 0x00000000;
	DRAM_REG[126] = 0x00000000;
	DRAM_REG[127] = 0x00000000;
	DRAM_REG[128] = 0x00000000;
	DRAM_REG[129] = 0x00000000;
	DRAM_REG[130] = 0x00000000;
	DRAM_REG[131] = 0x00000000;
	DRAM_REG[132] = 0x00000000;
	DRAM_REG[133] = 0x00000000;
	DRAM_REG[134] = 0x00000000;
	DRAM_REG[135] = 0x00000000;
	DRAM_REG[136] = 0x00000000;
	DRAM_REG[137] = 0x00000000;
	DRAM_REG[138] = 0x00000000;
	DRAM_REG[139] = 0x00000000;
	DRAM_REG[140] = 0x00000000;
	DRAM_REG[141] = 0x00000000;
	DRAM_REG[142] = 0x00000000;
	DRAM_REG[143] = 0x00000000;
	DRAM_REG[144] = 0x00000000;
	DRAM_REG[145] = 0x00000000;
	DRAM_REG[146] = 0x00000000;
	DRAM_REG[147] = 0x00000000;
	DRAM_REG[148] = 0x00000000;
	DRAM_REG[149] = 0x00000000;
	DRAM_REG[150] = 0x00000000;
	DRAM_REG[151] = 0x00000000;
	DRAM_REG[152] = 0x00000000;
	DRAM_REG[153] = 0x00000000;
	DRAM_REG[154] = 0x00000000;
	DRAM_REG[155] = 0x00000000;
	DRAM_REG[156] = 0x00000000;
	DRAM_REG[157] = 0x00000000;
	DRAM_REG[158] = 0x00000000;
	DRAM_REG[159] = 0x00000000;
	DRAM_REG[160] = 0x00000000;
	DRAM_REG[161] = 0x00000000;
	DRAM_REG[162] = 0x00010000;
	DRAM_REG[163] = 0x00030404;
	DRAM_REG[164] = 0x00000002;
	DRAM_REG[165] = 0x00000000;
	DRAM_REG[166] = 0x00000000;
	DRAM_REG[167] = 0x00000000;
	DRAM_REG[168] = 0x00000000;
	DRAM_REG[169] = 0x00000000;
	DRAM_REG[170] = 0x00000000;
	DRAM_REG[171] = 0x01010000;
	DRAM_REG[172] = 0x01000000;
	DRAM_REG[173] = 0x03030000;
	DRAM_REG[174] = 0x00010303;
	DRAM_REG[175] = 0x01020202;
	DRAM_REG[176] = 0x00000000;
	DRAM_REG[177] = 0x02040303;
	DRAM_REG[178] = 0x21002103;
	DRAM_REG[179] = 0x00050e00;
	DRAM_REG[180] = 0x050e050e;
	DRAM_REG[181] = 0x04420442;
	DRAM_REG[182] = 0x04420442;
	DRAM_REG[183] = 0x00040004;
	DRAM_REG[184] = 0x00040004;
	DRAM_REG[185] = 0x00000000;
	DRAM_REG[186] = 0x00000000;
	DRAM_REG[187] = 0x00000000;
	DRAM_REG[188] = 0x00000000;
	DRAM_REG[189] = 0xffffffff;

}

void DDR2EmiController_EDE1116_200MHz(void)
{
	DRAM_REG[0] = 0x00000000;
	DRAM_REG[1] = 0x00000000;
	DRAM_REG[2] = 0x00000000;
	DRAM_REG[3] = 0x00000000;
	DRAM_REG[4] = 0x00000000;
	DRAM_REG[5] = 0x00000000;
	DRAM_REG[6] = 0x00000000;
	DRAM_REG[7] = 0x00000000;
	DRAM_REG[8] = 0x00000000;
	DRAM_REG[9] = 0x00000000;
	DRAM_REG[10] = 0x00000000;
	DRAM_REG[11] = 0x00000000;
	DRAM_REG[12] = 0x00000000;
	DRAM_REG[13] = 0x00000000;
	DRAM_REG[14] = 0x00000000;
	DRAM_REG[15] = 0x00000000;
	DRAM_REG[16] = 0x00000000;
	DRAM_REG[17] = 0x00000100;
	DRAM_REG[18] = 0x00000000;
	DRAM_REG[19] = 0x00000000;
	DRAM_REG[20] = 0x00000000;
	DRAM_REG[21] = 0x00000000;
	DRAM_REG[22] = 0x00000000;
	DRAM_REG[23] = 0x00000000;
	DRAM_REG[24] = 0x00000000;
	DRAM_REG[25] = 0x00000000;
	DRAM_REG[26] = 0x00010101;
	DRAM_REG[27] = 0x01010101;
	DRAM_REG[28] = 0x000f0f01;
	DRAM_REG[29] = 0x0f02020a;
	DRAM_REG[30] = 0x00000000;
	DRAM_REG[31] = 0x00010101;
	DRAM_REG[32] = 0x00000100;
	DRAM_REG[33] = 0x00000100;
	DRAM_REG[34] = 0x00000000;
	DRAM_REG[35] = 0x00000002;
	DRAM_REG[36] = 0x01010000;
	DRAM_REG[37] = 0x07080403;
	DRAM_REG[38] = 0x06005003;
	DRAM_REG[39] = 0x0a0000c8;
	DRAM_REG[40] = 0x02009c40;
	DRAM_REG[41] = 0x0002030c;
	DRAM_REG[42] = 0x0036a609;
	DRAM_REG[43] = 0x031a0612;
	DRAM_REG[44] = 0x02030202;
	DRAM_REG[45] = 0x00c8001c;
	DRAM_REG[46] = 0x00000000;
	DRAM_REG[47] = 0x00000000;
	DRAM_REG[48] = 0x00012100;
	DRAM_REG[49] = 0xffff0303;
	DRAM_REG[50] = 0x00012100;
	DRAM_REG[51] = 0xffff0303;
	DRAM_REG[52] = 0x00012100;
	DRAM_REG[53] = 0xffff0303;
	DRAM_REG[54] = 0x00012100;
	DRAM_REG[55] = 0xffff0303;
	DRAM_REG[56] = 0x00000003;
	DRAM_REG[57] = 0x00000000;
	DRAM_REG[58] = 0x00000000;
	DRAM_REG[59] = 0x00000000;
	DRAM_REG[60] = 0x00000000;
	DRAM_REG[61] = 0x00000000;
	DRAM_REG[62] = 0x00000000;
	DRAM_REG[63] = 0x00000000;
	DRAM_REG[64] = 0x00000000;
	DRAM_REG[65] = 0x00000000;
	DRAM_REG[66] = 0x00000612;
	DRAM_REG[67] = 0x01000f02;
	DRAM_REG[68] = 0x06120612;
	DRAM_REG[69] = 0x00000200;
	DRAM_REG[70] = 0x00020007;
	DRAM_REG[71] = 0xf4004a27;
	DRAM_REG[72] = 0xf4004a27;
	DRAM_REG[73] = 0xf4004a27;
	DRAM_REG[74] = 0xf4004a27;
	DRAM_REG[75] = 0x07000300;
	DRAM_REG[76] = 0x07000300;
	DRAM_REG[77] = 0x07400300;
	DRAM_REG[78] = 0x07400300;
	DRAM_REG[79] = 0x00000005;
	DRAM_REG[80] = 0x00000000;
	DRAM_REG[81] = 0x00000000;
	DRAM_REG[82] = 0x01000000;
	DRAM_REG[83] = 0x01020408;
	DRAM_REG[84] = 0x08040201;
	DRAM_REG[85] = 0x000f1133;
	DRAM_REG[86] = 0x00000000;
	DRAM_REG[87] = 0x00001f04;
	DRAM_REG[88] = 0x00001f04;
	DRAM_REG[89] = 0x00001f04;
	DRAM_REG[90] = 0x00001f04;
	DRAM_REG[91] = 0x00001f04;
	DRAM_REG[92] = 0x00001f04;
	DRAM_REG[93] = 0x00001f04;
	DRAM_REG[94] = 0x00001f04;
	DRAM_REG[95] = 0x00000000;
	DRAM_REG[96] = 0x00000000;
	DRAM_REG[97] = 0x00000000;
	DRAM_REG[98] = 0x00000000;
	DRAM_REG[99] = 0x00000000;
	DRAM_REG[100] = 0x00000000;
	DRAM_REG[101] = 0x00000000;
	DRAM_REG[102] = 0x00000000;
	DRAM_REG[103] = 0x00000000;
	DRAM_REG[104] = 0x00000000;
	DRAM_REG[105] = 0x00000000;
	DRAM_REG[106] = 0x00000000;
	DRAM_REG[107] = 0x00000000;
	DRAM_REG[108] = 0x00000000;
	DRAM_REG[109] = 0x00000000;
	DRAM_REG[110] = 0x00000000;
	DRAM_REG[111] = 0x00000000;
	DRAM_REG[112] = 0x00000000;
	DRAM_REG[113] = 0x00000000;
	DRAM_REG[114] = 0x00000000;
	DRAM_REG[115] = 0x00000000;
	DRAM_REG[116] = 0x00000000;
	DRAM_REG[117] = 0x00000000;
	DRAM_REG[118] = 0x00000000;
	DRAM_REG[119] = 0x00000000;
	DRAM_REG[120] = 0x00000000;
	DRAM_REG[121] = 0x00000000;
	DRAM_REG[122] = 0x00000000;
	DRAM_REG[123] = 0x00000000;
	DRAM_REG[124] = 0x00000000;
	DRAM_REG[125] = 0x00000000;
	DRAM_REG[126] = 0x00000000;
	DRAM_REG[127] = 0x00000000;
	DRAM_REG[128] = 0x00000000;
	DRAM_REG[129] = 0x00000000;
	DRAM_REG[130] = 0x00000000;
	DRAM_REG[131] = 0x00000000;
	DRAM_REG[132] = 0x00000000;
	DRAM_REG[133] = 0x00000000;
	DRAM_REG[134] = 0x00000000;
	DRAM_REG[135] = 0x00000000;
	DRAM_REG[136] = 0x00000000;
	DRAM_REG[137] = 0x00000000;
	DRAM_REG[138] = 0x00000000;
	DRAM_REG[139] = 0x00000000;
	DRAM_REG[140] = 0x00000000;
	DRAM_REG[141] = 0x00000000;
	DRAM_REG[142] = 0x00000000;
	DRAM_REG[143] = 0x00000000;
	DRAM_REG[144] = 0x00000000;
	DRAM_REG[145] = 0x00000000;
	DRAM_REG[146] = 0x00000000;
	DRAM_REG[147] = 0x00000000;
	DRAM_REG[148] = 0x00000000;
	DRAM_REG[149] = 0x00000000;
	DRAM_REG[150] = 0x00000000;
	DRAM_REG[151] = 0x00000000;
	DRAM_REG[152] = 0x00000000;
	DRAM_REG[153] = 0x00000000;
	DRAM_REG[154] = 0x00000000;
	DRAM_REG[155] = 0x00000000;
	DRAM_REG[156] = 0x00000000;
	DRAM_REG[157] = 0x00000000;
	DRAM_REG[158] = 0x00000000;
	DRAM_REG[159] = 0x00000000;
	DRAM_REG[160] = 0x00000000;
	DRAM_REG[161] = 0x00000000;
	DRAM_REG[162] = 0x00010000;
	DRAM_REG[163] = 0x00030404;
	DRAM_REG[164] = 0x00000003;
	DRAM_REG[165] = 0x00000000;
	DRAM_REG[166] = 0x00000000;
	DRAM_REG[167] = 0x00000000;
	DRAM_REG[168] = 0x00000000;
	DRAM_REG[169] = 0x00000000;
	DRAM_REG[170] = 0x00000000;
	DRAM_REG[171] = 0x01010000;
	DRAM_REG[172] = 0x01000000;
	DRAM_REG[173] = 0x03030000;
	DRAM_REG[174] = 0x00010303;
	DRAM_REG[175] = 0x01020202;
	DRAM_REG[176] = 0x00000000;
	DRAM_REG[177] = 0x02040303;
	DRAM_REG[178] = 0x21002103;
	DRAM_REG[179] = 0x00061200;
	DRAM_REG[180] = 0x06120612;
	DRAM_REG[181] = 0x04420442;
	DRAM_REG[182] = 0x04420442;
	DRAM_REG[183] = 0x00040004;
	DRAM_REG[184] = 0x00040004;
	DRAM_REG[185] = 0x00000000;
	DRAM_REG[186] = 0x00000000;
	DRAM_REG[187] = 0x00000000;
	DRAM_REG[188] = 0x00000000;
	DRAM_REG[189] = 0xffffffff;

}
