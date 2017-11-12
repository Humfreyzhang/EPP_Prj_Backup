
#include "rtwtypes.h"
#include "DSP2803x_Device.h"
#include "hal_can.h"
#include "interface_can.h"
//#pragma CODE_SECTION(Hal_CAN_Send, "ramfuncs");


void Hal_CAN_SendWord(CANMailBox_T channel, uint16_T *Buffer, uint8_T Length)
{
	IO_CAN_SendWord( Buffer, channel, Length);
}

void Hal_CAN_SendByte(CANMailBox_T channel, uint8_T *Buffer, uint8_T Length)
{
	IO_CAN_SendByte( Buffer, channel, Length);
}