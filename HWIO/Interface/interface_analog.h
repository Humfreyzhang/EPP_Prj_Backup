#ifndef INTERFACE_ANALOG_H
#define INTERFACE_ANALOG_H

typedef enum
{
   IsenP_V,
   Ign_V,
   Temp_V,
   Analog_Max
}ANALOGType_T;

extern uint16_T IO_Analog_Get(ANALOGType_T Anlog_T);

#endif
