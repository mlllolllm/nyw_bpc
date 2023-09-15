debug := 0
buildbits := 64
symlinks := absolute
static_libs=0

OS_NAME_SZ ?= $(shell uname -s)

ifeq ($(OS_NAME_SZ),Linux)
  include makeinclude/platform_linux.GNU
endif

ifeq ($(OS_NAME_SZ),SunOS)
  include makeinclude/platform_sunos5_g++.GNU
endif

ifeq ($(OS_NAME_SZ),HP-UX)
  include makeinclude/platform_hpux_gcc.GNU
endif

ifeq ($(OS_NAME_SZ),AIX)
  include makeinclude/platform_aix_g++.GNU
endif
