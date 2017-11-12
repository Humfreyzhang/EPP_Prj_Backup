#ifndef HAL_CAN_H
#define HAL_CAN_H
#include "io_type.h"



extern void Hal_CAN_SendWord(CANMailBox_T channel, uint16_T *Buffer, uint8_T Length);
extern void Hal_CAN_SendByte(CANMailBox_T channel, uint8_T *Buffer, uint8_T Length);

#endif

