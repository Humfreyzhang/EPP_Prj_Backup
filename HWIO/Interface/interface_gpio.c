#include "DSP28x_Project.h"
#include "interface_gpio.h"
//#include "os_types.h"
//#include "interface_gpio.h"
//
//#include "os_task.h"
#include "iomm.h"


uint8_T IO_Shutdown_Get(void)
{
	return (IgnState == Ign_Off ? FALSE: TRUE);
}


