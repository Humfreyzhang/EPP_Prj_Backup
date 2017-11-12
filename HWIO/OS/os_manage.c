
#include "os_types.h"

/* Function Definition */
void StartOS_Task(void); 


/*===========================================================================*\
 * StartOS
 *
 *
 *
\*===========================================================================*/
void StartOS(AppModeType_T Mode)
{

   if( Mode == AM_normal || Mode == AM_HardwareTest )
   {
      StartOS_Task();
   }
   else
   {
      while(1);
   }

   return;
}