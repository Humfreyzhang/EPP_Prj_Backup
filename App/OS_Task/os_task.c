#include "rtwtypes.h"
#include "os_task.h"
#include "hal_pulse.h"
#include "hal_can.h"
#include "motor_cnm.h"
#include "instmain.h"
#include "instdaq.h"
#include "motor_cnm.h"
#include "iomm.h"
#include "AppLayer_Uds.h"
#include "epp.h"
#include "can_matrix.h"
#include "Rom_checksum.h"

//#pragma CODE_SECTION(OSTK_10msTasks, "ramfuncs");
//#pragma CODE_SECTION(OSTK_10msTasks_Interrupt, "ramfuncs");




void OSTK_Powerup_Task(void)
{
	EPP_Motor_Init();
	Epp_initialize();
	Rom_Checksum_init();

}



void OSTK_10msTasks_Interrupt(void)
{
	UpdateEPP_State();
	//CntrlEPP_Motor();
	Epp_step();

}

void OSTK_FreeTasks(void)
{


}

void OSTK_1msTasks(void)
{

	Check_If_Time_To_Transmit_DAQ_Lists( EVENT_1MSEC_LOOP );



}

void OSTK_5msTasks(void)
{

	UDSApp_v_g();




}

void OSTK_10msTasks(void)
{
	Cal_Analog_input();
	
	Instrumentation_Update();
	
	Rom_Checksum_cal_10ms();

}


void OSTK_20msTasks0(void)
{

	CAN_Msg_Lost_Update();
	CAN_Msg_error_Update();

}


void OSTK_20msTasks1(void)
{

	Hal_WatchDog_Service();






}

void OSTK_50msTasks0(void)
{






}


void OSTK_50msTasks1(void)
{




}



void OSTK_50msTasks2(void)
{


}


void OSTK_50msTasks3(void)
{




}


void OSTK_50msTasks4(void)
{




}


void OSTK_100msTasks0(void)
{
	uint8_T SendData[8];

	SendData[0] =0x0201;
	SendData[1] =0x0403;
	SendData[2] =0x0605;
	SendData[3] =0x0807;

	//Hal_CAN_SendRev(MailBox27, &SendData, 0x701, 8, TRUE);
	CAN_Msg_100ms_Tasks();

}


void OSTK_100msTasks1(void)
{
	




}



void OSTK_100msTasks2(void)
{




}


void OSTK_100msTasks3(void)
{




}


void OSTK_100msTasks4(void)
{

	Check_If_Time_To_Transmit_DAQ_Lists( EVENT_100MSEC_LOOP );


}



