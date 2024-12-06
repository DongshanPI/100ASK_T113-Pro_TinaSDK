// SPDX-License-Identifier: GPL-2.0+
/*
 * FB driver for the ST7789V LCD Controller
 *
 * Copyright (C) 2015 Dennis Menschel
 */

#include <linux/bitops.h>
#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/completion.h>
#include <linux/module.h>

#include <video/mipi_display.h>

#include "fbtft.h"

#define DRVNAME "fb_st7789v"

#define DEFAULT_GAMMA \
	"70 2C 2E 15 10 09 48 33 53 0B 19 18 20 25\n" \
	"70 2C 2E 15 10 09 48 33 53 0B 19 18 20 25"

#define HSD20_IPS_GAMMA \
	"D0 05 0A 09 08 05 2E 44 45 0F 17 16 2B 33\n" \
	"D0 05 0A 09 08 05 2E 43 45 0F 16 16 2B 33"

#define HSD20_IPS 1

/**
 * enum st7789v_command - ST7789V display controller commands
 *
 * @PORCTRL: porch setting
 * @GCTRL: gate control
 * @VCOMS: VCOM setting
 * @VDVVRHEN: VDV and VRH command enable
 * @VRHS: VRH set
 * @VDVS: VDV set
 * @VCMOFSET: VCOM offset set
 * @PWCTRL1: power control 1
 * @PVGAMCTRL: positive voltage gamma control
 * @NVGAMCTRL: negative voltage gamma control
 *
 * The command names are the same as those found in the datasheet to ease
 * looking up their semantics and usage.
 *
 * Note that the ST7789V display controller offers quite a few more commands
 * which have been omitted from this list as they are not used at the moment.
 * Furthermore, commands that are compliant with the MIPI DCS have been left
 * out as well to avoid duplicate entries.
 */
enum st7789v_command {
	PORCTRL = 0xB2,
	GCTRL = 0xB7,
	VCOMS = 0xBB,
	VDVVRHEN = 0xC2,
	VRHS = 0xC3,
	VDVS = 0xC4,
	VCMOFSET = 0xC5,
	PWCTRL1 = 0xD0,
	PVGAMCTRL = 0xE0,
	NVGAMCTRL = 0xE1,
};

#define MADCTL_BGR BIT(3) /* bitmask for RGB/BGR order */
#define MADCTL_MV BIT(5) /* bitmask for page/column order */
#define MADCTL_MX BIT(6) /* bitmask for column address order */
#define MADCTL_MY BIT(7) /* bitmask for page address order */

/* 60Hz for 16.6ms, configured as 2*16.6ms */
#define PANEL_TE_TIMEOUT_MS  33

static struct completion panel_te; /* completion for panel TE line */
static int irq_te; /* Linux IRQ for LCD TE line */

static irqreturn_t panel_te_handler(int irq, void *data)
{
	complete(&panel_te);
	return IRQ_HANDLED;
}

/**
 * init_display() - initialize the display controller
 *
 * @par: FBTFT parameter object
 *
 * Most of the commands in this init function set their parameters to the
 * same default values which are already in place after the display has been
 * powered up. (The main exception to this rule is the pixel format which
 * would default to 18 instead of 16 bit per pixel.)
 * Nonetheless, this sequence can be used as a template for concrete
 * displays which usually need some adjustments.
 *
 * Return: 0 on success, < 0 if error occurred.
 */
static int init_display(struct fbtft_par *par)
{
	par->fbtftops.reset(par);
	mdelay(50);
	write_reg(par,0x36,0x00);
	//write_reg(par,0x36,0x40);
	write_reg(par,0x3A,0x05);
	write_reg(par,0xB2,0x1F,0x1F,0x00,0x33,0x33);
	write_reg(par,0xB7,0x35);
	write_reg(par,0xBB,0x20);
	write_reg(par,0xC0,0x2C);
	write_reg(par,0xC2,0x01);
	write_reg(par,0xC3,0x01);
	write_reg(par,0xC4,0x18);
	write_reg(par,0xC6,0x13);
	write_reg(par,0xD0,0xA4,0xA1);
	write_reg(par,0xE0,0xF0,0x04,0x07,0x04,0x04,0x04,0x25,0x33,0x3C,0x36,0x14,0x12,0x29,0x30);
	write_reg(par,0xE1,0xF0,0x02,0x04,0x05,0x05,0x21,0x25,0x32,0x3B,0x38,0x12,0x14,0x27,0x31);
	write_reg(par,0xE4,0x1D,0x00,0x00);
	write_reg(par,0x21);
	write_reg(par,0x11);
	mdelay(50);
	write_reg(par,0x29);
	mdelay(200);
	return 0;
}

/*
 * write_vmem() - write data to display.
 * @par: FBTFT parameter object.
 * @offset: offset from screen_buffer.
 * @len: the length of data to be writte.
 *
 * Return: 0 on success, or a negative error code otherwise.
 */
static int write_vmem(struct fbtft_par *par, size_t offset, size_t len)
{
	struct device *dev = par->info->device;
	int ret;

	if (irq_te) {
		enable_irq(irq_te);
		reinit_completion(&panel_te);
		ret = wait_for_completion_timeout(&panel_te,
				msecs_to_jiffies(PANEL_TE_TIMEOUT_MS));
		if (ret == 0)
			dev_err(dev, "wait panel TE timeout\n");

		disable_irq(irq_te);
	}

	switch (par->pdata->display.buswidth) {
		case 8:
			ret = fbtft_write_vmem16_bus8(par, offset, len);
			break;
		case 9:
			ret = fbtft_write_vmem16_bus9(par, offset, len);
			break;
		case 16:
			ret = fbtft_write_vmem16_bus16(par, offset, len);
			break;
		default:
			dev_err(dev, "Unsupported buswidth %d\n",
					par->pdata->display.buswidth);
			ret = 0;
			break;
	}

	return ret;
}

/**
 * set_var() - apply LCD properties like rotation and BGR mode
 *
 * @par: FBTFT parameter object
 *
 * Return: 0 on success, < 0 if error occurred.
 */
static int set_var(struct fbtft_par *par)
{
	u8 madctl_par = 0;

	if (par->bgr)
		madctl_par |= MADCTL_BGR;
	switch (par->info->var.rotate) {
		case 0:
			madctl_par |= MADCTL_MX;
			break;
		case 90:
			madctl_par |= (MADCTL_MV | MADCTL_MY);
			break;
		case 180:
			madctl_par |= (MADCTL_MX | MADCTL_MY);
			break;
		case 270:
			madctl_par |= (MADCTL_MV | MADCTL_MX);
			break;
		default:
			return -EINVAL;
	}
	write_reg(par, MIPI_DCS_SET_ADDRESS_MODE, madctl_par);
	return 0;
}

/**
 * set_gamma() - set gamma curves
 *
 * @par: FBTFT parameter object
 * @curves: gamma curves
 *
 * Before the gamma curves are applied, they are preprocessed with a bitmask
 * to ensure syntactically correct input for the display controller.
 * This implies that the curves input parameter might be changed by this
 * function and that illegal gamma values are auto-corrected and not
 * reported as errors.
 *
 * Return: 0 on success, < 0 if error occurred.
 */
static int set_gamma(struct fbtft_par *par, u32 *curves)
{
	int i;
	int j;
	int c; /* curve index offset */

	/*
	 * Bitmasks for gamma curve command parameters.
	 * The masks are the same for both positive and negative voltage
	 * gamma curves.
	 */
	static const u8 gamma_par_mask[] = {
		0xFF, /* V63[3:0], V0[3:0]*/
		0x3F, /* V1[5:0] */
		0x3F, /* V2[5:0] */
		0x1F, /* V4[4:0] */
		0x1F, /* V6[4:0] */
		0x3F, /* J0[1:0], V13[3:0] */
		0x7F, /* V20[6:0] */
		0x77, /* V36[2:0], V27[2:0] */
		0x7F, /* V43[6:0] */
		0x3F, /* J1[1:0], V50[3:0] */
		0x1F, /* V57[4:0] */
		0x1F, /* V59[4:0] */
		0x3F, /* V61[5:0] */
		0x3F, /* V62[5:0] */
	};

	for (i = 0; i < par->gamma.num_curves; i++) {
		c = i * par->gamma.num_values;
		for (j = 0; j < par->gamma.num_values; j++)
			curves[c + j] &= gamma_par_mask[j];
		write_reg(par, PVGAMCTRL + i,
				curves[c + 0],  curves[c + 1],  curves[c + 2],
				curves[c + 3],  curves[c + 4],  curves[c + 5],
				curves[c + 6],  curves[c + 7],  curves[c + 8],
				curves[c + 9],  curves[c + 10], curves[c + 11],
				curves[c + 12], curves[c + 13]);
	}
	return 0;
}

/**
 * blank() - blank the display
 *
 * @par: FBTFT parameter object
 * @on: whether to enable or disable blanking the display
 *
 * Return: 0 on success, < 0 if error occurred.
 */
static int blank(struct fbtft_par *par, bool on)
{
	if (on)
		write_reg(par, MIPI_DCS_SET_DISPLAY_OFF);
	else
		write_reg(par, MIPI_DCS_SET_DISPLAY_ON);
	return 0;
}

static void set_addr_win(struct fbtft_par *par, int xs, int ys, int xe, int ye)
{
	switch(par->info->var.rotate)
	{
		case   0:
			break;
		case  90: 
			xs+=80;xe+=80;
			break;
		case 180:
			break;
		case 270: 
			xs+=80;xe+=80;
			break;
		default :
			break;
	}
	write_reg(par, MIPI_DCS_SET_COLUMN_ADDRESS,
			(xs >> 8) & 0xFF, xs & 0xFF, (xe >> 8) & 0xFF, xe & 0xFF);

	write_reg(par, MIPI_DCS_SET_PAGE_ADDRESS,
			(ys >> 8) & 0xFF, ys & 0xFF, (ye >> 8) & 0xFF, ye & 0xFF);

	write_reg(par, MIPI_DCS_WRITE_MEMORY_START);
}

static void reset(struct fbtft_par *par)
{
	if (!par->gpio.reset)
		return;
	gpiod_set_value_cansleep(par->gpio.reset, 1);
	msleep(10);
	gpiod_set_value_cansleep(par->gpio.reset, 0);
	msleep(200);
	gpiod_set_value_cansleep(par->gpio.reset, 1);
	msleep(10);
	gpiod_set_value_cansleep(par->gpio.cs, 1);  /* Activate chip */

	msleep(10);
	gpiod_set_value_cansleep(par->gpio.latch, 1);
}

static struct fbtft_display display = {
	.regwidth = 8,
	.width = 320,
	.height = 480,
	.gamma_num = 2,
	.gamma_len = 14,
	.gamma = HSD20_IPS_GAMMA,
	.fbtftops = {
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.write_vmem = write_vmem,
		.set_var = set_var,
		.set_gamma = set_gamma,
		.blank = blank,
		.reset = reset,
	},
};

FBTFT_REGISTER_DRIVER(DRVNAME, "sitronix,st7789v", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:st7789v");
MODULE_ALIAS("platform:st7789v");

MODULE_DESCRIPTION("FB driver for the ST7789V LCD Controller");
MODULE_AUTHOR("Dennis Menschel");
MODULE_LICENSE("GPL");
