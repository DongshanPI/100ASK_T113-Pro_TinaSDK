
include $(TOPDIR)/mk/config.mk

LIB	:= $(obj)libmain.o

HEAD    := sboot_head.o
MAIN	:= sboot_main.o

COBJS-y += sboot_toc1.o
COBJS-y += sboot_ceritf.o
COBJS-y += sboot_flash.o

SRCS	:= $(MAIN:.o=.c) $(COBJS:.o=.c) $(HEAD:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS) $(COBJS-y) $(SOBJS))
HEAD    := $(addprefix $(obj),$(HEAD))
MAIN	:= $(addprefix $(obj),$(MAIN))

all:	$(obj).depend $(HEAD) $(MAIN) $(LIB)

$(LIB):	$(OBJS) $(HEAD)
	$(call cmd_link_o_target, $(OBJS))


#########################################################################

# defines $(obj).depend target
include $(TOPDIR)/mk/rules.mk

sinclude $(obj).depend

#########################################################################
