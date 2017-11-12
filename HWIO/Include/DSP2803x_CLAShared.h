//###########################################################################
//
// FILE:   DSP2803x_CLAShared.h
//
// TITLE:  CLA and CPU shared variables and constants
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef DSP2803x_CLA_SHARED_H
#define DSP2803x_CLA_SHARED_H

#ifdef __cplusplus
extern "C" {
#endif


  #include "IQmathLib.h"
  #include "DSP28x_Project.h"
  #include "t_types.h"

  #define NUM_DATA_POINTS (10)
  

//VIS=Iload£¯8£®5
#define Motor_ActualCur_Get(x) (T_Currentb)(x*3.3*8.5/256)

extern Uint16 IsenP;
extern Uint16 Vign;
extern Uint16 Vtemp;
extern Uint16 IsenP_CLA[NUM_DATA_POINTS];
extern Uint8 Motor_Dir_Command;
extern float Motor_duty;
extern uint8_T Motor_Current_Max;
extern float Motor_P_Slew;

typedef enum{
	Motor_Stop = 0,
	Motor_FWD = 1,
	Motor_REV =2
}Motor_Dir_T;

// The following are symbols defined in the CLA assembly code
// Including them in the shared header file makes them
// .global and the main CPU can make use of them.

__interrupt void Cla1Task1();
__interrupt void Cla1Task2();
__interrupt void Cla1Task3();
__interrupt void Cla1Task4();
__interrupt void Cla1Task5();
__interrupt void Cla1Task6();
__interrupt void Cla1Task7();
__interrupt void Cla1Task8();


#ifdef __cplusplus
}
#endif /* extern "C" */


#endif  // end of CLA_SHARED definition

