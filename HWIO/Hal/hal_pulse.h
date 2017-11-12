#ifndef HAL_PULSE_H
#define HAL_PULSE_H

extern uint8_T Motor_Dir_Command;
extern float Motor_duty;


extern void Hal_MOTOR_Duty_Set(uint8_T Dir, uint16_T fDuty);
extern void Hal_MOTOR_Freq_Set(uint16_T Freq);
extern void Hal_MOTOR_Enable_Set(uint8_T Enable);


#endif
