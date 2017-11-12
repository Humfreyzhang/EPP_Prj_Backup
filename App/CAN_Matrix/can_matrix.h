#ifndef CAN_MATRIX_H
#define CAN_MATRIX_H
#include "epp_types.h"

typedef struct {      // bits   description
	uint16_T		BYTE6:8;	 // 55:48
	uint16_T		BYTE7:8;	 // 63:56

	/**Byte4**/
	uint16_T         DrTorqRqstV: 1;//bit0
	uint16_T         VecActGearSts: 3;//bit3:1
	uint16_T         Reserve1: 4;//bit1:7:4

	/**Byte5**/
	uint16_T		BYTE5:8;	 // 47:40
	uint16_T		BYTE2:8;	 // 23:16
	uint16_T		BYTE3:8;	 // 31:24
	uint16_T		BYTE0:8;	 // 7:0
	uint16_T		BYTE1:8;	 // 15:8
}CAN_Msg_155_BYTES_T;

typedef struct {      // bits   description
	uint16_T		BYTE6:8;	 // 55:48
	uint16_T		BYTE7:8;	 // 63:56
	uint16_T		BYTE4:8;	 // 39:32
	uint16_T		BYTE5:8;	 // 47:40
	uint16_T		BYTE2:8;	 // 23:16
	uint16_T		BYTE3:8;	 // 31:24
	uint16_T		BYTE0:8;	 // 7:0
	uint16_T		BYTE1:8;	 // 15:8
}CAN_Msg_300_BYTES_T;

typedef struct {      // bits   description
	uint16_T		BYTE6:8;	 // 55:48
	uint16_T		BYTE7:8;	 // 63:56
	uint16_T		BYTE4:8;	 // 39:32
	uint16_T		BYTE5:8;	 // 47:40
	uint16_T		BYTE23:16;	 // 31:16
	uint16_T		BYTE01:16;	 // 15:0
}CAN_Msg_36A_BYTES_T;

typedef struct {      // bits   description
	uint16_T		BYTE6:8;	 // 55:48
	uint16_T		BYTE7:8;	 // 63:56
	uint16_T		BYTE4:8;	 // 39:32
	uint16_T		BYTE5:8;	 // 47:40
	uint16_T		BYTE23:16;	 // 31:16
	uint16_T		BYTE0:8;	 // 7:0
	uint16_T		BYTE1:8;	 // 15:8
}CAN_Msg_270_BYTES_T;

typedef struct {      // bits   description
	uint16_T		BYTE6:8;	 // 55:48
	uint16_T		BYTE7:8;	 // 63:56
	uint16_T		BYTE4:8;	 // 39:32
	uint16_T		BYTE5:8;	 // 47:40
	uint16_T		BYTE23:16;	 // 31:16
	uint16_T		BYTE0:8;	 // 7:0
	uint16_T		BYTE1:8;	 // 15:8
}CAN_Msg_380_BYTES_T;

typedef struct {      // bits   description
	uint16_T		BYTE6:8;	 // 55:48
	uint16_T		BYTE7:8;	 // 63:56
	uint16_T		BYTE4:8;	 // 39:32
	uint16_T		BYTE5:8;	 // 47:40
	uint16_T		BYTE2:8;	 // 23:16
	uint16_T		BYTE3:8;	 // 31:24
	uint16_T		BYTE0:8;	 // 7:0
	uint16_T		BYTE1:8;	 // 15:8
}CAN_Msg_599_BYTES_T;


typedef struct {     
	uint16_T		word3;
	uint16_T		word2;
	uint16_T		word1;
	uint16_T		word0;

}CAN_Msg_Words_T;


typedef union{

CAN_Msg_Words_T Dwords;

CAN_Msg_155_BYTES_T Bytes;


}CAN_Msg_155_T;

typedef union{

CAN_Msg_Words_T Dwords;

CAN_Msg_300_BYTES_T Bytes;


}CAN_Msg_300_T;

typedef union{

CAN_Msg_Words_T Dwords;

CAN_Msg_36A_BYTES_T Bytes;


}CAN_Msg_36A_T;

#define  _DEFINED_TYPEDEF_FOR_GearStatus_T_

typedef union{

CAN_Msg_Words_T Dwords;

CAN_Msg_270_BYTES_T Bytes;


}CAN_Msg_270_T;

typedef union{

CAN_Msg_Words_T Dwords;

CAN_Msg_380_BYTES_T Bytes;


}CAN_Msg_380_T;


typedef union{

CAN_Msg_Words_T Dwords;

CAN_Msg_599_BYTES_T Bytes;


}CAN_Msg_599_T;


#if 0
// for SGMW prj
typedef enum{
	Neutral,
	Driver,
	Rerverse,
	Park,
	Unknown
} GearStatus_T;
#endif

#ifndef _DEFINED_TYPEDEF_FOR_GearStatus_T_
#define _DEFINED_TYPEDEF_FOR_GearStatus_T_

//For datong prj
typedef enum{
	Off,
	Park,
	Unpark,
	Invalid
} GearStatus_T;
#endif

typedef enum{
	Valid,
	Unvalid
} VecTMActSpdV_T;


extern CAN_Msg_300_T CAN_ID_300;
extern GearStatus_T  GearStatus;
extern VecTMActSpdV_T Veh_spd_v;
extern int16_T Veh_spd;

extern void CAN_Msg_300_Task(uint8_T *buffer);
extern void CAN_Msg_36A_Task(uint8_T *buffer);
extern void CAN_Msg_270_Task(uint8_T *buffer);
extern void CAN_Msg_380_Task(uint8_T *buffer);
extern void CAN_Msg_599_Task(uint8_T *buffer);
extern void CAN_Msg_55C_Tx();
extern void CAN_Msg_56C_Tx();
extern void CAN_Msg_Lost_Update();
extern void CAN_Msg_error_Update();

#endif


