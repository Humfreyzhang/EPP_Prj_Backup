#ifndef HAL_ANALOG_H
#define HAL_ANALOG_H

typedef enum
{
   IsenP_T,
   Ign_T,
   Temp_T,
   Analog_Max
}Hal_Analog_T;


extern uint16_T Hal_Analog_Get(Hal_Analog_T Analog_T);



#endif
