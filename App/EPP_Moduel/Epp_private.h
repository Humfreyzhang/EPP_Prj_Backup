/*
 * File: Epp_private.h
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

#ifndef RTW_HEADER_Epp_private_h_
#define RTW_HEADER_Epp_private_h_
#include "rtwtypes.h"
#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#else
#ifdef TMWTYPES_PREVIOUSLY_INCLUDED
#error This file requires rtwtypes.h to be included before tmwtypes.h
#else

/* Check for inclusion of an incorrect version of rtwtypes.h */
#ifndef RTWTYPES_ID_C16S16I16L32N16F1
#error This code was generated with a different "rtwtypes.h" than the file included
#endif                                 /* RTWTYPES_ID_C16S16I16L32N16F1 */
#endif                                 /* TMWTYPES_PREVIOUSLY_INCLUDED */
#endif                                 /* __RTWTYPES_H__ */

/* Imported (extern) block signals */
extern IGNState_T IgnState;            /* '<S2>/IGN State' */
extern Bool_T CAN_Error;               /* '<Root>/In1' */
extern int16_T Motor_Speed;            /* '<Root>/In2' */
extern GearStatus_T GearStatus;        /* '<Root>/In3' */
extern Bool_T ActionFinished;          /* '<Root>/In4' */
extern uint16_T IGN_V;                 /* '<Root>/In5' */
extern uint16_T Kf_IGNOFF_Threshhold_Low;/* '<Root>/In6' */
extern uint16_T Kf_IGNOFF_Threshhold_Hi;/* '<Root>/In7' */
extern uint16_T Kt_IGNOFF_Delay;       /* '<Root>/In8' */
extern uint16_T Kf_MotorStall_Rpm;     /* '<Root>/In9' */
extern Bool_T SensorError;             /* '<Root>/In11' */
extern Motor_Position_T Motor_Position;/* '<Root>/In12' */
extern uint16_T Kf_VehiclStall_KPH;    /* '<Root>/In10' */
extern Bool_T VehicleSig_Lost;         /* '<Root>/In13' */
extern Bool_T MotorSig_Lost;           /* '<Root>/In14' */
extern uint16_T VehicleSpeed;          /* '<Root>/In15' */

#endif                                 /* RTW_HEADER_Epp_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
