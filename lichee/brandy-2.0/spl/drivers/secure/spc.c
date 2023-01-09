/*
 * (C) Copyright 2018
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 *
 * wangwei@allwinnertech.com
 */

#include <common.h>
#include <arch/spc.h>


void sunxi_spc_config(void)
{
	writel(0xbe, SPC_SET_REG(0));
	writel(0x7f, SPC_SET_REG(1));
	writel(0x10, SPC_SET_REG(2));
}

void sunxi_spc_set_to_s(uint type)
{
	u8  sub_type0, sub_type1;

	sub_type0 = type & 0xff;
	sub_type1 = (type>>8) & 0xff;

	if(sub_type0)
	{
		writel(sub_type0, SPC_CLEAR_REG(0));
	}
	if(sub_type1)
	{
		writel(sub_type1, SPC_CLEAR_REG(1));
	}
}

uint sunxi_spc_probe_status(uint type)
{
	if(type < 8)
	{
		return (readl(SPC_STATUS_REG(0)) >> type) & 1;
	}
	if(type < 16)
	{
		return (readl(SPC_STATUS_REG(1)) >> type) & 1;
	}

	return 0;
}

