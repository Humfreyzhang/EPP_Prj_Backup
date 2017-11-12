#ifndef DSP2803X_ISR_H
#define DSP2803X_ISR_H


__interrupt void cpu_timer0_isr(void);
__interrupt void cpu_timer1_isr(void);
__interrupt void CAN_receive_isr(void);
__interrupt void CAN_tx_isr(void);


#endif

