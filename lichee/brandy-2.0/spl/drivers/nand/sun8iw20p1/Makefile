#
# (C) Copyright 2013-2016
#  Allwinner Technology Co., Ltd. <www.allwinnertech.com>
#
#


include $(TOPDIR)/mk/config.mk

LIB	:= $(obj)libnand.o

COBJS += nand/adv_NF_read.o
COBJS += nand/basic_nf_read.o

COBJS += nand_bsp/nand_for_boot0/nand_for_boot0.o  nand_bsp/nand_for_boot0/osal/nand_osal_boot0.o
COBJS += nand_bsp/nfc_for_boot0/src/nand_scan_for_boot.o  nand_bsp/nfc_for_boot0/src/nfc_for_boot0.o  nand_bsp/nfc_for_boot0/src/nand_simple_for_boot0.o

COBJS += spinand/spic_op.o
COBJS += spinand/spinand.o
COBJS += spinand/spinand_basic_op.o
COBJS += spinand/spinand_osal_boot0.o



COBJS	:= $(COBJS)
SRCS	:= $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS))

all:	$(LIB)

$(LIB):	$(obj).depend $(OBJS)
	$(call cmd_link_o_target, $(OBJS))

#########################################################################

# defines $(obj).depend target
include $(TOPDIR)/mk/rules.mk

sinclude $(obj).depend

#########################################################################
