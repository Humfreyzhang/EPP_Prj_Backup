#ifndef INTERFACE_PWM_H
#define INTERFACE_PWM_H

typedef enum{
	Motor_Stop,
	Motor_FWD,
	Motor_REV
}Motor_Dir_T;

extern void IO_PWM_Enable(uint8_T Enable);
extern void IO_PWM_DC_Set(uint8_T Dir, float fDuty);
extern void IO_PWM_Freq_Set(uint16_T Freq);


#endif