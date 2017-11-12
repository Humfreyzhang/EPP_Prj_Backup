#ifndef T_TYPES_H
#define T_TYPES_H

#include "rtwtypes.h"


typedef uint16_T                T_PERCENT_MULT_W;
#define V_PERCENT_MULT_W(val)   (uint16_T)((val)*65536)
#define S_PERCENT_MULTW        16

typedef uint16_T                T_VOLTb;
#define V_VOLTb(val)            (uint16_T)((val)*1024)
#define S_VOLTb                 10

typedef uint8_T                T_VOLTb_B;
#define V_VOLTb_B(val)            (uint8_T)((val)*2)
#define S_VOLTb_B                 1


typedef uint16_T                T_DUTY_CYCLEb;
#define V_DUTY_CYCLEb(val)     (uint16_T)((val)*(65536))
#define S_DUTY_CYCLEb          1

typedef uint8_T                T_PERCENT_MULT_B;
#define V_PERCENT_MULT_B(val)   (uint8_T)((val)*2)
#define S_PERCENT_MULTB        1

typedef uint16_T                T_Currentb;
#define V_Currentb(val)        (uint16_T)((val)*(16))
#define S_DUTY_CYCLEb          4

typedef int16_T                T_CurrentS;
#define V_CurrentS(val)        (int16_T)((val)*(16))
#define S_DUTY_CYCLES          4

typedef uint16_T                T_Secondes;
#define V_Secondes(val)        (uint16_T)((val)*(100))

typedef uint16_T                T_Veh_Spd;
#define V_Veh_Spd(val)        (uint16_T)((val)*(100))

typedef struct{
	T_Currentb Current_Desired;
	T_Currentb Current_Max;
	T_DUTY_CYCLEb Motor_DC_Max;
	float Motor_P;
	float Motor_I;
}CPUtoCLA_MotorMsg;

#ifndef _DEFINED_TYPEDEF_FOR_IGNState_T_
#define _DEFINED_TYPEDEF_FOR_IGNState_T_

typedef enum {
  Ign_Unknow = 0,                      /* Default value */
  Ign_On,
  Ign_Off_Delay,
  Ign_Off
} IGNState_T;

#endif

#endif

