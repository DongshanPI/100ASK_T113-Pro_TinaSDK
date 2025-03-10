cmd_drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_strs.o := arm-openwrt-linux-muslgnueabi-gcc -Wp,-MD,drivers/net/wireless/aic8800/aic8800_fdrv/.rwnx_strs.o.d  -nostdinc -isystem /home/ubuntu/tina-d1-h/prebuilt/gcc/linux-x86/arm/toolchain-sunxi-musl/toolchain/bin/../lib/gcc/arm-openwrt-linux-muslgnueabi/6.4.1/include -I./arch/arm/include -I./arch/arm/include/generated  -I./include -I./arch/arm/include/uapi -I./arch/arm/include/generated/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/kconfig.h -include ./include/linux/compiler_types.h -D__KERNEL__ -mlittle-endian -Wall -Wundef -Werror=strict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -fshort-wchar -fno-PIE -Werror=implicit-function-declaration -Werror=implicit-int -Wno-format-security -std=gnu89 -fno-dwarf2-cfi-asm -fno-ipa-sra -mabi=aapcs-linux -mfpu=vfp -funwind-tables -marm -Wa,-mno-warn-deprecated -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -fno-delete-null-pointer-checks -Wno-frame-address -Os --param=allow-store-data-races=0 -Wframe-larger-than=2048 -fstack-protector-strong -Wno-unused-but-set-variable -Wno-unused-const-variable -fomit-frame-pointer -fno-var-tracking-assignments -Wdeclaration-after-statement -Wvla -Wno-pointer-sign -Wno-array-bounds -Wno-maybe-uninitialized -fno-strict-overflow -fno-merge-all-constants -fmerge-constants -fno-stack-check -fconserve-stack -Werror=date-time -Werror=incompatible-pointer-types -Werror=designated-init -DCONFIG_RWNX_DEBUGFS -DCONFIG_RWNX_UM_HELPER_DFLT=\""/dini/dini_bin/rwnx_umh.sh"\" -DNX_VIRT_DEV_MAX=4 -DNX_REMOTE_STA_MAX_FOR_OLD_IC=10 -DNX_REMOTE_STA_MAX=32 -DNX_MU_GROUP_MAX=62 -DNX_TXDESC_CNT=64 -DNX_TX_MAX_RATES=4 -DNX_CHAN_CTXT_CNT=3 -DCONFIG_START_FROM_BOOTROM -DCONFIG_PMIC_SETTING -DCONFIG_VRF_DCDC_MODE -DCONFIG_ROM_PATCH_EN -DCONFIG_COEX -DCONFIG_RWNX_FULLMAC -I. -I./drivers/net/wireless/aic8800/aic8800_fdrv -I./drivers/net/wireless/aic8800/aic8800_fdrv/../aic8800_bsp -DCONFIG_AIC_FW_PATH=\""/lib/firmware"\" -DCONFIG_RWNX_RADAR -DCONFIG_RWNX_MON_DATA -DCONFIG_RWNX_DBG -DCONFIG_RFTEST -DDEFAULT_COUNTRY_CODE=""\"00""\" -DCONFIG_SUPPORT_REALTIME_CHANGE_MAC -DCONFIG_SCHED_SCAN -DCONFIG_PREALLOC_TXQ -DAICWF_SDIO_SUPPORT -DCONFIG_SDIO_PWRCTRL -DCONFIG_USER_MAX=1 -DNX_TXQ_CNT=5 -DAICWF_RX_REORDER -DAICWF_ARP_OFFLOAD -DCONFIG_RX_NETIF_RECV_SKB -DAIC_TRACE_INCLUDE_PATH=drivers/net/wireless/aic8800/aic8800_fdrv -DCONFIG_PLATFORM_ALLWINNER -DANDROID_PLATFORM  -DMODULE  -DKBUILD_BASENAME='"rwnx_strs"' -DKBUILD_MODNAME='"aic8800_fdrv"' -c -o drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_strs.o drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_strs.c

source_drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_strs.o := drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_strs.c

deps_drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_strs.o := \
    $(wildcard include/config/rwnx/fullmac.h) \
  include/linux/kconfig.h \
    $(wildcard include/config/cc/version/text.h) \
    $(wildcard include/config/cpu/big/endian.h) \
    $(wildcard include/config/booger.h) \
    $(wildcard include/config/foo.h) \
  include/linux/compiler_types.h \
    $(wildcard include/config/have/arch/compiler/h.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/optimize/inlining.h) \
    $(wildcard include/config/cc/has/asm/inline.h) \
  include/linux/compiler_attributes.h \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/retpoline.h) \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
  drivers/net/wireless/aic8800/aic8800_fdrv/lmac_msg.h \
    $(wildcard include/config/rwnx/fhost.h) \
    $(wildcard include/config/mcu/message.h) \
  drivers/net/wireless/aic8800/aic8800_fdrv/lmac_mac.h \
    $(wildcard include/config/he/for/old/kernel.h) \
    $(wildcard include/config/vht/for/old/kernel.h) \
  drivers/net/wireless/aic8800/aic8800_fdrv/lmac_types.h \
    $(wildcard include/config/rwnx/tl4.h) \
  include/generated/uapi/linux/version.h \
  include/linux/types.h \
    $(wildcard include/config/have/uid16.h) \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  include/uapi/linux/types.h \
  arch/arm/include/uapi/asm/types.h \
  include/asm-generic/int-ll64.h \
  include/uapi/asm-generic/int-ll64.h \
  arch/arm/include/generated/uapi/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/uapi/asm-generic/bitsperlong.h \
  include/uapi/linux/posix_types.h \
  include/linux/stddef.h \
  include/uapi/linux/stddef.h \
  include/linux/compiler_types.h \
  arch/arm/include/uapi/asm/posix_types.h \
  include/uapi/asm-generic/posix_types.h \
  include/linux/bits.h \
  include/linux/const.h \
  include/vdso/const.h \
  include/uapi/linux/const.h \
  include/vdso/bits.h \

drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_strs.o: $(deps_drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_strs.o)

$(deps_drivers/net/wireless/aic8800/aic8800_fdrv/rwnx_strs.o):
