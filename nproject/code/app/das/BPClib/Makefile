#------------------------------------------------------------------------------
# Makefile for mytest
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
include ~/Make/Makefile.init

#------------------------------------------------------------------------------
TARGET_NAME := BPC
TARGET_TYPE := dll

#------------------------------------------------------------------------------
#CXX_MACRO += -DLINK_DBSRV
CXX_MACRO += 

#------------------------------------------------------------------------------
# INPUT_FILES += -lNodeMan
# SHARE_FILES += -lcrypto -lssl
INPUT_FILES += -ldppclientMR64 -lmdbMR64 -lsdbMR64 -lACEMR64 -lnetMR64 -lZIPMR64 -ldboperMR64 -ldasbase -ldpf -ltopana
# SHARE_FILES += -lcrypto -lssl -lACEMR64
# INPUT_FILES += 

#------------------------------------------------------------------------------
VPATH := $(VPATH):$(PROGRAMS_DIR)/app/das/BPClib

#------------------------------------------------------------------------------
SOURCE_LIST := CalCaseDataOp.cpp geneticalAlgorithm.cpp

#------------------------------------------------------------------------------
include ~/Make/Makefile.rule

#------------------------------------------------------------------------------
# End
#-------------------------------------------------------------------------
