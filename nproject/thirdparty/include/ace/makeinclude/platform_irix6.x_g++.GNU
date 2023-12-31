# $Id: platform_irix6.x_g++.GNU 80826 2008-03-04 14:51:23Z wotte $

# Irix 6.X with GNU C++

include makeinclude/platform_irix6.x_common.GNU

CC              = gcc
CXX             = g++
CFLAGS          += $(DCFLAGS)

DCFLAGS         += -g
DLD             = $(CXX)
LD              = $(CXX)
LDFLAGS         += -L$(ACE_ROOT)/lib -Wl,-dont_warn_unused
LIBS            += -lpthread
OCFLAGS         += -O2
PIC             = -fpic
# AR            = ar
ARFLAGS         = rv
RANLIB          = @true
SOFLAGS         += -shared $(CPPFLAGS)
SOBUILD         = $(COMPILE.cc) $(PIC) -o $(VSHDIR)$*.o $<; \
                  $(SOLINK.cc) $(LDFLAGS) -o $@ $(VSHDIR)$*.o

# Test for template instantiation, add to SOFLAGS if SONAME set,
# add -E to LDFLAGS if using GNU ld
#
include makeinclude/platform_g++_common.GNU

CCFLAGS         += $(CFLAGS) $(TEMPLATES_FLAG)
