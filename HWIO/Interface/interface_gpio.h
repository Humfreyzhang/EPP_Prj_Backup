#ifndef INTERFACE_GPIO_H
#define INTERFACE_GPIO_H

#include "stdint.h"
#include "rtwtypes.h"

extern volatile struct GPIO_DATA_REGS GpioDataRegs;

#define uC_Enable_Set()  (GpioDataRegs.GPASET.bit.GPIO12 = 1)
#define uC_Enable_Cls()  (GpioDataRegs.GPASET.bit.GPIO12 = 0)

/* Motor Location Sensing GPIO Input */
#define SEN1_uC_Get()		    (GpioDataRegs.GPADAT.bit.GPIO21)
#define SEN2_uC_Get()			(GpioDataRegs.GPADAT.bit.GPIO22)
#define SEN3_uC_Get()			(GpioDataRegs.GPADAT.bit.GPIO23)
#define SEN4_uC_Get()			(GpioDataRegs.GPADAT.bit.GPIO24)
/* External Key Sensing GPIO Input */
#define KEY1_uC_Get()			(GpioDataRegs.GPADAT.bit.GPIO16)
#define KEY2_uC_Get()			(GpioDataRegs.GPADAT.bit.GPIO17)






uint8_T IO_Shutdown_Get(void);





#endif

