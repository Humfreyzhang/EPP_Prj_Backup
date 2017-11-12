###############################################################################
# Define targets to build object files
###############################################################################
OBJS_D		=$(patsubst %.c,$(DEPEND_DIR)/%.d,$(filter-out $(FILES_FILTERED), $(wildcard *.c)) )
OBJS_D	       +=$(patsubst %.cpp,$(DEPEND_DIR)/%.d,$(filter-out $(FILES_FILTERED), $(wildcard *.cpp)) )
OBJS_C		=$(patsubst %.c,$(OBJ_DIR)/%.o,$(filter-out $(FILES_FILTERED), $(wildcard *.c)))
OBJS_C	       +=$(patsubst %.cpp,$(OBJ_DIR)/%.o,$(filter-out $(FILES_FILTERED), $(wildcard *.cpp)))
OBJS_ASM	=$(patsubst %.asm,$(OBJ_DIR)/%.o,$(filter-out $(FILES_FILTERED), $(wildcard *.asm)))
OBJS_S		=$(patsubst %.s,$(OBJ_DIR)/%.o,$(filter-out $(FILES_FILTERED), $(wildcard *.s)))
OBJS_SPT	=$(patsubst %.spt,$(OBJ_DIR)/%.o,$(filter-out $(FILES_FILTERED), $(wildcard *.spt)))
OBJS_CLA	=$(patsubst %.cla,$(OBJ_DIR)/%.o,$(filter-out $(FILES_FILTERED), $(wildcard *.cla)))

###############################################################################
# Define targets to build list files
###############################################################################
LST_C			=$(patsubst %.c,$(LISTING_DIR)/%.lst,$(filter-out $(FILES_FILTERED), $(wildcard *.c)))
LST_C		       +=$(patsubst %.cpp,$(LISTING_DIR)/%.lst,$(filter-out $(FILES_FILTERED), $(wildcard *.cpp)))
LST_ASM		=$(patsubst %.asm,$(LISTING_DIR)/%.lst,$(filter-out $(FILES_FILTERED), $(wildcard *.asm)))
LST_S			=$(patsubst %.s,$(LISTING_DIR)/%.lst,$(filter-out $(FILES_FILTERED), $(wildcard *.s)))

###############################################################################
# Build All for this sub project
###############################################################################

###############################################################################
# Create macro containing all known required object files for the subproject
###############################################################################
ALLOBJECTS		+= $(OBJS_C)
ALLOBJECTS		+= $(OBJS_S)
ALLOBJECTS		+= $(OBJS_ASM)
ALLOBJECTS		+= $(OBJS_SPT)
ALLOBJECTS		+= $(OBJS_CLA)

###############################################################################
# select which build_dependency macros to use
###############################################################################
ifeq "$(DIAB_ESYS_BACKSLASH_POUNDS_IN_DEPS)" "0"
build_c_to_dependency = $(build_c_to_dependency_orig)
build_cpp_to_dependency = $(build_cpp_to_dependency_orig)
build_assembly_to_dependency = $(build_assembly_to_dependency_orig)
else
build_c_to_dependency = $(build_c_to_dependency_backslash_pounds)
build_cpp_to_dependency = $(build_cpp_to_dependency_backslash_pounds)
build_assembly_to_dependency = $(build_assembly_to_dependency_backslash_pounds)
endif

# Compiler flags to generate dependency files
#GENDEPFLAGS = -MMD -MP -MF $(DEPEND_DIR)/$(*F).d
###############################################################################
# Build list of all object files created to be streamed to the linker file
###############################################################################
OBJS_TO_LNK	= $(patsubst %.o,%.tolnk,$(ALLOBJECTS))

###############################################################################
# Stream object files to the linker file
###############################################################################
.PHONY: $(OBJS_TO_LNK)
$(OBJS_TO_LNK): $(ALLOBJECTS)
	@echo on
	@echo $(LINKER_OPTION_FILE)
# gmake 4.0 with USE_MULTIPLE_CORES=1 and -O produces nice stdout, 
# but requires the use of $(file) for the generated linker option file to be correct
ifdef GMAKE_4_0
	$(file >>$(LINKER_OPTION_FILE),$(patsubst %.tolnk,%.o,$@))
else
	$(ECHO) $(patsubst %.tolnk,%.o,$@) >> $(LINKER_OPTION_FILE)
endif


###############################################################################
# echo_objects can be used as a target to build linker file
###############################################################################
.PHONY: echo_objects 
echo_objects: $(OBJS_TO_LNK)

###############################################################################
# Build all targets
###############################################################################
.PHONY: all
all: $(ALLOBJECTS)
#ifndef DONT_USE_DIAB_PPC_LINKER_OPTION_FILE)
#	$(MAKE) -C $(CURDIR) -f $(HOME_DIR)/Tools/$(SUBPROJECT_MAK).mak echo_objects
#endif

###############################################################################
# Implicit Rules
###############################################################################
#
###############################################################################
# Implicit rule to create an object file in $(OBJ_DIR) directory from 
# a C file in $(CURDIR) directory
###############################################################################
$(OBJ_DIR)/%.o:$(CURDIR)/%.c
	$(ECHO) Building $(<F) to $(@F)
	$(CC) $< $(CFLAGS)  $(GENDEPFLAGS) --output_file=$@

###############################################################################
# Implicit rule to create an object file in $(OBJ_DIR) directory from 
# assembly file in $(CURDIR) directory
###############################################################################
$(OBJ_DIR)/%.o:$(CURDIR)/%.asm
	$(ECHO) Building $(<F) to $(@F)
	$(CC) $< $(CFLAGS) $(INCLUDE_DIR) --output_file=$@
	
###############################################################################
# Implicit rule to create an object file in $(OBJ_DIR) directory from 
# cla file in $(CURDIR) directory
###############################################################################
$(OBJ_DIR)/%.o:$(CURDIR)/%.cla
	$(ECHO) Building $(<F) to $(@F)
	$(CC) $< $(CFLAGS) $(INCLUDE_DIR) --output_file=$@
###############################################################################
# Implicit rule to create a dependency file
###############################################################################
$(DEPEND_DIR)/%.d:$(CURDIR)/%.c 
	$(GENDEPFLAGS)
###############################################################################
# Default rule: mostly invoked when .h file has been deleted (and deps not yet
# updated)
###############################################################################
.DEFAULT:
	$(warning $< not found.  Default rule used.)