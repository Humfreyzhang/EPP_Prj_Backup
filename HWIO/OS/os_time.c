
#include "os_types.h"
#include "interface_gpio.h"
#include "DSP2803x_Device.h"
#include "os_task.h"
#include "interface_can.h"
#include "instmain.h"
#include "interface_other.h"
#include "os_throughput.h"
#include "AppLayer_Uds.h"

uint16_T SysInit_OK;  //Sys initialization has been complted.

extern OS_Executive_Segment_T OS_Executive_Segment[OS_MAX_EXECUTIVES];
extern const OS_Executive_T OS_Executives[];
extern uint16_T os_loop_counter;

/* ============================================================================ *\
 * Function definitions
 * ============================================================================ */
void Base_Loop1_Executive(uint8_T loop)
{

   switch (loop)
   {
      case 0 :
            OSTK_1msTasks();
            break;
      case 1 :
            OSTK_1msTasks();
            break;
      case 2 :
            OSTK_1msTasks();
            break;
      case 3 :
            OSTK_1msTasks();
            break;
      case 4 :
            OSTK_1msTasks();
            OSTK_5msTasks();
            break;
	  default:
	  	    break;
   	}

}

void Base_Loop2_Executive(uint8_T loop)
{

   switch (loop)
   {
      case 0 :
            OSTK_10msTasks();
            OSTK_20msTasks0();
            OSTK_50msTasks0();
            OSTK_100msTasks0();
            break;
      case 1 :
            OSTK_10msTasks();
            OSTK_20msTasks1();
            OSTK_50msTasks1();
            break;
      case 2 :
            OSTK_10msTasks();
            OSTK_20msTasks0();
            OSTK_50msTasks2();
            OSTK_100msTasks1();
            break;
      case 3 :
            OSTK_10msTasks();
            OSTK_20msTasks1();
            OSTK_50msTasks3();
            break;
      case 4 :
            OSTK_10msTasks();
            OSTK_20msTasks0();
            OSTK_50msTasks4();
            OSTK_100msTasks2();
            break;
      case 5 :
            OSTK_10msTasks();
            OSTK_20msTasks1();
            OSTK_50msTasks0();
            break;
      case 6 :
            OSTK_10msTasks();
            OSTK_20msTasks0();
            OSTK_50msTasks1();
            OSTK_100msTasks3();
            break;
      case 7 :
            OSTK_10msTasks();
            OSTK_20msTasks1();
            OSTK_50msTasks2();
            break;
      case 8 :
            OSTK_10msTasks();
            OSTK_20msTasks0();
            OSTK_50msTasks3();
            OSTK_100msTasks4();
            break;
      case 9 :
            OSTK_10msTasks();
            OSTK_20msTasks1();
            OSTK_50msTasks4();
			break;
	  default:
	  	    break;
   	}

}


void OS_Startup_Hook(void)
{
	CAN_Receive_Task_Trigger = 0x0000;
	os_loop_counter = 0;
	WatchDog_init();
	Init_InitThroughputData();
	CAN_RestInit();
	GearStatus_RestInit();
	inst_resetkeyon();
	FlashInit_API();
	UdsInit_v_g();
	EEPROM_Restore();
    OSTK_Powerup_Task();

}


void OS_Powerdown_Hook(void)
{
	EEPROM_Backup();


}


void OS_Free_Task_Hook(void)
{
    CAN_Rev_Scheduel();
	OSTK_FreeTasks();

}


void OS_Executive_1_Hook(uint8_T loop)
{   
      Base_Loop1_Executive(loop);
}

void OS_Executive_2_Hook(uint8_T loop)
{   
      Base_Loop2_Executive(loop);
}

void StartOS_Task(void)
{
    uint8_T index;
	
	uC_Enable_Set();
	OS_Startup_Hook();
   	EINT;   // Enable Global interrupt INTM
   	ERTM;   // Enable Global realtime interrupt DBGM
   	SysInit_OK =1; //system init has been completed.
	while(IO_Shutdown_Get())
	{
		Enter_OSThroughputMeasure(CeOSTK_SEG_LOOP_BkG);

		for (index=0; index < OS_MAX_EXECUTIVES; index++)
		{
		   if (OS_Executive_Segment[index].Pending_Segments != \
			   OS_Executive_Segment[index].Active_Segment)
		   {
			   OS_Executive_Segment[index].Active_Segment++;
			  if (OS_Executive_Segment[index].Active_Segment > \
					   *OS_Executives[index].Max_Segments)
			  {
				   OS_Executive_Segment[index].Active_Segment = 0;
			  }
			  (OS_Executives[index].Callback)(OS_Executive_Segment[index].Active_Segment);
		   }
		}
		
		OS_Free_Task_Hook();
		Leave_OSThroughputMeasure(CeOSTK_SEG_LOOP_BkG);
	}
	OS_Powerdown_Hook();
}

