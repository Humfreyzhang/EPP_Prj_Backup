/*
 * File: Epp.h
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

#ifndef RTW_HEADER_Epp_h_
#define RTW_HEADER_Epp_h_
#ifndef Epp_COMMON_INCLUDES_
# define Epp_COMMON_INCLUDES_
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#endif                                 /* Epp_COMMON_INCLUDES_ */

#include "Epp_types.h"

/* Child system includes */
#include "EppStateFcn.h"
#include "IGNStateFcn.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((void*) 0)
#endif

/* user code (top of header file) */
#include "externfunction.h"

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint16_T IGNState_Cnt;               /* '<S2>/IGN State' */
  uint16_T is_active_c2_Epp;           /* '<S2>/IGN State' */
  uint16_T is_c2_Epp;                  /* '<S2>/IGN State' */
  uint16_T is_active_c1_Epp;           /* '<S1>/epp state' */
  uint16_T is_c1_Epp;                  /* '<S1>/epp state' */
} D_Work_Epp;

/* Real-time Model Data Structure */
struct tag_RTM_Epp {
  const char_T *errorStatus;
};

/* Block states (auto storage) */
extern D_Work_Epp Epp_DWork;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern EPP_State_T EPP_State;          /* '<S1>/epp state' */

/* Model entry point functions */
extern void Epp_initialize(void);
extern void Epp_step(void);

/* Real-time Model object */
extern RT_MODEL_Epp *const Epp_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Epp'
 * '<S1>'   : 'Epp/EPP State'
 * '<S2>'   : 'Epp/IGN State'
 * '<S3>'   : 'Epp/EPP State/epp state'
 * '<S4>'   : 'Epp/IGN State/IGN State'
 */
#endif                                 /* RTW_HEADER_Epp_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
