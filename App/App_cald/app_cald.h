#ifndef APP_CALD_H
#define APP_CALD_H
#include "scale_cal.h"


#define uMotor_DC_Set(x)    (uint8_T)(x * 2)
#define uMotor_DC_Get(x)    (uint8_T)(x / 2)


#define PID_Scal_Set(x)     (uint8_T)(x * 2)
#define PID_Scal_Get(x)     (uint8_T)(x / 2)

#define Motor_Cur_Set(x)   (uint8_T)(x * 2)
#define Motor_Cur_Get(x)   (uint8_T)(x / 2)

extern const uint8_T Kf_Motor_DC_Park[4];
extern const uint8_T Kf_Motor_DC_unPark[4];

extern const uint8_T Kf_Motor_DC_P[PID_Talbe_Sizes];
extern const uint8_T Kf_Motor_DC_D[PID_Talbe_Sizes];


extern const uint8_T kf_Motor_P_Max;
extern const uint8_T kf_Motor_D_Max;

extern const uint8_T kf_Motor_Current_Max;
extern const uint8_T kf_Motor_Current_Min;

extern const T_PERCENT_MULT_B Kf_Motor_DC_Park_Max;
extern const T_PERCENT_MULT_B Kf_Motor_DC_unPark_Max;

extern const uint8_T kf_Motor_Slew;

extern const T_VOLTb_B Kf_IGNOFF_Threshhold_Low;
extern const T_VOLTb_B Kf_IGNOFF_Threshhold_Hi;

extern const T_Secondes Kt_IGNOFF_Delay;

extern const uint16_T Kf_MotorStall_Rpm;
extern const uint16_T Kf_VehiclStall_KPH;

#endif

