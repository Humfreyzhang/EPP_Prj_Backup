
#include "rtwtypes.h"
#include "DSP2803x_CLAShared.h"
#include "interface_analog.h"


uint16_T IO_Analog_Get(ANALOGType_T Anlog_T)
{
	uint16_T Temp_Return;
	switch(Anlog_T)
	{
		case IsenP_V:
			Temp_Return = IsenP;
			break;
		case Ign_V:
			Temp_Return = Vign;
			break;
		case Temp_V:
			Temp_Return = Vtemp;
			break;
		default:
			break;
	}

	return (uint16_T)(Temp_Return << 4);
}


