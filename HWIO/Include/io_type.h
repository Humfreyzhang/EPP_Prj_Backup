#ifndef IO_TYPE_H
#define IO_TYPE_H
#include "rtwtypes.h"

typedef enum
{
   MailBox0,
   MailBox1,
   MailBox2,
   MailBox3,
   MailBox4,
   MailBox5,
   MailBox6,
   MailBox7,
   MailBox8,
   MailBox9,
   MailBox10,
   MailBox11,
   MailBox12,
   MailBox13,
   MailBox14,
   MailBox15,
   MailBox16,
   MailBox17,
   MailBox18,
   MailBox19,
   MailBox20,
   MailBox21,
   MailBox22,
   MailBox23,
   MailBox24,
   MailBox25,
   MailBox26,
   MailBox27,
   MailBox28,
   MailBox29,
   MailBox30,
   MailBox31,
   MailBox_Max
}CANMailBox_T;


typedef union CAN_Msg_Tag
{
   uint16_T      Word[4];
   struct{
	   uint16_T      BYTE0:8;     // 7:0
	   uint16_T      BYTE1:8;     // 15:8
	   uint16_T      BYTE2:8;     // 23:16
	   uint16_T      BYTE3:8;     // 31:24
	   uint16_T      BYTE4:8;     // 39:32
	   uint16_T      BYTE5:8;     // 47:40
	   uint16_T      BYTE6:8;     // 55:48
	   uint16_T      BYTE7:8;     // 63:56
   }Byte;

}CAN_Msg_T;





#endif
