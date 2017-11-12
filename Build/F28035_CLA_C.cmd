/*
//###########################################################################
//
// FILE:	F28035_CLA_C.cmd
//
// TITLE:	Linker Command File For F28035 Device
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################
*/

/* ======================================================
// For Code Composer Studio V2.2 and later
// ---------------------------------------
// In addition to this memory linker command file,
// add the header linker command file directly to the project.
// The header linker command file is required to link the
// peripheral structures to the proper locations within
// the memory map.
//
// The header linker files are found in <base>\DSP2803x_Headers\cmd
//
// For BIOS applications add:      DSP2803x_Headers_BIOS.cmd
// For nonBIOS applications add:   DSP2803x_Headers_nonBIOS.cmd
========================================================= */

/* ======================================================
// For Code Composer Studio prior to V2.2
// --------------------------------------
// 1) Use one of the following -l statements to include the
// header linker command file in the project. The header linker
// file is required to link the peripheral structures to the proper
// locations within the memory map                                    */

/* Uncomment this line to include file only for non-BIOS applications */
/* -l DSP2803x_Headers_nonBIOS.cmd */

/* Uncomment this line to include file only for BIOS applications */
/* -l DSP2803x_Headers_BIOS.cmd */

/* 2) In your project add the path to <base>\DSP2803x_headers\cmd to the
   library search path under project->build options, linker tab,
   library search path (-i).
/*========================================================= */

/* Define the memory block start/length for the F28035
   PAGE 0 will be used to organize program sections
   PAGE 1 will be used to organize data sections

   Notes:
         Memory blocks on F2803x are uniform (ie same
         physical memory) in both PAGE 0 and PAGE 1.
         That is the same memory region should not be
         defined for both PAGE 0 and PAGE 1.
         Doing so will result in corruption of program
         and/or data.

         L0 memory block is mirrored - that is
         it can be accessed in high memory or low memory.
         For simplicity only one instance is used in this
         linker file.

         Contiguous SARAM memory blocks or flash sectors can be
         be combined if required to create a larger memory block.
*/
_Cla1Prog_Start = _Cla1funcsRunStart;
-heap 0x200
-stack 0x200

// Define a size for the CLA scratchpad area that will be used
// by the CLA compiler for local symbols and temps
// Also force references to the special symbols that mark the
// scratchpad are. 
// CLA_SCRATCHPAD_SIZE = 0x100;
--undef_sym=__cla_scratchpad_end
--undef_sym=__cla_scratchpad_start

MEMORY
{
PAGE 0:    /* Program Memory */
           /* Memory (RAM/FLASH/OTP) blocks can be moved to PAGE1 for data allocation */
   RAMM0_stack : origin = 0x000050, length = 0x000200     /* on-chip RAM block M0 */
   UNclear     : origin = 0x000250, length = 0x000008     /* on-chip RAM block M1 unclear area*/
   RAMM0_Run   : origin = 0x000258, length = 0x0000A8     /* on-chip RAM block M0 */
   RAMM0_CAL   : origin = 0x000300, length = 0x000100     /* on-chip RAM block M0 CAL*/
   RAML3       : origin = 0x009000, length = 0x001000     /* on-chip RAM block L3 */ 
   OTP         : origin = 0x3D7800, length = 0x000400     /* on-chip OTP */
   FLASHH_CAL  : origin = 0x3E8000, length = 0x000100  f = 0x0000   /* on-chip FLASH CAL*/
   FLASHH_run  : origin = 0x3E8100, length = 0x000700  f = 0x0000   /* on-chip FLASH run function*/ 
   FLASHH_Const: origin = 0x3E8800, length = 0x0007FC  f = 0x0000   /* on-chip FLASH const vars*/
   FLASHH_SWVR : origin = 0x3E8FFC, length = 0x000003  f = 0x0000   /* on-chip FLASH const vars*/
   FLASHH_IDCal: origin = 0x3E8FFF, length = 0x000001  f = 0x0000   /* on-chip FLASH const vars*/
   FLASH_APP   : origin = 0x3E9000, length = 0x00B000  f = 0x0000   /* on-chip FLASH */
   IQTABLES    : origin = 0x3FE000, length = 0x000B50     /* IQ Math Tables in Boot ROM */
   IQTABLES2   : origin = 0x3FEB50, length = 0x00008C     /* IQ Math Tables in Boot ROM */
   IQTABLES3   : origin = 0x3FEBDC, length = 0x0000AA	  /* IQ Math Tables in Boot ROM */
   RESET       : origin = 0x3FFFC0, length = 0x000002     /* part of boot ROM  */


PAGE 1 :   /* Data Memory */
           /* Memory (RAM/FLASH/OTP) blocks can be moved to PAGE0 for program allocation */
           /* Registers remain on PAGE1                                                  */
   BOOT_RSVD   : origin = 0x000000, length = 0x000050     /* Part of M0, BOOT rom will use this for stack */
   RAMM1       : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
   RAML        : origin = 0x008000, length = 0x000700     /* on-chip RAM block L0 */
   RAMEE       : origin = 0x008700, length = 0x0001FF     /* on-chip RAM block L0 */
   RAMEE_cksum : origin = 0x0088FF, length = 0x000001     /* on-chip RAM block L0 */   
   RAML1_CAN   : origin = 0x008900, length = 0x000300     /* on-chip RAM block L1 CAN*/
/* CLARAM0     : origin = 0x008800, length = 0x000400     */
   CLARAM1     : origin = 0x008C00, length = 0x000400

   CLA1_MSGRAMLOW   : origin = 0x001480, length = 0x000080
   CLA1_MSGRAMHIGH  : origin = 0x001500, length = 0x000080
   
   FLASHB      : origin = 0x3F4000, length = 0x002000     /* on-chip FLASH */

}

/* Allocate sections to memory blocks.
   Note:
         codestart user defined section in DSP28_CodeStartBranch.asm used to redirect code
                   execution when booting to flash
         ramfuncs  user defined section to store functions that will be copied from Flash into RAM
*/

SECTIONS
{

   /* Allocate program areas: */
   ramfuncs            : LOAD = FLASHH_run,
                         RUN = RAMM0_Run,
                         LOAD_START(_RamfuncsLoadStart),
                         LOAD_SIZE(_RamfuncsLoadSize),
                         RUN_START(_RamfuncsRunStart),
                         PAGE = 0

   /* Allocate uninitalized data sections: */
   .stack              : > RAMM0_stack       PAGE = 0
   .cio                : > RAMM1      PAGE = 1
   .sysmem             : > RAMM1       PAGE = 1
   .ebss               : >> RAMM1 | RAML      PAGE = 1
   .esysmem            : > RAML       PAGE = 1
                     
   /* Initalized sections go in Flash */
   /* For SDFlash to program these, they must be allocated to page 0 */
   .econst             : > FLASHH_Const      PAGE = 0
   .switch             : > FLASHH_Const      PAGE = 0
   .cinit              : > FLASHH_Const      PAGE = 0
   .pinit              : > FLASHH_Const,     PAGE = 0   
   
   /* Allocate IQ math areas: */
   IQmath              : > FLASHH_run      PAGE = 0            /* Math Code */
   IQmathTables        : > IQTABLES,   PAGE = 0, TYPE = NOLOAD
   
   .bss_cla		       : > CLARAM1,   PAGE = 1
   .scratchpad         : > CLARAM1,   PAGE = 1
   Cla1Prog            : LOAD = FLASHH_run,
                         RUN = RAML3,
                         LOAD_START(_Cla1funcsLoadStart),
                         LOAD_END(_Cla1funcsLoadEnd),
                         RUN_START(_Cla1funcsRunStart),
                         LOAD_SIZE(_Cla1funcsLoadSize),
                         PAGE = 0
						 
   Cla1ToCpuMsgRAM     : > CLA1_MSGRAMLOW,   PAGE = 1
   CpuToCla1MsgRAM     : > CLA1_MSGRAMHIGH,  PAGE = 1
   /*Cla1DataRam0		   : > CLARAM0,		  PAGE = 1*/
   Cla1DataRam1		   : > CLARAM1,		  PAGE = 1
   CANBuffer           : > RAML1_CAN,   PAGE = 1
   unClearRam          : > UNclear,   PAGE = 0
   EEPROM              : > RAMEE, PAGE = 1
   EE_CKSUM            : > RAMEE_cksum, PAGE = 1
   SWPN_Section        : > FLASHH_SWVR, PAGE = 0
   ID_CAL              : > FLASHH_IDCal, PAGE = 0
   GROUP	           : LOAD = FLASHH_run,
                         RUN = CLARAM1,
                         LOAD_START(_Cla1mathTablesLoadStart),
                         LOAD_END(_Cla1mathTablesLoadEnd),
                         RUN_START(_Cla1mathTablesRunStart),
                         LOAD_SIZE(_Cla1mathTablesLoadSize),
                         PAGE = 1
   
   {
    CLA1mathTables
    .const_cla
   }  
   
   Main_FLASH            : LOAD = FLASH_APP
                         PAGE = 0
   
   {
    StartofAppROM = .;
    DSP2803x_main.o(.text)
	*(.text)
    EndofAppROM =.;
    SizeofAppROMused = . - StartofAppROM;
	SizeofAppROMfree = SIZE(FLASH_APP) - SizeofAppROMused;
   }  

   
   CAL_FLASH            : LOAD = FLASHH_CAL,
                         RUN = RAMM0_CAL,
						 LOAD_START(_CALTablesLoadStart),
                         LOAD_END(_CALTablesLoadEnd),
						 LOAD_SIZE(_CALTablesLoadSize),
						 RUN_START(_CALWorkingpageStart),
                         PAGE = 0
   
   {
    StartofCalROM = .;
    app_cald.o
	hwiocald.o
	EndofCalROM = .;
	SizeofCalROMused = . - StartofCalROM;
	SizeofCalROMfree = SIZE(FLASHH_CAL) - SizeofCalROMused;
   }   	
   CLAscratch          : 
                         { *.obj(CLAscratch)
                         . += CLA_SCRATCHPAD_SIZE;
                         *.obj(CLAscratch_end) } > CLARAM1,
					     PAGE = 1
					 
  /* Uncomment the section below if calling the IQNexp() or IQexp()
      functions from the IQMath.lib library in order to utilize the
      relevant IQ Math table in Boot ROM (This saves space and Boot ROM
      is 1 wait-state). If this section is not uncommented, IQmathTables2
      will be loaded into other memory (SARAM, Flash, etc.) and will take
      up space, but 0 wait-state is possible.
   */
   /*
   IQmathTables2    : > IQTABLES2, PAGE = 0, TYPE = NOLOAD
   {

              IQmath.lib<IQNexpTable.obj> (IQmathTablesRam)

   }
   */
    /* Uncomment the section below if calling the IQNasin() or IQasin()
       functions from the IQMath.lib library in order to utilize the
       relevant IQ Math table in Boot ROM (This saves space and Boot ROM
       is 1 wait-state). If this section is not uncommented, IQmathTables2
       will be loaded into other memory (SARAM, Flash, etc.) and will take
       up space, but 0 wait-state is possible.
    */
    /*
    IQmathTables3    : > IQTABLES3, PAGE = 0, TYPE = NOLOAD
    {

               IQmath.lib<IQNasinTable.obj> (IQmathTablesRam)

    }
    */

   /* .reset is a standard section used by the compiler.  It contains the */
   /* the address of the start of _c_int00 for C Code.   /*
   /* When using the boot ROM this section and the CPU vector */
   /* table is not needed.  Thus the default type is set here to  */
   /* DSECT  */
   .reset              : > RESET,      PAGE = 0, TYPE = DSECT

}

/*
//===========================================================================
// End of file.
//===========================================================================
*/

