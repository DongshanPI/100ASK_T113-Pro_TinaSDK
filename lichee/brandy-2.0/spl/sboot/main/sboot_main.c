/*
 * (C) Copyright 2007-2013
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * Jerry Wang <wangflord@allwinnertech.com>
 * wangwei <wangwei@allwinnertech.com>
 */

#include <common.h>
#include <private_boot0.h>
#include <private_uboot.h>
#include <private_toc.h>
#include <arch/clock.h>
#include <arch/uart.h>
#include <arch/dram.h>
#include <arch/gpio.h>
#include <arch/rtc.h>
#include <arch/efuse.h>
#include "sboot_flash.h"
#include "sboot_toc.h"

sbrom_toc0_config_t *toc0_config = (sbrom_toc0_config_t *)(CONFIG_TOC0_CFG_ADDR);
phys_addr_t mmc_config_addr = (phys_addr_t)(((sbrom_toc0_config_t *)CONFIG_TOC0_CFG_ADDR)->storage_data + 160);

static int sboot_clear_env(void);

static void print_commit_log(void)
{
	printf("HELLO! SBOOT is starting!\n");
	printf("sboot commit : %s \n",sboot_head.hash);
	sunxi_set_printf_debug_mode(toc0_config->debug_mode, 0);
}

void sboot_main(void)
{
	toc0_private_head_t *toc0 = (toc0_private_head_t *)CONFIG_TOC0_HEAD_BASE;
	uint dram_size;
	u16 pmu_type = 0, key_input = 0; /* TODO: set real value */
	int  ret;

	sunxi_board_init_early();
	sunxi_serial_init(toc0_config->uart_port, toc0_config->uart_ctrl, 2);
	print_commit_log();

	ret = sunxi_board_init();
	if (ret)
		goto _BOOT_ERROR;

	if (rtc_probe_fel_flag()) {
		rtc_clear_fel_flag();
		goto _BOOT_ERROR;
#ifdef CFG_SUNXI_PHY_KEY
	} else if (check_update_key(&key_input)) {
		goto _BOOT_ERROR;
#endif
	}

	if (toc0_config->enable_jtag) {
		printf("enable_jtag\n");
		boot_set_gpio((normal_gpio_cfg *)toc0_config->jtag_gpio, 5, 1);
	}
#if CFG_SUNXI_JTAG_DISABLE
	else {
		sid_disable_jtag();
	}
#endif

	char uart_input_value = get_uart_input();

	if (uart_input_value == '2') {
		sunxi_set_printf_debug_mode(3, 0);
		printf("detected user input 2\n");
		goto _BOOT_ERROR;
	} else if (uart_input_value == 'd') {
		sunxi_set_printf_debug_mode(8, 1);
		printf("detected user input d\n");
	} else if (uart_input_value == 'q') {
		printf("detected user input q\n");
		sunxi_set_printf_debug_mode(0, 1);
	}

#ifdef FPGA_PLATFORM
	dram_size = mctl_init((void *)toc0_config->dram_para);
#else
	dram_size = init_DRAM(0, (void *)toc0_config->dram_para);
#endif
	if (!dram_size) {
		printf("init dram fail\n");
		goto _BOOT_ERROR;
	} else {
		printf("dram size =%d\n", dram_size);
	}

	mmu_enable(dram_size);
	malloc_init(CONFIG_HEAP_BASE, CONFIG_HEAP_SIZE);

	ret = sunxi_board_late_init();
	if (ret)
		goto _BOOT_ERROR;

	if (toc0->platform[0] & 0xf0)
		printf("read toc0 from emmc backup\n");

	ret = sunxi_flash_init(toc0->platform[0] & 0x0f);
	if (ret)
		goto _BOOT_ERROR;

	ret = toc1_init();
	if (ret)
		goto _BOOT_ERROR;

	ret = toc1_verify_and_run(dram_size, pmu_type, uart_input_value, key_input);
	if (ret)
		goto _BOOT_ERROR;

_BOOT_ERROR:
	sboot_clear_env();
	boot0_jmp(SECURE_FEL_BASE);
}

static int sboot_clear_env(void)
{
	sunxi_board_exit();
	sunxi_board_clock_reset();
	mmu_disable();
	mdelay(10);
	return 0;
}
