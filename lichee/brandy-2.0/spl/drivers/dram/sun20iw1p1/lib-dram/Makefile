# # (C) Copyright 2013-2016
# SPDX-License-Identifier: GPL-2.0+
# SPDX-License-Identifier: GPL-2.0+
#  Allwinner Technology Co., Ltd. <www.allwinnertech.com>
#
#  SPDX-License-Identifier:     GPL-2.0+
#


include $(TOPDIR)/mk/config.mk

LIB	:= $(obj)libdram.o

COBJS += mctl_hal.o


COBJS	:= $(COBJS)
SRCS	:= $(COBJS:.o=.S)
OBJS	:= $(addprefix $(obj),$(COBJS))

all:	$(LIB)

$(LIB):	$(obj).depend $(OBJS)
	$(call cmd_link_o_target, $(OBJS))
	cp $(LIB) ../libdram

#########################################################################

# defines $(obj).depend target
include $(TOPDIR)/mk/rules.mk

sinclude $(obj).depend

#########################################################################
