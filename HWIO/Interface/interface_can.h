#ifndef INTERFACE_CAN_H
#define INTERFACE_CAN_H
#include "rtwtypes.h"
#include "io_type.h"

#define CANBufferDepth (6)
#define CANbufferSize  (4*CANBufferDepth)
#define NULL      0

typedef enum
{
	DAQ_1ms,
	DAQ_10ms,
	DAQ_100ms,
	DAQ_Max
}DAQ_T;

typedef void (*CAN_Receive_Callback)(uint8_T index);

typedef struct OS_CAN_Receive_Table_Tag
{
   uint16_T  CAN_ID;
   uint8_T   CAN_Length;
   CAN_Receive_Callback CallBack;
} OS_CAN_Receive_Table_T;

typedef struct OS_CAN_Tx_Ptr_Tag
{
   uint16_T   MailBox:5;
   uint16_T   transmit_requested:2;
   uint16_T   transmit_full:2;
   uint16_T   message_num_in_buffer:7;
   uint16_T  *buffer_base_address;
   uint16_T  *buffer_max_address;
   uint16_T  *next_data_out_ptr;
} OS_CAN_Tx_Ptr_T;

typedef struct CAN_Tx_Table_Tag
{
	uint16_T   MailBox:8;
	uint16_T   DEPTHBUF:8;
	uint16_T  *buffer_base_address;

}CAN_Tx_Table_T;

extern uint8_T CAN_Receive_Task_Trigger;


#define MailBox_SizeOffset  (4)
#define CANTRS_Low_Addr    (0x6004)
#define CANTRS_High_Addr    (0x6005)

#define CANTA_High_Addr    (0x6009)

#define CAN_MsgMailBox_Max     (10)
#define CAN_SIZE_ONCEOUT    (4)
#define CAN_RevTask_Trigger_Set(x)  (CAN_Receive_Task_Trigger = CAN_Receive_Task_Trigger | (1 << x))
#define CAN_RevTask_Active_Get(x)   (CAN_Receive_Task_Trigger & (1 << x))
#define CAN_RevTask_Active_Cls(x)   (CAN_Receive_Task_Trigger = CAN_Receive_Task_Trigger & (~(1 << x)))

extern void IO_CAN_SendSourceByte(uint8_T *SendAddress, uint16_T Channel, uint8_T Length);
extern void IO_CAN_SendWord(uint16_T *SendAddress, uint16_T Channel, uint8_T Length);
extern void IO_CAN_SendByte(uint8_T *SendAddress, uint16_T Channel, uint8_T Length);
extern void IO_CAN_Recive(uint16_T *RecvAddress, uint16_T Channel, uint8_T Length);

extern void CAN_Rev_Scheduel(void);

extern void CAN_RestInit(void);
extern uint8_T CAN_CCP_Out(uint16_T *message_address, uint8_T DAQ_Index);
extern uint8_T CAN_CCP_Tx_isr(uint8_T DAQ_Index);
#endif

