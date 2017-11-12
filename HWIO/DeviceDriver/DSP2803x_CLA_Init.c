#include "DSP28x_Project.h"
#include "rtwtypes.h"
#include "DSP2803x_CLAShared.h"
#include "DSP2803x_CLA_Init.h"
#include "DSP2803x_function.h"
// These are defined by the linker file
extern Uint16 Cla1Prog_Start;
extern Uint16 Cla1funcsLoadStart;
extern Uint16 Cla1funcsLoadEnd;
extern Uint16 Cla1funcsRunStart;
extern Uint16 Cla1funcsLoadSize;

void DSP2803x_CLA_Init(void)
{

   // Copy CLA code from its load address to CLA program RAM
   //
   // Note: during debug the load and run addresses can be
   // the same as Code Composer Studio can load the CLA program
   // RAM directly.
   //
   // The ClafuncsLoadStart, ClafuncsLoadEnd, and ClafuncsRunStart
   // symbols are created by the linker.
   //memcpy((uint16_T *)&Cla1funcsRunStart,(uint16_T *)&Cla1funcsLoadStart, (unsigned long)&Cla1funcsLoadSize);
   Copydata((uint16_T *)&Cla1funcsRunStart,(uint16_T *)&Cla1funcsLoadStart, (unsigned long)&Cla1funcsLoadSize);
   /* Compute all CLA task vectors */
   EALLOW;
   Cla1Regs.MVECT1 = (uint16_T)((uint32_T)&Cla1Task1 - (uint32_T)&Cla1Prog_Start);
   Cla1Regs.MVECT2 = (uint16_T)((uint32_T)&Cla1Task2 - (uint32_T)&Cla1Prog_Start);
   Cla1Regs.MVECT3 = (uint16_T)((uint32_T)&Cla1Task3 - (uint32_T)&Cla1Prog_Start);
   Cla1Regs.MVECT4 = (uint16_T)((uint32_T)&Cla1Task4 - (uint32_T)&Cla1Prog_Start);
   Cla1Regs.MVECT5 = (uint16_T)((uint32_T)&Cla1Task5 - (uint32_T)&Cla1Prog_Start);
   Cla1Regs.MVECT6 = (uint16_T)((uint32_T)&Cla1Task6 - (uint32_T)&Cla1Prog_Start);
   Cla1Regs.MVECT7 = (uint16_T)((uint32_T)&Cla1Task7 - (uint32_T)&Cla1Prog_Start);
   Cla1Regs.MVECT8 = (uint16_T)((uint32_T)&Cla1Task8 - (uint32_T)&Cla1Prog_Start);

   //Mapping CLA tasks
   /*  All tasks are enabled and will be started by an ePWM trigger
    *  Map CLA program memory to the CLA and enable software breakpoints
    */
   Cla1Regs.MPISRCSEL1.bit.PERINT1SEL 	= CLA_INT1_NONE;
   Cla1Regs.MPISRCSEL1.bit.PERINT2SEL   = CLA_INT2_ADCINT2; // ADCINT2 starts CLA Task 2
   Cla1Regs.MPISRCSEL1.bit.PERINT3SEL 	= CLA_INT3_NONE;
   Cla1Regs.MPISRCSEL1.bit.PERINT4SEL 	= CLA_INT4_NONE;
   Cla1Regs.MPISRCSEL1.bit.PERINT5SEL 	= CLA_INT5_EPWM5INT;
   Cla1Regs.MPISRCSEL1.bit.PERINT6SEL 	= CLA_INT6_NONE;
   Cla1Regs.MPISRCSEL1.bit.PERINT7SEL   = CLA_INT7_ADCINT7; // ADCINT7 starts CLA Task 7
   Cla1Regs.MPISRCSEL1.bit.PERINT8SEL 	= CLA_INT8_NONE;
   
   Cla1Regs.MMEMCFG.bit.PROGE = 1;		   // Map CLA program memory to the CLA
   Cla1Regs.MIER.all = (M_INT7 |M_INT5 | M_INT2);   // Enable Task 7 Task 5 and Task 2
   Cla1Regs.MMEMCFG.bit.RAM0E	= CLARAM0_DISABLE;
   Cla1Regs.MMEMCFG.bit.RAM1E	= CLARAM1_ENABLE;
   EDIS;
}