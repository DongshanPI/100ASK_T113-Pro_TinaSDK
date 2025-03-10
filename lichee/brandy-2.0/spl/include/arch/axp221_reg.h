/*
 * (C) Copyright 2012 Henrik Nordstrom <henrik@henriknordstrom.net>
* SPDX-License-Identifier:	GPL-2.0+
 *
 * (C) Copyright 2007-2011
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * wangwei <wangwei@allwinnertech.com>
 *
 * Some init for sunxi platform.
 *
 */
#ifndef __AXP221_REGS_H__
#define __AXP221_REGS_H__

#include <arch/axp.h>

#define   AXP221_CHIP_ID              (0x06)

#ifdef CFG_SUNXI_TWI
#define AXP221_RUNTIME_ADDR			(0x34)
#define AXP221_DEVICE_ADDR			400000
#else
#define AXP221_RUNTIME_ADDR         (0x2d)
#define AXP221_DEVICE_ADDR          (0x3A3)

#endif

#define AXP221_SUNXI_CPU_VOL	"dcdc2"
#define AXP221_SUNXI_SYS_VOL	"dcdc3"
#define AXP221_SUNXI_DRAM_VOL	"dcdc5"

#define BOOT_POWER221_POWER_KEY_STATUS BOOT_POWER221_INTSTS5
#define BOOT_POWER221_POWER_KEY_OFFSET 0x5

/*define AXP803 REGISTER */
#define   BOOT_POWER221_STATUS              			(0x00)
#define   BOOT_POWER221_MODE_CHGSTATUS      			(0x01)
#define   BOOT_POWER221_OTG_STATUS          			(0x02)
#define   BOOT_POWER221_VERSION         	   			(0x03)
#define   BOOT_POWER221_DATA_BUFFER0        			(0x04)
#define   BOOT_POWER221_DATA_BUFFER1        			(0x05)
#define   BOOT_POWER221_DATA_BUFFER2        			(0x06)
#define   BOOT_POWER221_DATA_BUFFER3        			(0x07)
#define   BOOT_POWER221_DATA_BUFFER4        			(0x08)
#define   BOOT_POWER221_DATA_BUFFER5        			(0x09)
#define   BOOT_POWER221_DATA_BUFFER6        			(0x0a)
#define   BOOT_POWER221_DATA_BUFFER7        			(0x0b)
#define   BOOT_POWER221_DATA_BUFFER8        			(0x0c)
#define   BOOT_POWER221_DATA_BUFFER9        			(0x0d)
#define   BOOT_POWER221_DATA_BUFFER10       			(0x0e)
#define   BOOT_POWER221_DATA_BUFFER11       			(0x0f)
#define   BOOT_POWER221_OUTPUT_CTL1     	   			(0x10)
#define   BOOT_POWER221_OUTPUT_CTL2     	   			(0x12)
#define   BOOT_POWER221_ALDO_CTL     	   			    (0x13)
#define   BOOT_POWER221_DLDO1_VOL                       (0x15)
#define   BOOT_POWER221_DLDO2_VOL                       (0x16)
#define   BOOT_POWER221_DLDO3_VOL                       (0x17)
#define   BOOT_POWER221_DLDO4_VOL                       (0x18)

#define   BOOT_POWER221_ELDO1_VOL                       (0x19)
#define   BOOT_POWER221_ELDO2_VOL                       (0x1A)
#define   BOOT_POWER221_ELDO3_VOL                       (0x1B)
#define   BOOT_POWER221_DC5LDO3_VOL                     (0x1C)

#define   BOOT_POWER221_DC1OUT_VOL                  	(0x21)
#define   BOOT_POWER221_DC2OUT_VOL          			(0x22)
#define   BOOT_POWER221_DC3OUT_VOL          			(0x23)
#define   BOOT_POWER221_DC4OUT_VOL          			(0x24)
#define   BOOT_POWER221_DC5OUT_VOL          			(0x25)


#define   BOOT_POWER221_DC23_DVM_CTL          			(0x27)
#define   BOOT_POWER221_ALDO1OUT_VOL                    (0x28)
#define   BOOT_POWER221_ALDO2OUT_VOL                    (0x29)
#define   BOOT_POWER221_ALDO3OUT_VOL                    (0x2A)

#define   BOOT_POWER221_VBUS_SET             			(0x30)
#define   BOOT_POWER221_VOFF_SET            			(0x31)
#define   BOOT_POWER221_OFF_CTL             			(0x32)
#define   BOOT_POWER221_CHARGE1             			(0x33)
#define   BOOT_POWER221_CHARGE2             			(0x34)
#define   BOOT_POWER221_CHARGE3             			(0x35)

#define   BOOT_POWER221_BAT_AVERVOL_H8                  (0x78)
#define   BOOT_POWER221_BAT_AVERVOL_L4                  (0x79)

#define   BOOT_POWER221_DCDC_MODESET        			(0x80)
#define   BOOT_POWER221_VOUT_MONITOR        			(0x81)
#define   BOOT_POWER221_ADC_EN             			    (0x82)
#define   BOOT_POWER221_ADC_SPEED_TS           			(0x84)
#define   BOOT_POWER221_ADC_SPEED      			        (0x85)
#define   BOOT_POWER221_TIMER_CTL           			(0x8A)
#define   BOOT_POWER221_HOTOVER_CTL         			(0x8F)
#define   BOOT_POWER221_GPIO0_CTL           			(0x90)
#define   BOOT_POWER221_GPIO0_VOL           			(0x91)
#define   BOOT_POWER221_GPIO1_CTL           			(0x92)
#define   BOOT_POWER221_GPIO1_VOL           			(0x93)
#define   BOOT_POWER221_GPIO012_SIGNAL      			(0x94)

#define   BOOT_POWER221_GPIO012_PDCTL       			(0x97)

#define   BOOT_POWER221_INTEN1              			(0x40)
#define   BOOT_POWER221_INTEN2              			(0x41)
#define   BOOT_POWER221_INTEN3              			(0x42)
#define   BOOT_POWER221_INTEN4              			(0x43)
#define   BOOT_POWER221_INTEN5              			(0x44)

#define   BOOT_POWER221_INTSTS1             			(0x48)
#define   BOOT_POWER221_INTSTS2             			(0x49)
#define   BOOT_POWER221_INTSTS3             			(0x4a)
#define   BOOT_POWER221_INTSTS4             			(0x4b)
#define   BOOT_POWER221_INTSTS5             			(0x4c)

#define   BOOT_POWER221_FUEL_GAUGE_CTL         			(0xB8)
#define   BOOT_POWER221_BAT_PERCEN_CAL					(0xB9)

#define   BOOT_POWER221_RDC1                			(0xBA)
#define   BOOT_POWER221_RDC0         					(0xBB)
#define   BOOT_POWER221_OCV1                			(0xBC)
#define   BOOT_POWER221_OCV0         					(0xBD)

#define   BOOT_POWER221_BAT_MAX_CAP1   					(0xE0)
#define   BOOT_POWER221_BAT_MAX_CAP0   					(0xE1)
#define   BOOT_POWER221_BAT_COULOMB_CNT1				(0xE2)
#define   BOOT_POWER221_BAT_COULOMB_CNT0				(0xE3)


int axp221_set_power_reset(void);
int axp221_probe_power_key(void);
int axp221_set_ddr_voltage(int set_vol);
int axp221_set_pll_voltage(int set_vol);
int axp221_set_sys_voltage(int set_vol, int onoff);
int axp221_set_sys_voltage_ext(char *name, int set_vol, int onoff);
int axp221_axp_init(u8 power_mode);
int axp221_get_power_source(void);
int axp221_reg_read(u8 addr, u8 *val);
int axp221_reg_write(u8 addr, u8 val);


#endif /* __AXP809_REGS_H__ */
