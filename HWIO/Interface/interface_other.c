#include "DSP28x_Project.h"
#include "rtwtypes.h"
#include "interface_other.h"

#pragma DATA_SECTION(unClearRam,     "unClearRam");

uint32_T System_counter;
unClearRAM_T unClearRam;


void WatchDog_init(void)
{

	// Enable the watchdog
	EALLOW;
	if((SysCtrlRegs.SCSR & 0x0001) == 0)
	{
		SysCtrlRegs.SCSR = 0x0001;//watchdog interrput disable
	}
	//watch dog timeout timer about 105ms
	SysCtrlRegs.WDCR = 0x002C;//10MhZ/512/8
	EDIS;
	// Reset the watchdog counter
	ServiceDog();

}

void IO_ECU_SoftwareReset(void)
{
	while(TRUE)
	{};

}

uint32_T IO_Get_SystemTimerValue(void)
{
	return (CpuTimer2Regs.TIM.all);
}

void IO_WatchDog_Service(void)
{
	if((uint32_T)(System_counter - IO_Get_SystemTimerValue()) > WD_Service_Time)
	{
		ServiceDog();
		System_counter = IO_Get_SystemTimerValue();
	}

}




