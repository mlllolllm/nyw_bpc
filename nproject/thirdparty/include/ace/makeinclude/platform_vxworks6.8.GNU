# $Id: platform_vxworks6.8.GNU 87036 2009-10-10 18:21:39Z johnnyw $
# VxWorks 6.8

ifeq ($(VXWORKS_VERSION_FLAG),)
  VXWORKS_VERSION_FLAG = -DACE_VXWORKS=0x680
endif # VXWORKS_VERSION_FLAG

include makeinclude/platform_vxworks6.7.GNU

