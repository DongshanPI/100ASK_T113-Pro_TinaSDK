#
# (C) Copyright 2000-2003
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# See file CREDITS for list of people who contributed to this
# project.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

include $(TOPDIR)/mk/config.mk
LIB	=  libsecure.o

COBJS-$(CFG_SUNXI_CE_20)+= ce.o
COBJS-$(CFG_SUNXI_CE_10)+= ce.o
COBJS-$(CFG_SUNXI_CE_21)+= ce_2.1.o
COBJS-$(CFG_SUNXI_CE_23)+= ce_2.3.o
COBJS-$(CFG_SUNXI_SBOOT) += smc.o
#COBJS-y	+= spc.o
COBJS-$(CFG_SUNXI_EFUSE)	+= efuse.o

SRCS	:= $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS-y))

all:	$(obj).depend $(LIB)

$(LIB):	$(OBJS)
	$(call cmd_link_o_target, $(OBJS))

#########################################################################

depend:	$(obj).depend
.PHONY: depend

# defines $(obj).depend target
include $(TOPDIR)/mk/rules.mk
