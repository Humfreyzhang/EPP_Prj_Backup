
MAKFILE_DEPENDS=$(CURDIR)/Makefile.mak

export HOME_DIR =$(subst /Makefile,,$(CURDIR))

export ABS_MAK_PATH = $(CURDIR)

export PRODUCTS_DIR ?= $(HOME_DIR)

export OBJ_DIR  ?= $(PRODUCTS_DIR)/objs_$(PROG_NAME)

export OUTPUT_DIR ?= $(PRODUCTS_DIR)/out_$(PROG_NAME)

export LISTING_DIR ?= $(PRODUCTS_DIR)/listing_$(PROG_NAME)

export PRE_DIR ?= $(PRODUCTS_DIR)/pre_$(PROG_NAME)

export DEPEND_DIR ?= $(PRODUCTS_DIR)/depend_$(PROG_NAME)

export ASM_DIR ?= $(PRODUCTS_DIR)/asm_$(PROG_NAME)

export SRC_DIR ?= $(PRODUCTS_DIR)/src_$(PROG_NAME)

# detect if using gmake (gnumake 4.0)
export GMAKE_4_0 ?= $(if $(findstring gmake,$(MAKE)),1)

###############################################################################
# Include the Program Named Makefile that is in the Application Build Directory
###############################################################################
include $(subst \,/,$(BUILD))

BEFORE_BUILD_TARGETS += bldalldirs

BUILD_DIRS=$(SUBDIRS)

###############################################################################
# program name macro must be defined.
###############################################################################
ifndef PROG_NAME 
$(error Application must define PROG_NAME macro )
endif

##############################################################################
# VERSION_FILE variables
###############################################################################
VERSION_FILE ?= $(OUTPUT_DIR)/$(PROG_NAME).versions
VERSION_FILE_DELIM ?= ::

###############################################################################
# export PROG_NAME so other make process can use this macro.
###############################################################################
export PROG_NAME

###############################################################################
# This is the directory where your .h and .hpp, files reside.
###############################################################################
#INCLUDE_DIR += $(patsubst %,--include_path=$(HOME_DIR)/%,$(SUBDIRS))
INCLUDE_DIR += $(patsubst %,--include_path=$(HOME_DIR)/%,$(INCDIRS))

export INCLUDE_DIR
###############################################################################
# Include Compiler specific Make
###############################################################################
# default extensions
LST_EXT=lst
OBJ_EXT=o

###############################################################################
# GCC Compiler
###############################################################################
ifeq "$(config_Compiler_Vendor)" "option_TI_C28X"
MTSA_TOOLSET = TI_C280X
else

###############################################################################
# No Compiler Defined
###############################################################################
$(error Invalid vendor for Compile process -> $(config_Compiler_Vendor))
endif

MTSA_MAKEFILE ?= $(MTSA_TOOLSET)
include $(HOME_DIR)/Tools/$(MTSA_MAKEFILE).mak

###############################################################################
# ASAP define
###############################################################################
ASAP = $(HOME_DIR)/Tools/ASAP.mak
###############################################################################
# Build Targets
###############################################################################

###############################################################################
# Build all targets
###############################################################################
all: $(BEFORE_BUILD_TARGETS) subproject generatefiles
	@echo building is compiled.
#
#subproject $(AFTER_BUILD_TARGETS) 
###############################################################################
# Subproject Build Process
###############################################################################
###############################################################################
# Subproject required directories
###############################################################################


###############################################################################
# Create output Directories
###############################################################################
.PHONY: bldalldirs
bldalldirs : bldproddir bldoutputdir blddependdir  bldobjdir 
#
###############################################################################
# Create products depository directory
###############################################################################
.PHONY: bldproddir
bldproddir: $(PRODUCTS_DIR)
$(PRODUCTS_DIR):
	$(MAKE_DIR) $@

###############################################################################
# Make sure we have a output directory
###############################################################################
.PHONY: bldoutputdir
bldoutputdir : $(OUTPUT_DIR)
$(OUTPUT_DIR): $(PRODUCT_DIR)
	$(MAKE_DIR) $@
	
###############################################################################
# create subproject dependency directory
###############################################################################
.PHONY: blddependdir
blddependdir: $(DEPEND_DIR)
$(DEPEND_DIR): $(PRODUCT_DIR)
	$(MAKE_DIR) $@

###############################################################################
# Create subproject c to assembly directory
###############################################################################
.PHONY: bldasmdir
bldasmdir: $(ASM_DIR)
$(ASM_DIR): $(PRODUCT_DIR)
	$(MAKE_DIR) $@

###############################################################################
# Create object file depository directory
###############################################################################
.PHONY: bldobjdir
bldobjdir: $(OBJ_DIR)
$(OBJ_DIR): $(PRODUCT_DIR)
	$(MAKE_DIR) $@
	

###############################################################################
# Create preprocessed file depository directory
###############################################################################
.PHONY: bldpredir
bldpredir: $(PRE_DIR)
$(PRE_DIR): $(PRODUCT_DIR)
	$(MAKE_DIR) $@
	
###############################################################################
# Create file listing depository directory
###############################################################################
.PHONY: bldlstdir
bldlstdir: $(LISTING_DIR)
$(LISTING_DIR): $(PRODUCT_DIR)
	$(MAKE_DIR) $@
	

###############################################################################
# Phony target to remove linker option file
###############################################################################
.PHONY: remove_linker_option 
remove_linker_option: $(OUTPUT_DIR)
	$(RM) -f $(LINKER_OPTION_FILE)
	
###############################################################################
# 				BUILD SUB PROJECTS
###############################################################################
# Build all source code here
###############################################################################
SUBMAKALLS = $(patsubst %,%.makall,$(BUILD_DIRS))

.PHONY: subproject $(SUBMAKALLS)
subproject: $(SUBMAKALLS)

$(SUBMAKALLS): remove_linker_option
	$(MAKE) all -C $(patsubst %.makall,$(HOME_DIR)/%,$@) -f $(HOME_DIR)/Tools/$(SUBPROJECT_MAK).mak SUBPROJECT_FILTER="$($(patsubst %.makall,%,$@)_FILTER)"
.PHONY: generatefiles
generatefiles:
	$(MAKE) all -C $(HOME_DIR)/Tools -f $(ASAP) all

	
.PHONY: cleanall
cleanall:
	$(RM) -rf $(OUTPUT_DIR)
	$(RM) -rf $(OBJ_DIR)  
	$(RM) -rf $(DEPEND_DIR) 
	$(RM) -rf $(PRODUCTS_DIR)