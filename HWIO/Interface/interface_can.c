#include "rtwtypes.h"
#include "DSP2803x_Device.h"     // DSP28 Headerfile Include File
#include "DSP2803x_ECan.h"
#include "interface_can.h"
#include "io_type.h"
#include "DSP2803x_function.h"

#pragma DATA_SECTION(CAN_Buffer,     "CANBuffer");
#pragma DATA_SECTION(CAN_Transmit_Ptr,     "CANBuffer");



uint16_T CAN_Buffer[3][CANbufferSize];


uint8_T CAN_Receive_Task_Trigger;

void CAN_Rev_Callback_300(uint8_T index);
void CAN_Rev_Callback_380(uint8_T index);
void CAN_Rev_Callback_599(uint8_T index);
void CAN_Rev_Callback_300(uint8_T index);
void CAN_Rev_Callback_00A(uint8_T index);
void CAN_Rev_Callback_08C(uint8_T index);
void CAN_Rev_Callback_52A(uint8_T index);
void CAN_Rev_Callback_270(uint8_T index);
void CAN_Rev_Callback_36A(uint8_T index);
void CAN_Rev_Callback_703(uint8_T index);


extern CAN_Msg_T CAN_Msg_Buffer[CAN_MsgMailBox_Max];



const OS_CAN_Receive_Table_T CAN_Receive_Table[CAN_MsgMailBox_Max]=
{
	{0x300, 8, &CAN_Rev_Callback_300},
	{0x380, 8, &CAN_Rev_Callback_380},
	{0x599, 8, &CAN_Rev_Callback_599},
	{0x36A, 8, &CAN_Rev_Callback_36A},
	{0x00A, 8, &CAN_Rev_Callback_00A},
	{0x08C, 8, &CAN_Rev_Callback_08C},
	{0x52A, 8, &CAN_Rev_Callback_52A},
	{0x270, 8, &CAN_Rev_Callback_270},
	{0x7D0, 8, NULL},
	{0x703, 8, &CAN_Rev_Callback_703}

};

OS_CAN_Tx_Ptr_T CAN_Transmit_Ptr[3];

const CAN_Tx_Table_T CAN_Transmit_Table[3] =
{
	{MailBox22, CANBufferDepth, &CAN_Buffer[0]},
	{MailBox23, CANBufferDepth, &CAN_Buffer[1]},
	{MailBox24, CANBufferDepth, &CAN_Buffer[2]}

};
 

void CAN_RestInit(void)
{
	uint8_T index;

	for(index =0; index < 3; index ++)
	{
		CAN_Transmit_Ptr[index].MailBox = CAN_Transmit_Table[index].MailBox;
		CAN_Transmit_Ptr[index].transmit_full = FALSE;
		CAN_Transmit_Ptr[index].transmit_requested = FALSE;
		CAN_Transmit_Ptr[index].buffer_base_address = CAN_Transmit_Table[index].buffer_base_address;
		CAN_Transmit_Ptr[index].next_data_out_ptr   = CAN_Transmit_Table[index].buffer_base_address;
	    CAN_Transmit_Ptr[index].buffer_max_address  = CAN_Transmit_Table[index].buffer_base_address + \
			                                   CAN_SIZE_ONCEOUT*CAN_Transmit_Table[index].DEPTHBUF;
		CAN_Transmit_Ptr[index].message_num_in_buffer = 0;
	}
}

void IO_CAN_SendSourceByte(uint8_T *SendAddress, uint16_T Channel, uint8_T Length)
{
	uint16_T *CanBuffer;
	uint16_T *CANTRS;
	uint8_T index;

	CanBuffer = &ECanaMboxes.MBOX0.MDL + MailBox_SizeOffset*Channel;
	CANTRS = CANTRS_High_Addr;

	#if 0
	ECanaMboxes.MBOX16.MDL.byte.BYTE0 = SendAddress[0];
	ECanaMboxes.MBOX16.MDL.byte.BYTE1 = SendAddress[1];
	ECanaMboxes.MBOX16.MDL.byte.BYTE2 = SendAddress[2];
	ECanaMboxes.MBOX16.MDL.byte.BYTE3 = SendAddress[3];
	ECanaMboxes.MBOX16.MDH.byte.BYTE4 = SendAddress[4];
	ECanaMboxes.MBOX16.MDH.byte.BYTE5 = SendAddress[5];
	ECanaMboxes.MBOX16.MDH.byte.BYTE6 = SendAddress[6];
	ECanaMboxes.MBOX16.MDH.byte.BYTE7 = SendAddress[7];
	#endif

	CopyMemory_With_SourceByte(CanBuffer, SendAddress, LSB, Length);
	*CANTRS = (1<< (Channel - 16));

}

/*CAN Date send out with bytes*/
void IO_CAN_SendByte(uint8_T *SendAddress, uint16_T Channel, uint8_T Length)
{
	uint16_T *CanBuffer;
	uint16_T *CANTRS;
	uint8_T index;

	CanBuffer = &ECanaMboxes.MBOX0.MDL + MailBox_SizeOffset*Channel;
	CANTRS = CANTRS_High_Addr;

	CopyMemory_WithNone_Byte(CanBuffer, SendAddress, LSB, LSB, 8);
	*CANTRS = (1<< (Channel - 16));

}

/*CAN Data Send out with words*/
void IO_CAN_SendWord(uint16_T *SendAddress, uint16_T Channel, uint8_T Length)
{
	uint16_T *CanBuffer;
	uint16_T *CANTRS;

	CanBuffer = &ECanaMboxes.MBOX0.MDL + MailBox_SizeOffset*Channel;
	CANTRS = CANTRS_High_Addr;

	*CanBuffer++ = *SendAddress++;
	*CanBuffer++ = *SendAddress++;
	*CanBuffer++ = *SendAddress++;
	*CanBuffer++ = *SendAddress++;

	*CANTRS = (1<< (Channel - 16));

}


void IO_CAN_Recive(uint16_T *RecvAddress, uint16_T Channel, uint8_T Length)
{
	uint16_T *MailBox;

	MailBox = &ECanaMboxes.MBOX0.MDL + MailBox_SizeOffset*Channel;

	*RecvAddress++ = *MailBox++;
	*RecvAddress++ = *MailBox++;
	*RecvAddress++ = *MailBox++;
	*RecvAddress++ = *MailBox++;

	CAN_RevTask_Trigger_Set(Channel);

}

void CAN_Rev_Scheduel(void)
{
	uint8_T index;

	for(index =0; index < CAN_MsgMailBox_Max; index++)
	{
		if(CAN_RevTask_Active_Get(index))
		{
			CAN_RevTask_Active_Cls(index);

			if(CAN_Receive_Table[index].CallBack !=NULL)
			{
				CAN_Receive_Table[index].CallBack(index);
			}
		}

	}
}

void CAN_Rev_Callback_300(uint8_T index)
{

	CAN_Msg_300_Task(&CAN_Msg_Buffer[index]);


}

extern void CAN_Msg_703_Task(uint8_T *buffer, uint8_T index);
void CAN_Rev_Callback_703(uint8_T index)
{

	CAN_Msg_703_Task(&CAN_Msg_Buffer[index], index);

}


void CAN_Rev_Callback_380(uint8_T index)
{
	
	CAN_Msg_380_Task(&CAN_Msg_Buffer[index]);
}


void CAN_Rev_Callback_599(uint8_T index)
{
	
	CAN_Msg_599_Task(&CAN_Msg_Buffer[index]);
}


void CAN_Rev_Callback_71A(uint8_T index)
{


}


void CAN_Rev_Callback_00A(uint8_T index)
{


}


void CAN_Rev_Callback_08C(uint8_T index)
{


}


void CAN_Rev_Callback_52A(uint8_T index)
{


}

void CAN_Rev_Callback_270(uint8_T index)
{

	CAN_Msg_270_Task(&CAN_Msg_Buffer[index]);
}

void CAN_Rev_Callback_36A(uint8_T index)
{

	CAN_Msg_36A_Task(&CAN_Msg_Buffer[index]);
}

uint8_T CAN_CCP_Out(uint16_T *message_address, uint8_T DAQ_Index)
{
	uint16_T *Current_out_ptr;

	if(CAN_Transmit_Ptr[DAQ_Index].transmit_full != TRUE)
	{
		Current_out_ptr = CAN_Transmit_Ptr[DAQ_Index].next_data_out_ptr;
		
		*CAN_Transmit_Ptr[DAQ_Index].next_data_out_ptr ++ = *message_address++;
		*CAN_Transmit_Ptr[DAQ_Index].next_data_out_ptr ++ = *message_address++;
		*CAN_Transmit_Ptr[DAQ_Index].next_data_out_ptr ++ = *message_address++;
		*CAN_Transmit_Ptr[DAQ_Index].next_data_out_ptr ++ = *message_address++;
		CAN_Transmit_Ptr[DAQ_Index].message_num_in_buffer ++;

		if((CAN_Transmit_Ptr[DAQ_Index].next_data_out_ptr ) > CAN_Transmit_Ptr[DAQ_Index].buffer_max_address)
		{
			CAN_Transmit_Ptr[DAQ_Index].transmit_full = TRUE;

		}
		
		if(CAN_Transmit_Ptr[DAQ_Index].transmit_requested != TRUE)
		{
			IO_CAN_SendWord(Current_out_ptr,  \
				            CAN_Transmit_Ptr[DAQ_Index].MailBox, 8);

			CAN_Transmit_Ptr[DAQ_Index].transmit_requested = TRUE;
		}
		
		return TRUE;

	}
	else
	{
		return FALSE;
	}

}


uint8_T CAN_CCP_Tx_isr(uint8_T DAQ_Index)
{
	//uint16_T *Current_out_ptr;

	CAN_Transmit_Ptr[DAQ_Index].transmit_full = FALSE;
	CAN_Transmit_Ptr[DAQ_Index].next_data_out_ptr = CAN_Transmit_Ptr[DAQ_Index].next_data_out_ptr - CAN_SIZE_ONCEOUT;
	CAN_Transmit_Ptr[DAQ_Index].message_num_in_buffer --;
	
	if((CAN_Transmit_Ptr[DAQ_Index].next_data_out_ptr > CAN_Transmit_Ptr[DAQ_Index].buffer_base_address)&&\
		(CAN_Transmit_Ptr[DAQ_Index].message_num_in_buffer > 0))
	{
		//Current_out_ptr = CAN_Transmit_Ptr[DAQ_Index].next_data_out_ptr - CAN_SIZE_ONCEOUT;
		IO_CAN_SendWord(CAN_Transmit_Ptr[DAQ_Index].next_data_out_ptr,  \
	            CAN_Transmit_Ptr[DAQ_Index].MailBox, 8);

		return TRUE;
	}
	else
	{
		CAN_Transmit_Ptr[DAQ_Index].transmit_requested = FALSE;
		return TRUE;
	}
}

