
#include "os_types.h"
#include "os_time.h"
/*===========================================================================*\
 * Macro Definitions
\*===========================================================================*/
#define NUM_EMS_LOOP1 5
#define NUM_EMS_LOOP2 10


/*===========================================================================*\
 * Global Variables
\*===========================================================================*/
const uint8_T OS_EXEC1_SEGS = (NUM_EMS_LOOP1-1);
const uint8_T OS_EXEC2_SEGS = (NUM_EMS_LOOP2-1);

OS_Executive_Segment_T OS_Executive_Segment[OS_MAX_EXECUTIVES];
uint16_T os_loop_counter;


void OS_Exec_Callback_1(uint8_T loop)
{
   OS_Executive_1_Hook(loop);

}


void OS_Exec_Callback_2(uint8_T loop)
{
   OS_Executive_2_Hook(loop);

}



const OS_Executive_T OS_Executives[] =
{
   {OS_Exec_Callback_1, (uint8_T *)&OS_EXEC1_SEGS},
   {OS_Exec_Callback_2, (uint8_T *)&OS_EXEC2_SEGS}
};




