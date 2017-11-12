
#include "DSP2803x_Device.h"
#include "interface_gpio.h"
#include "hal_discrete_io.h"


extern volatile struct GPIO_DATA_REGS GpioDataRegs;

uint8_T Hal_Discrete_IO_Get(HAL_DISCRETE_IO_T Discrete_I)
{
	uint8_T Hal_Discrete_IO;

	switch(Discrete_I)
	{	
		case Sen1_uC_I:
			Hal_Discrete_IO = SEN1_uC_Get();
			break;
		case Sen2_uC_I:
			Hal_Discrete_IO = SEN2_uC_Get();
			break;
		case Sen3_uC_I:
			Hal_Discrete_IO = SEN3_uC_Get();
			break;
		case Sen4_uC_I:
			Hal_Discrete_IO = SEN4_uC_Get();
			break;
		case Emg_Set_I:
		    Hal_Discrete_IO = KEY1_uC_Get();
			break;
		case Spare_Set_I:
			Hal_Discrete_IO = KEY2_uC_Get();
			break;
	
		default:
			break;
	}

	return Hal_Discrete_IO;
}

