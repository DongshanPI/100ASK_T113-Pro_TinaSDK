#/*
# * Copyright 2000-2009
#  * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#   *
#    */

include $(TOPDIR)/mk/config.mk

all:
ifeq ($(notdir $(shell find ./ -name lib-dram)), lib-dram)
	make -C lib-dram
else
	@echo "libdram exist"
endif

ifeq ($(notdir $(shell find ./ -name lib-chipid)), lib-chipid)
	make -C lib-chipid
else
	@echo "lib-chipid exist"
endif


#########################################################################

depend:	$(obj).depend
.PHONY: depend

# defines $(obj).depend target
include $(TOPDIR)/mk/rules.mk

#########################################################################
