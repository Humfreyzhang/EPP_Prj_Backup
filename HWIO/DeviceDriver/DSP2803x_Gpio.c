//###########################################################################
//
// FILE:	DSP2803x_Gpio.c
//
// TITLE:	DSP2803x General Purpose I/O Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "DSP2803x_Device.h"     // DSP2803x Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP2803x Examples Include File
#include "io_config_gpio.h"

//---------------------------------------------------------------------------
// InitGpio:
//---------------------------------------------------------------------------
// This function initializes the Gpio to a known (default) state.
//
// For more details on configuring GPIO's as peripheral functions,
// refer to the individual peripheral examples and/or GPIO setup example.
void InitGpio(void)
{
	EALLOW;
	
	 // GpioCtrlRegs.GPAMUX1.all = 0x0000;	   // GPIO functionality GPIO16-GPIO31
	  GpioCtrlRegs.GPAMUX1.bit.GPIO0=GPIO;
	  GpioCtrlRegs.GPAMUX1.bit.GPIO1=GPIO;
	  GpioCtrlRegs.GPAMUX1.bit.GPIO2=GPIO;
	  GpioCtrlRegs.GPAMUX1.bit.GPIO3=GPIO;
	  GpioCtrlRegs.GPAMUX1.bit.GPIO4=GPIO;
	  GpioCtrlRegs.GPAMUX1.bit.GPIO5=GPIO;
	  GpioCtrlRegs.GPAMUX1.bit.GPIO6=GPIO;
	  GpioCtrlRegs.GPAMUX1.bit.GPIO7=GPIO;
	  GpioCtrlRegs.GPAMUX1.bit.GPIO8=GPIO;
	  GpioCtrlRegs.GPAMUX1.bit.GPIO9=GPIO;
	  GpioCtrlRegs.GPAMUX1.bit.GPIO10=GPIO;
	  GpioCtrlRegs.GPAMUX1.bit.GPIO11=GPIO;
	  GpioCtrlRegs.GPAMUX1.bit.GPIO12=GPIO;
	  GpioCtrlRegs.GPAMUX1.bit.GPIO13=GPIO;
	  GpioCtrlRegs.GPAMUX1.bit.GPIO14=GPIO;
	  GpioCtrlRegs.GPAMUX1.bit.GPIO15=GPIO;
	 
	  
	  
	  //GpioCtrlRegs.GPAMUX2.all = 0x0000;	   // GPIO functionality GPIO16-GPIO31
	  GpioCtrlRegs.GPAMUX2.bit.GPIO16=GPIO;
	  GpioCtrlRegs.GPAMUX2.bit.GPIO17=GPIO;
	  GpioCtrlRegs.GPAMUX2.bit.GPIO18=GPIO;
	  GpioCtrlRegs.GPAMUX2.bit.GPIO19=GPIO;
	  GpioCtrlRegs.GPAMUX2.bit.GPIO20=GPIO;    //QEPA;
	  GpioCtrlRegs.GPAMUX2.bit.GPIO21=GPIO;    //QEPB;
	  GpioCtrlRegs.GPAMUX2.bit.GPIO22=GPIO;
	  GpioCtrlRegs.GPAMUX2.bit.GPIO23=GPIO;
	  GpioCtrlRegs.GPAMUX2.bit.GPIO24=GPIO;
	  GpioCtrlRegs.GPAMUX2.bit.GPIO25=GPIO;
	  GpioCtrlRegs.GPAMUX2.bit.GPIO26=GPIO;
	  GpioCtrlRegs.GPAMUX2.bit.GPIO27=GPIO;
	  GpioCtrlRegs.GPAMUX2.bit.GPIO28=SCIRX;
	  GpioCtrlRegs.GPAMUX2.bit.GPIO29=SCITX;
	  GpioCtrlRegs.GPAMUX2.bit.GPIO30=CANRX;
	  GpioCtrlRegs.GPAMUX2.bit.GPIO31=CANTX;
	  
	 // GpioCtrlRegs.GPBMUX1.all = 0x0000;	   // GPIO functionality GPIO32-GPIO44
	
	  GpioCtrlRegs.GPBMUX1.bit.GPIO32=GPIO;
	  GpioCtrlRegs.GPBMUX1.bit.GPIO33=GPIO;
	  GpioCtrlRegs.GPBMUX1.bit.GPIO34=GPIO;
	  GpioCtrlRegs.GPBMUX1.bit.GPIO39=GPIO;
	  GpioCtrlRegs.GPBMUX1.bit.GPIO40=GPIO;
	  GpioCtrlRegs.GPBMUX1.bit.GPIO41=GPIO;
	  GpioCtrlRegs.GPBMUX1.bit.GPIO42=GPIO;
	  GpioCtrlRegs.GPBMUX1.bit.GPIO43=GPIO;
	  GpioCtrlRegs.GPBMUX1.bit.GPIO44=GPIO;
	 
	  
	  //GpioCtrlRegs.AIOMUX1.all = 0x0000;	   // Dig.IO funct. applies to AIO2,4,6,10,12,14
	  GpioCtrlRegs.AIOMUX1.bit.AIO2=GPIO;
	  GpioCtrlRegs.AIOMUX1.bit.AIO4=GPIO;
	  GpioCtrlRegs.AIOMUX1.bit.AIO6=GPIO;
	  GpioCtrlRegs.AIOMUX1.bit.AIO10=GPIO;
	  GpioCtrlRegs.AIOMUX1.bit.AIO12=GPIO;
	  GpioCtrlRegs.AIOMUX1.bit.AIO14=GPIO;
	  
	   
	  //GpioCtrlRegs.GPADIR.all = 0x0000;	   // GPIO0-GPIO31 are GP inputs
	  GpioCtrlRegs.GPADIR.bit.GPIO0=OUTPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO1=OUTPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO2=OUTPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO3=OUTPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO3=OUTPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO4=OUTPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO5=OUTPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO6=OUTPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO7=OUTPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO8=OUTPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO9=OUTPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO10=OUTPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO11=OUTPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO12=OUTPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO13=OUTPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO14=OUTPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO15=OUTPUT;
	
	  GpioCtrlRegs.GPADIR.bit.GPIO16=INPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO17=INPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO18=INPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO19=OUTPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO20=OUTPUT;  //KNOB_A - QEPA
	  GpioCtrlRegs.GPADIR.bit.GPIO21=INPUT;  //KNOB_B - QEPB
	  GpioCtrlRegs.GPADIR.bit.GPIO22=INPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO23=INPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO24=INPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO25=OUTPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO26=OUTPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO27=OUTPUT;
	  GpioCtrlRegs.GPADIR.bit.GPIO28=INPUT;    //LACH00 (SCIARX)
	  GpioCtrlRegs.GPADIR.bit.GPIO29=OUTPUT;   //LACH01 (SCIATX)
	  GpioCtrlRegs.GPADIR.bit.GPIO30=Default;  //CANRX
	  GpioCtrlRegs.GPADIR.bit.GPIO31=Default;  //CANTX
	
	  //GpioCtrlRegs.GPBDIR.all = 0x0000;	   // GPIO32-GPIO44 are inputs
	  GpioCtrlRegs.GPBDIR.bit.GPIO32=OUTPUT; 
	  GpioCtrlRegs.GPBDIR.bit.GPIO33=OUTPUT;
	  GpioCtrlRegs.GPBDIR.bit.GPIO34=INPUT;
	  GpioCtrlRegs.GPBDIR.bit.GPIO39=OUTPUT;
	  GpioCtrlRegs.GPBDIR.bit.GPIO40=OUTPUT;
	  GpioCtrlRegs.GPBDIR.bit.GPIO41=OUTPUT;
	  GpioCtrlRegs.GPBDIR.bit.GPIO42=OUTPUT;
	  GpioCtrlRegs.GPBDIR.bit.GPIO43=OUTPUT;
	  GpioCtrlRegs.GPBDIR.bit.GPIO44=OUTPUT;
	  
	 // GpioCtrlRegs.AIODIR.all = 0x0000;	   // AIO2,4,6,19,12,14 are digital inputs
	  
	  GpioCtrlRegs.AIODIR.bit.AIO2=INPUT;
	  GpioCtrlRegs.AIODIR.bit.AIO4=INPUT;
	  GpioCtrlRegs.AIODIR.bit.AIO6=INPUT;
	  GpioCtrlRegs.AIODIR.bit.AIO10=INPUT;
	  GpioCtrlRegs.AIODIR.bit.AIO12=INPUT;
	  GpioCtrlRegs.AIODIR.bit.AIO14=INPUT;
	  
	  // Each input can have different qualification
	  // a) input synchronized to SYSCLKOUT
	  // b) input qualified by a sampling window
	  // c) input sent asynchronously (valid for peripheral inputs only)
	  GpioCtrlRegs.GPAQSEL1.all = 0x0000;	 // GPIO0-GPIO15 Synch to SYSCLKOUT
	  GpioCtrlRegs.GPAQSEL2.all = 0x0000;	 // GPIO16-GPIO31 Synch to SYSCLKOUT
	  GpioCtrlRegs.GPBQSEL1.all = 0x0000;	 // GPIO32-GPIO44 Synch to SYSCLKOUT
	
	  // Pull-ups can be enabled or disabled.
	  GpioCtrlRegs.GPAPUD.all = 0x0000; 	 // Pullup's enabled GPIO0-GPIO31
	  GpioCtrlRegs.GPBPUD.all = 0x0000; 	 // Pullup's enabled GPIO32-GPIO44
	  //GpioCtrlRegs.GPAPUD.all = 0xFFFF;	 // Pullup's disabled GPIO0-GPIO31
	  //GpioCtrlRegs.GPBPUD.all = 0xFFFF;	 // Pullup's disabled GPIO32-GPIO44
	//	GpioCtrlRegs.GPAPUD.bit.GPIO12=1;
	//	REG_INH2_SET;
	
	  EDIS;


}

//===========================================================================
// End of file.
//===========================================================================
