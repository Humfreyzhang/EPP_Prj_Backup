#ifndef MOTOR_CNM_H
#define MOTOR_CNM_H

#include "t_types.h"



typedef enum{
	Motor_Stop,
	Motor_FWD,
	Motor_REV
}Motor_Dir_T;

typedef struct{

	uint16_T Pos_Desired: 8;
	uint16_T Pos_Current: 8;
	//int16_T  Pos_Error_Cur;
	//int16_T  Pos_Error_Pre;
	//int16_T  Pos_Error_Delta;
	Motor_Dir_T  Motor_Dir;
	//uint16_T Motor_P;
	//uint16_T Motor_D;
	uint16_T Motor_DC_Output;

}Motor_Parameter_T;

#ifndef _DEFINED_TYPEDEF_FOR_Motor_Position_T_
#define _DEFINED_TYPEDEF_FOR_Motor_Position_T_

typedef enum{
	LEFT_STOP,
	LEFT_OF_HIGH,
	HIGH,
	RIGHT_OF_HIGH,
	ZONE_1,
	HIGH_LOCK,
	ZONE_2,
	LOW,
	RIGHT_STOP,
	ERROR_Position
}Motor_Position_T;
#endif

extern Motor_Position_T Motor_Position;

void EPP_Motor_Init(void);
void UpdateEPP_State();
void CntrlEPP_Motor(void);

#endif

