
RECORD_TIMES = 0
export RECORD_TIMES


DIAB_ESYS_COMPILER_BASE_PATH ?= $(HOME_DIR)/Tools/C28X/bin
LinkInf_FILE = $(OUTPUT_DIR)/EPP_Project_linkInfo.xml

export SUBPROJECT_MAK = SubProject_TI_C280X


ifndef DIAB_ESYS_BACKSLASH_POUNDS_IN_DEPS
DIAB_ESYS_BACKSLASH_POUNDS_IN_DEPS=0
endif
export DIAB_ESYS_BACKSLASH_POUNDS_IN_DEPS


# Define programs and commands
export TOOLCHAIN = $(DIAB_ESYS_COMPILER_BASE_PATH)
export CC        = $(TOOLCHAIN)/cl2000
export IntertoHex = $(TOOLCHAIN)/hex2000
export NM        = $(TOOLCHAIN)/nm2000
export link      = $(TOOLCHAIN)/lnk2000

 
CPU = -v28 -ml -mt --cla_support=cla0 

OPT = 2
CFLAGS  = -O$(OPT)
CFLAGS   += $(CPU) $(INCLUDE_DIR)
CFLAGS += --verbose -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile 
export CFLAGS
#---------------- Linker Options ----------------
#  -Wl,...:     tell GCC to pass this to linker
#    -Map:      create map file
#    --cref:    add cross reference to  map file
LDFLAGS  += $(CPU) -g --diag_warning=225 --display_error_number --diag_wrap=off -z -m$(SYS_MAP_FILE) 
LDFLAGS  += --stack_size=0x200 --warn_sections $(Link_Include_DIR) 
LDFLAGS += --reread_libs --define=CLA_SCRATCHPAD_SIZE=0x100 --display_error_number --diag_wrap=off 
LDFLAGS += --xml_link_info=$(LinkInf_FILE) --rom_model -o 


	
export ASFLAGS =

ASFLAGS  += $(CPU)
export LDFLAGS
# Compiler flags to generate dependency files
export GENDEPFLAGS = --preproc_dependency=$(DEPEND_DIR)/$$(*F).d

export LINKER_OPTION_FILE =

export DIAB_ESYS_DDUMP ?= 

export DIAB_ESYS_DDUMP_FLAGS += -R -m2 -v

export DIAB_ESYS_DDUMP_S19 =$(DUMP) $(DIAB_ESYS_DDUMP_FLAGS) $(DIAB_ESYS_ELF_FILE) -o$(DIAB_ESYS_S19_FILE)
MAKFILE_DEPENDS += $(HOME_DIR)/Tools/TI_C280X.mak