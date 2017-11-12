#include "rtwtypes.h"
#include "app_cald.h"



const T_PERCENT_MULT_B Kf_Motor_DC_Park[4] =
    {
		V_PERCENT_MULT_B(90.0),
		V_PERCENT_MULT_B(85.0),
		V_PERCENT_MULT_B(80.0),
		V_PERCENT_MULT_B(70.0)
	};
	
const T_PERCENT_MULT_B Kf_Motor_DC_unPark[4] =
    {
		V_PERCENT_MULT_B(90.0),
		V_PERCENT_MULT_B(85.0),
		V_PERCENT_MULT_B(80.0),
		V_PERCENT_MULT_B(70.0)	
	};


const uint8_T Kf_Motor_DC_P[PID_Talbe_Sizes] =
	{
		PID_Scal_Set(50.0),
		PID_Scal_Set(50.0),
		PID_Scal_Set(50.0),
		PID_Scal_Set(50.0),
		PID_Scal_Set(50.0),
		PID_Scal_Set(50.0),
		PID_Scal_Set(50.0),
		PID_Scal_Set(50.0),
		PID_Scal_Set(50.0),
		PID_Scal_Set(50.0)
	};

const uint8_T Kf_Motor_DC_D[PID_Talbe_Sizes] =
	{
		PID_Scal_Set(50.0),
		PID_Scal_Set(50.0),
		PID_Scal_Set(50.0),
		PID_Scal_Set(50.0),
		PID_Scal_Set(50.0),
		PID_Scal_Set(50.0),
		PID_Scal_Set(50.0),
		PID_Scal_Set(50.0),
		PID_Scal_Set(50.0),
		PID_Scal_Set(50.0)
	};


const uint8_T kf_Motor_P_Max = PID_Scal_Set(90.0);
const uint8_T kf_Motor_D_Max = PID_Scal_Set(90.0);

const uint8_T kf_Motor_Current_Max = Motor_Cur_Set(20.0);
const uint8_T kf_Motor_Current_Min = Motor_Cur_Set(5.0);

const uint8_T kf_Motor_Slew = PID_Scal_Set(10.0);

const T_PERCENT_MULT_B Kf_Motor_DC_Park_Max = V_PERCENT_MULT_B(80.0);
const T_PERCENT_MULT_B Kf_Motor_DC_unPark_Max = V_PERCENT_MULT_B(80.0);

const T_VOLTb_B Kf_IGNOFF_Threshhold_Low = V_VOLTb_B(5.0);
const T_VOLTb_B Kf_IGNOFF_Threshhold_Hi  = V_VOLTb_B(8.0);

const T_Secondes Kt_IGNOFF_Delay = V_Secondes(5.0);

const uint16_T Kf_MotorStall_Rpm = 200;
const T_Veh_Spd Kf_VehiclStall_KPH = V_Veh_Spd(3);

