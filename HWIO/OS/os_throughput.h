#ifndef OS_THROUGHPUT_H
#define OS_THROUGHPUT_H
#include "rtwtypes.h"

#define TIMEMEASURE_PARAMETER             ( 5 )

typedef struct {
    uint32_T  t_AvgExecTime;
    uint32_T  t_MaxExecTime;
    uint32_T  t_MinExecTime;
    uint32_T  t_CurrExecTime;
    uint32_T  t_EnterTime;
    uint32_T  t_LeaveTime;
} LOOP_THROUGHPUT_T;

typedef enum {
    CeOSTK_SEG_LOOP_BkG,
    CeOSTK_SEG_10ms_Int,
    NUMBER_OF_CeOSTK_SEG
} OSTK_SEG_T;

void Init_InitThroughputData(void);
void Enter_OSThroughputMeasure(OSTK_SEG_T index);
void Leave_OSThroughputMeasure(OSTK_SEG_T index);

#endif