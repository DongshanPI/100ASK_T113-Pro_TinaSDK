/*
 * (C) Copyright 2013-2016
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 *
 */

#include <common.h>
#include <arch/clock.h>
#include <arch/ce.h>
#include <cache_align.h>

#define SYMM_TRPE     0
#define HASH_RBG_TRPE 1
#define ASYM_TRPE     2
#define RAES_TRPE     3

static int ss_base_mode = 1;

static void __rsa_padding(u8 *dst_buf, u8 *src_buf, u32 data_len, u32 group_len)
{
	int i = 0;

	memset(dst_buf, 0, group_len);
	for (i = group_len - data_len; i < group_len; i++) {
		dst_buf[i] = src_buf[group_len - 1 - i];
	}
}

void sunxi_ce_open(void)
{
	u32 reg_val;

	reg_val = readl(CCMU_CE_CLK_REG); /*ce CLOCK*/
	reg_val &= ~(CE_CLK_DIV_RATION_M_MASK << CE_CLK_DIV_RATION_M_BIT);
	reg_val &= ~(CE_CLK_DIV_RATION_N_MASK << CE_CLK_DIV_RATION_N_BIT);
	writel(reg_val, CCMU_CE_CLK_REG);
	udelay(10);

	reg_val = readl(CCMU_CE_CLK_REG);
	/*set CE src clock*/
	reg_val &= ~(CE_CLK_SRC_MASK << CE_CLK_SRC_SEL_BIT);

#ifdef FPGA_PLATFORM
	/* OSC24M */
	reg_val |= 0 << CE_CLK_SRC_SEL_BIT;
#else
	/* PLL_PERI0(2X) */
	reg_val |= CE_CLK_SRC << CE_CLK_SRC_SEL_BIT;

	/*set div n*/
	reg_val &= ~(CE_CLK_DIV_RATION_N_MASK << CE_CLK_DIV_RATION_N_BIT);
	reg_val |= CE_CLK_DIV_RATION_N << CE_CLK_DIV_RATION_N_BIT;

	/*set div m*/
	reg_val &= ~(CE_CLK_DIV_RATION_M_MASK << CE_CLK_DIV_RATION_M_BIT);
	reg_val |= CE_CLK_DIV_RATION_M << CE_CLK_DIV_RATION_M_BIT;
#endif

	/*set src clock on*/
	reg_val |= CE_SCLK_ON << CE_SCLK_ONOFF_BIT;

	writel(reg_val, CCMU_CE_CLK_REG);

	/*de-assert*/
	writel(0x0, CE_RST_REG_BASE);

	/*open CE gating*/
	reg_val = readl(CE_GATING_BASE);
	reg_val |= (CE_GATING_PASS << CE_GATING_BIT) |
		   (CE_GATING_PASS << CE_SYS_GATING_BIT);
	writel(reg_val, CE_GATING_BASE);

	reg_val = readl(CCMU_MBUS_MST_CLK_GATING_REG);
	reg_val |= 0x1 << 2;
	writel(reg_val, CCMU_MBUS_MST_CLK_GATING_REG);

	/*de-assert*/
	reg_val = readl(CE_RST_REG_BASE);
	reg_val |=
		(CE_DEASSERT << CE_RST_BIT) | (CE_DEASSERT << CE_SYS_RST_BIT);
	writel(reg_val, CE_RST_REG_BASE);
}

void sunxi_ss_close(void)
{
}

void ss_set_drq(u32 addr)
{
	writel(addr, SS_TDQ);
}

void ss_ctrl_start(u8 alg_type)
{
	u32 val = 0;
	while (((readl(SS_TLR)) & (0x1 << alg_type)) == 1) {
	}
	val = readl(SS_TLR);
	val |= (0x1 << alg_type);
	writel(val, SS_TLR);
}

void ss_ctrl_stop(void)
{
	writel(0x0, SS_TLR);
}

u32 ss_check_err(u32 channel_id)
{
	return (readl(SS_ERR) & (0xff << channel_id));
}

void ss_wait_finish(u32 task_id)
{
	uint int_en;
	int_en = readl(SS_ICR) & 0xf;
	int_en = int_en & (0x01 << task_id);
	if (int_en != 0) {
		while ((readl(SS_ISR) & (0x03 << task_id * 2)) == 0) {
			;
		}
	}
}

u32 ss_pending_clear(u32 task_id)
{
	u32 reg_val;
	u32 res, ret = 0;
	reg_val = readl(SS_ISR);
	res	= reg_val & (0x3 << task_id * 2);

	if (res == 0x1) {
		ret = 0;
	} else if (res == 0x2) {
		ret = ss_check_err(task_id);
	}
	reg_val = (reg_val & 0xff) | (0x3 << task_id * 2);
	writel(reg_val, SS_ISR);
	writel(0x0, SS_ICR);
	return ret;
}

void ss_irq_enable(u32 task_id)
{
	int val = readl(SS_ICR);
	val |= (0x1 << task_id);
	writel(val, SS_ICR);
}

void ss_irq_disable(u32 task_id)
{
	int val = readl(SS_ICR);
	val &= ~(1 << task_id);
	writel(val, SS_ICR);
}

int sunxi_sha_calc(u8 *dst_addr, u32 dst_len, u8 *src_addr, u32 src_len)
{
	u32 total_bit_len		  = 0;
	u32 md_size			  = 32;
	struct hash_task_descriptor task0 = { 0 };
	/* sha256  2word, sha512 4word*/
	total_bit_len = src_len * 8;

	task0.ctrl = (CHANNEL_0 << CHN) | (0x1 << LPKG) | (0x0 << DLAV) |
		     (0x1 << IE);
	task0.cmd = (SHA256 << 0);
	memcpy(task0.data_toal_len_addr, &total_bit_len, 4);
	memcpy(task0.sg[0].source_addr, (void *)&src_addr, 4);
	task0.sg[0].source_len = src_len;
	memcpy(task0.sg[0].dest_addr, (void *)&dst_addr, 4);
	task0.sg[0].dest_len = md_size;

	/* make sure memory operation has finished */
	data_sync_barrier();

	ss_set_drq(((u32)&task0));
	ss_irq_enable(CHANNEL_0);
	ss_ctrl_start(HASH_RBG_TRPE);
	ss_wait_finish(CHANNEL_0);
	ss_pending_clear(CHANNEL_0);
	ss_ctrl_stop();
	ss_irq_disable(CHANNEL_0);
	if (ss_check_err(CHANNEL_0)) {
		printf("SS %s fail 0x%x\n", __func__, ss_check_err(CHANNEL_0));
		return -1;
	}

	return 0;
}

s32 sunxi_rsa_calc(u8 *n_addr, u32 n_len, u8 *e_addr, u32 e_len, u8 *dst_addr,
		   u32 dst_len, u8 *src_addr, u32 src_len)
{
#define TEMP_BUFF_LEN ((2048 >> 3) + 32)
	struct other_task_descriptor task0 = { 0 };
	u32 mod_bit_size		   = 2048;
	u32 mod_size_len_inbytes	   = mod_bit_size >> 3;

	ALLOC_CACHE_ALIGN_BUFFER(u8, p_n, TEMP_BUFF_LEN);
	ALLOC_CACHE_ALIGN_BUFFER(u8, p_e, TEMP_BUFF_LEN);
	ALLOC_CACHE_ALIGN_BUFFER(u8, p_src, TEMP_BUFF_LEN);
	ALLOC_CACHE_ALIGN_BUFFER(u8, p_dst, TEMP_BUFF_LEN);
	__rsa_padding(p_src, src_addr, src_len, mod_size_len_inbytes);
	__rsa_padding(p_n, n_addr, n_len, mod_size_len_inbytes);

	/*
	 * e usually 0x010001, so rsa padding, aka little-end ->
	 * big-end transfer is useless like, still do this rsa
	 * padding here, in case e is no longer 0x010001 some day
	 */
	memset(p_e, 0, mod_size_len_inbytes);
	__rsa_padding(p_e, e_addr, e_len, e_len);
	//memcpy(p_e, e_addr, e_len);

	task0.task_id	     = CHANNEL_0;
	task0.common_ctl     = (ALG_RSA | (1U << 31));
	task0.asymmetric_ctl = (mod_bit_size >> 5);
	memcpy(task0.sg[0].source_addr, &p_e, 4);
	task0.sg[0].source_len = mod_size_len_inbytes;
	memcpy(task0.sg[1].source_addr, &p_n, 4);
	task0.sg[1].source_len = mod_size_len_inbytes;
	memcpy(task0.sg[2].source_addr, &p_src, 4);
	task0.sg[2].source_len = mod_size_len_inbytes;
	task0.data_len += task0.sg[0].source_len;
	task0.data_len += task0.sg[1].source_len;
	task0.data_len += task0.sg[2].source_len;

	memcpy(task0.sg[0].dest_addr, &p_dst, 4);
	task0.sg[0].dest_len = mod_size_len_inbytes;

	/* make sure memory opration has finished */
	data_sync_barrier();

	ss_set_drq(((u32)&task0));
	ss_irq_enable(task0.task_id);
	ss_ctrl_start(ASYM_TRPE);
	ss_wait_finish(task0.task_id);
	ss_pending_clear(task0.task_id);
	ss_ctrl_stop();
	ss_irq_disable(task0.task_id);
	if (ss_check_err(task0.task_id)) {
		printf("SS %s fail 0x%x\n", __func__,
		       ss_check_err(task0.task_id));
		return -1;
	}

	__rsa_padding(dst_addr, p_dst, mod_bit_size / 64, mod_bit_size / 64);

	return 0;
}

int sunxi_trng_gen(u8 *trng_buf, u32 trng_len)
{
	struct hash_task_descriptor task0 __aligned(CACHE_LINE_SIZE) = { 0 };

	ALLOC_CACHE_ALIGN_BUFFER(u8, p_sign, CACHE_LINE_SIZE);

	memset(p_sign, 0, CACHE_LINE_SIZE);

	if (trng_buf == NULL) {
		return -1;
	}
	/*
	 * len should be TRANG_BYTE_LEN aligned, but p_sign could
	 * have just 32 byte, so only len TRANG_BYTE_LEN is allowed
	 */
	if (trng_len != TRNG_BYTE_LEN) {
		return -2;
	}

	task0.ctrl = (CHANNEL_0 << CHN) | (0x1 << LPKG) | (0x0 << DLAV) |
		     (0x1 << IE);
	task0.cmd = (TRNG << RGB_SEL) | (SHA256 << HASH_SEL);
	memcpy(task0.sg[0].dest_addr, &p_sign, 4);
	task0.sg[0].dest_len = (trng_len);

	/* make sure memory operation has finished */
	data_sync_barrier();

	ss_set_drq(((u32)&task0));
	ss_irq_enable(CHANNEL_0);
	ss_ctrl_start(HASH_RBG_TRPE);
	ss_wait_finish(CHANNEL_0);
	ss_pending_clear(CHANNEL_0);
	ss_ctrl_stop();
	ss_irq_disable(CHANNEL_0);
	if (ss_check_err(CHANNEL_0)) {
		printf("SS %s fail 0x%x\n", __func__, ss_check_err(CHANNEL_0));
		return -1;
	}

	/*copy data*/
	memcpy(trng_buf, p_sign, trng_len);

	return 0;
}
