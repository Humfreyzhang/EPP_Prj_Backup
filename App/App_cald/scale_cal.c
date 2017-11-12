#include "scale_cal.h"
#include "t_types.h"


const int8_T P_Scale[PID_Talbe_Sizes] =
	{
	   -10, -8, -5, -2, 0, 2, 5, 8, 10, 15
	};

const int8_T D_Scale[PID_Talbe_Sizes] =
	{
	   -10, -8, -5, -2, 0, 2, 5, 8, 10, 15
	};

const T_VOLTb V_Scale[Volt_Talbe_Sizes] = 
	{
		V_VOLTb(8.0), 
		V_VOLTb(10.0), 
		V_VOLTb(13.0), 
		V_VOLTb(15.0)
	};