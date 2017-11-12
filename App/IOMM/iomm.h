#ifndef IOMM_H
#define IOMM_H
#include "t_types.h"

#define IGN_To_V   (0.2527f) //AD*3.3*4.9*1024/65536
#define Motor_Cur  (0.006848f) //AD*3.3*8.5*16*65536

extern T_VOLTb IGN_V;
extern T_Currentb Cur_V;
extern T_VOLTb Temprature_V;
extern IGNState_T IgnState;

void Cal_Analog_input(void);

#endif

