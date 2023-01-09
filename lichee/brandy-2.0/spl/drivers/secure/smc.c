/*
 * (C) Copyright 2013-2016
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 *
 */

#include <common.h>
#include <private_toc.h>
#include <private_uboot.h>
#include <arch/smc.h>

static uint __tzasc_calc_2_power(u64 data)
{
	uint ret = 0;
	do {
		data >>= 1;
		ret++;
	} while (data);

	return (ret - 1);
}


int sunxi_smc_resume(int secure_entry)
{
	struct sec_mem_region sec_mem_map[5] = {0};
	int secure_entry2 = 0;
	int map_cnt = 0;
	if (secure_entry) {
		sec_mem_map[map_cnt].startAddr = secure_entry;
		sec_mem_map[map_cnt].size      = 0x100000;
		map_cnt++;
#ifdef CONFIG_MONITOR
		struct spare_monitor_head *monitor_head = (struct spare_monitor_head *)secure_entry;
		secure_entry2 = monitor_head->secureos_base;
#endif
	}
	if (secure_entry2) {
		sec_mem_map[map_cnt].startAddr = secure_entry2;
		sec_mem_map[map_cnt].size      = 0x100000;
		map_cnt++;
	}
	sunxi_smc_config(sec_mem_map);
	return 0;
}

int sunxi_smc_config(struct sec_mem_region *sec_mem_map)
{
	int i, size_setting;
	/* config smc action: non-secure master access protected region get 0*/
	writel(0x0, SMC_ACTION_REG);
#if defined(CFG_SUNXI_SMC_10)
	writel(0, SMC_MASTER_BYPASS0_REG);
	writel(0xffffffff, SMC_MASTER_SECURITY0_REG);
#else
	/* config all master(cpu|gpu...) access dram by SMC*/
	writel(0, SMC_MST0_BYP_REG);
	writel(0, SMC_MST1_BYP_REG);
	writel(0, SMC_MST2_BYP_REG);
	/* config config all master(cpu|gpu...) to non-secure mode */
	writel(0xffffffff, SMC_MST0_SEC_REG);
	writel(0xffffffff, SMC_MST1_SEC_REG);
	writel(0xffffffff, SMC_MST2_SEC_REG);
#endif


	/* 0xf : config dram to secure rw, non-secure rw */
	/* 0x1f: 4G area */
	/* 0x1 : enable */
	writel((0xf<<28) | (0x1f<<1) | (0x1<<0), SMC_REGIN_ATTRIBUTE_REG(1));

	boot_info("set smc for optee\n");

	i = 2;
	while (sec_mem_map->size != 0) {
		writel((u32)((sec_mem_map->startAddr - 0x40000000) >> 32) &
			       0xFFFF8000,
		       SMC_REGIN_SETUP_HIGH_REG(i));
		writel((u32)(sec_mem_map->startAddr - 0x40000000) & 0xFFFF8000,
		       SMC_REGIN_SETUP_LOW_REG(i));
		size_setting =
			__tzasc_calc_2_power(sec_mem_map->size / (32 * 1024)) +
			0xE;
		writel((0xc << 28) | (size_setting << 1) | (0x1 << 0),
		       SMC_REGIN_ATTRIBUTE_REG(i));
#if 0 /*debug print */
		printf("startAddr:0x%lx,size:0x%lx\n",
		       (u32)sec_mem_map->startAddr, (u32)sec_mem_map->size);
		printf("high:0x%x,low:0x%x,size:0x%x\n",
		       (u32)((sec_mem_map->startAddr - 0x40000000) >> 32) &
			       0xFFFF8000,
		       (u32)(sec_mem_map->startAddr - 0x40000000) & 0xFFFF8000,
		       size_setting);
#endif
		sec_mem_map++;
		i++;
	}
	return 0;
}

#if defined(CFG_SUNXI_SMC_10)
int sunxi_drm_config(u32 dram_end, u32 drm_region_size)
{
	if (dram_end < drm_region_size) {
		writel(0, SMC_LOW_SADDR_REG);
		writel(0, SMC_LOW_EADDR_REG);

		return -1;
	}

	writel((dram_end - drm_region_size), SMC_LOW_SADDR_REG);
	writel(dram_end, SMC_LOW_EADDR_REG);

	return 0;
}
#elif defined(CFG_SUNXI_SMC_11)
int sunxi_drm_config(u32 dram_end, u32 drm_region_size)
{
	if (!drm_region_size) {
		printf("drm_region_size is 0\n");
		return 0;
	}
	if (dram_end < drm_region_size) {
		writel(0, SMC_DRM_STATADDR_REG0);
		writel(0, SMC_DRM_ENDADDR_REG0);
		return -1;
	}

#ifdef DRM_TEST
	u32 i = 0;
	printf("drm_region_size = %d\n", drm_region_size);
	for (i = 0; i < 0x10000; i = i + 4) {
		writel(0xefe80123, 0x41F00000 + i);
	}
	printf("addr:0x%x---->0x%x\n", 0x41F00000, *(uint *)0x41F00000);
	dram_end = 0x41F10000;
	drm_region_size = 0x10000;
	writel(0xffffffff, SMC_DRM_MATER0_EN_REG);
	printf("drm_mst = 0x%x\n", readl(SMC_DRM_MATER0_EN_REG));
#endif
	writel((dram_end - drm_region_size), SMC_DRM_STATADDR_REG0);
	writel(dram_end, SMC_DRM_ENDADDR_REG0);

	return 0;
}
#elif defined(CFG_SUNXI_SMC_30)
int sunxi_drm_config(u32 dram_end, u32 drm_region_size)
{
#if defined(CFG_SUNXI_DRM_BITMAP)
	if (dram_end < drm_region_size) {
		writel(0, SMC_BITMAP_LOW_SADDR_REG);
		writel(0, SMC_BITMAP_LOW_EADDR_REG);

		return -1;
	}
#ifdef DRM_TEST
	*(uint *)0x47500000 = 0xa0a0;
	printf("addr:0x%x---->0x%x\n", 0x47500000, *(uint *)0x47500000);
	dram_end = 0x47600000;
	drm_region_size = 0x100000;
#endif
	/*whole region non-drm by default*/
	memset((char *)SMC_BMR_SRAM, 0x0, SMC_BMR_SRAM_SIZE);
	writel((((dram_end - drm_region_size) >> 15) << 13 | 1<<0), SMC_BITMAP_LOW_SADDR_REG);
	writel(((dram_end >> 15) << 13), SMC_BITMAP_LOW_EADDR_REG);
#else
	if (dram_end < drm_region_size) {
		writel(0, SMC_LOW_SADDR_REG);
		writel(0, SMC_LOW_EADDR_REG);

		return -1;
	}
#ifdef DRM_TEST
	*(uint *)0x47500000 = 0xa0a0;
	printf("addr:0x%x---->0x%x\n", 0x47500000, *(uint *)0x47500000);
	dram_end = 0x47600000;
	drm_region_size = 0x100000;
#endif
	writel((((dram_end - drm_region_size) >> 15) << 13), SMC_LOW_SADDR_REG);
	writel(((dram_end >> 15) << 13), SMC_LOW_EADDR_REG);

#endif
	return 0;
}

#else
int sunxi_drm_config(u32 dram_end, u32 drm_region_size)
{
	u32 ctrl = 0;
	u32 drm_region_ofs, bit_map_ofs, bitmap_write_len, i;
	u32 drm_region_sel = 0;
	/*set 0x47500000~0x47600000 for drm dram*/
#ifdef DRM_TEST
	u32 dram_size = (0x47600000 - CONFIG_SYS_DRAM_BASE) >> 20;
	*(uint *)0x47500000 = 0xa5a5;
	drm_region_size = 1<<20;/*1M*/
#else
	u32 dram_size = (dram_end - CONFIG_SYS_DRAM_BASE) >> 20;
#endif
	u32 bitmap_total_len = 0;

	/*bitmap: total len 32K Bytes
	1bit   --->4K
	256bit --->1M
	32*1024 Bytes ---> 1G Bytes
	*/

	/*clear sram for bitmap */
	bitmap_total_len = 1024*256;
	for (i = 0; i < bitmap_total_len; i += 8) {
		/* data 8bit | len | addr */
		ctrl = (0x00 << 24) | (0x8 << 20) |  i;
		writel(ctrl, DRM_BITMAP_CTRL_REG);
	}

	if (drm_region_size <= 0) {
			return 0;
	}

	drm_region_size = drm_region_size >> 20;
	drm_region_ofs = (dram_size - drm_region_size) % 1024;
	bit_map_ofs = (drm_region_ofs * 256);
	bitmap_write_len = drm_region_size * 256;
	/*printf("drm_region_ofs = %d, bitmap_ofs = %d,
		bitmap_write_len = %d\n", drm_region_ofs,bit_map_ofs,bitmap_write_len);
	*/
	for (i = 0; i < bitmap_write_len; i += 8) {
		/* data 8bit | len | addr */
		ctrl = (0xff<<24) | (0x8<<20) |  (bit_map_ofs+i);
		writel(ctrl, DRM_BITMAP_CTRL_REG);
	}

	/* 0x4000 0000 ~ 0x7FFF FFFF  region0
	   0x8000 0000 ~ 0xBFFF FFFF  region1
	   0xC000 0000 ~ 0xFFFF FFFF  region2
	*/
	if (dram_size > 2048)
		drm_region_sel = 0x2;  /* > 2G*/
	else if (dram_size > 1024)
		drm_region_sel = 0x1;  /* > 1G */
	else
		drm_region_sel = 0x0;

	writel(drm_region_sel, DRM_BITMAP_SEL_REG);

#ifdef DRM_TEST
	printf("0x47500000---->0x%x\n", *(uint *)0x47500000);
	/* drm enable */
	writel(1<<31, SMC_DRM_MATER0_EN_REG);
#endif

#ifdef DRM_DEBUG

	u32 val;
	for (i = 0; i < bitmap_write_len; i += 32) {
		ctrl = (0x0<<20) |	(bit_map_ofs+i);
		writel(ctrl, DRM_BITMAP_CTRL_REG);
		val = readl(DRM_BITMAP_VAL_REG);
		printf("0x%x ", val);
		if ((i+1)%16 == 0)
			printf("\n");
	}

	printf("\n");
	printf("secure enable bit: %x\n", readl(0x03006248));
	printf("secure DRM bit: %x\n", readl(SMC_DRM_MATER0_EN_REG));
	printf("drm_region_sel: %x\n", drm_region_sel);
#endif
	return 0;

}

#endif
