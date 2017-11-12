#ifndef OS_TYPES_H
#define OS_TYPES_H

#include "rtwtypes.h"

/* Data Types */
typedef enum
{
   AM_normal,
   AM_HardwareTest,
   AM_ManufacturingTest
}AppModeType_T;


/*===========================================================================*\
 * Type Definitions                                                          
\*===========================================================================*/
typedef enum OS_Executive_Loops_tag
{
   OS_Executive_Loop1,
   OS_Executive_Loop2,
   OS_MAX_EXECUTIVES
} OS_Executive_Loops_T;


typedef void (*OS_Executive_Callback)(uint8_T);
typedef void (*OS_Callback)(void);

typedef struct OS_Executive_Segment_Tag
{
   uint16_T  Pending_Segments:8;
   uint16_T  Active_Segment:8;
} OS_Executive_Segment_T;

typedef struct
{
   OS_Executive_Callback   Callback;
   uint8_T*                Max_Segments;
}  OS_Executive_T;












#endif