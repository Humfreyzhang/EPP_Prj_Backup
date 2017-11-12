#include "DSP2803x_Device.h"     // DSP2803x Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP2803x Examples Include File
#include "DSP2803x_isr.h"
#include "os_types.h"
#include "io_type.h"
#include "interface_can.h"
#include "os_throughput.h"

//#pragma CODE_SECTION(cpu_timer0_isr, "ramfuncs");
#pragma CODE_SECTION(cpu_timer1_isr, "ramfuncs");
//#pragma CODE_SECTION(CAN_receive_isr, "ramfuncs");
#pragma DATA_SECTION(CAN_Msg_Buffer,     "CANBuffer");

extern OS_Executive_Segment_T OS_Executive_Segment[OS_MAX_EXECUTIVES];
extern const uint8_T OS_EXEC1_SEGS;
extern const uint8_T OS_EXEC2_SEGS;
extern void OSTK_10msTasks_Interrupt(void);

extern uint16_T os_loop_counter;

CAN_Msg_T CAN_Msg_Buffer[CAN_MsgMailBox_Max];

__interrupt void  cpu_timer0_isr(void)
{
	Enter_OSThroughputMeasure(CeOSTK_SEG_10ms_Int);
	OSTK_10msTasks_Interrupt();
	Leave_OSThroughputMeasure(CeOSTK_SEG_10ms_Int);
   	// Acknowledge this interrupt to receive more interrupts from group 1
   	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

}

/*interrput in 1ms*/
__interrupt void  cpu_timer1_isr(void)
{
	os_loop_counter++;
	OS_Executive_Segment[OS_Executive_Loop1].Pending_Segments++;

	if(os_loop_counter >= 10)
	{
		OS_Executive_Segment[OS_Executive_Loop2].Pending_Segments++;
		os_loop_counter = 0;
	}
	
	if (OS_Executive_Segment[OS_Executive_Loop1].Pending_Segments > OS_EXEC1_SEGS)
	{
		 OS_Executive_Segment[OS_Executive_Loop1].Pending_Segments = 0;
	}

	if (OS_Executive_Segment[OS_Executive_Loop2].Pending_Segments > OS_EXEC2_SEGS)
	{
		 OS_Executive_Segment[OS_Executive_Loop2].Pending_Segments = 0;
	}
	
}


__interrupt void  CAN_receive_isr(void)
{
    uint16_T index;
	uint16_T *CANRMP;

	CANRMP = &ECanaRegs.CANRMP;
	for(index =0; index < CAN_MsgMailBox_Max; index++)
	{
		if((*CANRMP & (1 << index)))
		{
			IO_CAN_Recive(&CAN_Msg_Buffer[index], index,  8);
			*CANRMP = (1<< index);
		}
	}

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

__interrupt void  CAN_tx_isr(void)
{

	if(ECanaRegs.CANTA.bit.TA22 ==1)
	{
		(void)CAN_CCP_Tx_isr(DAQ_1ms);
		ECanaRegs.CANTA.bit.TA22 = 1;
	}

	if(ECanaRegs.CANTA.bit.TA23 ==1)
	{
		(void)CAN_CCP_Tx_isr(DAQ_10ms);
		ECanaRegs.CANTA.bit.TA23 = 1;
	}

	if(ECanaRegs.CANTA.bit.TA24 ==1)
	{
		(void)CAN_CCP_Tx_isr(DAQ_100ms);
		ECanaRegs.CANTA.bit.TA24 = 1;
	}
	
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}