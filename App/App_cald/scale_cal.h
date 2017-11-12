#ifndef SCALE_CAL_H
#define SCALE_CAL_H
#include "rtwtypes.h"
#include "t_types.h"

#define PID_Talbe_Sizes   (10)
#define Volt_Talbe_Sizes   (4)

#define IGN_Volt_Set(x)    (uint16_T)(x << 4)
#define IGN_Volt_Get(x)    (float)(x >> 4)

extern const int8_T P_Scale[PID_Talbe_Sizes];
extern const int8_T D_Scale[PID_Talbe_Sizes];
extern const T_VOLTb V_Scale[Volt_Talbe_Sizes];
#endif

