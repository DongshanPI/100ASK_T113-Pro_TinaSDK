/*
 * (C) Copyright 2018-2020
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * wangwei <wangwei@allwinnertech.com>
 *
 */

#include <common.h>
#include <asm/io.h>
#include <arch/clock.h>
#include <arch/uart.h>
#include <arch/efuse.h>

static void set_pll_cpux_axi(void)
{
	u32 reg_val;
	/* select CPUX  clock src: OSC24M,AXI divide ratio is 2, system apb clk ratio is 4 */
	writel((0 << 24) | (3 << 8) | (1 << 0), CCMU_CPUX_AXI_CFG_REG);
	udelay(1);

	/* disable pll gating*/
	reg_val = readl(CCMU_PLL_CPUX_CTRL_REG);
	reg_val &= ~(1 << 27);
	writel(reg_val, CCMU_PLL_CPUX_CTRL_REG);

	/* set default val: clk is 1008M  ,PLL_OUTPUT= 24M*N/( M*P)*/
	reg_val = readl(CCMU_PLL_CPUX_CTRL_REG);
	reg_val &= ~((0x3 << 16) | (0xff << 8) | (0x3 << 0));
	reg_val |= (41 << 8);
	writel(reg_val, CCMU_PLL_CPUX_CTRL_REG);
	/* lock enable */
	reg_val = readl(CCMU_PLL_CPUX_CTRL_REG);
	reg_val |= (1 << 29);
	writel(reg_val, CCMU_PLL_CPUX_CTRL_REG);

	reg_val = readl(CCMU_PLL_CPUX_CTRL_REG);
	reg_val |= (0x1U << 30);
	writel(reg_val, CCMU_PLL_CPUX_CTRL_REG);
	udelay(5);

/*wait PLL_CPUX stable*/
#ifndef FPGA_PLATFORM
	while (!(readl(CCMU_PLL_CPUX_CTRL_REG) & (0x1 << 28)))
		;
	udelay(20);
#endif

	/* enable pll gating*/
	reg_val = readl(CCMU_PLL_CPUX_CTRL_REG);
	reg_val |= (1 << 27);
	writel(reg_val, CCMU_PLL_CPUX_CTRL_REG);

	/* lock disable */
	reg_val = readl(CCMU_PLL_CPUX_CTRL_REG);
	reg_val &= ~(1 << 29);
	writel(reg_val, CCMU_PLL_CPUX_CTRL_REG);

	/*set and change cpu clk src to PLL_CPUX,  PLL_CPUX:AXI0 = 408M:136M*/
	reg_val = readl(CCMU_CPUX_AXI_CFG_REG);
	reg_val &= ~(0x03 << 24 | 0x3 << 16 | 0x3 << 8 | 0x3 << 0);
	reg_val |= (0x03 << 24 | 0x3 << 8 | 0x1 << 0);
	writel(reg_val, CCMU_CPUX_AXI_CFG_REG);
	udelay(1);
}

static void set_pll_periph0(void)
{
	u32 reg_val;

	if ((1U << 31) & readl(CCMU_PLL_PERI0_CTRL_REG)) {
		/*fel has enable pll_periph0*/
		printf("periph0 has been enabled\n");
		return;
	}
	/*change  psi/ahb src to OSC24M before set pll6
	reg_val = readl(CCMU_PSI_AHB1_AHB2_CFG_REG);
	reg_val &= (~(0x3<<24));
	writel(reg_val,CCMU_PSI_AHB1_AHB2_CFG_REG) */;

	/* disable pll gating*/
	reg_val = readl(CCMU_PLL_PERI0_CTRL_REG);
	reg_val &= ~(1 << 27);
	writel(reg_val, CCMU_PLL_PERI0_CTRL_REG);

	/* set default val*/
	reg_val = readl(CCMU_PLL_PERI0_CTRL_REG);
	reg_val &= ~(1 << 1 | 0xff << 8 | 0x7 << 16 | 0x7 << 20);
	reg_val |= (0x63 << 8 | 0x1 << 16 | 0x2 << 20);
	writel(reg_val, CCMU_PLL_PERI0_CTRL_REG);

	/* lock enable */
	reg_val = readl(CCMU_PLL_PERI0_CTRL_REG);
	reg_val |= (1 << 29);
	writel(reg_val, CCMU_PLL_PERI0_CTRL_REG);

	reg_val = readl(CCMU_PLL_PERI0_CTRL_REG);
	reg_val |= (1 << 30);
	writel(reg_val, CCMU_PLL_PERI0_CTRL_REG);

	/* enabe PLL: 600M(1X)  1200M(2x)*/
	reg_val = readl(CCMU_PLL_PERI0_CTRL_REG);
	reg_val |= (1 << 31);
	writel(reg_val, CCMU_PLL_PERI0_CTRL_REG);

#ifndef FPGA_PLATFORM
	while (!(readl(CCMU_PLL_PERI0_CTRL_REG) & (0x1 << 28)))
		;
	udelay(20);
#endif

	/* enable pll gating*/
	reg_val = readl(CCMU_PLL_PERI0_CTRL_REG);
	reg_val |= (1 << 27);
	writel(reg_val, CCMU_PLL_PERI0_CTRL_REG);

	/* lock disable */
	reg_val = readl(CCMU_PLL_PERI0_CTRL_REG);
	reg_val &= (~(1 << 29));
	writel(reg_val, CCMU_PLL_PERI0_CTRL_REG);
}

static void set_ahb(void)
{
	/* PLL6:AHB1:AHB2 = 600M:200M:200M */
	writel((2 << 0) | (0 << 8), CCMU_PSI_AHB1_AHB2_CFG_REG);
	writel((0x03 << 24) | readl(CCMU_PSI_AHB1_AHB2_CFG_REG),
	       CCMU_PSI_AHB1_AHB2_CFG_REG);
	udelay(1);
}

static void set_apb(void)
{
	/*PLL6:APB1 = 600M:100M */
	writel((2 << 0) | (1 << 8), CCMU_APB1_CFG_GREG);
	writel((0x03 << 24) | readl(CCMU_APB1_CFG_GREG), CCMU_APB1_CFG_GREG);
	udelay(1);
}

static void set_pll_dma(void)
{
	/*dma reset*/
	writel(readl(CCMU_DMA_BGR_REG) | (1 << 16), CCMU_DMA_BGR_REG);
	udelay(20);
	/*gating clock for dma pass*/
	writel(readl(CCMU_DMA_BGR_REG) | (1 << 0), CCMU_DMA_BGR_REG);
}

static void set_pll_mbus(void)
{
	u32 reg_val;

	/*reset mbus domain*/
	reg_val = readl(CCMU_MBUS_CFG_REG);
	reg_val |= (0x1 << 30);
	writel(reg_val, CCMU_MBUS_CFG_REG);
	udelay(1);
}

static void set_modules_clock(void)
{
	u32 reg_val, i;
	unsigned long ccmu_pll_addr[] = {
				CCMU_PLL_PERI0_CTRL_REG,
				CCMU_PLL_VIDE00_CTRL_REG,
				CCMU_PLL_VIDE01_CTRL_REG,
				CCMU_PLL_VE_CTRL_REG,
				CCMU_PLL_AUDIO0_CTRL_REG,
				CCMU_PLL_AUDIO1_CTRL_REG,
				};

	for (i = 0; i < sizeof(ccmu_pll_addr)/sizeof(ccmu_pll_addr[0]); i++) {
		reg_val = readl((const volatile void __iomem *)ccmu_pll_addr[i]);
		if (!(reg_val & (1 << 31))) {
			writel(reg_val, (volatile void __iomem *)ccmu_pll_addr[i]);

			reg_val = readl((const volatile void __iomem *)ccmu_pll_addr[i]);
			writel(reg_val | (1 << 31) | (1 << 30), (volatile void __iomem *)ccmu_pll_addr[i]);
#ifndef FPGA_PLATFORM
			/* lock enable */
			reg_val = readl((const volatile void __iomem *)ccmu_pll_addr[i]);
			reg_val |= (1 << 29);
			writel(reg_val, (volatile void __iomem *)ccmu_pll_addr[i]);

			while (!(readl((const volatile void __iomem *)ccmu_pll_addr[i]) & (0x1 << 28)))
				;
			udelay(20);

			reg_val = readl((const volatile void __iomem *)ccmu_pll_addr[i]);
			reg_val &= ~(1 << 29);
			writel(reg_val, (volatile void __iomem *)ccmu_pll_addr[i]);
#endif
		}
	}
}

static void set_pll_ldo_enable(void)
{
	u32 reg_val = 0x00;

	reg_val = readl(PLL_CTRL_REG1);
	reg_val |= (0x1 << 0);
	reg_val |= (0xa7 << 24);
	writel(reg_val, PLL_CTRL_REG1);
	writel(reg_val, PLL_CTRL_REG1);
	mdelay(4);
}

static void set_rtc32k_clock(void)
{
	u32 reg_val = 0x00;
	u32 standby_flag = 0;

	reg_val = readl(RTC_STANDBY_FLAG_REG);
	standby_flag = (reg_val & ~(0xfffe0000)) >> 16;

	if (0 == standby_flag)
		return;

	printf("#rtc standby flag reg is 0x%x, super standby flag is 0x%x\n",
			reg_val, standby_flag);

	reg_val = readl(RTC_LOSC_CTRL);
	reg_val |= (0x1 << 4);
	reg_val |= (0xa7 << 16);
	writel(reg_val, RTC_LOSC_CTRL);
	writel(reg_val, RTC_LOSC_CTRL);
	udelay(10);
	reg_val = readl(RTC_LOSC_CTRL);
	reg_val |= (0x1 << 0);
	reg_val |= (0x16aa << 16);
	writel(reg_val, RTC_LOSC_CTRL);
	writel(reg_val, RTC_LOSC_CTRL);
	udelay(10);
	reg_val = readl(RTC_LOSC_OUT_GATING);
	reg_val |= (0x1 <<0);
	writel(reg_val, RTC_LOSC_OUT_GATING);
}

static void set_ldo_analog(void)
{
	u32 soc_version = (readl(SUNXI_SID_BASE + 0x200) >> 22) & 0x3f;
	u32 audio_codec_bg_trim = (readl(SUNXI_SID_BASE + 0x228) >> 16) & 0xff;

	clrbits_le32(SUNXI_CCM_BASE + 0xA5C, 1 << (SUNXI_GATING_BIT));
	udelay(2);
	clrbits_le32(SUNXI_CCM_BASE + 0xA5C, 1 << (SUNXI_RST_BIT));
	udelay(2);
	/* deassert audio codec reset */
	setbits_le32(SUNXI_CCM_BASE + 0xA5C, 1 << (SUNXI_RST_BIT));
	/* open the clock for audio codec */
	setbits_le32(SUNXI_CCM_BASE + 0xA5C, 1 << (SUNXI_GATING_BIT));

	if (soc_version == 0b1010 || soc_version == 0) {
		setbits_le32(SUNXI_AUDIO_CODEC + 0x31C, 1 << 1);
		setbits_le32(SUNXI_AUDIO_CODEC + 0x348, 1 << 30);
	} else {
		clrbits_le32(SUNXI_AUDIO_CODEC + 0x31C, 3 << 0);
		clrbits_le32(SUNXI_AUDIO_CODEC + 0x348, 1 << 30);
	}

	if (!audio_codec_bg_trim) {
		clrsetbits_le32(SUNXI_AUDIO_CODEC + 0x348, 0xff, 0x19 << 0);
	} else {
		clrsetbits_le32(SUNXI_AUDIO_CODEC + 0x348, 0xff, audio_codec_bg_trim << 0);
	}

}

void set_aldo_analog(void)
{
	u32 aldo_val = (readl(SUNXI_SID_BASE + 0x21c)) & 0x19;
	if (aldo_val != 0x19) {
		sid_program_key(0x1c, 0x19);
		aldo_val = sid_read_key(0x1c) & 0x1f;
	}

}

void set_ldoa_analog(void)
{
	u32 ldoa_val = (readl(SUNXI_SID_BASE + 0x218) & 0xff);
	u32 sys_ldo_ctl = (readl(SUNXI_SYSCRL_BASE + 0x150) & 0xffffff00);
	if (ldoa_val) {
		writel(ldoa_val | sys_ldo_ctl, SUNXI_SYSCRL_BASE + 0x150);
	}
}


static void set_vccio_detect(void)
{
	void __iomem *vccio_det = sunxi_get_iobase(SUNXI_RTC_BASE + 0x1F4);
	u32 value = 0x0;

	value = readl(vccio_det);
	/*printf("vccio detect value:0x%x\n", value);*/

	if (!(value & 0x1))
		return;

	/* threshold value is 2.9v */
	value &= ~(0x7 << 4);
	value |= (0x4 << 4);
	writel(value, vccio_det);

	/* enable vccio detect */
	value |= (0x1 << 7);
	writel(value, vccio_det);

	/* not bypass */
	value &= ~(1 << 0);
	writel(value, vccio_det);
	printf("fix vccio detect value:0x%x\n", readl(vccio_det));
}

static void set_platform_config(void)
{
	set_ldoa_analog();
	set_ldo_analog();
	set_aldo_analog();
	set_vccio_detect();
}


void sunxi_board_pll_init(void)
{
	printf("set pll start\n");
	set_platform_config();
	set_pll_ldo_enable();
	set_pll_cpux_axi();
	set_pll_periph0();
	set_ahb();
	set_apb();
	set_pll_dma();
	set_pll_mbus();
	set_rtc32k_clock();
	set_modules_clock();
	printf("set pll end\n");
	return;
}

void sunxi_board_clock_reset(void)
{
	u32 reg_val;

	/*set ahb,apb to default, use OSC24M*/
	reg_val = readl(CCMU_PSI_AHB1_AHB2_CFG_REG);
	reg_val &= (~((0x3 << 24) | (0x3 << 8) | (0x3)));
	writel(reg_val, CCMU_PSI_AHB1_AHB2_CFG_REG);

	reg_val = readl(CCMU_APB1_CFG_GREG);
	reg_val &= (~((0x3 << 24) | (0x3 << 8) | (0x3)));
	writel(reg_val, CCMU_APB1_CFG_GREG);

	/*set cpux pll to default,use OSC24M*/
	writel(0x0301, CCMU_CPUX_AXI_CFG_REG);
	return;
}

int sunxi_clock_init_key(void)
{
	uint reg_val = 0;

	/* reset */
	reg_val = readl(CCMU_GPADC_BGR_REG);
	reg_val &= ~(1 << 16);
	writel(reg_val, CCMU_GPADC_BGR_REG);

	udelay(2);

	reg_val |= (1 << 16);
	writel(reg_val, CCMU_GPADC_BGR_REG);

	/* enable KEYADC gating */
	reg_val = readl(CCMU_GPADC_BGR_REG);
	reg_val |= (1 << 0);
	writel(reg_val, CCMU_GPADC_BGR_REG);

	return 0;
}

int sunxi_clock_exit_key(void)
{
	uint reg_val = 0;

	/* disable KEYADC gating */
	reg_val = readl(CCMU_GPADC_BGR_REG);
	reg_val &= ~(1 << 0);
	writel(reg_val, CCMU_GPADC_BGR_REG);

	return 0;
}

void sunxi_clock_init_uart(int port)
{
	u32 i, reg;

	/* reset */
	reg = readl(CCMU_UART_BGR_REG);
	reg &= ~(1<<(CCM_UART_RST_OFFSET + port));
	writel(reg, CCMU_UART_BGR_REG);
	for (i = 0; i < 100; i++)
		;
	reg |= (1 << (CCM_UART_RST_OFFSET + port));
	writel(reg, CCMU_UART_BGR_REG);
	/* gate */
	reg = readl(CCMU_UART_BGR_REG);
	reg &= ~(1<<(CCM_UART_GATING_OFFSET + port));
	writel(reg, CCMU_UART_BGR_REG);
	for (i = 0; i < 100; i++)
		;
	reg |= (1 << (CCM_UART_GATING_OFFSET + port));
	writel(reg, CCMU_UART_BGR_REG);
}
