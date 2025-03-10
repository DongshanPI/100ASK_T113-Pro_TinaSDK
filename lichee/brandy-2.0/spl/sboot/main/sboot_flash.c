/*
 * (C) Copyright 2007-2013
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * Jerry Wang <wangflord@allwinnertech.com>
 * wangwei <wangwei@allwinnertech.com>
 */


#include <common.h>
#include <spare_head.h>
#ifdef CFG_SUNXI_NAND
#include <nand_boot0.h>
#endif
#ifdef CFG_SUNXI_MMC
#include <mmc_boot0.h>
#endif
#ifdef CFG_SUNXI_SPINAND
#include <spinand_boot0.h>
#endif
#ifdef CFG_SUNXI_SPINOR
#include <arch/spinor.h>
#endif

#include <private_toc.h>
#include <private_boot0.h>
#include <private_uboot.h>
#include "sboot_flash.h"


int sunxi_flash_init(int boot_type)
{
	int ret = -1;

	if ((boot_type == BOOT_FROM_SD0) || (boot_type == BOOT_FROM_SD2)) {
#ifdef CFG_SUNXI_MMC
		ret = load_toc1_from_mmc(boot_type);
#endif
	}
	else if (boot_type == BOOT_FROM_NFC) {
#ifdef CFG_SUNXI_NAND
		ret = load_toc1_from_nand();
#endif
	} else if (boot_type == BOOT_FROM_SPI_NAND) {
#ifdef CFG_SUNXI_SPINAND
		ret = load_toc1_from_spinand();
#endif
	} else if (boot_type == BOOT_FROM_SPI_NOR) {
#ifdef CFG_SUNXI_SPINOR
		ret = load_toc1_from_spinor();
#endif
	} else {
		printf("PANIC: boot_type(%d) not support now\n",boot_type);
		return -1;
	}
	return ret;
}

int sunxi_flash_read(u32 start_sector, u32 blkcnt, void *buff)
{
	memcpy(buff, (void *)(CONFIG_BOOTPKG_BASE + 512 * start_sector), 512 * blkcnt);

	return blkcnt;
}
#ifdef CFG_SUNXI_MMC
int load_toc1_from_mmc( int boot_type)
{
	u8  *tmp_buff = (u8 *)CONFIG_BOOTPKG_BASE;
	sbrom_toc1_head_info_t  *toc1_head;
	int  sunxi_flash_mmc_card_no;
	int start_sector, i, ret;
	uint head_size;
	int start_sectors[4] = {UBOOT_START_SECTOR_IN_SDMMC,UBOOT_BACKUP_START_SECTOR_IN_SDMMC,0,0};

	if(boot_type == BOOT_FROM_SD0)
	{
		sunxi_flash_mmc_card_no = 0;
	}
	else
	{
		sunxi_flash_mmc_card_no = 2;
	}
	ret = sunxi_mmc_init(sunxi_flash_mmc_card_no, (sunxi_flash_mmc_card_no == 0 ? 4 : 8), toc0_config->storage_gpio + 24, 8);
	if(ret <= 0)
	{
		printf("mmc: init failed\n");
		return -1;
	}

	for(i = 0; i<4; i++)
	{
		start_sector = start_sectors[i];
		tmp_buff = (u8 *)CONFIG_BOOTPKG_BASE;
		if(start_sector == 0)
		{
			printf("mmc: read all toc1 failed\n");
			return -1;
		}

		ret = mmc_bread(sunxi_flash_mmc_card_no, start_sector, 64, tmp_buff);
		if(!ret)
		{
			printf("mmc: read error,start=%d\n",start_sector);
			continue;
		}
		toc1_head = (struct sbrom_toc1_head_info *)tmp_buff;
		if(toc1_head->magic != TOC_MAIN_INFO_MAGIC)
		{
			printf("mmc: toc1 magic error\n");
			continue;
		}
		head_size = toc1_head->valid_len;
		if(head_size > 64 * 512)
		{
			tmp_buff += 64*512;
			ret = mmc_bread(sunxi_flash_mmc_card_no, start_sector + 64, (head_size - 64*512 + 511)/512, tmp_buff);
			if(!ret)
			{
				printf("mmc:read error\n");
				continue;
			}
		}
		if( verify_addsum( (__u32 *)CONFIG_BOOTPKG_BASE, head_size) != 0 )
		{
			printf("mmc: toc1 checksun error.\n");
			continue;
		}
		printf("read toc1 from emmc %d sector\n",start_sector);
		break;
	}
	return 0;
}
#endif

#ifdef CFG_SUNXI_NAND
int load_toc1_from_nand( void )
{
	__u32 i;
	__s32  status;
	__u32 length;
	__u32 read_blks;
	sbrom_toc1_head_info_t  *toc1_head;
	char *buffer = (void*)CONFIG_BOOTPKG_BASE;

	if(NF_open( ) == NF_ERROR)
	{
		printf("fail in opening nand flash\n");
		return -1;
	}

	printf("block from %d to %d\n", BOOT1_START_BLK_NUM, BOOT1_LAST_BLK_NUM);
	for( i = BOOT1_START_BLK_NUM;  i <= BOOT1_LAST_BLK_NUM;  i++ )
	{
		if( NF_read_status( i ) == NF_BAD_BLOCK )
		{
			printf("nand block %d is bad\n", i);
			continue;
		}
		/*read head*/
		if( NF_read( i * ( NF_BLOCK_SIZE >> NF_SCT_SZ_WIDTH ), (void *)buffer, 1 )  == NF_OVERTIME_ERR )
		{
			printf("the first data is error\n");
			continue;
		}
		/* check magic */
		toc1_head = (sbrom_toc1_head_info_t *) buffer;
		if(toc1_head->magic != TOC_MAIN_INFO_MAGIC)
		{
			printf("%s err: the toc1 head magic is invalid\n", __func__);
			continue;
		}
		/* check align */
		length =  toc1_head->valid_len;
		if( ( length & ( ALIGN_SIZE - 1 ) ) != 0 )
		{
			printf("the boot1 is not aligned by 0x%x\n", ALIGN_SIZE);
			continue;
		}
		if( 1==load_uboot_in_one_block_judge(length) )
		{
			/* load toc1 in one blk */
			status = load_and_check_in_one_blk( i, (void *)buffer, length, NF_BLOCK_SIZE );
			if( status == ADV_NF_OVERTIME_ERR )
			{
				continue;
			}
			else if( status == ADV_NF_OK )
			{
				printf("Check is correct.\n");
				NF_close( );
				return 0;
			}
		}
		else
		{
			/* load toc in many blks */
			status = load_in_many_blks( i, BOOT1_LAST_BLK_NUM,
			                          (void*)buffer,length,
			                          NF_BLOCK_SIZE, &read_blks );
			if( status == ADV_NF_LACK_BLKS )
			{
				printf("ADV_NF_LACK_BLKS\n");
				NF_close( );
				return -1;
			}
			else if( status == ADV_NF_OVERTIME_ERR )
			{
				printf("mult block ADV_NF_OVERTIME_ERR\n");
				continue;
			}
			if( verify_addsum( (__u32 *)buffer, length ) == 0 )
			{
				printf("The file stored in start block %u is perfect.\n", i );
				NF_close( );
				return 0;
			}
		}
	}

	printf("Can't find a good Boot1 copy in nand.\n");
	NF_close( );
	return -1;
}

int BOOT_NandGetPara(void *param, uint size)
{
    memcpy( (void *)param, toc0_config->storage_data, size);

	return 0;
}
#endif
#ifdef CFG_SUNXI_SPINAND
int load_toc1_from_spinand(void)
{
	__u32 i;
	__s32 status;
	__u32 length;
	__u32 read_blks;
	sbrom_toc1_head_info_t *toc1_head;
	char *buffer = (void *)CONFIG_BOOTPKG_BASE;

	if (SpiNand_PhyInit() != 0) {
		printf("fail in opening nand flash\n");
		return -1;
	}

	printf("block from %d to %d\n", UBOOT_START_BLK_NUM,
	       UBOOT_LAST_BLK_NUM);
	for (i = UBOOT_START_BLK_NUM; i <= UBOOT_LAST_BLK_NUM; i++) {
		if (SpiNand_Check_BadBlock(i) == SPINAND_BAD_BLOCK) {
			printf("spi nand block %d is bad\n", i);
			continue;
		}
		if (SpiNand_Read(i * (SPN_BLOCK_SIZE >> NF_SCT_SZ_WIDTH),
				 (void *)buffer, 1) == NAND_OP_FALSE) {
			printf("the first data is error\n");
			continue;
		}
		toc1_head = (sbrom_toc1_head_info_t *)buffer;
		if (toc1_head->magic != TOC_MAIN_INFO_MAGIC) {
			printf("%s err:  magic is invalid\n", __func__);
			continue;
		}

		/*check align*/
		length = toc1_head->valid_len;
		if ((length & (ALIGN_SIZE - 1)) != 0) {
			printf("the boot1 is not aligned by 0x%x\n",
			       ALIGN_SIZE);
			continue;
		}

		status = Spinand_Load_Boot1_Copy(i, (void *)buffer, length,
						 SPN_BLOCK_SIZE, &read_blks);
		if (status == NAND_OP_FALSE) {
			printf("SPI nand load uboot copy fail\n");
			continue;
		}
		if (verify_addsum(buffer, length) == 0) {
			printf("Check is correct.\n");
			SpiNand_PhyExit();
			return 0;
		}
	}

	printf("Can't find a good Boot1 copy in spi nand.\n");
	SpiNand_PhyExit();
	return -1;
}
#endif

#ifdef CFG_SUNXI_SPINOR
int load_toc1_from_spinor(void)
{
	sbrom_toc1_head_info_t	*toc1_head;
	u8  *tmp_buff = (u8 *)CONFIG_BOOTPKG_BASE;
	int start_sector = CFG_SPINOR_UBOOT_OFFSET;
	uint total_size = 0;

	if(spinor_init(0))
	{
		printf("spinor init fail\n");
		return -1;
	}

	if(spinor_read(start_sector, 1, (void *)tmp_buff ) )
	{
		printf("the first data is error\n");
		goto __load_boot1_from_spinor_fail;
	}
	printf("Succeed in reading toc file head.\n");

	toc1_head = (struct sbrom_toc1_head_info *)tmp_buff;
	if(toc1_head->magic != TOC_MAIN_INFO_MAGIC)
	{
		printf("toc1 magic error\n");
		goto __load_boot1_from_spinor_fail;
	}
	total_size = toc1_head->valid_len;
	printf("The size of toc is %x.\n", total_size );

	if(spinor_read(start_sector, total_size/512, (void *)tmp_buff ))
	{
		printf("spinor read data error\n");
		goto __load_boot1_from_spinor_fail;
	}

	return 0;

__load_boot1_from_spinor_fail:

	return -1;
}
#endif

