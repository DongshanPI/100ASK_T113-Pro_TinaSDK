/*
 * (C) Copyright 2007-2013
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * Jerry Wang <wangflord@allwinnertech.com>
 * wangwei <wangwei@allwinnertech.com>
 */

#include <common.h>
#include <openssl_ext.h>
#include <arch/efuse.h>
#include <arch/ce.h>
#include "sboot_ceritf.h"
#include "private_toc.h"

int sunxi_pubkey_hash_cal(char *out_buf, sunxi_key_t *pubkey)
{
	char pk[RSA_BIT_WITDH / 8 * 2 + 256]; /*For the stupid sha padding */

	memset(pk, 0x91, sizeof(pk));
	char *align = (char *)(((phys_addr_t)pk + 31) & (~31));
	if (*(pubkey->n)) {
		memcpy(align, pubkey->n, pubkey->n_len);
		memcpy(align + pubkey->n_len, pubkey->e, pubkey->e_len);
	} else {
		memcpy(align, pubkey->n + 1, pubkey->n_len - 1);
		memcpy(align + pubkey->n_len - 1, pubkey->e, pubkey->e_len);
	}

	if (sunxi_sha_calc((u8 *)out_buf, 32, (u8 *)align,
			   RSA_BIT_WITDH / 8 * 2)) {
		printf("sunxi_sha_calc: calc  pubkey sha256 with hardware err\n");
		return -1;
	}
	return 0;
}

int sunxi_certif_pubkey_check(sunxi_key_t *pubkey)
{
	char efuse_hash[256], rotpk_hash[256];
	char all_zero[32];

	if (sunxi_pubkey_hash_cal(rotpk_hash, pubkey)) {
		return -1;
	}

	sid_read_rotpk(efuse_hash);
	memset(all_zero, 0, 32);
	if (!memcmp(all_zero, efuse_hash, 32)) {
		printf("don't have rotpk, skip check\n");
		return 0 ; /*Don't check if rotpk efuse is empty*/
	} else {
		printf("have rotpk, do check\n");
		/* already have rotpk, don't need flag */
		toc0_config->rotpk_flag = 0;
		if (memcmp(rotpk_hash, efuse_hash, 32)) {

			char pk[RSA_BIT_WITDH/8 * 2 + 256]; /*For the stupid sha padding */
			char *align = (char *)(((phys_addr_t)pk + 31) & (~31));

			memset(pk, 0x91, sizeof(pk));
			if (*(pubkey->n)) {
				memcpy(align, pubkey->n, pubkey->n_len);
				memcpy(align + pubkey->n_len, pubkey->e, pubkey->e_len);
			} else {
				memcpy(align, pubkey->n + 1, pubkey->n_len - 1);
				memcpy(align + pubkey->n_len - 1, pubkey->e, pubkey->e_len);
			}

			printf("certif pk dump:\n");
			ndump((u8 *)align , RSA_BIT_WITDH/8*2 );

			printf("calc certif pk hash dump:\n");
			ndump((u8 *)rotpk_hash,32);

			printf("efuse pk dump:\n");
			ndump((u8 *)efuse_hash,32);

			printf("sunxi_certif_pubkey_check: pubkey hash check err\n");
			return -1;
		}
		return 0 ;
	}

}

int sunxi_root_certif_pk_verify(sunxi_certif_info_t *sunxi_certif, u8 *buf, u32 len)
{
	X509 *certif;
	int  ret;

	sunxi_certif_mem_reset();
	ret = sunxi_certif_create(&certif, buf, len);
	if(ret < 0) {
		printf("fail to create a certif\n");
		return -1;
	}
	ret = sunxi_certif_probe_pubkey(certif, &sunxi_certif->pubkey);
	if(ret) {
		printf("fail to probe the public key\n");
		return -1;
	}
	ret = sunxi_certif_pubkey_check(&sunxi_certif->pubkey);
	if(ret){
		printf("fail to check the public key hash against efuse\n");
		return -1;
	}

	sunxi_certif_free(certif);

	return 0;
}
