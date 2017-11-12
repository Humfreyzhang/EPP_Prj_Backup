#include "rtwtypes.h"
#include "can_matrix.h"
#include "io_type.h"
#include "motor_cnm.h"

CAN_Msg_300_T CAN_ID_300;
VecTMActSpdV_T Veh_spd_v;
int16_T Veh_spd;

Bool_T CAN_Error;
int16_T Motor_Speed;

uint16_T MotorSig_Loss_counter = 0;
Bool_T MotorSig_Lost = False;
uint16_T VehicleSig_Loss_counter = 0;
Bool_T VehicleSig_Lost = False;
uint16_T ParkSig_Loss_counter = 0;
Bool_T ParkSig_Lost = False;

uint16_T CAN_Recover_Counter;

void CAN_Msg_300_Task(uint8_T *buffer)
{

	CAN_ID_300.Dwords.word0 = *buffer++;
	CAN_ID_300.Dwords.word1 = *buffer++;
	CAN_ID_300.Dwords.word2 = *buffer++;
	CAN_ID_300.Dwords.word3 = *buffer++;

	Motor_Speed = (int16_T)(((CAN_ID_300.Bytes.BYTE4)<<8)|CAN_ID_300.Bytes.BYTE3)*0.5;
	MotorSig_Lost = False;
	MotorSig_Loss_counter = 0;

}

CAN_Msg_36A_T CAN_ID_36A;
void CAN_Msg_36A_Task(uint8_T *buffer)
{

	CAN_ID_36A.Dwords.word0 = *buffer++;
	CAN_ID_36A.Dwords.word1 = *buffer++;
	CAN_ID_36A.Dwords.word2 = *buffer++;
	CAN_ID_36A.Dwords.word3 = *buffer++;

	Veh_spd_v = (CAN_ID_36A.Bytes.BYTE4 & 0x80)>>7;
	Motor_Speed =(int16_T)( ((CAN_ID_36A.Bytes.BYTE4 & 0x7F)<<8) |CAN_ID_36A.Bytes.BYTE5 )- 0x4000;
	MotorSig_Lost = False;
	MotorSig_Loss_counter = 0;

}

CAN_Msg_270_T CAN_ID_270;
GearStatus_T  GearStatus;
void CAN_Msg_270_Task(uint8_T *buffer)
{
	CAN_ID_270.Dwords.word0 = *buffer++;
	CAN_ID_270.Dwords.word1 = *buffer++;
	CAN_ID_270.Dwords.word2 = *buffer++;
	CAN_ID_270.Dwords.word3 = *buffer++;

	GearStatus = (CAN_ID_270.Bytes.BYTE0)&0x03;
	ParkSig_Lost = False;
	ParkSig_Loss_counter = 0;

}

CAN_Msg_380_T CAN_ID_380;
T_Veh_Spd VehicleSpeed;
void CAN_Msg_380_Task(uint8_T *buffer)
{
	CAN_ID_380.Dwords.word0 = *buffer++;
	CAN_ID_380.Dwords.word1 = *buffer++;
	CAN_ID_380.Dwords.word2 = *buffer++;
	CAN_ID_380.Dwords.word3 = *buffer++;

	VehicleSpeed = ((CAN_ID_380.Bytes.BYTE1)<<8)|(CAN_ID_380.Bytes.BYTE0);
	VehicleSig_Lost = False;
	VehicleSig_Loss_counter = 0;

}

CAN_Msg_599_T CAN_ID_599;
void CAN_Msg_599_Task(uint8_T *buffer)
{
	CAN_ID_599.Dwords.word0 = *buffer++;
	CAN_ID_599.Dwords.word1 = *buffer++;
	CAN_ID_599.Dwords.word2 = *buffer++;
	CAN_ID_599.Dwords.word3 = *buffer++;

	VehicleSpeed = ((CAN_ID_599.Bytes.BYTE1)<<0x0F)|((CAN_ID_599.Bytes.BYTE2)<<0x07)|((CAN_ID_599.Bytes.BYTE3)>>1);
	VehicleSig_Lost = False;
	VehicleSig_Loss_counter = 0;
}


uint8_T EPP_Tx_55C[4];
extern EPP_State_T EPP_State;                 /* '<S1>/epp state' */
void CAN_Msg_55C_Tx()
{

	if(EPP_State==Parking){
	EPP_Tx_55C[0]=0x0006;
	}else if(EPP_State==Parked){
	EPP_Tx_55C[0]=0x0008;
	}else if(EPP_State==unParking){
	EPP_Tx_55C[0]=0x0012;
	}else if(EPP_State==unPark){
	EPP_Tx_55C[0]=0x0017;
	}
	else if(EPP_State==Initial)
	{
	switch(Motor_Position)
	{
		case 	LEFT_STOP:
		case	LEFT_OF_HIGH:
		case	HIGH:
				EPP_Tx_55C[0]=0x0008;
				break;
		case	RIGHT_OF_HIGH:
		case	ZONE_1:
		case	HIGH_LOCK:
				EPP_Tx_55C[0]=0x0012;
				break;
		case	ZONE_2:
		case	LOW:
		case	RIGHT_STOP:
				EPP_Tx_55C[0]=0x0017;
				break;
		case	ERROR_Position:
				EPP_Tx_55C[0]=0x0000;
			break;
		default:
			break;
	}

	}
	Hal_CAN_SendByte(MailBox20, &EPP_Tx_55C, 8);

}
uint8_T EPP_Tx_56C[4];
void CAN_Msg_56C_Tx()
{
	EPP_Tx_56C[0]=CAN_Error;
	EPP_Tx_56C[1]=0;
	EPP_Tx_56C[2]=0;
	EPP_Tx_56C[3]=0;
	Hal_CAN_SendByte(MailBox19, &EPP_Tx_56C, 8);

}

void CAN_Msg_Lost_Update(void)
{
	/*Motor speed signal timeout update*/
	MotorSig_Loss_counter++;

	if(MotorSig_Loss_counter>100){
		MotorSig_Lost = True;
	}
	/*Vehicle speed signal timeout update*/
	VehicleSig_Loss_counter++;

	if(VehicleSig_Loss_counter>100){
		VehicleSig_Lost = True;
	}
	
	/*Park Request signal timeout update*/
	ParkSig_Loss_counter++;

	if(ParkSig_Loss_counter>100){
		ParkSig_Lost = True;
	}
}

void CAN_Msg_error_Update(void)
{
	if((MotorSig_Lost&&VehicleSig_Lost)||ParkSig_Lost)
	{
		CAN_Error = True;
		CAN_Recover_Counter = 0;
	}
	else{

		CAN_Recover_Counter ++;
		if(CAN_Recover_Counter >= 5)
		{
			CAN_Error = False;
			CAN_Recover_Counter = 5;//100ms later will cleared
		}
	}

}
void CAN_Msg_100ms_Tasks(void)
{
	CAN_Msg_55C_Tx();
	CAN_Msg_56C_Tx();

}
