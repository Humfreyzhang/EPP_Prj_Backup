//###########################################################################
// Description:
//
// Declare shared memory variables and assign them to specific CLA-accessible
// memory locations
//
//! \addtogroup f2803x_example_cla_list
//! \b Memory \b Allocation \n
//!  - CLA1 to CPU Message RAM
//!    - cla_pass_count - Logic test pass count
//!    - cla_fail_count - Logic test fail count
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "DSP28x_Project.h"
// Include the test header file whose name is based on the test name
// which is defined by the macro TEST on the command line
#include "DSP2803x_CLAShared.h"



//GLobal Data
 //Ensure that all data is placed in the data rams

#pragma DATA_SECTION(IsenP,     "Cla1ToCpuMsgRAM");
#pragma DATA_SECTION(Vign,      "Cla1ToCpuMsgRAM");
#pragma DATA_SECTION(Vtemp,     "Cla1ToCpuMsgRAM");
#pragma DATA_SECTION(IsenP_CLA, "Cla1DataRam1");


Uint16 IsenP;
Uint16 Vign;
Uint16 Vtemp;
Uint16 IsenP_CLA[NUM_DATA_POINTS];



//Task 2 (C) Variables

//Task 3 (C) Variables

//Task 4 (C) Variables

//Task 5 (C) Variables

//Task 6 (C) Variables

//Task 7 (C) Variables

//Task 8 (C) Variables

//Common (C) Variables
