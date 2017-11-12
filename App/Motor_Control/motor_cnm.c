#include "rtwtypes.h"
#include "Epp_types.h"
#include "motor_cnm.h"
#include "app_cald.h"
#include "hal_pulse.h"
#include "hal_analog.h"
#include "hal_discrete_io.h"
#include "can_matrix.h"
#include "scale_cal.h"
#include "iomm.h"

//#pragma DATA_SECTION(Motor_P, "CpuToCla1MsgRAM");
//#pragma DATA_SECTION(Motor_I, "CpuToCla1MsgRAM");
#pragma DATA_SECTION(Motor_Dir_Command, "CpuToCla1MsgRAM");
#pragma DATA_SECTION(Motor_duty,"CpuToCla1MsgRAM");
#pragma DATA_SECTION(Motor_Current_Max,"CpuToCla1MsgRAM");
#pragma DATA_SECTION(Motor_P_Slew,"CpuToCla1MsgRAM");

extern uint16_T SysInit_OK;  //Sys initialization has been complted.


Motor_Parameter_T Motor_Con;
uint8_T Motor_Dir_Command;
float Motor_duty;
uint8_T Motor_Current_Max;
float Motor_P_Slew;
Motor_Position_T Motor_Position;
//float Motor_P[4], Motor_I[4];
uint8_T ActionFinished;

#define System_Status_Get()     (1)


void CalcMotor_Pct_PositionError(void)
{


    Motor_Con.Pos_Current  = Hal_Discrete_IO_Get(Sen1_uC_I) << 3|
   	                         Hal_Discrete_IO_Get(Sen2_uC_I) << 2|
   	                         Hal_Discrete_IO_Get(Sen3_uC_I) << 1|
   	                         Hal_Discrete_IO_Get(Sen4_uC_I) << 0;
}
void GearStatus_RestInit(void)
{
	/*Initilize the Gearstatus as Unknown*/
	GearStatus = 0x04;
}
void MotorPos_Process(void)
{
	switch(Motor_Con.Pos_Current)
	{
		case 0x08:// Left Stop : Parked(1000 / 0x08)
			Motor_Position = LEFT_STOP;
			break;
		case 0x0A:// Left of high : Parked(1000 / 0x08)
			Motor_Position = LEFT_OF_HIGH;
			break;
		case 0x0B:// High : Parked(1111 / 0x0F)
			Motor_Position = HIGH;
			break;
		case 0x0F:// Right of High (1111)
			Motor_Position = RIGHT_OF_HIGH;
			break;
		case 0x0E:// Zone#1 (1110)
			Motor_Position = ZONE_1;
			break;
		case 0x06:// High Lock (0110)
			Motor_Position = HIGH_LOCK;
			break;
		case 0x07:// Zone#2 : Unparked(0111 / 0x07)
			Motor_Position = ZONE_2;
			break;
		case 0x05:// LOW : Unparked(0101 / 0x05)
			Motor_Position = LOW;
			break;
		case 0x0D:// Righ Stop : Unparked(0101 / 0x0D)
			Motor_Position = RIGHT_STOP;
			break;
		default:/* Unknown*/
			Motor_Position = ERROR_Position;
			break;
	}
}
#if 0
uint16_T CalMotor_DC_DerivativeTerm(int16_T Error)
{
  uint8_T index;
  float index_f;
  uint16_T D_parameter;
  
  for(index =0; index < PID_Talbe_Sizes; index ++)
  {
	if(Error < D_Scale[index])
		break;
  }
  index_f = (Error - D_Scale[index - 1])/(D_Scale[index] - D_Scale[index - 1]);
  D_parameter = Kf_Motor_DC_D[index - 1] + (Kf_Motor_DC_D[index] - Kf_Motor_DC_D[index - 1])*index_f;

  return D_parameter;
}

uint16_T CalMotor_DC_ProportionalTerm(int16_T Error)
{
  uint8_T index;
  float index_f;
  uint16_T P_parameter;
  
  for(index =0; index < PID_Talbe_Sizes; index ++)
  {
	if(Error < P_Scale[index])
		break;
  }
  index_f = (Error - P_Scale[index - 1])/(P_Scale[index] - P_Scale[index - 1]);
  P_parameter = Kf_Motor_DC_P[index - 1] + (Kf_Motor_DC_P[index] - Kf_Motor_DC_P[index - 1])*index_f;

  return P_parameter;
}
#endif

T_DUTY_CYCLEb Cal_Park_DC(T_VOLTb IGN_V)
{
	uint8_T index;
    float index_f;
    uint16_T D_parameter;
  
	for(index =3; index >=0; index--)
	{
		if(IGN_V >= V_Scale[index])
			break;
	}

	if(index == 3)
	{
		return Kf_Motor_DC_Park[3];
	}
	
	index_f = (float)(IGN_V - V_Scale[index])/(V_Scale[index + 1] - V_Scale[index]);
	D_parameter = Kf_Motor_DC_Park[index] - (T_PERCENT_MULT_B)((Kf_Motor_DC_Park[index ] - Kf_Motor_DC_Park[index + 1])*index_f);
	
	return D_parameter;
}

T_DUTY_CYCLEb Cal_unPark_DC(T_VOLTb IGN_V)
{
	uint8_T index;
    uint16_T D_parameter;
    float index_f;
	
	for(index =3; index >=0; index--)
	{
		if(IGN_V >= V_Scale[index])
			break;
	}

	if(index == 3)
	{
		return Kf_Motor_DC_unPark[3];
	}
	
	index_f = (float)(IGN_V - V_Scale[index])/(V_Scale[index + 1] - V_Scale[index]);
	D_parameter = Kf_Motor_DC_unPark[index] - (T_PERCENT_MULT_B)((Kf_Motor_DC_unPark[index ] - Kf_Motor_DC_unPark[index + 1])*index_f);
	
	return D_parameter;
}

void EPP_Motor_Init(void)
{
    Motor_Current_Max = kf_Motor_Current_Max;
	Motor_P_Slew = (float)(kf_Motor_Slew/200.0);
	Hal_MOTOR_Duty_Set(Motor_Stop, 0.0);
	Hal_MOTOR_Enable_Set(TRUE);
}
/*Update CAN command and EPP state*/
void UpdateEPP_State()
{
    uint16_T Motor_DC_Max;

	CalcMotor_Pct_PositionError();
	MotorPos_Process();
	Motor_Con.Motor_DC_Output = Cal_Park_DC(IGN_V);

	if(Motor_Con.Motor_DC_Output > Kf_Motor_DC_Park_Max)
	{
		Motor_Con.Motor_DC_Output = Kf_Motor_DC_Park_Max;
	}
}

void Motor_Unpark_Process()
{
	switch(Motor_Position)
	{
		case 	LEFT_STOP:
		case	LEFT_OF_HIGH:
		case	HIGH:
		case	RIGHT_OF_HIGH:
		case	ZONE_1:
		case	HIGH_LOCK:
			Hal_MOTOR_Duty_Set(Motor_FWD, Motor_Con.Motor_DC_Output);
			break;
		case	ZONE_2:
			Hal_MOTOR_Duty_Set(Motor_Stop, 0);
			ActionFinished = TRUE;
			break;
		case	LOW:
		case	RIGHT_STOP:
			Hal_MOTOR_Duty_Set(Motor_REV, Motor_Con.Motor_DC_Output/2);
			break;
		case	ERROR_Position:
			
			break;
		default:
			break;
	}
}

uint16_T High_closing_counter; 
void Motor_Park_Process()
{
	switch(Motor_Position)
	{
		case 	LEFT_STOP:
		case	LEFT_OF_HIGH:
			/*If the Motor has passed the HIGH position, the motor will reverse back to the high*/
			/*position with a smaller DC*/
			Hal_MOTOR_Duty_Set(Motor_FWD, Motor_Con.Motor_DC_Output/2);
			ActionFinished = 1;
			break;
		case	HIGH:
			if((High_closing_counter >= 10)||(1==ActionFinished))
			{
				Hal_MOTOR_Duty_Set(Motor_Stop, 0);
				High_closing_counter = 0;
				ActionFinished = TRUE;
			}
			else if(!ActionFinished)
			{
				High_closing_counter++;
			}
			break;
		case	RIGHT_OF_HIGH:
		case	ZONE_1:
		case	HIGH_LOCK:
		case	ZONE_2:
		case	LOW:
		case	RIGHT_STOP:
			Hal_MOTOR_Duty_Set(Motor_REV, Motor_Con.Motor_DC_Output);
			break;
		case	ERROR_Position:
			
			break;
		default:
			break;
	}

}
int Motor_Is_Running; //EPP motor is running
Motor_Dir_T Set_Command, Set_Command_old, Set_Command_Trg;
int16_T nElec_Engine_RMP;
uint16_T nElec_Engine_RMP_abs;
void CntrlEPP_Motor(void)
{

	/*****************************************************************************/
	/* Sys initialization has been completed */
	if(SysInit_OK==0)		return;



	/*****************************************************************************/
	//  CAN Data Command Process
	/*****************************************************************************/
	// Fault Clear Request

	//Customer defined CAN command.
	#if 0
	//for SGMW prj
	if (GearStatus == 0x03){
		Set_Command = Motor_REV; //park
	}
	else if ((GearStatus == 0x00)||(GearStatus == 0x01)||(GearStatus == 0x02))
	{
		Set_Command = Motor_FWD; //unpark
	}
	#endif

	//datong prj
	if (GearStatus == 0x01){
		Set_Command = Motor_REV; //park
	}
	else if (GearStatus == 0x02)
	{
		Set_Command = Motor_FWD; //Unpark
	}
	//Electric Motor(Engine) Speed Check */
	//SGMW prj: 	nElec_Engine_RMP = Veh_spd;
	//For Datong Prj: nElec_Engine_RMP = Veh_spd/2;
	nElec_Engine_RMP = Veh_spd/2;
	nElec_Engine_RMP_abs = abs(Veh_spd);
	/*****************************************************************************/
	// Update Motor command
	//If motor is running, the Set_Command_Trg will stay unchaged.
	/*****************************************************************************/
	if(Motor_Is_Running ==0){
		if(Set_Command==Motor_REV){
			if(nElec_Engine_RMP_abs <=200){
				Set_Command_Trg = Motor_REV; 
			}else{
				Set_Command_Trg = Motor_Stop;
			}
		}else if(Set_Command==Motor_FWD){
			Set_Command_Trg = Motor_FWD;
		}
	}

	Set_Command = Motor_Stop;
#if 0
	/*****************************************************************************/
	// Fault diagnostics
	/*****************************************************************************/
	if(Set_Command_Trg==RST_CMD){
		Fault_State_Reset();	
	}	
#endif

	/*Unpark process*/
	if(Set_Command_Trg == Motor_FWD)
	{
		Motor_Unpark_Process();		
	}
	/*Park process*/
	else if(Set_Command_Trg == Motor_REV )
	{
		Motor_Park_Process();
	}
	else if(Set_Command_Trg == Motor_Stop )
	{
		Hal_MOTOR_Duty_Set(Motor_Stop, 0);
	}

}

void EppAction(uint8_T state)
{
	if((state == Parked)||(state == Parking))
	{
		Motor_Park_Process();
	}
	else if((state == unPark)||(state == unParking))
	{
		Motor_Unpark_Process();	
	}
	else
	{
		Hal_MOTOR_Duty_Set(Motor_Stop, 0);
	}
}

void EppParktoUnpark(void)
{
	ActionFinished = FALSE;
}

void EppUnParktoPark(void)
{
	ActionFinished = FALSE;
}
