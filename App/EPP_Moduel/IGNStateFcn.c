/*
 * File: IGNStateFcn.c
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

#include "IGNStateFcn.h"

/* Include model header file for global data */
#include "Epp.h"
#include "Epp_private.h"

/* Named constants for Chart: '<S2>/IGN State' */
#define Epp_IN_NO_ACTIVE_CHILD_o       ((uint8_T)0U)
#define Epp_IN_ON                      ((uint8_T)1U)
#define Epp_IN_Off                     ((uint8_T)2U)
#define Epp_IN_Off_Delay               ((uint8_T)3U)

/* Initial conditions for atomic system: '<S2>/IGN State' */
void IGNStateFcn_Init(void)
{
  Epp_DWork.is_active_c2_Epp = 0U;
  Epp_DWork.is_c2_Epp = Epp_IN_NO_ACTIVE_CHILD_o;
  Epp_DWork.IGNState_Cnt = 0U;
  IgnState = Ign_Unknow;
}

/* Output and update for atomic system: '<S2>/IGN State' */
void IGNStateFcn(void)
{
  /* Gateway: IGN State/IGN State */
  /* During: IGN State/IGN State */
  if (Epp_DWork.is_active_c2_Epp == 0U) {
    /* Entry: IGN State/IGN State */
    Epp_DWork.is_active_c2_Epp = 1U;

    /* Entry Internal: IGN State/IGN State */
    /* Transition: '<S4>:4' */
    IgnState = Ign_On;
    Epp_DWork.is_c2_Epp = Epp_IN_ON;

    /* Entry 'ON': '<S4>:1' */
    Epp_DWork.IGNState_Cnt = 0U;
  } else {
    switch (Epp_DWork.is_c2_Epp) {
     case Epp_IN_ON:
      /* During 'ON': '<S4>:1' */
      if (IGN_V < (Kf_IGNOFF_Threshhold_Low << 9)) {
        /* Transition: '<S4>:5' */
        IgnState = Ign_Off_Delay;
        Epp_DWork.is_c2_Epp = Epp_IN_Off_Delay;
      }
      break;

     case Epp_IN_Off:
      break;

     default:
      /* During 'Off_Delay': '<S4>:2' */
      if (Epp_DWork.IGNState_Cnt > Kt_IGNOFF_Delay) {
        /* Transition: '<S4>:6' */
        IgnState = Ign_Off;
        Epp_DWork.is_c2_Epp = Epp_IN_Off;
      } else if (IGN_V > (Kf_IGNOFF_Threshhold_Hi << 9)) {
        /* Transition: '<S4>:9' */
        IgnState = Ign_On;
        Epp_DWork.is_c2_Epp = Epp_IN_ON;

        /* Entry 'ON': '<S4>:1' */
        Epp_DWork.IGNState_Cnt = 0U;
      } else {
        Epp_DWork.IGNState_Cnt++;
      }
      break;
    }
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
