/*
 * File: EppStateFcn.c
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

#include "EppStateFcn.h"

/* Include model header file for global data */
#include "Epp.h"
#include "Epp_private.h"

/* Named constants for Chart: '<S1>/epp state' */
#define Epp_IN_Initial                 ((uint8_T)1U)
#define Epp_IN_NO_ACTIVE_CHILD         ((uint8_T)0U)
#define Epp_IN_Park                    ((uint8_T)2U)
#define Epp_IN_Parking                 ((uint8_T)3U)
#define Epp_IN_Safe                    ((uint8_T)4U)
#define Epp_IN_Unknown                 ((uint8_T)5U)
#define Epp_IN_unPark                  ((uint8_T)6U)
#define Epp_IN_unParking               ((uint8_T)7U)

/* Initial conditions for atomic system: '<S1>/epp state' */
void EppStateFcn_Init(void)
{
  Epp_DWork.is_active_c1_Epp = 0U;
  Epp_DWork.is_c1_Epp = Epp_IN_NO_ACTIVE_CHILD;
  EPP_State = Initial;
}

/* Output and update for atomic system: '<S1>/epp state' */
void EppStateFcn(void)
{
  boolean_T guard = FALSE;
  int16_T tmp;

  /* Gateway: EPP State/epp state */
  /* During: EPP State/epp state */
  if (Epp_DWork.is_active_c1_Epp == 0U) {
    /* Entry: EPP State/epp state */
    Epp_DWork.is_active_c1_Epp = 1U;

    /* Entry Internal: EPP State/epp state */
    /* Transition: '<S3>:30' */
    EPP_State = Initial;
    Epp_DWork.is_c1_Epp = Epp_IN_Initial;
  } else {
    switch (Epp_DWork.is_c1_Epp) {
     case Epp_IN_Initial:
      /* During 'Initial': '<S3>:25' */
      if (SensorError == True) {
        /* Transition: '<S3>:101' */
        Epp_DWork.is_c1_Epp = Epp_IN_Safe;

        /* Entry 'Safe': '<S3>:8' */
        EPP_State = Safe;
      } else if (CAN_Error == True) {
        /* Transition: '<S3>:28' */
        Epp_DWork.is_c1_Epp = Epp_IN_Safe;

        /* Entry 'Safe': '<S3>:8' */
        EPP_State = Safe;
      } else {
        /* Transition: '<S3>:92' */
        if (Motor_Position == HIGH) {
          /* Transition: '<S3>:26' */
          Epp_DWork.is_c1_Epp = Epp_IN_Park;

          /* Entry 'Park': '<S3>:5' */
          EPP_State = Parked;
        } else if (Motor_Position == LEFT_OF_HIGH) {
          /* Transition: '<S3>:110' */
          Epp_DWork.is_c1_Epp = Epp_IN_Park;

          /* Entry 'Park': '<S3>:5' */
          EPP_State = Parked;
        } else if (Motor_Position == LEFT_STOP) {
          /* Transition: '<S3>:111' */
          Epp_DWork.is_c1_Epp = Epp_IN_Park;

          /* Entry 'Park': '<S3>:5' */
          EPP_State = Parked;
        } else {
          /* Transition: '<S3>:94' */
          if (Motor_Position == ZONE_2) {
            /* Transition: '<S3>:27' */
            Epp_DWork.is_c1_Epp = Epp_IN_unPark;

            /* Entry 'unPark': '<S3>:1' */
            EPP_State = unPark;
          } else if (Motor_Position == LOW) {
            /* Transition: '<S3>:112' */
            Epp_DWork.is_c1_Epp = Epp_IN_unPark;

            /* Entry 'unPark': '<S3>:1' */
            EPP_State = unPark;
          } else if (Motor_Position == RIGHT_STOP) {
            /* Transition: '<S3>:113' */
            Epp_DWork.is_c1_Epp = Epp_IN_unPark;

            /* Entry 'unPark': '<S3>:1' */
            EPP_State = unPark;
          } else {
            /* Transition: '<S3>:117' */
            Epp_DWork.is_c1_Epp = Epp_IN_Unknown;

            /* Entry 'Unknown': '<S3>:116' */
            EPP_State = Unknown;
            EppAction(EPP_State);
          }
        }
      }
      break;

     case Epp_IN_Park:
      /* During 'Park': '<S3>:5' */
      if ((SensorError == True) || (CAN_Error == True)) {
        /* Transition: '<S3>:102' */
        /* Transition: '<S3>:10' */
        /* Transition: '<S3>:137' */
        Epp_DWork.is_c1_Epp = Epp_IN_Safe;

        /* Entry 'Safe': '<S3>:8' */
        EPP_State = Safe;
      } else {
        /* Transition: '<S3>:124' */
        if (GearStatus == Unpark) {
          /* Transition: '<S3>:145' */
          EPP_State = unParking;
          Epp_DWork.is_c1_Epp = Epp_IN_unParking;

          /* Entry 'unParking': '<S3>:7' */
          EppParktoUnpark();
        } else {
          EppAction(EPP_State);
        }
      }
      break;

     case Epp_IN_Parking:
      /* During 'Parking': '<S3>:6' */
      if (ActionFinished == True) {
        /* Transition: '<S3>:15' */
        Epp_DWork.is_c1_Epp = Epp_IN_Park;

        /* Entry 'Park': '<S3>:5' */
        EPP_State = Parked;
      } else {
        EppAction(EPP_State);
      }
      break;

     case Epp_IN_Safe:
      /* During 'Safe': '<S3>:8' */
      if (CAN_Error == False) {
        /* Transition: '<S3>:153' */
        Epp_DWork.is_c1_Epp = Epp_IN_Initial;
      } else {
        EppAction(EPP_State);
      }
      break;

     case Epp_IN_Unknown:
      /* During 'Unknown': '<S3>:116' */
      /* Transition: '<S3>:131' */
      if ((CAN_Error == True) || (SensorError == True)) {
        /* Transition: '<S3>:127' */
        /* Transition: '<S3>:128' */
        /* Transition: '<S3>:107' */
        Epp_DWork.is_c1_Epp = Epp_IN_Safe;

        /* Entry 'Safe': '<S3>:8' */
        EPP_State = Safe;
      } else {
        /* Transition: '<S3>:125' */
        if (GearStatus == Unpark) {
          /* Transition: '<S3>:145' */
          EPP_State = unParking;
          Epp_DWork.is_c1_Epp = Epp_IN_unParking;

          /* Entry 'unParking': '<S3>:7' */
          EppParktoUnpark();
        } else {
          /* Transition: '<S3>:121' */
          if (GearStatus == Park) {
            /* Transition: '<S3>:69' */
            if (Motor_Speed < 0) {
              tmp = -Motor_Speed;
            } else {
              tmp = Motor_Speed;
            }

            if ((MotorSig_Lost != True) && ((uint16_T)tmp < Kf_MotorStall_Rpm))
            {
              /* Transition: '<S3>:201' */
              /* Transition: '<S3>:75' */
              Epp_DWork.is_c1_Epp = Epp_IN_Parking;

              /* Entry 'Parking': '<S3>:6' */
              EPP_State = Parking;
              EppUnParktoPark();
            } else {
              if ((MotorSig_Lost == True) && (VehicleSpeed < Kf_VehiclStall_KPH))
              {
                /* Transition: '<S3>:142' */
                /* Transition: '<S3>:143' */
                Epp_DWork.is_c1_Epp = Epp_IN_Parking;

                /* Entry 'Parking': '<S3>:6' */
                EPP_State = Parking;
                EppUnParktoPark();
              }
            }
          }
        }
      }
      break;

     case Epp_IN_unPark:
      /* During 'unPark': '<S3>:1' */
      if ((SensorError == True) || (CAN_Error == True)) {
        /* Transition: '<S3>:103' */
        /* Transition: '<S3>:11' */
        /* Transition: '<S3>:135' */
        Epp_DWork.is_c1_Epp = Epp_IN_Safe;

        /* Entry 'Safe': '<S3>:8' */
        EPP_State = Safe;
      } else {
        /* Transition: '<S3>:122' */
        if (GearStatus == Park) {
          /* Transition: '<S3>:69' */
          if (Motor_Speed < 0) {
            tmp = -Motor_Speed;
          } else {
            tmp = Motor_Speed;
          }

          if ((MotorSig_Lost != True) && ((uint16_T)tmp < Kf_MotorStall_Rpm)) {
            /* Transition: '<S3>:201' */
            /* Transition: '<S3>:75' */
            Epp_DWork.is_c1_Epp = Epp_IN_Parking;

            /* Entry 'Parking': '<S3>:6' */
            EPP_State = Parking;
            EppUnParktoPark();
          } else if ((MotorSig_Lost == True) && (VehicleSpeed <
                      Kf_VehiclStall_KPH)) {
            /* Transition: '<S3>:142' */
            /* Transition: '<S3>:143' */
            Epp_DWork.is_c1_Epp = Epp_IN_Parking;

            /* Entry 'Parking': '<S3>:6' */
            EPP_State = Parking;
            EppUnParktoPark();
          } else {
            guard = TRUE;
          }
        } else {
          guard = TRUE;
        }
      }
      break;

     default:
      /* During 'unParking': '<S3>:7' */
      if (ActionFinished == True) {
        /* Transition: '<S3>:17' */
        Epp_DWork.is_c1_Epp = Epp_IN_unPark;

        /* Entry 'unPark': '<S3>:1' */
        EPP_State = unPark;
      } else {
        EppAction(EPP_State);
      }
      break;
    }

    if (guard) {
      EppAction(EPP_State);
    }
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
