//###########################################################################
// Description:
//! \addtogroup f2803x_example_list
//! <h1> ADC Start of Conversion (adc_soc)</h1>
//!
//! This ADC example uses ePWM1 to generate a periodic ADC SOC - ADCINT1.
//! Two channels are converted, ADCINA4 and ADCINA2.
//!
//! \b Watch \b Variables \n
//! - Voltage1[10]    - Last 10 ADCRESULT0 values
//! - Voltage2[10]    - Last 10 ADCRESULT1 values
//! - ConversionCount - Current result number 0-9
//! - LoopCount       - Idle loop counter
//
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "os_time.h"
#include "hwiocald.h"
#include "DSP2803x_CLAShared.h"
#include "DSP2803x_CLA_Init.h"
#include "DSP2803x_isr.h"
#include "DSP2803x_function.h"
#include "interface_file.h"


// Global variables used in this example:
#define	TSC_ISR0				(0.01)						// 10.0[ms]
#define	TSC_ISR1				(0.001)					    // 1.0[ms] 

#define F28035_TIMER0_PERIOD	(TSC_ISR0*1000000)			// 10.0[ms]
#define F28035_TIMER1_PERIOD	(TSC_ISR1*1000000)			// 1.0[ms]

extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadSize;
extern Uint16 RamfuncsRunStart;


main()
{
	// Initialize System Control:
	// PLL, WatchDog, enable Peripheral Clocks
	// This example function is found in the DSP2803x_SysCtrl.c file.
	InitSysCtrl();
	Ramclear();

	// Initialize GPIO:
	// This example function is found in the DSP2803x_Gpio.c file and
	// illustrates how to set the GPIO to it's default state.
	InitGpio();

	// Clear all interrupts and initialize PIE vector table:
	// Disable CPU interrupts
	DINT;

	// Initialize the PIE control registers to their default state.
	// The default state is all PIE interrupts disabled and flags
	// are cleared.
	// This function is found in the DSP2803x_PieCtrl.c file.
	InitPieCtrl();

	// Disable CPU interrupts and clear all CPU interrupt flags:
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
	//cla initial
	DSP2803x_CLA_Init();

	//Initialize all the Device Peripherals:
	InitAdcAio();

	InitAdc();  // init the ADC
	if(K_ADCSelfCal_Enable == true)
	{
	AdcOffsetSelfCal();
	}
	InitADC_Conf();

	InitEPwmGpio();

	Cal_Workspace_Init();
	
	//Set the TBCLKSYNC should EALLOW first
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	EDIS;
	InitEPwm();
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	EDIS;

	InitCpuTimers();
	ConfigCpuTimer(&CpuTimer0, 60, F28035_TIMER0_PERIOD);		// 10msec
	ConfigCpuTimer(&CpuTimer1, 60, F28035_TIMER1_PERIOD);		// 10ms
	CpuTimer0Regs.TCR.all = 0x4000;
	CpuTimer1Regs.TCR.all = 0x4000; 		// Use write-only instruction to set TSS bit = 0

	/*Initial the CAN moduel*/
	InitECanGpio();
	InitECan();

	Copydata((uint16_T *)&RamfuncsRunStart,(uint16_T *)&RamfuncsLoadStart, (unsigned long)&RamfuncsLoadSize);

	// Initialize the PIE vector table with pointers to the shell Interrupt
	// Service Routines (ISR).
	// This will populate the entire table, even if the interrupt
	// is not used in this example.	This is useful for debug purposes.
	// The shell ISR routines are found in DSP2803x_DefaultIsr.c.
	// This function is found in DSP2803x_PieVect.c.
	IER |= M_INT1;						// Enable CPU Interrupt 1
	IER |= M_INT13;						// Enable CPU Interrupt 13
	IER |= M_INT9;						// Enable CPU Interrupt 9
	StartOS(AM_normal);

}





