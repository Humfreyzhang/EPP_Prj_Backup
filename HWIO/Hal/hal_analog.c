
#include "rtwtypes.h"
#include "DSP2803x_Device.h"
#include "hal_analog.h"

uint16_T Hal_Analog_Get(Hal_Analog_T Analog_T)
{
	return IO_Analog_Get(Analog_T);
}

