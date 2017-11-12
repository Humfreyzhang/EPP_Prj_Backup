
#include "rtwtypes.h"
#include "hal_analog.h"
#include "t_types.h"
#include "iomm.h"
#include "app_cald.h"

T_VOLTb IGN_V;
T_Currentb Cur_V;
T_VOLTb Temprature_V;


IGNState_T IgnState;

void Cal_Analog_input(void)
{
	
	IGN_V = (T_VOLTb)(Hal_Analog_Get(Ign_T)*IGN_To_V);
	Cur_V = (T_Currentb)(Hal_Analog_Get(IsenP_T)*Motor_Cur);
	Temprature_V = (T_VOLTb)Hal_Analog_Get(Temp_T);

	
}


