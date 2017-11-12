###############################################################################
#
#       
#
#       Confidential
#
# ============================================================================
#
#  Multi-target makefile to build subproject code
#
# %name:            Tool_Compile.mak %
# %derived_by:      zzrfyj %
# %date_modified:                     Thu Dec  4 17:44:31 2014 %
# %version:         ctc_pt3#8.1.12 %
#
###############################################################################

config_CPU_Type=TI_C2000

config_Compiler_Vendor=option_TI_C28X


TOOLS_PATH ?= $(HOME_DIR)/Tools/Utilities
###############################################################################
# export TOOLS_PATH so other make process can use this macro.
###############################################################################
export TOOLS_PATH

###############################################################################
# Make Tools
###############################################################################
SED	?= $(TOOLS_PATH)/sed
export SED

RM 	= $(TOOLS_PATH)/rm
export RM

RMDIR 	?= $(TOOLS_PATH)/rmdir
export RMDIR

COPY 	?= $(TOOLS_PATH)/cp
export COPY

MOVE 	?= $(TOOLS_PATH)/mv
export MOVE

ECHO 	?= $(TOOLS_PATH)/echo
export ECHO

TOUCH 	?= $(TOOLS_PATH)/touch
export TOUCH

MAKE_DIR ?=$(TOOLS_PATH)/mkdir -p
export MAKE_DIR

TYPE 	?= $(TOOLS_PATH)/cat
export TYPE

CAT 	?= $(TOOLS_PATH)/cat
export CAT

#TEST 	?= $(TOOLS_PATH)/test
#export TEST

PTP 	?= $(TOOLS_PATH)/ptp
export PTP


CHMOD 	?= $(TOOLS_PATH)/chmod
export CHMOD

FLIP 	?= $(TOOLS_PATH)/legacy/flip
export FLIP

LS	?= $(TOOLS_PATH)/ls
export LS

CALG	?= $(TOOLS_PATH)/CalCreate
export CALG

DATE	?= $(TOOLS_PATH)/date
export DATE

export DUMP ?=$(TOOLS_PATH)/ddump

export S19toBin ?=$(TOOLS_PATH)/S19toBin

ifeq ($(SMAKE),YES)
USE_MULTIPLE_CORES = 1
JOBS = 16
else
USE_MULTIPLE_CORES = 0
endif




PRODUCTS_DIR= $(HOME_DIR)/Products



###############################################################################
# This is a path to the compiler/linker.
###############################################################################








###############################################################################
# Setup the make files which are included in the build
###############################################################################
MAKFILE_DEPENDS += $(HOME_DIR)/Tools/Tool_Compile.mak

