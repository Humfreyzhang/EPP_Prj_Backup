/*
 * File: Epp.c
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

#include "Epp.h"
#include "Epp_private.h"

/* Exported block signals */
EPP_State_T EPP_State;                 /* '<S1>/epp state' */

/* Block states (auto storage) */
D_Work_Epp Epp_DWork;

/* Real-time model */
RT_MODEL_Epp Epp_M_;
RT_MODEL_Epp *const Epp_M = &Epp_M_;

/* Model step function */
void Epp_step(void)
{
  /* Chart: '<S1>/epp state' */
  EppStateFcn();

  /* Chart: '<S2>/IGN State' */
  IGNStateFcn();
}

/* Model initialize function */
void Epp_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Epp_M, (NULL));

  /* block I/O */

  /* exported global signals */
  EPP_State = Initial;

  /* states (dwork) */
  (void) memset((void *)&Epp_DWork, 0,
                sizeof(D_Work_Epp));

  /* InitializeConditions for Chart: '<S1>/epp state' */
  EppStateFcn_Init();

  /* InitializeConditions for Chart: '<S2>/IGN State' */
  IGNStateFcn_Init();
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
