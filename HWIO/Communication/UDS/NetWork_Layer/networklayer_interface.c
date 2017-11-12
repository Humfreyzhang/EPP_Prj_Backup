/*!******************************************************************************************************
*	@file 	networklayer_interface.c
*	@brief 	networklayer_interface 源文件
*	@author Matt Zhang
*	@version 1.0
*	@date  2015-9-3
*	@warning
*                (c) Copyright 2015, KAIT Automotive Technology(Suzhou) Co., Ltd.
*                                       All Rights Reserved
*	@note
-
*********************************************************************************************************/
//#include "EPC_parameter.h"
//#include "EPC_Library.h"
//#include "EPC_TimerIR.h"
//#include "EPC_HwdECan.h"
//#include "EPC_AppECan.h"
//#include "EPC_ApiECan.h"
#include "rtwtypes.h"
#include "DSP2803x_Device.h"     // DSP28 Headerfile Include File
#include "DSP2803x_ECan.h"
#include "interface_can.h"
#include "io_type.h"
#include "DSP2803x_function.h"
#include "AppLayer_Uds.h"
#include "interface_other.h"

struct  UDSMSG_BITS {     // bits  description
   Uint16 DLC:4;          // 0:3
   Uint16 RTR:1;          // 4
   Uint16 rsvd1:3;        // 7:5   reserved
   Uint16 TPL:5;          // 12:8
   Uint16 rsvd2:3;        // 15:13 reserved
   Uint16 rsvd3:16;       // 31:16 reserved
};

/*
*********************************************************************************************************
*                                                MACROS 
*********************************************************************************************************
*/
//extern EPMMI5_bool CanA_TX27(unsigned int length, unsigned char *buffer);
/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/
unsigned char RequestCmd_u8_Sig=0;     
unsigned char IndicationCmd_u8_Sig=0;     
unsigned char ConfirmCmd_u8_Sig=0;     
uint16_T RXbuffer_u8a8_Sig[4]={0};  
unsigned char RecFlag_u8_Sig=0;   
unsigned long RecID_u8_Sig=1;    





/*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void CAN_Msg_703_Task(uint8_T *buffer, uint8_T index)
{
	uint16_T *MailBox;
	uint16_T  x;
	uint16_T  Data_length;
	uint16_T UDS_Data[4];

	UDS_Data[0] = *buffer++;
	UDS_Data[1] = *buffer++;
	UDS_Data[2] = *buffer++;
	UDS_Data[3] = *buffer++;

	MailBox = &ECanaMboxes.MBOX0.MSGCTRL + 4*index;
	Data_length = *MailBox;

	CANLength_u8_Sig = Data_length&0x0F;
	RecFlag_u8_Sig = 1;
	RecID_u8_Sig = PHYSICAL_ID;

	CopyMemory_WithNone_Byte(&RXbuffer_u8a8_Sig,&UDS_Data, LSB, LSB, CANLength_u8_Sig);

}


/*
*********************************************************************************************************
*                                             C ENTRY POINT
*********************************************************************************************************
*/
/*!******************************************************************************************************
*	@fn	unsigned char UdsSend(unsigned char length,unsigned char* buffer)
*	@brief	Can发送函数
*	@author Matt Zhang
*	@para length为发送长度；buffer发送的buffer
*	@return	unsigned char
*	@note
-此发送函数是网络层和底层的接口
*********************************************************************************************************
*/
unsigned char UdsSend(unsigned char length,unsigned char* buffer){  

      unsigned char len,cnt;
	  uint32_T timer, delta_time;
	  
	    len = length;
	    if(length!=8 && length!=0)/*判断发送的长度是否为8*/
	    {
		   length=8;/*长度置为8*/
	    }

	    for(cnt=len;cnt<8;cnt++)
	    {
	    	buffer[cnt]=0x00;/*将没有用到的元素全部填充为0*/

	    }
		
		CopyMemory_With_SourceByte(&ECanaMboxes.MBOX16.MDL, buffer, LSB, 8);
		
		ECanaRegs.CANTRS.bit.TRS16 = 1;
		timer = IO_Get_SystemTimerValue();
		while(!ECanaRegs.CANTA.bit.TA16)
		{
			delta_time = (uint32_T)(IO_Get_SystemTimerValue() - timer);
			if(delta_time > 1000)
				break;
		}
		
		ECanaRegs.CANTA.bit.TA16 = 1;
	 return 1;
}




