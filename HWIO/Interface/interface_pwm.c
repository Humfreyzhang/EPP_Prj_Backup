
#include "rtwtypes.h"
#include "DSP2803x_Device.h"     // DSP2803x Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP2803x Examples Include File
#include "interface_pwm.h"
#include "DSP2803x_function.h"


#define GATE_IN_P(n)		GpioDataRegs.GPADAT.bit.GPIO2 = n		// Gate Drive#1 Inhibit 
#define GATE_IN_N(n)		GpioDataRegs.GPADAT.bit.GPIO4 = n		// Gate Drive#2 Inhibit 

#define CPU_CLK			(long)(60000000)			// 60MHz

static uint8_T PWM_Dir_Last;

void IO_PWM_Enable(uint8_T Enable)
{
	GATE_IN_P(Enable);
	Delay_us(5);
	GATE_IN_N(Enable);
}


void IO_PWM_DC_Set(uint8_T Dir, float fDuty)
{

	if(PWM_Dir_Last != Dir)
	{
		if(Dir == Motor_FWD)
		{
		/*A channel with aways high, so the BTN7960 high side will active aways */
		/*B channel will will clear at zero, and set at compare with period, so the 0 - period will be low
		and the BTN7960 low side was active*/
			EPwm1Regs.CMPB = (uint16_T)((EPwm1Regs.TBPRD + 1)*fDuty);
			EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;
			EPwm1Regs.AQCTLA.bit.CAU = AQ_NO_ACTION;
			EPwm1Regs.AQCTLB.bit.ZRO = AQ_CLEAR;
			EPwm1Regs.AQCTLB.bit.CBU = AQ_SET;
		}
		else if(Dir == Motor_REV)
		{
			EPwm1Regs.CMPA.half.CMPA = (uint16_T)((EPwm1Regs.TBPRD + 1)*fDuty);
			EPwm1Regs.AQCTLA.bit.ZRO = AQ_CLEAR;
			EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;
			EPwm1Regs.AQCTLB.bit.ZRO = AQ_SET;
			EPwm1Regs.AQCTLB.bit.CBU = AQ_NO_ACTION;
		}
		else
		{
			EPwm1Regs.AQCTLA.bit.ZRO = AQ_CLEAR;
			EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
			EPwm1Regs.AQCTLB.bit.ZRO = AQ_CLEAR;
			EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;

		}
	}
	else
	{
		if(Dir == Motor_REV)
		{
			EPwm1Regs.CMPB = (uint16_T)(((EPwm1Regs.TBPRD + 1)*fDuty));
		}
		else if(Dir == Motor_FWD)
		{
			EPwm1Regs.CMPA.half.CMPA = (uint16_T)(((EPwm1Regs.TBPRD + 1)*fDuty));
		}
		else
		{
			EPwm1Regs.AQCTLA.bit.ZRO = AQ_CLEAR;
			EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
			EPwm1Regs.AQCTLB.bit.ZRO = AQ_CLEAR;
			EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;
		}

	}
	
	PWM_Dir_Last = Dir ;

}

void IO_PWM_Freq_Set(uint16_T Freq)
{
	EPwm1Regs.TBPRD = (uint16_T)((uint16_T)(CPU_CLK/Freq) - 1u);
}

