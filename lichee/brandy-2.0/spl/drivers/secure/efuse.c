
/*
 * (C) Copyright 2018
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * wangwei <wangwei@allwinnertech.com>
 */

#include <common.h>
#include <errno.h>
#include <arch/efuse.h>
#include <asm/io.h>

#define SID_OP_LOCK  (0xAC)

void sid_read_work_status(void)
{
#ifdef SID_WORK_STATUS
	while (readl(SID_PRCTL) & (0x1 << SID_WORK_STATUS)) {
	};
#endif
}

uint sid_sram_read(uint key_index)
{
	return readl(SID_EFUSE+key_index);
}

uint sid_read_key(uint key_index)
{
	uint reg_val;

	sid_read_work_status();

	reg_val = readl(SID_PRCTL);
	reg_val &= ~((0x1ff<<16)|0x3);
	reg_val |= key_index<<16;
	writel(reg_val, SID_PRCTL);

	reg_val &= ~((0xff<<8)|0x3);
	reg_val |= (SID_OP_LOCK<<8) | 0x2;
	writel(reg_val, SID_PRCTL);

	while (readl(SID_PRCTL) & 0x2) {
	};

	reg_val &= ~((0x1ff<<16)|(0xff<<8)|0x3);
	writel(reg_val, SID_PRCTL);

	reg_val = readl(SID_RDKEY);

	return reg_val;
}

void sid_program_key(uint key_index, uint key_value)
{
	uint reg_val;
#ifdef EFUSE_HV_SWITCH
	reg_val = readl(EFUSE_HV_SWITCH);
	reg_val |= (0x1 << 0);
	writel(reg_val, EFUSE_HV_SWITCH);
#endif

	sid_read_work_status();

	writel(key_value, SID_PRKEY);

	reg_val = readl(SID_PRCTL);
	reg_val &= ~((0x1ff<<16)|0x3);
	reg_val |= key_index<<16;
	writel(reg_val, SID_PRCTL);

	reg_val &= ~((0xff<<8)|0x3);
	reg_val |= (SID_OP_LOCK<<8) | 0x1;
	writel(reg_val, SID_PRCTL);

	while (readl(SID_PRCTL) & 0x1) {
	};

	reg_val &= ~((0x1ff<<16)|(0xff<<8)|0x3);
	writel(reg_val, SID_PRCTL);
#ifdef EFUSE_HV_SWITCH
	reg_val = readl(EFUSE_HV_SWITCH);
	reg_val &= ~(0x1 << 0);
	writel(reg_val, EFUSE_HV_SWITCH);
#endif
	return;
}

void sid_read_rotpk(void *dst)
{
	uint chipid_index = EFUSE_ROTPK;
	uint id_length = 32;
	uint i = 0;
	for (i = 0; i < id_length; i += 4) {
		*(u32 *)dst = sid_read_key(chipid_index + i);
		dst += 4;
	}
	return ;
}

void sid_set_security_mode(void)
{
	uint reg_val;

	reg_val  = sid_read_key(EFUSE_LCJS);
	reg_val |= (0x01 << 11);
	sid_program_key(EFUSE_LCJS, reg_val);
	reg_val = (sid_read_key(EFUSE_LCJS) >> 11) & 1;

	printf("burn finished,secure mode: %d\n", reg_val);

	return;
}

void sid_disable_jtag(void)
{
	writel(JTAG_AT_SOURCE, SJTAG_S);
	writel(JTAG_DEVICEEN, SJTAG_AT1);
}

int sid_probe_security_mode(void)
{
	return readl(SID_SECURE_MODE) & 1;
}
