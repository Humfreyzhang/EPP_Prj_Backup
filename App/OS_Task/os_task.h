#ifndef OS_TASK_H
#define OS_TASK_H

extern void OSTK_FreeTasks(void);
extern void OSTK_1msTasks(void);
extern void OSTK_5msTasks(void);
extern void OSTK_10msTasks(void);
extern void OSTK_20msTasks0(void);
extern void OSTK_20msTasks1(void);
extern void OSTK_50msTasks0(void);
extern void OSTK_50msTasks1(void);
extern void OSTK_50msTasks2(void);
extern void OSTK_50msTasks3(void);
extern void OSTK_50msTasks4(void);
extern void OSTK_100msTasks0(void);
extern void OSTK_100msTasks1(void);
extern void OSTK_100msTasks2(void);
extern void OSTK_100msTasks3(void);
extern void OSTK_100msTasks4(void);
extern void OSTK_10msTasks_Interrupt(void);
extern void OSTK_Powerup_Task(void);

//extern void OS_Powerup_Hook(void);


#endif
