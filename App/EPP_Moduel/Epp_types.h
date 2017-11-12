/*
 * File: Epp_types.h
 *
 * Code generated for Simulink model 'Epp'.
 *
 * Model version                  : 1.236
 * Simulink Coder version         : 8.3 (R2012b) 20-Jul-2012
 * TLC version                    : 8.3 (Jul 21 2012)
 * C/C++ source code generated on : Mon Oct 16 23:39:11 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Epp_types_h_
#define RTW_HEADER_Epp_types_h_
#include "rtwtypes.h"
#ifndef _DEFINED_TYPEDEF_FOR_Bool_T_
#define _DEFINED_TYPEDEF_FOR_Bool_T_

typedef enum {
  False = 0,                           /* Default value */
  True
} Bool_T;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_GearStatus_T_
#define _DEFINED_TYPEDEF_FOR_GearStatus_T_

typedef enum {
  Off = 0,                             /* Default value */
  Park,
  Unpark,
  Invalid
} GearStatus_T;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_Motor_Position_T_
#define _DEFINED_TYPEDEF_FOR_Motor_Position_T_

typedef enum {
  LEFT_STOP = 0,                       /* Default value */
  LEFT_OF_HIGH,
  HIGH,
  RIGHT_OF_HIGH,
  ZONE_1,
  HIGH_LOCK,
  ZONE_2,
  LOW,
  RIGHT_STOP,
  ERROR_Position
} Motor_Position_T;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_EPP_State_T_
#define _DEFINED_TYPEDEF_FOR_EPP_State_T_

typedef enum {
  Initial = 0,                         /* Default value */
  Parked,
  unPark,
  Parking,
  unParking,
  Safe,
  Unknown
} EPP_State_T;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_IGNState_T_
#define _DEFINED_TYPEDEF_FOR_IGNState_T_

typedef enum {
  Ign_Unknow = 0,                      /* Default value */
  Ign_On,
  Ign_Off_Delay,
  Ign_Off
} IGNState_T;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_Epp RT_MODEL_Epp;

#endif                                 /* RTW_HEADER_Epp_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
