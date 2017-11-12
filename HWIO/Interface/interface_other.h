#ifndef INTERFACE_OTHER_H
#define INTERFACE_OTHER_H

typedef struct unClearRAM_Tag
{
   uint16_T   reset_cnt;
   uint16_T   Pattern[2];
   uint16_T   reserve[5];
} unClearRAM_T;

extern uint32_T System_counter;
extern unClearRAM_T unClearRam;
//20000us
#define WD_Service_Time  (20000)


void WatchDog_init(void);
void IO_ECU_SoftwareReset(void);
uint32_T IO_Get_SystemTimerValue(void);
void IO_WatchDog_Service(void);

#endif
