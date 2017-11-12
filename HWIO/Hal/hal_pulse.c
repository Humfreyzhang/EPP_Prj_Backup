
#include "rtwtypes.h"
#include "DSP2803x_Device.h"
#include "hal_pulse.h"

void Hal_MOTOR_Duty_Set(uint8_T Dir, uint16_T fDuty)
{
	Motor_Dir_Command = Dir;
	Motor_duty = (float)(fDuty/200.0f);
}

void Hal_MOTOR_Freq_Set(uint16_T Freq)
{
	IO_PWM_Freq_Set(Freq);
}

void Hal_MOTOR_Enable_Set(uint8_T Enable)
{
	IO_PWM_Enable(Enable);
}
