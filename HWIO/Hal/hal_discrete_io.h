#ifndef HAL_DISCRETE_IO_H
#define HAL_DISCRETE_IO_H

typedef enum
{
   Sen1_uC_I,
   Sen2_uC_I,
   Sen3_uC_I,
   Sen4_uC_I,
   Emg_Set_I,
   Spare_Set_I,
   Discrete_I_Max
}HAL_DISCRETE_IO_T;




uint8_T Hal_Discrete_IO_Get(HAL_DISCRETE_IO_T Discrete_I);

#endif
