IPTARGETS := lib
ifneq ($(IPMAKEFILE),)
include $(IPMAKEFILE)
else
include $(IPCOM_ROOT)/Makefile
endif
include InterpeakMntn.mk
include $(IPCOM_ROOT)/gmake/ipcom_make.mk

lib: dirs $(IPLIBFILE)
