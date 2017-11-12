//###########################################################################
//
// FILE:    DSP2803x_ECan.c
//
// TITLE:   DSP2803x Enhanced CAN Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2803x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "DSP2803x_Device.h"     // DSP28 Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP28 Examples Include File

//---------------------------------------------------------------------------
// InitECan:
//---------------------------------------------------------------------------
// This function initializes the eCAN module to a known state.
//
void InitECan(void)
{
   InitECana();
   InitECan_MailBox();
}

void InitECana(void)        // Initialize eCAN-A module
{

/* Create a shadow register structure for the CAN control registers. This is
 needed, since only 32-bit access is allowed to these registers. 16-bit access
 to these registers could potentially corrupt the register contents or return
 false data. */

struct ECAN_REGS ECanaShadow;

    EALLOW;     // EALLOW enables access to protected bits

/* Configure eCAN RX and TX pins for CAN operation using eCAN regs*/

    ECanaShadow.CANTIOC.all = ECanaRegs.CANTIOC.all;
	ECanaShadow.CANTIOC.all = 0x00000000;
    ECanaShadow.CANTIOC.bit.TXFUNC = 1;
    ECanaRegs.CANTIOC.all = ECanaShadow.CANTIOC.all;

    ECanaShadow.CANRIOC.all = ECanaRegs.CANRIOC.all;
	ECanaShadow.CANRIOC.all = 0x00000000;
    ECanaShadow.CANRIOC.bit.RXFUNC = 1;
    ECanaRegs.CANRIOC.all = ECanaShadow.CANRIOC.all;

/* Configure eCAN for HECC mode - (reqd to access mailboxes 16 thru 31) */
                                    // HECC mode also enables time-stamping feature

    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
	ECanaShadow.CANMC.all = 0x00000000;
    ECanaShadow.CANMC.bit.SCB = 1;
    ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

/* Initialize all bits of 'Message Control Register' to zero */
// Some bits of MSGCTRL register come up in an unknown state. For proper operation,
// all bits (including reserved bits) of MSGCTRL must be initialized to zero

    ECanaMboxes.MBOX0.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX1.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX2.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX3.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX4.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX5.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX6.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX7.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX8.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX9.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX10.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX11.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX12.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX13.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX14.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX15.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX16.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX17.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX18.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX19.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX20.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX21.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX22.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX23.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX24.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX25.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX26.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX27.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX28.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX29.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX30.MSGCTRL.all = 0x00000000;
    ECanaMboxes.MBOX31.MSGCTRL.all = 0x00000000;
// TAn, RMPn, GIFn bits are all zero upon reset and are cleared again
//  as a matter of precaution.

    ECanaRegs.CANTA.all = 0xFFFFFFFF;   /* Clear all TAn bits */

    ECanaRegs.CANRMP.all = 0xFFFFFFFF;  /* Clear all RMPn bits */

    ECanaRegs.CANGIF0.all = 0xFFFFFFFF; /* Clear all interrupt flag bits */
    ECanaRegs.CANGIF1.all = 0xFFFFFFFF;


/* Configure bit timing parameters for eCANA*/

    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
    ECanaShadow.CANMC.bit.CCR = 1 ;            // Set CCR = 1
    ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

    // Wait until the CPU has been granted permission to change the configuration registers
    do
    {
      ECanaShadow.CANES.all = ECanaRegs.CANES.all;
    } while(ECanaShadow.CANES.bit.CCE != 1 );       // Wait for CCE bit to be set..

    ECanaShadow.CANBTC.all = 0;
    /* The following block is only for 60 MHz SYSCLKOUT. (30 MHz CAN module clock Bit rate = 1 Mbps
       See Note at end of file. */

    ECanaShadow.CANBTC.bit.BRPREG = 5; //500Kbps
    ECanaShadow.CANBTC.bit.TSEG2REG = 1;
    ECanaShadow.CANBTC.bit.TSEG1REG = 6;

    ECanaShadow.CANBTC.bit.SAM = 1;
    ECanaRegs.CANBTC.all = ECanaShadow.CANBTC.all;

    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
    ECanaShadow.CANMC.bit.CCR = 0 ;            // Set CCR = 0
    ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

    // Wait until the CPU no longer has permission to change the configuration registers
    do
    {
      ECanaShadow.CANES.all = ECanaRegs.CANES.all;
    } while(ECanaShadow.CANES.bit.CCE != 0 );       // Wait for CCE bit to be  cleared..

/* Disable all Mailboxes  */
    ECanaRegs.CANME.all = 0;        // Required before writing the MSGIDs

    EDIS;
}

//---------------------------------------------------------------------------
// Example: InitECanGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as eCAN pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
// Only one GPIO pin should be enabled for CANTXA operation.
// Only one GPIO pin shoudl be enabled for CANRXA operation.
// Comment out other unwanted lines.

void InitECanGpio(void)
{
   InitECanaGpio();
}

void InitECanaGpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected CAN pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO30 = 0;     // Enable pull-up for GPIO30 (CANRXA)
    GpioCtrlRegs.GPAPUD.bit.GPIO31 = 0;     // Enable pull-up for GPIO31 (CANTXA)

/* Set qualification for selected CAN pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.
// This will select asynch (no qualification) for the selected pins.

    GpioCtrlRegs.GPAQSEL2.bit.GPIO30 = 3;   // Asynch qual for GPIO30 (CANRXA)

/* Configure eCAN-A pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eCAN functional pins.

    GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;    // Configure GPIO30 for CANRXA operation
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;    // Configure GPIO31 for CANTXA operation

    EDIS;
}

/* Note: Bit timing parameters must be chosen based on the network parameters such as
   the sampling point desired and the propagation delay of the network. The propagation
   delay is a function of length of the cable, delay introduced by the
   transceivers and opto/galvanic-isolators (if any).

   The parameters used in this file must be changed taking into account the above mentioned
   factors in order to arrive at the bit-timing parameters suitable for a network.
*/
void InitECan_MailBox(void)
{

	struct ECAN_REGS ECanaShadow;
	


    // Write to the MSGID field of RECEIVE mailboxes MBOX16 - 31
    ECanaMboxes.MBOX0.MSGID.all = 0x0000;
    ECanaMboxes.MBOX0.MSGID.bit.STDMSGID = 0x300;//깃硫煉 0x00000703;

	ECanaMboxes.MBOX1.MSGID.all = 0x0000;
    ECanaMboxes.MBOX1.MSGID.bit.STDMSGID = 0x380;//0x000007DF;

	ECanaMboxes.MBOX2.MSGID.all = 0x0000;
	ECanaMboxes.MBOX2.MSGID.bit.STDMSGID	= 0x599;	// DBG_TCM_CCP_CRO_ID (구현 X)

	ECanaMboxes.MBOX3.MSGID.all = 0x0000;
	ECanaMboxes.MBOX3.MSGID.bit.STDMSGID	= 0x36A;	// MS_308h (Cycle : 10[ms] / 0x308 -> 0x300)

	ECanaMboxes.MBOX4.MSGID.all = 0x0000;
	ECanaMboxes.MBOX4.MSGID.bit.STDMSGID	= 0x00A;	// VMS_TCM_VCMD_VERSION (Event?? -> Request the TCM Version)

	ECanaMboxes.MBOX5.MSGID.all = 0x0000;
	ECanaMboxes.MBOX5.MSGID.bit.STDMSGID	= 0x08C;	// VMS_DMC_BOOLEANS (Event?? -> Clean Faults)

	ECanaMboxes.MBOX6.MSGID.all = 0x0000;
	ECanaMboxes.MBOX6.MSGID.bit.STDMSGID	= 0x52A;	// InvokeBootloaderCmd (구현 X)

	ECanaMboxes.MBOX7.MSGID.all = 0x0000;
	ECanaMboxes.MBOX7.MSGID.bit.STDMSGID	= 0x270;	// MS_308h (Cycle : 10[ms] / 0x308 -> 0x270)

	ECanaMboxes.MBOX8.MSGID.all = 0x0000;
	ECanaMboxes.MBOX8.MSGID.bit.STDMSGID	= 0x7D0;	// CCP
	
	ECanaMboxes.MBOX9.MSGID.all = 0x0000;
	ECanaMboxes.MBOX9.MSGID.bit.STDMSGID	= 0x703;	// UDS pyh


	ECanaMboxes.MBOX16.MSGID.all = 0x0000;
    ECanaMboxes.MBOX16.MSGID.bit.STDMSGID = 0x783;//stadard ID 783;

	ECanaMboxes.MBOX17.MSGID.all = 0x0000;
	ECanaMboxes.MBOX17.MSGID.bit.STDMSGID	= 0x500;	// TCM_VMS_VCMD_VERSION

	ECanaMboxes.MBOX18.MSGID.all = 0x0000;
	ECanaMboxes.MBOX18.MSGID.bit.STDMSGID	= 0x580;	// TCM_VMC_ALERT_LOG (0x590 -> 0x56C->0x580)

	ECanaMboxes.MBOX19.MSGID.all = 0x0000;
	ECanaMboxes.MBOX19.MSGID.bit.STDMSGID	= 0x56C;	// TCM_VMS_ALERT_FAULT (Cycle : 1000[ms], 0x580->0x56C)

	ECanaMboxes.MBOX20.MSGID.all = 0x0000;
	ECanaMboxes.MBOX20.MSGID.bit.STDMSGID	= 0x55C;	// TCM_DMC_STATE (Cycle : 100[ms] )

	ECanaMboxes.MBOX21.MSGID.all = 0x0000;
	ECanaMboxes.MBOX21.MSGID.bit.STDMSGID	= 0x7D8;	// CCP

	ECanaMboxes.MBOX22.MSGID.all = 0x0000;
	ECanaMboxes.MBOX22.MSGID.bit.STDMSGID	= 0x7D4;	// CCP DAQ0

	ECanaMboxes.MBOX23.MSGID.all = 0x0000;
	ECanaMboxes.MBOX23.MSGID.bit.STDMSGID	= 0x7D5;	// CCP DAQ1

    ECanaMboxes.MBOX24.MSGID.all = 0x0000;
	ECanaMboxes.MBOX24.MSGID.bit.STDMSGID	= 0x7D6;	// CCP DAQ2

	EALLOW;
	//ECanaShadow.CANMIL.all = ECanaRegs.CANMIL.all;
 	//ECanaShadow.CANMIL.all = 0x00000000;  		 
	//ECanaRegs.CANMIL.all  = ECanaShadow.CANMIL.all;
	ECanaShadow.CANMIL.all = 0x00000000;
	ECanaShadow.CANMIL.bit.MIL16 =1;//interrupt generrate to interrupt line1
	ECanaShadow.CANMIL.bit.MIL17 =1;
	ECanaShadow.CANMIL.bit.MIL18 =1;
	ECanaShadow.CANMIL.bit.MIL19 =1;
	ECanaShadow.CANMIL.bit.MIL20 =1;
	ECanaShadow.CANMIL.bit.MIL21 =1;
	ECanaShadow.CANMIL.bit.MIL22 =1;
	ECanaShadow.CANMIL.bit.MIL23 =1;
	ECanaShadow.CANMIL.bit.MIL24 =1;
	ECanaShadow.CANMIL.bit.MIL25 =1;
	ECanaShadow.CANMIL.bit.MIL26 =1;
	ECanaShadow.CANMIL.bit.MIL27 =1;
	ECanaShadow.CANMIL.bit.MIL28 =1;
	ECanaShadow.CANMIL.bit.MIL29 =1;
	ECanaShadow.CANMIL.bit.MIL30 =1;
	ECanaShadow.CANMIL.bit.MIL31 =1;
	ECanaRegs.CANMIL.all = ECanaShadow.CANMIL.all;

	
	#if 0
	ECanaRegs.CANMIM.bit.MIM16 =1;//enable interrupt
	ECanaRegs.CANMIM.bit.MIM17 =1;
	ECanaRegs.CANMIM.bit.MIM18 =1;
	ECanaRegs.CANMIM.bit.MIM19 =1;
	ECanaRegs.CANMIM.bit.MIM20 =1;
	ECanaRegs.CANMIM.bit.MIM21 =1;
	ECanaRegs.CANMIM.bit.MIM22 =1;
	ECanaRegs.CANMIM.bit.MIM23 =1;
	//ECanaRegs.CANMIM.all = ECanaShadow.CANMIM.all;
#endif
	ECanaRegs.CANGIM.bit.I0EN = 1;
	//ECanaRegs.CANGIM.bit.I1EN = 1;

	ECanaShadow.CANMD.all=0x00000000;
	ECanaShadow.CANMD.bit.MD0=1;
	ECanaShadow.CANMD.bit.MD1=1;
	ECanaShadow.CANMD.bit.MD2=1;								  
	ECanaShadow.CANMD.bit.MD3=1;								  
	ECanaShadow.CANMD.bit.MD4=1;								  
	ECanaShadow.CANMD.bit.MD5=1;								  
	ECanaShadow.CANMD.bit.MD6=1;								  
	ECanaShadow.CANMD.bit.MD7=1;								  
	ECanaShadow.CANMD.bit.MD8=1;
	ECanaShadow.CANMD.bit.MD9=1;
	ECanaShadow.CANMD.bit.MD10=1; 							  
	ECanaShadow.CANMD.bit.MD11=1;
	ECanaShadow.CANMD.bit.MD12=1; 							  
	ECanaShadow.CANMD.bit.MD13=1; 							  ;
	ECanaShadow.CANMD.bit.MD14=1; 							  
	ECanaShadow.CANMD.bit.MD15=1; 							  
	ECanaShadow.CANMD.bit.MD16=0; 							  
	ECanaShadow.CANMD.bit.MD17=0; 							  
	ECanaShadow.CANMD.bit.MD18=0; 							  
	ECanaShadow.CANMD.bit.MD19=0; 							  
	ECanaShadow.CANMD.bit.MD20=0; 							  
	ECanaShadow.CANMD.bit.MD21=0;   
	ECanaShadow.CANMD.bit.MD22=0; 							  
	ECanaShadow.CANMD.bit.MD23=0; 							  
	ECanaShadow.CANMD.bit.MD24=0; 							   
	ECanaShadow.CANMD.bit.MD25=0; 							  
	ECanaShadow.CANMD.bit.MD26=0; 							  
	ECanaShadow.CANMD.bit.MD27=0; 							   
	ECanaShadow.CANMD.bit.MD28=0; 							  
	ECanaShadow.CANMD.bit.MD29=0; 							  
	ECanaShadow.CANMD.bit.MD30=0; 							  
	ECanaShadow.CANMD.bit.MD31=0; 
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all;
 						   

 
	ECanaShadow.CANGIM.all = ECanaRegs.CANGIM.all;
	ECanaShadow.CANGIM.all = 0x00000000;
	ECanaShadow.CANGIM.bit.I0EN = 1;
	ECanaShadow.CANGIM.bit.I1EN = 1;	
	ECanaRegs.CANGIM.all	 = ECanaShadow.CANGIM.all; 
 
	//  ECanaShadow.CANMIM.all = ECanaRegs.CANMIM.all;  
	ECanaShadow.CANMIM.all = 0x00000000;
	ECanaRegs.CANMIM.all	 = ECanaShadow.CANMIM.all;

	/* Write to DLC field in Master Control reg  Data Size를 8byte로 선언*/

	ECanaMboxes.MBOX0.MSGCTRL.bit.DLC = 8;  
	ECanaMboxes.MBOX1.MSGCTRL.bit.DLC = 8;						   
	ECanaMboxes.MBOX2.MSGCTRL.bit.DLC = 8;					  
	ECanaMboxes.MBOX3.MSGCTRL.bit.DLC = 8;					  
	ECanaMboxes.MBOX4.MSGCTRL.bit.DLC = 8;						  
	ECanaMboxes.MBOX5.MSGCTRL.bit.DLC = 8;						  
	ECanaMboxes.MBOX6.MSGCTRL.bit.DLC = 8;						  
	ECanaMboxes.MBOX7.MSGCTRL.bit.DLC = 8;						  
	ECanaMboxes.MBOX8.MSGCTRL.bit.DLC = 8;						  
	ECanaMboxes.MBOX9.MSGCTRL.bit.DLC = 8;					   
	ECanaMboxes.MBOX10.MSGCTRL.bit.DLC = 8; 

	ECanaMboxes.MBOX11.MSGCTRL.bit.DLC = 8;					   
	ECanaMboxes.MBOX12.MSGCTRL.bit.DLC = 8;					  
	ECanaMboxes.MBOX13.MSGCTRL.bit.DLC = 8;					  
	ECanaMboxes.MBOX14.MSGCTRL.bit.DLC = 8;					  
	ECanaMboxes.MBOX15.MSGCTRL.bit.DLC = 8;					  
	ECanaMboxes.MBOX16.MSGCTRL.bit.DLC = 8;					  
	ECanaMboxes.MBOX17.MSGCTRL.bit.DLC = 8;					  
	ECanaMboxes.MBOX18.MSGCTRL.bit.DLC = 8;					  
	ECanaMboxes.MBOX19.MSGCTRL.bit.DLC = 8;					   
	ECanaMboxes.MBOX20.MSGCTRL.bit.DLC = 8; 

	ECanaMboxes.MBOX21.MSGCTRL.bit.DLC = 8;					   
	ECanaMboxes.MBOX22.MSGCTRL.bit.DLC = 8;					  
	ECanaMboxes.MBOX23.MSGCTRL.bit.DLC = 8;					  
	ECanaMboxes.MBOX24.MSGCTRL.bit.DLC = 8;					  
	ECanaMboxes.MBOX25.MSGCTRL.bit.DLC = 8;					  
	ECanaMboxes.MBOX26.MSGCTRL.bit.DLC = 8;					  
	ECanaMboxes.MBOX27.MSGCTRL.bit.DLC = 8;					  
	ECanaMboxes.MBOX28.MSGCTRL.bit.DLC = 8;					  
	ECanaMboxes.MBOX29.MSGCTRL.bit.DLC = 8;					   
	ECanaMboxes.MBOX30.MSGCTRL.bit.DLC = 8;					  
	ECanaMboxes.MBOX31.MSGCTRL.bit.DLC = 8; 

	/*Transmit-priority level. This 5-bit field defines the priority of this mailbox as compared to the other
31 mailboxes. The highest number has the highest priority. When two mailboxes have the same
priority, the one with the higher mailbox number is transmitted. TPL applies only for transmit
mailboxes. TPL is not used in SCC-mode.*/
	ECanaMboxes.MBOX16.MSGCTRL.bit.TPL = 6;
	ECanaMboxes.MBOX17.MSGCTRL.bit.TPL = 6;
	ECanaMboxes.MBOX18.MSGCTRL.bit.TPL = 6;
	ECanaMboxes.MBOX19.MSGCTRL.bit.TPL = 6;
	ECanaMboxes.MBOX20.MSGCTRL.bit.TPL = 6;
	ECanaMboxes.MBOX21.MSGCTRL.bit.TPL = 6;
	ECanaMboxes.MBOX22.MSGCTRL.bit.TPL = 10;
	ECanaMboxes.MBOX23.MSGCTRL.bit.TPL = 9;
	ECanaMboxes.MBOX24.MSGCTRL.bit.TPL = 6;
	ECanaMboxes.MBOX25.MSGCTRL.bit.TPL = 2;
	ECanaMboxes.MBOX26.MSGCTRL.bit.TPL = 2;
	ECanaMboxes.MBOX27.MSGCTRL.bit.TPL = 2;
	ECanaMboxes.MBOX28.MSGCTRL.bit.TPL = 2;
	ECanaMboxes.MBOX29.MSGCTRL.bit.TPL = 2;
	ECanaMboxes.MBOX30.MSGCTRL.bit.TPL = 2;
	ECanaMboxes.MBOX31.MSGCTRL.bit.TPL = 2;

	ECanaShadow.CANGAM.all = ECanaRegs.CANGAM.all;
	ECanaShadow.CANGAM.all = 0x00000000;
	ECanaShadow.CANGAM.bit.AMI = 1;						  
	ECanaRegs.CANGAM.all	 = ECanaShadow.CANGAM.all;


	ECanaMboxes.MBOX0.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX1.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX2.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX3.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX4.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX5.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX6.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX7.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX8.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX9.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX10.MSGID.bit.IDE = 0;

	ECanaMboxes.MBOX11.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX12.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX13.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX14.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX15.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX16.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX17.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX18.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX19.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX20.MSGID.bit.IDE = 0;

	ECanaMboxes.MBOX21.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX22.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX23.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX24.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX25.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX26.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX27.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX28.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX29.MSGID.bit.IDE = 0;
	ECanaMboxes.MBOX30.MSGID.bit.IDE = 0;

	ECanaMboxes.MBOX31.MSGID.bit.IDE = 0;
	//Message Box 값을 모두 초기화


	ECanaMboxes.MBOX0.MDL.all = 0x00000000;
	ECanaMboxes.MBOX0.MDH.all = 0x00000000;

	ECanaMboxes.MBOX1.MDL.all = 0x00000000;
	ECanaMboxes.MBOX1.MDH.all = 0x00000000;

	ECanaMboxes.MBOX2.MDL.all = 0x00000000;
	ECanaMboxes.MBOX2.MDH.all = 0x00000000;

	ECanaMboxes.MBOX3.MDL.all = 0x00000000;
	ECanaMboxes.MBOX3.MDH.all = 0x00000000;

	ECanaMboxes.MBOX4.MDL.all = 0x00000000;
	ECanaMboxes.MBOX4.MDH.all = 0x00000000;

	ECanaMboxes.MBOX5.MDL.all = 0x00000000;
	ECanaMboxes.MBOX5.MDH.all = 0x00000000;

	ECanaMboxes.MBOX6.MDL.all = 0x00000000;
	ECanaMboxes.MBOX6.MDH.all = 0x00000000;

	ECanaMboxes.MBOX7.MDL.all = 0x00000000;
	ECanaMboxes.MBOX7.MDH.all = 0x00000000;

	ECanaMboxes.MBOX8.MDL.all = 0x00000000;
	ECanaMboxes.MBOX8.MDH.all = 0x00000000;

	ECanaMboxes.MBOX9.MDL.all = 0x00000000;
	ECanaMboxes.MBOX9.MDH.all = 0x00000000;

	ECanaMboxes.MBOX10.MDL.all = 0x00000000;
	ECanaMboxes.MBOX10.MDH.all = 0x00000000;


	ECanaMboxes.MBOX11.MDL.all = 0x00000000;
	ECanaMboxes.MBOX11.MDH.all = 0x00000000;

	ECanaMboxes.MBOX12.MDL.all = 0x00000000;
	ECanaMboxes.MBOX12.MDH.all = 0x00000000;

	ECanaMboxes.MBOX13.MDL.all = 0x00000000;
	ECanaMboxes.MBOX13.MDH.all = 0x00000000;

	ECanaMboxes.MBOX14.MDL.all = 0x00000000;
	ECanaMboxes.MBOX14.MDH.all = 0x00000000;

	ECanaMboxes.MBOX15.MDL.all = 0x00000000;
	ECanaMboxes.MBOX15.MDH.all = 0x00000000;

	ECanaMboxes.MBOX16.MDL.all = 0x00000000;
	ECanaMboxes.MBOX16.MDH.all = 0x00000000;

	ECanaMboxes.MBOX17.MDL.all = 0x00000000;
	ECanaMboxes.MBOX17.MDH.all = 0x00000000;

	ECanaMboxes.MBOX18.MDL.all = 0x00000000;
	ECanaMboxes.MBOX18.MDH.all = 0x00000000;

	ECanaMboxes.MBOX19.MDL.all = 0x00000000;
	ECanaMboxes.MBOX19.MDH.all = 0x00000000;

	ECanaMboxes.MBOX20.MDL.all = 0x00000000;
	ECanaMboxes.MBOX20.MDH.all = 0x00000000;

	ECanaMboxes.MBOX21.MDL.all = 0x00000000;
	ECanaMboxes.MBOX21.MDH.all = 0x00000000;

	ECanaMboxes.MBOX22.MDL.all = 0x00000000;
	ECanaMboxes.MBOX22.MDH.all = 0x00000000;

	ECanaMboxes.MBOX23.MDL.all = 0x00000000;
	ECanaMboxes.MBOX23.MDH.all = 0x00000000;

	ECanaMboxes.MBOX24.MDL.all = 0x00000000;
	ECanaMboxes.MBOX24.MDH.all = 0x00000000;

	ECanaMboxes.MBOX25.MDL.all = 0x00000000;
	ECanaMboxes.MBOX25.MDH.all = 0x00000000;

	ECanaMboxes.MBOX26.MDL.all = 0x00000000;
	ECanaMboxes.MBOX26.MDH.all = 0x00000000;

	ECanaMboxes.MBOX27.MDL.all = 0x00000000;
	ECanaMboxes.MBOX27.MDH.all = 0x00000000;

	ECanaMboxes.MBOX28.MDL.all = 0x00000000;
	ECanaMboxes.MBOX28.MDH.all = 0x00000000;

	ECanaMboxes.MBOX29.MDL.all = 0x00000000;
	ECanaMboxes.MBOX29.MDH.all = 0x00000000;

	ECanaMboxes.MBOX30.MDL.all = 0x00000000;
	ECanaMboxes.MBOX30.MDH.all = 0x00000000;

	ECanaMboxes.MBOX31.MDL.all = 0x00000000;
	ECanaMboxes.MBOX31.MDH.all = 0x00000000;

	ECanaRegs.CANMC.bit.DBO = BigEnd;	
	ECanaRegs.CANMIM.all = 0x01C003FF;

	ECanaShadow.CANME.all=0x00000000;
	ECanaShadow.CANME.bit.ME0 = 1;
	ECanaShadow.CANME.bit.ME1 = 1;
	ECanaShadow.CANME.bit.ME2 = 1;
	ECanaShadow.CANME.bit.ME3 = 1;
	ECanaShadow.CANME.bit.ME4 = 1;
	ECanaShadow.CANME.bit.ME5 = 1;
	ECanaShadow.CANME.bit.ME6 = 1;
	ECanaShadow.CANME.bit.ME7 = 1;
	ECanaShadow.CANME.bit.ME8 = 1;
	ECanaShadow.CANME.bit.ME9 = 1;
	ECanaShadow.CANME.bit.ME10 = 0;
	ECanaShadow.CANME.bit.ME11 = 0;
	ECanaShadow.CANME.bit.ME12 = 0;
	ECanaShadow.CANME.bit.ME13 = 0;
	ECanaShadow.CANME.bit.ME14 = 0;
	ECanaShadow.CANME.bit.ME15 = 0;
	ECanaShadow.CANME.bit.ME16 = 1;
	ECanaShadow.CANME.bit.ME17 = 1;
	ECanaShadow.CANME.bit.ME18 = 1;
	ECanaShadow.CANME.bit.ME19 = 1;
	ECanaShadow.CANME.bit.ME20 = 1;
	ECanaShadow.CANME.bit.ME21 = 1;
	ECanaShadow.CANME.bit.ME22 = 1;
	ECanaShadow.CANME.bit.ME23 = 1;
	ECanaShadow.CANME.bit.ME24 = 1;
	ECanaShadow.CANME.bit.ME25 = 0;
	ECanaShadow.CANME.bit.ME26 = 0;
	ECanaShadow.CANME.bit.ME27 = 0;
	ECanaShadow.CANME.bit.ME28 = 0;
	ECanaShadow.CANME.bit.ME29 = 0;
	ECanaShadow.CANME.bit.ME30 = 0;
	ECanaShadow.CANME.bit.ME31 = 0;
	ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	EDIS;

}
//===========================================================================
// End of file.
//===========================================================================




