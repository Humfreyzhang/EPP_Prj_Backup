##############################################################################
#
#  COPYRIGHT, 2001,2009, DELPHI DELCO ELECTRONICS SYSTEMS CORPORATION
# ---------------------------------------------------------------------------
#
#  Multi-target makefile to build subproject code
#
#  Authors: hz1fbl
# ---------------------------------------------------------------------------
#
# %name:            OBD_Communication.mak %
# created_by:       hz1fbl
# date_created:
# %derived_by:      pz0vmh %
# %version:         1 %
#
##############################################################################
#PROGRAM_DIR = 10020457



SUBDIRS += STM32F4-Discovery
SUBDIRS += Third_Party\fat_fs\src
SUBDIRS += Third_Party\fat_fs\src\option



#I6L_COMM_CALIBRATION_FILES += Communication/OBDLIB/ofvccald.c

###############################################################################
# Directory included for compiling.
# Section 3
###############################################################################
INCDIRS += STM32F4-Discovery
INCDIRS += Third_Party\fat_fs\inc

# Setup the make files which are included in the build
###############################################################################
#MAKFILE_DEPENDS += $(HOME_DIR)/$(PROGRAM_DIR)_Communication/OBD/build/OBD_Communication.mak
