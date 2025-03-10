#
#config file for sun20iw1
#
#stroage
FILE_EXIST=$(shell if [ -f $(TOPDIR)/board/$(PLATFORM)/common.mk ]; then echo yes; else echo no; fi;)
ifeq (x$(FILE_EXIST),xyes)
include $(TOPDIR)/board/$(PLATFORM)/common.mk
else
include $(TOPDIR)/board/$(CP_BOARD)/common.mk
endif

MODULE=sboot
CFG_SUNXI_MMC =y
CFG_SUNXI_NAND =y
CFG_SUNXI_SPINAND =y
CFG_SUNXI_DMA =y
CFG_SUNXI_CE_10 =y
CFG_SUNXI_SMC_11 =y

CFG_SUNXI_SBOOT =y
CFG_SUNXI_ITEM_HASH =n
CFG_SUNXI_KEY_PROVISION =n

CFG_SUNXI_JTAG_DISABLE =y
CFG_SUNXI_VERIFY_MALLCO_SIZE = 4096
