
#include "DSP28x_Project.h"
#include "rtwtypes.h"
#include "interface_other.h"
#include "os_throughput.h"

LOOP_THROUGHPUT_T VaOSTK_ThruPutData[NUMBER_OF_CeOSTK_SEG];
static uint8_T VbOSTK_ThruPutData_FirstTime[NUMBER_OF_CeOSTK_SEG];


void Init_InitThroughputData(void)
{

	VbOSTK_ThruPutData_FirstTime[CeOSTK_SEG_LOOP_BkG] = true;
	VbOSTK_ThruPutData_FirstTime[CeOSTK_SEG_10ms_Int] = true;
}


void Enter_OSThroughputMeasure(OSTK_SEG_T index)
{
	VaOSTK_ThruPutData[index].t_EnterTime = IO_Get_SystemTimerValue();
}

void Leave_OSThroughputMeasure(OSTK_SEG_T index)
{
	VaOSTK_ThruPutData[index].t_LeaveTime = IO_Get_SystemTimerValue();
	if(VaOSTK_ThruPutData[index].t_EnterTime ==0)
		return;
	VaOSTK_ThruPutData[index].t_CurrExecTime = \
		VaOSTK_ThruPutData[index].t_EnterTime - VaOSTK_ThruPutData[index].t_LeaveTime;
	if ( VbOSTK_ThruPutData_FirstTime[index] ) {
		VbOSTK_ThruPutData_FirstTime[index] = false;
		VaOSTK_ThruPutData[index].t_AvgExecTime = VaOSTK_ThruPutData[index].t_CurrExecTime;
		VaOSTK_ThruPutData[index].t_MaxExecTime = VaOSTK_ThruPutData[index].t_CurrExecTime;
		VaOSTK_ThruPutData[index].t_MinExecTime = VaOSTK_ThruPutData[index].t_CurrExecTime;
	} else {
		if ( VaOSTK_ThruPutData[index].t_CurrExecTime < VaOSTK_ThruPutData[index].t_MinExecTime ) {
			/* find minimum value */
			VaOSTK_ThruPutData[index].t_MinExecTime = VaOSTK_ThruPutData[index].t_CurrExecTime;
		} else if ( VaOSTK_ThruPutData[index].t_CurrExecTime > VaOSTK_ThruPutData[index].t_MaxExecTime ) {
			/* find maximum value */
			VaOSTK_ThruPutData[index].t_MaxExecTime = VaOSTK_ThruPutData[index].t_CurrExecTime;
		} else {
			// nothing to do
		}
	}

	if ( VaOSTK_ThruPutData[index].t_AvgExecTime < VaOSTK_ThruPutData[index].t_CurrExecTime ) {
		VaOSTK_ThruPutData[index].t_AvgExecTime += 
			(VaOSTK_ThruPutData[index].t_CurrExecTime-VaOSTK_ThruPutData[index].t_AvgExecTime) >> TIMEMEASURE_PARAMETER ;
	} else {
		VaOSTK_ThruPutData[index].t_AvgExecTime -= 
			(VaOSTK_ThruPutData[index].t_AvgExecTime-VaOSTK_ThruPutData[index].t_CurrExecTime) >> TIMEMEASURE_PARAMETER ;
	}
}


