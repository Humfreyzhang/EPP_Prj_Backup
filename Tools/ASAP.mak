
##############################################################################
# Diab S19 macros
###############################################################################

.PHONY: all 

all: echofile $(SYS_OUT_FILE) $(SYS_HEX_FILE) $(SYS_S19_FILE) $(SYS_CAL_FILE) $(SYS_BIN_FILE)
	@echo ASAP.mak is complited.
	
	
###############################################################################
# Create an link cmd file 
###############################################################################
.PHONY: echofile
echofile:cleanobjectlist
	@dir $(subst /,\,$(OBJ_DIR))\*.o  /B /S > $(subst /,\,$(SYS_Objlst_FILE))
	
cleanobjectlist:
	-@$(RM) -f $(subst /,\,$(SYS_Objlst_FILE))
	
###############################################################################
# Create an bin file 
###############################################################################
$(SYS_BIN_FILE): $(SYS_S19_FILE)
	@echo on
	$(RM) -f $@
	@echo Creating bin file: $@
	$(S19toBin) $< $@  3E8000 3F3FFF
	
###############################################################################
# Create an elf file
###############################################################################
$(SYS_OUT_FILE):
	$(ECHO) Linking $(@F)
	$(RM) -f $@
	$(CC) $(LDFLAGS) $@ $(SYS_Objlst_FILE) $(Link_CMD) $(Link_Lib_DIR)
	
###############################################################################
# Create final output files (.hex, .eep) from ELF output file.
###############################################################################
$(SYS_HEX_FILE): $(SYS_OUT_FILE)
	@echo on
	$(RM) -f $@
	@echo Creating hex file: $@
	$(IntertoHex) -i $< -o $@ -order MS  -romwidth 16

# Create a symbol table from ELF output file
$(SYS_SYM_FILE): $(SYS_OUT_FILE)
	@echo on
	$(RM) -f $@
	@echo Creating Symbol Table: $@
	$(NM) -n $< > $@
	
###############################################################################
# Create an s19 file 
###############################################################################
$(SYS_S19_FILE): $(SYS_OUT_FILE)
	$(ECHO) Building $(@F)
	$(RM) -f $@
	$(IntertoHex) -m3 $< -o $@ -order MS  -romwidth=16
	$(ECHO) $(@F) built

###############################################################################
# Create an CAL file 
###############################################################################
$(SYS_CAL_FILE): $(SYS_S19_FILE)
	$(RM) -f $@
	$(CALG) create $< 3E8000:3E8100 cksum_disalbe $(OUTPUT_DIR)/temp.s19
	$(PTP) convert $(OUTPUT_DIR)/temp.s19 -RECORDTYPE=3 -QUIET -output=$@
	$(RM) $(OUTPUT_DIR)/temp.s19
###############################################################################
# Show the build sizes
###############################################################################
Showsize:
	@$(SIZE) $(SYS_OUT_FILE)
	
	
MAKFILE_DEPENDS += $(HOME_DIR)/Tools/ASAP.mak