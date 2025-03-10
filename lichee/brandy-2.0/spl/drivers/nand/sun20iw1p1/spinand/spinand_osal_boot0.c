/*
 * (C) Copyright 2017-2020
* SPDX-License-Identifier:	GPL-2.0+
 *Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 *
 */

#include <common.h>
/*#include <asm/arch/gpio.h>*/
#include <private_boot0.h>
#include <asm/io.h>

int SPINAND_Print(const char *str, ...);

#define get_wvalue(addr) (*((volatile unsigned long *)(addr)))
#define put_wvalue(addr, v)             \
	(*((volatile unsigned long *)(addr)) = (unsigned long)(v))

#define spi_readl(a)   readl((volatile void __iomem *)(ulong)a)
#define spi_writel(v, a) writel(v, (volatile void __iomem *)(ulong)a)

#define SPIC0_BASE_ADDR SUNXI_SPI0_BASE
#define CCMU_BASE_ADDR (SUNXI_CCM_BASE)
#define GPIO_BASE_ADDR (SUNXI_PIO_BASE)

__u32 SPINAND_GetIOBaseAddr(void)
{
	return SPIC0_BASE_ADDR;
}

__u32 Getpll6Clk(void)
{
	return 600000000;
}

int SPINAND_ClkRequest(__u32 nand_index)
{
	__u32 cfg;

	/*reset*/
	cfg = spi_readl(CCMU_BASE_ADDR + 0x096c);
	cfg &= (~(0x1 << 16));
	spi_writel(cfg, CCMU_BASE_ADDR + 0x096c);

	cfg = spi_readl(CCMU_BASE_ADDR + 0x096c);
	cfg |= (0x1 << 16);
	spi_writel(cfg, CCMU_BASE_ADDR + 0x096c);

	/*open ahb*/
	cfg = spi_readl(CCMU_BASE_ADDR + 0x096c);
	cfg |= (0x1 << 0);
	spi_writel(cfg, CCMU_BASE_ADDR + 0x096c);
	/*printf("CCMU_BASE_ADDR + 0x096c 0x%x\n",spi_readl(CCMU_BASE_ADDR +
	 * 0x096c));*/

	return 0;
}

void SPINAND_ClkRelease(__u32 nand_index)
{
	return;
}

/*
**********************************************************************************************************************
*
*             NAND_GetCmuClk
*
*  Description:
*
*
*  Parameters:
*
*
*  Return value:
*
*
**********************************************************************************************************************
*/
int SPINAND_SetClk(__u32 nand_index, __u32 nand_clock)
{
	u32 reg_val;
	u32 sclk0_src_sel, sclk0, sclk0_src, sclk0_pre_ratio_n, sclk0_src_t,
	    sclk0_ratio_m;
	u32 sclk0_reg_adr;

	sclk0_reg_adr = (CCMU_BASE_ADDR + 0x0940); /*CCM_SPI0_CLK_REG*/

	/*close dclk and cclk*/
	if (nand_clock == 0) {
		reg_val = spi_readl(sclk0_reg_adr);
		reg_val &= (~(0x1U << 31));
		spi_writel(reg_val, sclk0_reg_adr);

		return 0;
	}

	sclk0_src_sel = 1; /* PLL_PERI(1X) */
	sclk0 = nand_clock;

	sclk0_src = Getpll6Clk() / 1000000;

	/*sclk0_pre_ratio_n*/
	sclk0_pre_ratio_n = 3;
	if (sclk0_src > 4 * 16 * sclk0)
		sclk0_pre_ratio_n = 3;
	else if (sclk0_src > 2 * 16 * sclk0)
		sclk0_pre_ratio_n = 2;
	else if (sclk0_src > 1 * 16 * sclk0)
		sclk0_pre_ratio_n = 1;
	else
		sclk0_pre_ratio_n = 0;

	sclk0_src_t = sclk0_src >> sclk0_pre_ratio_n;

	/*sclk0_ratio_m*/
	sclk0_ratio_m = (sclk0_src_t / (sclk0)) - 1;
	if (sclk0_src_t % (sclk0))
		sclk0_ratio_m += 1;

	/*close clock*/
	reg_val = spi_readl(sclk0_reg_adr);
	reg_val &= (~(0x1U << 31));
	spi_writel(reg_val, sclk0_reg_adr);

	/*configure*/
	reg_val = spi_readl(sclk0_reg_adr);
	/*clock source select*/
	reg_val &= (~(0x7 << 24));
	reg_val |= (sclk0_src_sel & 0x7) << 24;
	/*clock pre-divide ratio(N)*/
	reg_val &= (~(0x3 << 8));
	reg_val |= (sclk0_pre_ratio_n & 0x3) << 8;
	/*clock divide ratio(M)*/
	reg_val &= ~(0xf << 0);
	reg_val |= (sclk0_ratio_m & 0xf) << 0;
	spi_writel(reg_val, sclk0_reg_adr);

	/* open clock*/
	reg_val = spi_readl(sclk0_reg_adr);
	reg_val |= 0x1U << 31;
	spi_writel(reg_val, sclk0_reg_adr);

	/*printf("(NAND_CLK_BASE_ADDR + 0x0940) 0x%x\n",*((__u32
	 * *)sclk0_reg_adr));*/

	return 0;
}

int SPINAND_GetClk(__u32 nand_index)
{
	__u32 pll6_clk;
	__u32 cfg;
	__u32 nand_max_clock;
	__u32 m, n;

	/*set nand clock*/
	pll6_clk = Getpll6Clk();

	/*set nand clock gate on*/
	cfg = spi_readl(CCMU_BASE_ADDR + 0x0940);
	m = ((cfg)&0xf) + 1;
	n = ((cfg >> 8) & 0x3);
	nand_max_clock = pll6_clk / ((1 << n) * m);
	/*printf("(NAND_CLK_BASE_ADDR + 0x0940): 0x%x\n", *(volatile __u32
	 * *)(CCMU_BASE_ADDR + 0x0940));*/

	return nand_max_clock;
}

void SPINAND_PIORequest(__u32 nand_index)
{
#ifndef FPGA_PLATFORM
	u32 reg_val;

	/*spi0_sclk, spi0_cs0, spi0_mosi, spi0_miso, spi0_hold, spi0_wp*/
	reg_val = readl(GPIO_BASE_ADDR + 0x60);
	reg_val &= 0xff;
	reg_val |= 0x22222200;
	writel(reg_val, GPIO_BASE_ADDR + 0x60);
	/*spi0 dirve strength*/
	reg_val = readl(GPIO_BASE_ADDR + 0x74);
	reg_val &= 0xff;
	reg_val |= 0x11111100;
	writel(reg_val, GPIO_BASE_ADDR + 0x74);
	/*spi0_cs0, spi0_hold, spi0_wp pull*/
	reg_val = readl(GPIO_BASE_ADDR + 0x84);
	reg_val &= ~(0x3 << 6);
	reg_val &= ~(0x3 << 12);
	reg_val &= ~(0x3 << 14);
	reg_val |= (0x1 << 6);
	reg_val |= (0x1 << 12);
	reg_val |= (0x1 << 14);
	writel(reg_val, GPIO_BASE_ADDR + 0x84);
#else
	spi_writel(0x33337777, GPIO_BASE_ADDR + 0x24*1 + 0x4*1);
	spi_writel(0x55577555, GPIO_BASE_ADDR + 0x24*5 + 0x4*3);
#endif
}

void SPINAND_PIORelease(__u32 nand_index)
{
	spi_writel(0x0, GPIO_BASE_ADDR + 0x58);
	return;
}

/*
************************************************************************************************************
*
*                                             OSAL_malloc
*
*    �������ƣ�
*
*    �����б�
*
*    ����ֵ  ��
*
*    ˵��    ��
*����һ����ٵ�malloc������Ŀ��ֻ���ṩ����һ��������������벻ͨ��
*               �����ṩ�κεĺ�������
*
************************************************************************************************************
*/
void *SPINAND_Malloc(unsigned int Size)
{
	return (void *)CONFIG_SYS_DRAM_BASE;
}
#if 0
__s32 SPINAND_Print(const char *str, ...)
{
	printf(str);
    return 0;
}
#endif
