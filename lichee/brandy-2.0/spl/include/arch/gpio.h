/*
 * (C) Copyright 2007-2012
* SPDX-License-Identifier:	GPL-2.0+
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * Tom Cubie <tangliang@allwinnertech.com>
 */

#ifndef _SUNXI_GPIO_H
#define _SUNXI_GPIO_H

#include <linux/types.h>
#include <arch/cpu.h>

/*
 * sunxi has 9 banks of gpio, they are:
 * PA0 - PA17 | PB0 - PB23 | PC0 - PC24
 * PD0 - PD27 | PE0 - PE31 | PF0 - PF5
 * PG0 - PG9  | PH0 - PH27 | PI0 - PI12
 */

#define SUNXI_GPIO_A	0
#define SUNXI_GPIO_B	1
#define SUNXI_GPIO_C	2
#define SUNXI_GPIO_D	3
#define SUNXI_GPIO_E	4
#define SUNXI_GPIO_F	5
#define SUNXI_GPIO_G	6
#define SUNXI_GPIO_H	7
#define SUNXI_GPIO_I	8

/*
 * This defines the number of GPIO banks for the _main_ GPIO controller.
 * You should fix up the padding in struct sunxi_gpio_reg below if you
 * change this.
 */
#define SUNXI_GPIO_BANKS 9

/*
 * sun6i/sun8i and later SoCs have an additional GPIO controller (R_PIO)
 * at a different register offset.
 *
 * sun6i has 2 banks:
 * PL0 - PL8  | PM0 - PM7
 *
 * sun8i has 1 bank:
 * PL0 - PL11
 *
 * sun9i has 3 banks:
 * PL0 - PL9  | PM0 - PM15  | PN0 - PN1
 */
#define SUNXI_GPIO_L	11
#define SUNXI_GPIO_M	12
#define SUNXI_GPIO_N	13

#ifdef CFG_SUNXI_GPIO_V2
struct sunxi_gpio {
	u32 cfg[4];
	u32 dat;
	u32 drv[4];
	u32 pull[3];
};
#else
struct sunxi_gpio {
	u32 cfg[4];
	u32 dat;
	u32 drv[2];
	u32 pull[2];
};
#endif

/* gpio interrupt control */
struct sunxi_gpio_int {
	u32 cfg[3];
	u32 ctl;
	u32 sta;
	u32 deb;		/* interrupt debounce */
};

struct sunxi_gpio_reg {
	struct sunxi_gpio gpio_bank[SUNXI_GPIO_BANKS];
	u8 res[0xbc];
	struct sunxi_gpio_int gpio_int;
};

#define BANK_TO_GPIO(bank)	(((bank) < SUNXI_GPIO_L) ? \
	&((struct sunxi_gpio_reg *)SUNXI_PIO_BASE)->gpio_bank[bank] : \
	&((struct sunxi_gpio_reg *)SUNXI_R_PIO_BASE)->gpio_bank[(bank) - SUNXI_GPIO_L])

#define GPIO_BANK(pin)		((pin) >> 5)
#define GPIO_NUM(pin)		((pin) & 0x1f)

#define GPIO_CFG_INDEX(pin)	(((pin) & 0x1f) >> 3)
#define GPIO_CFG_OFFSET(pin)	((((pin) & 0x1f) & 0x7) << 2)

#define GPIO_DRV_INDEX(pin)	(((pin) & 0x1f) >> 4)
#define GPIO_DRV_OFFSET(pin)	((((pin) & 0x1f) & 0xf) << 1)

#define GPIO_PULL_INDEX(pin)	(((pin) & 0x1f) >> 4)
#define GPIO_PULL_OFFSET(pin)	((((pin) & 0x1f) & 0xf) << 1)

/* GPIO bank sizes */
#define SUNXI_GPIO_A_NR		32
#define SUNXI_GPIO_B_NR		32
#define SUNXI_GPIO_C_NR		32
#define SUNXI_GPIO_D_NR		32
#define SUNXI_GPIO_E_NR		32
#define SUNXI_GPIO_F_NR		32
#define SUNXI_GPIO_G_NR		32
#define SUNXI_GPIO_H_NR		32
#define SUNXI_GPIO_I_NR		32
#define SUNXI_GPIO_L_NR		32
#define SUNXI_GPIO_M_NR		32

#define SUNXI_GPIO_NEXT(__gpio) \
	((__gpio##_START) + (__gpio##_NR) + 0)

enum sunxi_gpio_number {
	SUNXI_GPIO_A_START = 0,
	SUNXI_GPIO_B_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_A),
	SUNXI_GPIO_C_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_B),
	SUNXI_GPIO_D_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_C),
	SUNXI_GPIO_E_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_D),
	SUNXI_GPIO_F_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_E),
	SUNXI_GPIO_G_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_F),
	SUNXI_GPIO_H_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_G),
	SUNXI_GPIO_I_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_H),
	SUNXI_GPIO_L_START = 352,
	SUNXI_GPIO_M_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_L),
	SUNXI_GPIO_N_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_M),
	SUNXI_GPIO_AXP0_START = 1024,
};

/* SUNXI GPIO number definitions */
#define SUNXI_GPA(_nr)	(SUNXI_GPIO_A_START + (_nr))
#define SUNXI_GPB(_nr)	(SUNXI_GPIO_B_START + (_nr))
#define SUNXI_GPC(_nr)	(SUNXI_GPIO_C_START + (_nr))
#define SUNXI_GPD(_nr)	(SUNXI_GPIO_D_START + (_nr))
#define SUNXI_GPE(_nr)	(SUNXI_GPIO_E_START + (_nr))
#define SUNXI_GPF(_nr)	(SUNXI_GPIO_F_START + (_nr))
#define SUNXI_GPG(_nr)	(SUNXI_GPIO_G_START + (_nr))
#define SUNXI_GPH(_nr)	(SUNXI_GPIO_H_START + (_nr))
#define SUNXI_GPI(_nr)	(SUNXI_GPIO_I_START + (_nr))
#define SUNXI_GPL(_nr)	(SUNXI_GPIO_L_START + (_nr))
#define SUNXI_GPM(_nr)	(SUNXI_GPIO_M_START + (_nr))
#define SUNXI_GPN(_nr)	(SUNXI_GPIO_N_START + (_nr))

#define SUNXI_GPAXP0(_nr)	(SUNXI_GPIO_AXP0_START + (_nr))

/* GPIO pin function config */
#define SUNXI_GPIO_INPUT	0
#define SUNXI_GPIO_OUTPUT	1
#define SUNXI_GPIO_DISABLE	7

#define SUNXI_GPA_EMAC		2
#define SUN6I_GPA_GMAC		2
#define SUN7I_GPA_GMAC		5
#define SUN6I_GPA_SDC2		5
#define SUN6I_GPA_SDC3		4
#define SUN8I_H3_GPA_UART0	2

#define SUN4I_GPB_PWM		2
#define SUN4I_GPB_TWI0		2
#define SUN4I_GPB_TWI1		2
#define SUN5I_GPB_TWI1		2
#define SUN4I_GPB_TWI2		2
#define SUN5I_GPB_TWI2		2
#define SUN4I_GPB_UART0		2
#define SUN5I_GPB_UART0		2
#define SUN8I_GPB_UART2		2
#define SUN8I_A33_GPB_UART0	3
#define SUN8I_A83T_GPB_UART0	2
#define SUN8I_V3S_GPB_UART0	3
#define SUN50I_GPB_UART0	4

#define SUNXI_GPC_NAND		2
#define SUNXI_GPC_SPI0		3
#define SUNXI_GPC_SDC2		3
#define SUN6I_GPC_SDC3		4
#define SUN50I_GPC_SPI0		4
#define SUN20I_GPC_SPI0		2

#define SUN8I_GPD_SDC1		3
#define SUNXI_GPD_LCD0		2
#define SUNXI_GPD_LVDS0		3

#define SUN5I_GPE_SDC2		3
#define SUN8I_GPE_TWI2		3

#define SUNXI_GPF_SDC0		2
#define SUNXI_GPF_UART0		4
#define SUN8I_GPF_UART0		3

#define SUN4I_GPG_SDC1		4
#define SUN5I_GPG_SDC1		2
#define SUN6I_GPG_SDC1		2
#define SUN8I_GPG_SDC1		2
#define SUN6I_GPG_TWI3		2
#define SUN5I_GPG_UART1		4

#define SUN6I_GPH_PWM		2
#define SUN8I_GPH_PWM		2
#define SUN4I_GPH_SDC1		5
#define SUN6I_GPH_TWI0		2
#define SUN8I_GPH_TWI0		2
#define SUN6I_GPH_TWI1		2
#define SUN8I_GPH_TWI1		2
#define SUN6I_GPH_TWI2		2
#define SUN6I_GPH_UART0		2
#define SUN9I_GPH_UART0		2

#define SUNXI_GPI_SDC3		2
#define SUN7I_GPI_TWI3		3
#define SUN7I_GPI_TWI4		3

#define SUN6I_GPL0_R_P2WI_SCK	3
#define SUN6I_GPL1_R_P2WI_SDA	3

#define SUN8I_GPL_R_RSB		2
#define SUN8I_H3_GPL_R_TWI	2
#define SUN8I_A23_GPL_R_TWI	3
#define SUN8I_GPL_R_UART	2

#define SUN9I_GPN_R_RSB		3

/* GPIO pin pull-up/down config */
#define SUNXI_GPIO_PULL_DISABLE	0
#define SUNXI_GPIO_PULL_UP	1
#define SUNXI_GPIO_PULL_DOWN	2

/* Virtual AXP0 GPIOs */
#define SUNXI_GPIO_AXP0_PREFIX "AXP0-"
#define SUNXI_GPIO_AXP0_VBUS_DETECT	4
#define SUNXI_GPIO_AXP0_VBUS_ENABLE	5
#define SUNXI_GPIO_AXP0_GPIO_COUNT	6

void sunxi_gpio_set_cfgbank(struct sunxi_gpio *pio, int bank_offset, u32 val);
void sunxi_gpio_set_cfgpin(u32 pin, u32 val);
int sunxi_gpio_get_cfgbank(struct sunxi_gpio *pio, int bank_offset);
int sunxi_gpio_get_cfgpin(u32 pin);
int sunxi_gpio_set_drv(u32 pin, u32 val);
int sunxi_gpio_set_pull(u32 pin, u32 val);
int sunxi_name_to_gpio_bank(const char *name);
int sunxi_name_to_gpio(const char *name);
#define name_to_gpio(name) sunxi_name_to_gpio(name)


#define GPIO_REG_READ(reg)              readl((reg))
#define GPIO_REG_WRITE(reg, value)      writel((value), (reg))

#ifdef CFG_SUNXI_GPIO_V2
#define PIOC_REG_o_CFG0                 (0x00)
#define PIOC_REG_o_CFG1                 (0x04)
#define PIOC_REG_o_CFG2                 (0x08)
#define PIOC_REG_o_CFG3                 (0x0C)
#define PIOC_REG_o_DATA                 (0x10)
#define PIOC_REG_o_DRV0                 (0x14)
#define PIOC_REG_o_DRV1                 (0x18)
#define PIOC_REG_o_DRV2                 (0x1C)
#define PIOC_REG_o_DRV3                 (0x20)
#define PIOC_REG_o_PUL0                 (0x24)
#define PIOC_REG_o_PUL1                 (0x28)
#define PIOC_o_OFFSET					(0x30)

#define PIO_CFG_MASK					(0xF)
#else
#define PIOC_REG_o_CFG0                 (0x00)
#define PIOC_REG_o_CFG1                 (0x04)
#define PIOC_REG_o_CFG2                 (0x08)
#define PIOC_REG_o_CFG3                 (0x0C)
#define PIOC_REG_o_DATA                 (0x10)
#define PIOC_REG_o_DRV0                 (0x14)
#define PIOC_REG_o_DRV1                 (0x18)
#define PIOC_REG_o_PUL0                 (0x1C)
#define PIOC_REG_o_PUL1                 (0x20)
#define PIOC_o_OFFSET					(0x24)

#define PIO_CFG_MASK					(0x7)
#endif

/**#############################################################################################################
 *
 *                           GPIO(PIN) Operations
 *
-##############################################################################################################*/
#define PIO_REG_CFG(n, i)               ((volatile unsigned int *)((phys_addr_t)SUNXI_PIO_BASE + ((n)-1) * PIOC_o_OFFSET + ((i)<<2) + PIOC_REG_o_CFG0))
#define PIO_REG_DLEVEL(n, i)            ((volatile unsigned int *)((phys_addr_t)SUNXI_PIO_BASE + ((n)-1) * PIOC_o_OFFSET + ((i)<<2) + PIOC_REG_o_DRV0))
#define PIO_REG_PULL(n, i)              ((volatile unsigned int *)((phys_addr_t)SUNXI_PIO_BASE + ((n)-1) * PIOC_o_OFFSET + ((i)<<2) + PIOC_REG_o_PUL0))
#define PIO_REG_DATA(n)                 ((volatile unsigned int *)((phys_addr_t)SUNXI_PIO_BASE + ((n)-1) * PIOC_o_OFFSET + PIOC_REG_o_DATA))
#define PIO_ONE_PIN_DATA(n, i)		(((*(volatile unsigned int *)((phys_addr_t)SUNXI_PIO_BASE + ((n) - 1) * PIOC_o_OFFSET + PIOC_REG_o_DATA)) & (1 << i)) >> i)

#define PIO_REG_CFG_VALUE(n, i)          readl(SUNXI_PIO_BASE + ((n)-1) * PIOC_o_OFFSET + ((i)<<2) + PIOC_REG_o_CFG0)
#define PIO_REG_DLEVEL_VALUE(n, i)       readl(SUNXI_PIO_BASE + ((n)-1) * PIOC_o_OFFSET + ((i)<<2) + PIOC_REG_o_DRV0)
#define PIO_REG_PULL_VALUE(n, i)         readl(SUNXI_PIO_BASE + ((n)-1) * PIOC_o_OFFSET + ((i)<<2) + PIOC_REG_o_PUL0)
#define PIO_REG_DATA_VALUE(n)            readl(SUNXI_PIO_BASE + ((n)-1) * PIOC_o_OFFSET + PIOC_REG_o_DATA)
#define PIO_REG_BASE(n)                  ((volatile unsigned int *)((phys_addr_t)SUNXI_PIO_BASE +((n)-1) * PIOC_o_OFFSET))

#ifdef SUNXI_R_PIO_BASE
#define R_PIO_REG_CFG(n, i)               ((volatile unsigned int *)((phys_addr_t)SUNXI_R_PIO_BASE + ((n)-12) * PIOC_o_OFFSET + ((i)<<2) + PIOC_REG_o_CFG0))
#define R_PIO_REG_DLEVEL(n, i)            ((volatile unsigned int *)((phys_addr_t)SUNXI_R_PIO_BASE + ((n)-12) * PIOC_o_OFFSET + ((i)<<2) + PIOC_REG_o_DRV0))
#define R_PIO_REG_PULL(n, i)              ((volatile unsigned int *)((phys_addr_t)SUNXI_R_PIO_BASE + ((n)-12) * PIOC_o_OFFSET + ((i)<<2) + PIOC_REG_o_PUL0))
#define R_PIO_REG_DATA(n)                 ((volatile unsigned int *)((phys_addr_t)SUNXI_R_PIO_BASE + ((n)-12) * PIOC_o_OFFSET + PIOC_REG_o_DATA))

#define R_PIO_REG_CFG_VALUE(n, i)          readl(SUNXI_R_PIO_BASE + ((n)-12) * PIOC_o_OFFSET + ((i)<<2) + PIOC_REG_o_CFG0)
#define R_PIO_REG_DLEVEL_VALUE(n, i)       readl(SUNXI_R_PIO_BASE + ((n)-12) * PIOC_o_OFFSET + ((i)<<2) + PIOC_REG_o_DRV0)
#define R_PIO_REG_PULL_VALUE(n, i)         readl(SUNXI_R_PIO_BASE + ((n)-12) * PIOC_o_OFFSET + ((i)<<2) + PIOC_REG_o_PUL0)
#define R_PIO_REG_DATA_VALUE(n)            readl(SUNXI_R_PIO_BASE + ((n)-12) * PIOC_o_OFFSET + PIOC_REG_o_DATA)
#define R_PIO_REG_BASE(n)                  ((volatile unsigned int *)((phys_addr_t)SUNXI_R_PIO_BASE +((n)-12) * PIOC_o_OFFSET))
#endif


/* struct for gpio */
typedef struct
{
    unsigned char      port;
    unsigned char      port_num;
    char               mul_sel;
    char               pull;
    char               drv_level;
    char               data;
    unsigned char      reserved[2];
}
normal_gpio_set_t;

int boot_set_gpio(void  *user_gpio_list, u32 group_count_max, int set_gpio);

#endif /* _SUNXI_GPIO_H */
