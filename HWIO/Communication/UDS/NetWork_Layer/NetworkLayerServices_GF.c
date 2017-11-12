/*
 * File: NetworkLayerServices_GF.c
 *
 * Code generated for Simulink model 'NetworkLayerServices_GF'.
 *
 * Model version                  : 1.137
 * Simulink Coder version         : 8.2 (R2012a) 29-Dec-2011
 * TLC version                    : 8.2 (Dec 29 2011)
 * C/C++ source code generated on : Sat Sep 05 18:37:42 2015
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->HC(S)12
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Safety precaution
 *    3. MISRA-C:2004 guidelines
 * Validation result: Not run
 */

#include "NetworkLayerServices_GF.h"
#include "NetworkLayerServices_GF_private.h"
#include "AppLayer_Uds.h"
#include "DSP2803x_function.h"

/* Named constants for Chart: '<Root>/Chart' */
#define Ne_IN_MultipleFrameTransmission ((uint8_T)2U)
#define Netw_IN_SingleFrameTransmission ((uint8_T)3U)
#define NetworkLaye_IN_ConsecutiveFrame ((uint8_T)1U)
#define NetworkLayerS_event_FC_Received (1L)
#define NetworkLayerSe_IN_MultipleFrame ((uint8_T)2U)
#define NetworkLayerSer_IN_Transmission ((uint8_T)2U)
#define NetworkLayerServ_IN_SingleFrame ((uint8_T)3U)
#define NetworkLayerServi_IN_FirstFrame ((uint8_T)2U)
#define NetworkLayerServic_event_CF_END (0L)
#define NetworkLayerServices_CALL_EVENT (-1L)
#define NetworkLayerServices_GF_IN_Idle ((uint8_T)1U)
#define NetworkLayerServices_GF_IN_Init ((uint8_T)1U)
#define NetworkLayerServices_GF_IN_Wait ((uint8_T)3U)
#define NetworkLayerServices_G_IN_Start ((uint8_T)4U)
#define NetworkLayerServices__IN_Switch ((uint8_T)4U)
#define NetworkLayer_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define NetworkLayer_IN_WaitFlowControl ((uint8_T)3U)
#if 0
const USDATAREQUEST NetworkLayerServices_GF_rtZUSDATAREQUEST = {
  diagnostics,                         /* Mtype */
  0U,                                  /* N_SA */
  0U,                                  /* N_TA */
  physical,                            /* N_TAtype */
  0U,                                  /* N_AE */

  {
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
  ,                                    /* MessageData */
  0U                                   /* Length */
} ;                                    /* USDATAREQUEST ground */

const USDATAFFINDICATION NetworkLayerServices_GF_rtZUSDATAFFINDICATION = {
  diagnostics,                         /* Mtype */
  0U,                                  /* N_SA */
  0U,                                  /* N_TA */
  physical,                            /* N_TAtype */
  0U,                                  /* N_AE */
  0U                                   /* Length */
} ;                                    /* USDATAFFINDICATION ground */

const USDATAINDICATION NetworkLayerServices_GF_rtZUSDATAINDICATION = {
  diagnostics,                         /* Mtype */
  0U,                                  /* N_SA */
  0U,                                  /* N_TA */
  physical,                            /* N_TAtype */
  0U,                                  /* N_AE */

  {
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
  ,                                    /* MessageData */
  0U,                                  /* Length */
  N_OK                                 /* N_Result */
} ;                                    /* USDATAINDICATION ground */

const USDATACONFIRM NetworkLayerServices_GF_rtZUSDATACONFIRM = {
  diagnostics,                         /* Mtype */
  0U,                                  /* N_SA */
  0U,                                  /* N_TA */
  physical,                            /* N_TAtype */
  0U,                                  /* N_AE */
  N_OK                                 /* N_Result */
} ;                                    /* USDATACONFIRM ground */
#endif
/* Exported block signals */
USDATAREQUEST UdsRequest;              /* '<Root>/In1' */
USDATAINDICATION UdsIndication;        /* '<Root>/Chart' (Output 2)  */
USDATACONFIRM UdsConfirm;              /* '<Root>/Chart' (Output 3)  */

/* Block signals and states (auto storage) */
D_Work_NetworkLayerServices_GF NetworkLayerServices_GF_DWork;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_NetworkLayerSer NetworkLayerServices_GF_Y;

/* Forward declaration for local functions */
static uint8_T NetworkLayerServices_RequestCmd(void);
static uint8_T NetworkLayerService_CheckResult(void);
static void NetworkLayerServ_CopyToTxbuffer(uint8_T length);
static void NetworkLayerServ_GetFCParameter(void);
static void NetworkLayerServices_GF_Request(void);
static uint8_T NetworkLayerServi_FrameReceived(void);
static void NetworkLayerService_CheckTatype(void);
static void NetworkLayerServ_CopyToRxbuffer(uint8_T length);
static void NetworkLayerServices_GF_Switch(void);
static void NetworkLayerServices_Indication(void);

/* Function for Chart: '<Root>/Chart' */
static uint8_T NetworkLayerServices_RequestCmd(void)
{
  uint8_T y;

  /* Graphical Function 'RequestCmd': '<S1>:466' */
  /* Transition: '<S1>:472' */
  /* comment */
  if (RequestCmd_u8_Sig == 1) {
    /* Transition: '<S1>:473' */
    /* Transition: '<S1>:475' */
    y = 1U;
    RequestCmd_u8_Sig = 0;

    /* Transition: '<S1>:476' */
  } else {
    /* Transition: '<S1>:474' */
    y = 0U;
  }

  /* Transition: '<S1>:477' */
  return y;
}

/* Function for Chart: '<Root>/Chart' */
static uint8_T NetworkLayerService_CheckResult(void)
{
  uint8_T y;

  /* Graphical Function 'CheckResult': '<S1>:530' */
  /* Transition: '<S1>:555' */
  /* comment */
  if (NetworkLayerServices_GF_DWork.Result_k != N_OK) {
    /* Transition: '<S1>:554' */
    /* Transition: '<S1>:553' */
    UdsConfirm.N_Result = NetworkLayerServices_GF_DWork.Result_k;
    y = 1U;

    /* Transition: '<S1>:552' */
  } else {
    /* Transition: '<S1>:551' */
    y = 0U;
  }

  /* Transition: '<S1>:550' */
  return y;
}

/* Function for Chart: '<Root>/Chart' */
static void NetworkLayerServ_CopyToTxbuffer(uint8_T length)
{
  //uint8_T i;
  uint8_T Dest_ptr, Source_ptr, Source_mod;

  /* Graphical Function 'CopyToTxbuffer': '<S1>:58' */
  /* Transition: '<S1>:69' */

  Dest_ptr = NetworkLayerServices_GF_DWork.tx_buffer_ptr;

  Source_ptr = NetworkLayerServices_GF_DWork.MessageDataPtr/2;
  Source_mod = NetworkLayerServices_GF_DWork.MessageDataPtr - Source_ptr*2;
  
  CopyMemory_With_DestByte(&NetworkLayerServices_GF_DWork.tx_buffer[Dest_ptr],
  						   &NetworkLayerServices_GF_DWork.BusConversion_InsertedFor_Chart.MessageData[Source_ptr],
  						   Source_mod,
  						   length);

  NetworkLayerServices_GF_DWork.tx_buffer_ptr = (uint8_T)
      (NetworkLayerServices_GF_DWork.tx_buffer_ptr + length);
    NetworkLayerServices_GF_DWork.MessageDataPtr = (uint8_T)
      (NetworkLayerServices_GF_DWork.MessageDataPtr + length); 

  /* Transition: '<S1>:64' */
}

/* Function for Chart: '<Root>/Chart' */
static void NetworkLayerServ_GetFCParameter(void)
{
  /* Graphical Function 'GetFCParameter': '<S1>:279' */
  /* Transition: '<S1>:281' */
  //NetworkLayerServices_GF_DWork.FS = (uint8_T)(((int16_T)RXbuffer_u8a8_Sig[0]) &
  //  0x0F);
  NetworkLayerServices_GF_DWork.FS = (uint8_T)(__byte(&RXbuffer_u8a8_Sig[0], LSB)&0x0F);
  //NetworkLayerServices_GF_DWork.BS = (uint8_T)RXbuffer_u8a8_Sig[1];
  NetworkLayerServices_GF_DWork.BS = __byte(&RXbuffer_u8a8_Sig[0], MSB);
  //NetworkLayerServices_GF_DWork.STmin = (uint8_T)RXbuffer_u8a8_Sig[2];
  NetworkLayerServices_GF_DWork.STmin = __byte(&RXbuffer_u8a8_Sig[1], LSB);
}

/* Function for Chart: '<Root>/Chart' */
static void NetworkLayerServices_GF_Request(void)
{
  uint16_T FF_N_PCI;
  uint16_T MaxBytes;
  boolean_T guard;
  boolean_T guard_0;
  boolean_T guard_1;
  boolean_T guard_2;
  boolean_T guard_3;
  boolean_T guard_4;
  /* During 'Request': '<S1>:212' */
  guard = FALSE;
  guard_0 = FALSE;
  guard_1 = FALSE;
  guard_2 = FALSE;
  guard_3 = FALSE;
  guard_4 = FALSE;
  switch (NetworkLayerServices_GF_DWork.is_Request) {
   case NetworkLayerServices_GF_IN_Idle:
    /* During 'Idle': '<S1>:74' */
    if (NetworkLayerServices_RequestCmd() != 0) {
      /* Transition: '<S1>:77' */
      NetworkLayerServices_GF_DWork.is_Request = NetworkLayerServices_G_IN_Start;

      /* Entry 'Start': '<S1>:49' */
      UdsConfirm.N_Result = NetworkLayerServices_GF_DWork.Result_k;
      NetworkLayerServices_GF_DWork.MessageDataPtr = 0U;
      NetworkLayerServices_GF_DWork.tx_buffer_ptr = 0U;
      NetworkLayerServices_GF_DWork.TransmissionType = 0U;
      UDS_Timeout_u8_Sig = 0;

      /* Entry Internal 'Start': '<S1>:49' */
      /* Transition: '<S1>:86' */
      /* comment */
      if ((NetworkLayerServices_GF_DWork.BusConversion_InsertedFor_Chart.Length >
           0U) &&
          (NetworkLayerServices_GF_DWork.BusConversion_InsertedFor_Chart.Length <=
           7U)) {
        /* Transition: '<S1>:88' */
        /* Transition: '<S1>:89' */
        NetworkLayerServices_GF_DWork.TransmissionType = 1U;

        /* Transition: '<S1>:92' */
        /* Transition: '<S1>:93' */
      } else {
        /* Transition: '<S1>:87' */
        if (NetworkLayerServices_GF_DWork.BusConversion_InsertedFor_Chart.Length
            <= 4095U) {
          /* Transition: '<S1>:90' */
          /* Transition: '<S1>:91' */
          NetworkLayerServices_GF_DWork.TransmissionType = 2U;

          /* Transition: '<S1>:93' */
        } else {
          /* Transition: '<S1>:94' */
          NetworkLayerServices_GF_DWork.Result_k = N_ERROR;
        }
      }

      /* Transition: '<S1>:95' */
    }
    break;

   case Ne_IN_MultipleFrameTransmission:
    /* During 'MultipleFrameTransmission': '<S1>:99' */
    /* Transition: '<S1>:564' */
    if (NetworkLayerService_CheckResult() != 0) {
      /* Transition: '<S1>:528' */
      /* Transition: '<S1>:559' */
      ConfirmCmd_u8_Sig = 1;

      /* Exit Internal 'MultipleFrameTransmission': '<S1>:99' */
      /* Exit Internal 'ConsecutiveFrame': '<S1>:123' */
      NetworkLayerServices_GF_DWork.is_ConsecutiveFrame =
        NetworkLayer_IN_NO_ACTIVE_CHILD;
      NetworkLayerServices_GF_DWork.is_MultipleFrameTransmission =
        NetworkLayer_IN_NO_ACTIVE_CHILD;
      NetworkLayerServices_GF_DWork.is_Request = NetworkLayerServices_GF_IN_Idle;

      /* Entry 'Idle': '<S1>:74' */
      NetworkLayerServices_GF_DWork.Result_k = N_OK;
    } else {
      switch (NetworkLayerServices_GF_DWork.is_MultipleFrameTransmission) {
       case NetworkLaye_IN_ConsecutiveFrame:
        /* During 'ConsecutiveFrame': '<S1>:123' */
        switch (NetworkLayerServices_GF_DWork.is_ConsecutiveFrame) {
         case NetworkLayerServices_GF_IN_Init:
          /* During 'Init': '<S1>:161' */
          if (NetworkLayerServices_GF_DWork.Result_k == N_OK) {
            /* Transition: '<S1>:202' */
            NetworkLayerServices_GF_DWork.is_ConsecutiveFrame =
              NetworkLayerServices_GF_IN_Wait;
            NetworkLayerServices_GF_DWork.temporalCounter_i1 = 0U;
          }
          break;

         case NetworkLayerSer_IN_Transmission:
          /* During 'Transmission': '<S1>:126' */
          /* Transition: '<S1>:173' */
          NetworkLayerServices_GF_DWork.is_ConsecutiveFrame =
            NetworkLayerServices_GF_IN_Wait;
          NetworkLayerServices_GF_DWork.temporalCounter_i1 = 0U;
          break;

         case NetworkLayerServices_GF_IN_Wait:
          /* During 'Wait': '<S1>:201' */
          if (NetworkLayerServices_GF_DWork.FF_DL_o == 0U) {
            /* Transition: '<S1>:206' */
            guard = TRUE;
          } else if (NetworkLayerServices_GF_DWork.CF_DL == 0U) {
            /* Transition: '<S1>:209' */
            NetworkLayerServices_GF_DWork.is_ConsecutiveFrame =
              NetworkLayer_IN_NO_ACTIVE_CHILD;
            NetworkLayerServices_GF_DWork.is_MultipleFrameTransmission =
              NetworkLayer_IN_WaitFlowControl;
            NetworkLayerServices_GF_DWork.temporalCounter_i1 = 0U;
          } else if ((NetworkLayerServices_GF_DWork.sfEvent ==
                      NetworkLayerServices_CALL_EVENT) &&
                     (NetworkLayerServices_GF_DWork.temporalCounter_i1 >=
                      NetworkLayerServices_GF_DWork.STmin)) {
            /* Transition: '<S1>:174' */
            NetworkLayerServices_GF_DWork.is_ConsecutiveFrame =
              NetworkLayerSer_IN_Transmission;

            /* Entry 'Transmission': '<S1>:126' */
            NetworkLayerServices_GF_DWork.tx_buffer_ptr = 0U;

            /* Entry Internal 'Transmission': '<S1>:126' */
            /* Transition: '<S1>:145' */
            /* comment */
            if (NetworkLayerServices_GF_DWork.SN < 15) {
              /* Transition: '<S1>:144' */
              /* Transition: '<S1>:143' */
              NetworkLayerServices_GF_DWork.SN = (uint8_T)
                (NetworkLayerServices_GF_DWork.SN + 1);

              /* Transition: '<S1>:142' */
            } else {
              /* Transition: '<S1>:141' */
              NetworkLayerServices_GF_DWork.SN = 0U;
            }

            /* Transition: '<S1>:130' */
            /* Transition: '<S1>:131' */
            NetworkLayerServices_GF_DWork.tx_buffer[NetworkLayerServices_GF_DWork.tx_buffer_ptr]
              = (uint8_T)(((uint8_T)(ConsecutiveFrame << 4)) +
                          NetworkLayerServices_GF_DWork.SN);
            NetworkLayerServices_GF_DWork.tx_buffer_ptr = (uint8_T)
              (NetworkLayerServices_GF_DWork.tx_buffer_ptr + 1);

            /* Transition: '<S1>:159' */
            /* comment */
            if (NetworkLayerServices_GF_DWork.CF_DL < 7U) {
              /* Transition: '<S1>:158' */
              /* Transition: '<S1>:157' */
              NetworkLayerServ_CopyToTxbuffer((uint8_T)
                NetworkLayerServices_GF_DWork.CF_DL);
              NetworkLayerServices_GF_DWork.FF_DL_o =
                NetworkLayerServices_GF_DWork.FF_DL_o -
                NetworkLayerServices_GF_DWork.CF_DL;
              NetworkLayerServices_GF_DWork.CF_DL = 0U;

              /* Transition: '<S1>:156' */
            } else {
              /* Transition: '<S1>:155' */
              NetworkLayerServ_CopyToTxbuffer(7U);
              NetworkLayerServices_GF_DWork.FF_DL_o =
                NetworkLayerServices_GF_DWork.FF_DL_o - ((uint16_T)7);
              NetworkLayerServices_GF_DWork.CF_DL =
                NetworkLayerServices_GF_DWork.CF_DL - ((uint16_T)7);
            }

            /* Transition: '<S1>:132' */
            UdsSend(NetworkLayerServices_GF_DWork.tx_buffer_ptr,
                    NetworkLayerServices_GF_DWork.tx_buffer);
          } else {
            if ((NetworkLayerServices_GF_DWork.sfEvent ==
                 NetworkLayerServices_CALL_EVENT) &&
                (NetworkLayerServices_GF_DWork.temporalCounter_i1 >=
                 CrTime_Limited_u16_Par)) {
              /* Transition: '<S1>:586' */
              NetworkLayerServices_GF_DWork.Result_k = N_TIMEOUT_Cr;
              UDS_Timeout_u8_Sig = 2;
              if (NetworkLayerService_CheckResult() != 0) {
                /* Transition: '<S1>:528' */
                guard = TRUE;
              }
            }
          }
          break;

         default:
          NetworkLayerServices_GF_DWork.is_ConsecutiveFrame =
            NetworkLayer_IN_NO_ACTIVE_CHILD;
          break;
        }
        break;

       case NetworkLayerServi_IN_FirstFrame:
        /* During 'FirstFrame': '<S1>:106' */
        /* Transition: '<S1>:118' */
        NetworkLayerServices_GF_DWork.is_MultipleFrameTransmission =
          NetworkLayer_IN_WaitFlowControl;
        NetworkLayerServices_GF_DWork.temporalCounter_i1 = 0U;
        break;

       case NetworkLayer_IN_WaitFlowControl:
        /* During 'WaitFlowControl': '<S1>:117' */
        if (NetworkLayerServices_GF_DWork.sfEvent ==
            NetworkLayerS_event_FC_Received) {
          /* Transition: '<S1>:207' */
          NetworkLayerServ_GetFCParameter();
          FC_RecStatus_u8_Sig = 1;
          if (NetworkLayerServices_GF_DWork.FS >= 2) {
            /* Transition: '<S1>:681' */
            /* Transition: '<S1>:682' */
            NetworkLayerServices_GF_DWork.Result_k = N_BUFFER_OVFLW;
            FrameErr_u8_Sig = 3;
            if (NetworkLayerService_CheckResult() != 0) {
              /* Transition: '<S1>:528' */
              guard_0 = TRUE;
            } else {
              guard_4 = TRUE;
            }
          } else {
            guard_4 = TRUE;
          }
        } else {
          guard_2 = TRUE;
        }
        break;

       default:
        NetworkLayerServices_GF_DWork.is_MultipleFrameTransmission =
          NetworkLayer_IN_NO_ACTIVE_CHILD;
        break;
      }
    }
    break;

   case Netw_IN_SingleFrameTransmission:
    /* During 'SingleFrameTransmission': '<S1>:30' */
    /* Transition: '<S1>:75' */
    /* Transition: '<S1>:559' */
    ConfirmCmd_u8_Sig = 1;
    NetworkLayerServices_GF_DWork.is_Request = NetworkLayerServices_GF_IN_Idle;

    /* Entry 'Idle': '<S1>:74' */
    NetworkLayerServices_GF_DWork.Result_k = N_OK;
    break;

   case NetworkLayerServices_G_IN_Start:
    /* During 'Start': '<S1>:49' */
    switch (NetworkLayerServices_GF_DWork.TransmissionType) {
     case 1:
      /* Transition: '<S1>:53' */
      NetworkLayerServices_GF_DWork.is_Request = Netw_IN_SingleFrameTransmission;

      /* Entry 'SingleFrameTransmission': '<S1>:30' */
      /* Entry Internal 'SingleFrameTransmission': '<S1>:30' */
      /* Transition: '<S1>:32' */
      NetworkLayerServices_GF_DWork.tx_buffer[NetworkLayerServices_GF_DWork.tx_buffer_ptr]
        = (uint8_T)(((uint8_T)(SingleFrame << 4)) + ((uint8_T)
        NetworkLayerServices_GF_DWork.BusConversion_InsertedFor_Chart.Length));

      NetworkLayerServices_GF_DWork.tx_buffer_ptr = (uint8_T)
        (NetworkLayerServices_GF_DWork.tx_buffer_ptr + 1);

      /* Transition: '<S1>:42' */
      NetworkLayerServ_CopyToTxbuffer((uint8_T)
        NetworkLayerServices_GF_DWork.BusConversion_InsertedFor_Chart.Length);

      /* Transition: '<S1>:46' */
      UdsSend(NetworkLayerServices_GF_DWork.tx_buffer_ptr,
              NetworkLayerServices_GF_DWork.tx_buffer);
      break;

     case 2:
      /* Transition: '<S1>:100' */
      NetworkLayerServices_GF_DWork.is_Request = Ne_IN_MultipleFrameTransmission;

      /* Entry 'MultipleFrameTransmission': '<S1>:99' */
      NetworkLayerServices_GF_DWork.CF_DL = 0U;
      NetworkLayerServices_GF_DWork.SN = 0U;

      /* Entry Internal 'MultipleFrameTransmission': '<S1>:99' */
      /* Transition: '<S1>:119' */
      if (NetworkLayerServices_GF_DWork.is_MultipleFrameTransmission ==
          NetworkLayerServi_IN_FirstFrame) {
      } else {
        NetworkLayerServices_GF_DWork.is_MultipleFrameTransmission =
          NetworkLayerServi_IN_FirstFrame;

        /* Entry 'FirstFrame': '<S1>:106' */
        FC_RecStatus_u8_Sig = 0;
      }

      /* Entry Internal 'FirstFrame': '<S1>:106' */
      /* Transition: '<S1>:110' */
      NetworkLayerServices_GF_DWork.FF_DL_o =
        NetworkLayerServices_GF_DWork.BusConversion_InsertedFor_Chart.Length;
      FF_N_PCI = ((uint16_T)(FirstFrame << 12)) +
        NetworkLayerServices_GF_DWork.FF_DL_o;

      /* Transition: '<S1>:111' */
      NetworkLayerServices_GF_DWork.tx_buffer[NetworkLayerServices_GF_DWork.tx_buffer_ptr]
        = (uint8_T)(FF_N_PCI >> 8);
      NetworkLayerServices_GF_DWork.tx_buffer_ptr = (uint8_T)
        (NetworkLayerServices_GF_DWork.tx_buffer_ptr + 1);
      NetworkLayerServices_GF_DWork.tx_buffer[NetworkLayerServices_GF_DWork.tx_buffer_ptr]
        = (uint8_T)FF_N_PCI;
      NetworkLayerServices_GF_DWork.tx_buffer_ptr = (uint8_T)
        (NetworkLayerServices_GF_DWork.tx_buffer_ptr + 1);
      NetworkLayerServ_CopyToTxbuffer(6U);
      NetworkLayerServices_GF_DWork.FF_DL_o =
        NetworkLayerServices_GF_DWork.FF_DL_o - ((uint16_T)6);

      /* Transition: '<S1>:112' */
      UdsSend(NetworkLayerServices_GF_DWork.tx_buffer_ptr,
              NetworkLayerServices_GF_DWork.tx_buffer);
      break;

     default:
      /* Transition: '<S1>:569' */
      if (NetworkLayerService_CheckResult() != 0) {
        /* Transition: '<S1>:528' */
        /* Transition: '<S1>:559' */
        ConfirmCmd_u8_Sig = 1;
        NetworkLayerServices_GF_DWork.is_Request =
          NetworkLayerServices_GF_IN_Idle;

        /* Entry 'Idle': '<S1>:74' */
        NetworkLayerServices_GF_DWork.Result_k = N_OK;
      }
      break;
    }
    break;

   default:
    NetworkLayerServices_GF_DWork.is_Request = NetworkLayer_IN_NO_ACTIVE_CHILD;
    break;
  }

  if (((int16_T)guard_4) == ((int16_T)TRUE)) {
    if (NetworkLayerServices_GF_DWork.FS == 0) {
      /* Transition: '<S1>:674' */
      if ((CANLength_u8_Sig >= 3) && (RecID_u8_Sig == PHYSICAL_ID)) {
        /* Transition: '<S1>:717' */
        NetworkLayerServices_GF_DWork.is_MultipleFrameTransmission =
          NetworkLaye_IN_ConsecutiveFrame;

        /* Entry 'ConsecutiveFrame': '<S1>:123' */
        /* Entry Internal 'ConsecutiveFrame': '<S1>:123' */
        /* Transition: '<S1>:147' */
        if (NetworkLayerServices_GF_DWork.is_ConsecutiveFrame ==
            NetworkLayerServices_GF_IN_Init) {
        } else {
          NetworkLayerServices_GF_DWork.is_ConsecutiveFrame =
            NetworkLayerServices_GF_IN_Init;

          /* Entry 'Init': '<S1>:161' */
          NetworkLayerServices_GF_DWork.CF_DL = 0U;
        }

        /* Entry Internal 'Init': '<S1>:161' */
        /* Transition: '<S1>:186' */
        /* comment */
        if (NetworkLayerServices_GF_DWork.STmin == 0) {
          /* Transition: '<S1>:188' */
          /* Transition: '<S1>:193' */
          NetworkLayerServices_GF_DWork.STmin = 0U;

          /* Transition: '<S1>:192' */
          /* Transition: '<S1>:191' */
          /* Transition: '<S1>:198' */
        } else {
          /* Transition: '<S1>:187' */
          if (NetworkLayerServices_GF_DWork.STmin <= 0x7F) {
            /* Transition: '<S1>:195' */
            /* Transition: '<S1>:194' */
            NetworkLayerServices_GF_DWork.STmin = (uint8_T)
              ((NetworkLayerServices_GF_DWork.STmin / UDStick_u8_Par) *
               STminCoef_u8_Par);
            if (NetworkLayerServices_GF_DWork.STmin >= 1) {
              /* Transition: '<S1>:704' */
              /* Transition: '<S1>:705' */
              NetworkLayerServices_GF_DWork.STmin = (uint8_T)
                (NetworkLayerServices_GF_DWork.STmin - 1);
            } else {
              /* Transition: '<S1>:701' */
              NetworkLayerServices_GF_DWork.STmin = 0U;
            }

            /* Transition: '<S1>:191' */
            /* Transition: '<S1>:198' */
          } else {
            /* Transition: '<S1>:190' */
            if ((NetworkLayerServices_GF_DWork.STmin >= 0xF1) &&
                (NetworkLayerServices_GF_DWork.STmin <= 0xF9)) {
              /* Transition: '<S1>:196' */
              /* Transition: '<S1>:197' */
              NetworkLayerServices_GF_DWork.STmin = 0U;

              /* Transition: '<S1>:198' */
            } else {
              /* Transition: '<S1>:199' */
              NetworkLayerServices_GF_DWork.Result_k = N_ERROR;
            }
          }
        }

        /* Transition: '<S1>:694' */
        if (NetworkLayerServices_GF_DWork.BS == 0) {
          /* Transition: '<S1>:698' */
          /* Transition: '<S1>:696' */
          NetworkLayerServices_GF_DWork.CF_DL =
            NetworkLayerServices_GF_DWork.FF_DL_o;
        } else {
          /* Transition: '<S1>:172' */
          MaxBytes = (uint16_T)(7 * NetworkLayerServices_GF_DWork.BS);
          if (NetworkLayerServices_GF_DWork.FF_DL_o > MaxBytes) {
            /* Transition: '<S1>:171' */
            /* Transition: '<S1>:170' */
            NetworkLayerServices_GF_DWork.CF_DL = MaxBytes;

            /* Transition: '<S1>:169' */
          } else {
            /* Transition: '<S1>:168' */
            NetworkLayerServices_GF_DWork.CF_DL =
              NetworkLayerServices_GF_DWork.FF_DL_o;
          }
        }

        /* Transition: '<S1>:167' */
      } else {
        /* Transition: '<S1>:719' */
        /* Transition: '<S1>:682' */
        NetworkLayerServices_GF_DWork.Result_k = N_BUFFER_OVFLW;
        FrameErr_u8_Sig = 3;
        if (NetworkLayerService_CheckResult() != 0) {
          /* Transition: '<S1>:528' */
          guard_0 = TRUE;
        } else {
          guard_3 = TRUE;
        }
      }
    } else {
      guard_3 = TRUE;
    }
  }

  if (((int16_T)guard_3) == ((int16_T)TRUE)) {
    if (NetworkLayerServices_GF_DWork.FS == 1) {
      /* Constant: '<Root>/BsTime' */
      /* Transition: '<S1>:679' */
      if ((NetworkLayerServices_GF_DWork.sfEvent ==
           NetworkLayerServices_CALL_EVENT) &&
          (NetworkLayerServices_GF_DWork.temporalCounter_i1 >=
           BsTime_Limited_u16_Par)) {
        /* Transition: '<S1>:714' */
        NetworkLayerServices_GF_DWork.Result_k = N_TIMEOUT_A;
        UDS_Timeout_u8_Sig = 1;
        if (NetworkLayerService_CheckResult() != 0) {
          /* Transition: '<S1>:528' */
          guard_0 = TRUE;
        } else {
          guard_1 = TRUE;
        }
      } else {
        guard_1 = TRUE;
      }

      /* End of Constant: '<Root>/BsTime' */
    } else {
      guard_2 = TRUE;
    }
  }

  if (((int16_T)guard_2) == ((int16_T)TRUE)) {
    /* Constant: '<Root>/AsTime' */
    if ((NetworkLayerServices_GF_DWork.sfEvent ==
         NetworkLayerServices_CALL_EVENT) &&
        (NetworkLayerServices_GF_DWork.temporalCounter_i1 >=
         AsTime_Limited_u16_Par)) {
      /* Transition: '<S1>:575' */
      NetworkLayerServices_GF_DWork.Result_k = N_TIMEOUT_A;
      UDS_Timeout_u8_Sig = 1;
      if (NetworkLayerService_CheckResult() != 0) {
        /* Transition: '<S1>:528' */
        guard_0 = TRUE;
      }
    }

    /* End of Constant: '<Root>/AsTime' */
  }

  if (((int16_T)guard_1) == ((int16_T)TRUE)) {
    /* Transition: '<S1>:715' */
    NetworkLayerServices_GF_DWork.is_MultipleFrameTransmission =
      NetworkLayer_IN_WaitFlowControl;
    NetworkLayerServices_GF_DWork.temporalCounter_i1 = 0U;
  }

  if (((int16_T)guard_0) == ((int16_T)TRUE)) {
    /* Transition: '<S1>:559' */
    ConfirmCmd_u8_Sig = 1;
    NetworkLayerServices_GF_DWork.is_MultipleFrameTransmission =
      NetworkLayer_IN_NO_ACTIVE_CHILD;
    NetworkLayerServices_GF_DWork.is_Request = NetworkLayerServices_GF_IN_Idle;

    /* Entry 'Idle': '<S1>:74' */
    NetworkLayerServices_GF_DWork.Result_k = N_OK;
  }

  if (((int16_T)guard) == ((int16_T)TRUE)) {
    /* Transition: '<S1>:559' */
    ConfirmCmd_u8_Sig = 1;
    NetworkLayerServices_GF_DWork.is_ConsecutiveFrame =
      NetworkLayer_IN_NO_ACTIVE_CHILD;
    NetworkLayerServices_GF_DWork.is_MultipleFrameTransmission =
      NetworkLayer_IN_NO_ACTIVE_CHILD;
    NetworkLayerServices_GF_DWork.is_Request = NetworkLayerServices_GF_IN_Idle;

    /* Entry 'Idle': '<S1>:74' */
    NetworkLayerServices_GF_DWork.Result_k = N_OK;
  }
}

/* Function for Chart: '<Root>/Chart' */
static uint8_T NetworkLayerServi_FrameReceived(void)
{
  uint8_T y;

  /* Graphical Function 'FrameReceived': '<S1>:250' */
  /* Transition: '<S1>:263' */
  /* comment */
  if (RecFlag_u8_Sig == 1) {
    /* Transition: '<S1>:262' */
    /* Transition: '<S1>:261' */
    y = 1U;
    RecFlag_u8_Sig = 0;

    /* Transition: '<S1>:260' */
  } else {
    /* Transition: '<S1>:259' */
    y = 0U;
  }

  /* Transition: '<S1>:258' */
  return y;
}

/* Function for Chart: '<Root>/Chart' */
static void NetworkLayerService_CheckTatype(void)
{
  /* Graphical Function 'CheckTatype': '<S1>:481' */
  /* Transition: '<S1>:501' */
  /* comment */
  if (RecID_u8_Sig == PHYSICAL_ID) {
    /* Transition: '<S1>:503' */
    /* Transition: '<S1>:504' */
    UdsIndication.N_TAtype = physical;

    /* Transition: '<S1>:507' */
    /* Transition: '<S1>:508' */
  } else {
    /* Transition: '<S1>:502' */
    if (RecID_u8_Sig == FUNCTIONAL_ID) {
      /* Transition: '<S1>:505' */
      /* Transition: '<S1>:506' */
      UdsIndication.N_TAtype = functional;

      /* Transition: '<S1>:508' */
    } else {
      /* Transition: '<S1>:509' */
      NetworkLayerServices_GF_DWork.Result = N_ERROR;
    }
  }

  /* Transition: '<S1>:510' */
}


/* Function for Chart: '<Root>/Chart' */
static void NetworkLayerServ_CopyToRxbuffer(uint8_T length)
{
  //uint8_T i;
  uint8_T Dest_ptr,Dest_mod, Source_ptr, Source_mod;

  /* Graphical Function 'CopyToRxbuffer': '<S1>:318' */
  /* Transition: '<S1>:323' */

  Dest_ptr = NetworkLayerServices_GF_DWork.RxMessageDataPtr/2;
  Dest_mod = NetworkLayerServices_GF_DWork.RxMessageDataPtr - Dest_ptr*2;
  Source_ptr = NetworkLayerServices_GF_DWork.rx_buffer_ptr/2;
  Source_mod = NetworkLayerServices_GF_DWork.rx_buffer_ptr - Source_ptr*2;
  
  CopyMemory_WithNone_Byte(&UdsIndication.MessageData[Dest_ptr],
  						   &RXbuffer_u8a8_Sig[Source_ptr],
  						   Dest_mod,
  						   Source_mod,
  						   length);

  NetworkLayerServices_GF_DWork.rx_buffer_ptr = (uint8_T)
      (NetworkLayerServices_GF_DWork.rx_buffer_ptr + length);
    NetworkLayerServices_GF_DWork.RxMessageDataPtr = (uint8_T)
      (NetworkLayerServices_GF_DWork.RxMessageDataPtr + length); 

  /* Transition: '<S1>:326' */
}

/* Function for Chart: '<Root>/Chart' */
static void NetworkLayerServices_GF_Switch(void)
{
  int32_T b_previousEvent;
  uint8_T FS;
  boolean_T guard;
  boolean_T guard_0;
  int16_T i;
  int16_T i_0;

  /* During 'Switch': '<S1>:215' */
  switch (NetworkLayerServices_GF_DWork.N_PCItype) {
   case SingleFrame:
    /* Transition: '<S1>:219' */
    NetworkLayerServices_GF_DWork.is_Indication =
      NetworkLayerServ_IN_SingleFrame;

    /* Entry 'SingleFrame': '<S1>:217' */
    NetworkLayerServices_GF_DWork.RxMessageDataPtr = 0U;
    NetworkLayerServices_GF_DWork.rx_buffer_ptr = 1U;

    /* Entry Internal 'SingleFrame': '<S1>:217' */
    /* Transition: '<S1>:332' */
    NetworkLayerService_CheckTatype();
    //UdsIndication.Length = (uint16_T)(((int16_T)RXbuffer_u8a8_Sig[0]) & 0x0F);__byte
    UdsIndication.Length = __byte(&RXbuffer_u8a8_Sig[0], LSB) & 0x0F;
    if (((UdsIndication.Length > 0U) && (UdsIndication.Length < 8U)) &&
        (CANLength_u8_Sig > UdsIndication.Length)) {
      /* Transition: '<S1>:650' */
      /* Transition: '<S1>:333' */
      NetworkLayerServ_CopyToRxbuffer((uint8_T)UdsIndication.Length);
    } else {
      /* Transition: '<S1>:652' */
      SFLength_Ovrn_u8_Sig = 1;

      /* Transition: '<S1>:657' */
      /* Transition: '<S1>:659' */
    }

    /* Transition: '<S1>:661' */
    break;

   case FlowControl:
    /* Transition: '<S1>:222' */
    /* Transition: '<S1>:233' */
    NetworkLayerServices_GF_DWork.is_Indication =
      NetworkLayer_IN_NO_ACTIVE_CHILD;

    /* Event: '<S1>:236' */
    b_previousEvent = NetworkLayerServices_GF_DWork.sfEvent;
    NetworkLayerServices_GF_DWork.sfEvent = NetworkLayerS_event_FC_Received;
    if (NetworkLayerServices_GF_DWork.is_active_Request == 0) {
    } else {
      NetworkLayerServices_GF_Request();
    }

    NetworkLayerServices_GF_DWork.sfEvent = b_previousEvent;
    NetworkLayerServices_GF_DWork.is_Indication =
      NetworkLayerServices_GF_IN_Idle;

    /* Entry 'Idle': '<S1>:214' */
    NetworkLayerServices_GF_DWork.Result = N_OK;
    break;

   default:
    if ((((int32_T)((int16_T)NetworkLayerServices_GF_DWork.N_PCItype)) ==
         ((int32_T)((int16_T)FirstFrame))) && (RecID_u8_Sig == PHYSICAL_ID)) {
      /* Transition: '<S1>:663' */
      /* Transition: '<S1>:665' */
      FrameSequ_u8_Sig = 1;
      NetworkLayerServices_GF_DWork.is_Indication =
        NetworkLayerSe_IN_MultipleFrame;

      /* Entry 'MultipleFrame': '<S1>:223' */
      FS = 0U;
      for (i_0 = 0; i_0 < 8; i_0 = i_0 + 1) {
        NetworkLayerServices_GF_DWork.fc_buffer[i_0] = 0U;
      }

      NetworkLayerServices_GF_DWork.SN_Check = 0U;
      NetworkLayerServices_GF_DWork.FF_DL = 0U;

      /* Entry Internal 'MultipleFrame': '<S1>:223' */
      /* Transition: '<S1>:247' */
      if (NetworkLayerServices_GF_DWork.is_MultipleFrame ==
          NetworkLayerServi_IN_FirstFrame) {
      } else {
        NetworkLayerServices_GF_DWork.is_MultipleFrame =
          NetworkLayerServi_IN_FirstFrame;

        /* Entry 'FirstFrame': '<S1>:241' */
        NetworkLayerServices_GF_DWork.RxMessageDataPtr = 0U;
        NetworkLayerServices_GF_DWork.rx_buffer_ptr = 0U;
        CFCount_u8_Sig = 0;
      }

      /* Entry Internal 'FirstFrame': '<S1>:241' */
      /* Transition: '<S1>:358' */
      //NetworkLayerServices_GF_DWork.FF_DL = (uint16_T)((((uint16_T)(((int16_T)
      //  RXbuffer_u8a8_Sig[0]) & 0x0F)) << 8) + RXbuffer_u8a8_Sig[1]);
	  
	  	
	  NetworkLayerServices_GF_DWork.FF_DL = (__byte(&RXbuffer_u8a8_Sig[0], LSB)&0x0F)*256;
	  NetworkLayerServices_GF_DWork.FF_DL +=__byte(&RXbuffer_u8a8_Sig[0], MSB);

      /* Transition: '<S1>:370' */
      NetworkLayerServices_GF_DWork.N_PCItype = (uint8_T)((int16_T)FlowControl);
      guard_0 = FALSE;
      if (NetworkLayerServices_GF_DWork.FF_DL > MaxBufferSize) {
        /* Transition: '<S1>:369' */
        /* Transition: '<S1>:368' */
        FS = (uint8_T)OverFlow;
        NetworkLayerServices_GF_DWork.FF_DL = 0U;
        NetworkLayerServices_GF_DWork.Result = N_BUFFER_OVFLW;
        FrameErr_u8_Sig = 3;

        /* Transition: '<S1>:367' */
        guard_0 = TRUE;
      } else if (NetworkLayerServices_GF_DWork.FF_DL == 0U) {
        /* Transition: '<S1>:684' */
        /* Transition: '<S1>:685' */
      } else {
        /* Transition: '<S1>:366' */
        FS = (uint8_T)ContinuedToSend;
        UdsIndication.Length = NetworkLayerServices_GF_DWork.FF_DL;
        NetworkLayerService_CheckTatype();
        NetworkLayerServices_GF_DWork.ffindication.Length = UdsIndication.Length;
        NetworkLayerServices_GF_DWork.ffindication.N_TAtype =
          UdsIndication.N_TAtype;
        IndicationCmd_u8_Sig = 1;
        guard_0 = TRUE;
      }

      if (((int16_T)guard_0) == ((int16_T)TRUE)) {
        /* Transition: '<S1>:365' */
        NetworkLayerServices_GF_DWork.fc_buffer[0] = (uint8_T)(((uint8_T)
          (NetworkLayerServices_GF_DWork.N_PCItype << 4)) + FS);
        NetworkLayerServices_GF_DWork.fc_buffer[1] = 8U;
        NetworkLayerServices_GF_DWork.fc_buffer[2] = (uint8_T)STmin_u8_Par;

        /* Transition: '<S1>:359' */
        UdsSend(3, NetworkLayerServices_GF_DWork.fc_buffer);
      }

      /* Transition: '<S1>:392' */
      /* comment */
      if (FS == ContinuedToSend) {
        /* Transition: '<S1>:394' */
        /* Transition: '<S1>:395' */
        NetworkLayerServices_GF_DWork.rx_buffer_ptr = 2U;
        NetworkLayerServ_CopyToRxbuffer(6U);
        NetworkLayerServices_GF_DWork.FF_DL =
          NetworkLayerServices_GF_DWork.FF_DL - ((uint16_T)6);

        /* Transition: '<S1>:398' */
        /* Transition: '<S1>:399' */
      } else {
        /* Transition: '<S1>:393' */
        /* Transition: '<S1>:400' */
      }

      /* Transition: '<S1>:401' */
    } else {
      guard = FALSE;
      if (((int32_T)((int16_T)NetworkLayerServices_GF_DWork.N_PCItype)) ==
          ((int32_T)((int16_T)ConsecutiveFrame))) {
        /* Transition: '<S1>:668' */
        if (FC_RecStatus_u8_Sig == 0) {
          /* Transition: '<S1>:732' */
          /* Transition: '<S1>:669' */
          FrameErr_u8_Sig = 1;
          guard = TRUE;
        } else {
          /* Transition: '<S1>:733' */
          /* Exit Internal: Chart */
          /* Exit Internal 'Indication': '<S1>:213' */
          NetworkLayerServices_GF_DWork.is_Indication =
            NetworkLayer_IN_NO_ACTIVE_CHILD;

          /* Exit Internal 'MultipleFrame': '<S1>:223' */
          NetworkLayerServices_GF_DWork.is_MultipleFrame =
            NetworkLayer_IN_NO_ACTIVE_CHILD;
          NetworkLayerServices_GF_DWork.is_active_Indication = 0U;

          /* Exit Internal 'Request': '<S1>:212' */
          /* Exit Internal 'MultipleFrameTransmission': '<S1>:99' */
          /* Exit Internal 'ConsecutiveFrame': '<S1>:123' */
          NetworkLayerServices_GF_DWork.is_ConsecutiveFrame =
            NetworkLayer_IN_NO_ACTIVE_CHILD;
          NetworkLayerServices_GF_DWork.is_active_Request = 1U;

          /* Entry 'Request': '<S1>:212' */
          NetworkLayerServices_GF_DWork.TransmissionType = 0U;
          NetworkLayerServices_GF_DWork.FF_DL_o = 0U;
          NetworkLayerServices_GF_DWork.MessageDataPtr = 0U;
          NetworkLayerServices_GF_DWork.FS = 0U;
          NetworkLayerServices_GF_DWork.STmin = 0U;
          NetworkLayerServices_GF_DWork.BS = 0U;
          NetworkLayerServices_GF_DWork.tx_buffer_ptr = 0U;
          for (i = 0; i < 8; i = i + 1) {
            NetworkLayerServices_GF_DWork.tx_buffer[i] = 0U;
          }

          NetworkLayerServices_GF_DWork.Result_k = N_OK;
          NetworkLayerServices_GF_DWork.is_Request =
            Ne_IN_MultipleFrameTransmission;

          /* Entry 'MultipleFrameTransmission': '<S1>:99' */
          NetworkLayerServices_GF_DWork.CF_DL = 0U;
          NetworkLayerServices_GF_DWork.SN = 0U;
          NetworkLayerServices_GF_DWork.is_MultipleFrameTransmission =
            NetworkLaye_IN_ConsecutiveFrame;

          /* Entry 'ConsecutiveFrame': '<S1>:123' */
          if (NetworkLayerServices_GF_DWork.is_ConsecutiveFrame ==
              NetworkLayerServices_GF_IN_Wait) {
          } else {
            NetworkLayerServices_GF_DWork.is_ConsecutiveFrame =
              NetworkLayerServices_GF_IN_Wait;
            NetworkLayerServices_GF_DWork.temporalCounter_i1 = 0U;
          }

          NetworkLayerServices_GF_DWork.is_active_Indication = 1U;

          /* Entry 'Indication': '<S1>:213' */
          NetworkLayerServices_GF_DWork.N_PCItype = 0U;
          NetworkLayerServices_GF_DWork.RxMessageDataPtr = 0U;
          NetworkLayerServices_GF_DWork.rx_buffer_ptr = 0U;
          NetworkLayerServices_GF_DWork.Result = N_OK;

          /* Entry Internal 'Indication': '<S1>:213' */
          /* Transition: '<S1>:225' */
          if (NetworkLayerServices_GF_DWork.is_Indication ==
              NetworkLayerServices_GF_IN_Idle) {
          } else {
            NetworkLayerServices_GF_DWork.is_Indication =
              NetworkLayerServices_GF_IN_Idle;

            /* Entry 'Idle': '<S1>:214' */
          }
        }
      } else {
        /* Transition: '<S1>:240' */
        NetworkLayerServices_GF_DWork.Result = N_ERROR;
        FrameErr_u8_Sig = 2;
        guard = TRUE;
      }

      if (((int16_T)guard) == ((int16_T)TRUE)) {
        /* Transition: '<S1>:573' */
        IndicationCmd_u8_Sig = 2;

        /* Transition: '<S1>:233' */
        NetworkLayerServices_GF_DWork.is_Indication =
          NetworkLayerServices_GF_IN_Idle;

        /* Entry 'Idle': '<S1>:214' */
        NetworkLayerServices_GF_DWork.Result = N_OK;
      }
    }
    break;
  }
}

/* Function for Chart: '<Root>/Chart' */
static void NetworkLayerServices_Indication(void)
{
  int32_T b_previousEvent;
  uint8_T SN;
  boolean_T guard;
  boolean_T guard_0;
  boolean_T guard_1;

  /* During 'Indication': '<S1>:213' */
  guard = FALSE;
  switch (NetworkLayerServices_GF_DWork.is_Indication) {
   case NetworkLayerServices_GF_IN_Idle:
    /* During 'Idle': '<S1>:214' */
    if (NetworkLayerServi_FrameReceived() != 0) {
      /* Transition: '<S1>:216' */
      NetworkLayerServices_GF_DWork.is_Indication =
        NetworkLayerServices__IN_Switch;

      /* Entry 'Switch': '<S1>:215' */
      UdsIndication.N_Result = NetworkLayerServices_GF_DWork.Result;

      /* Entry Internal 'Switch': '<S1>:215' */
      /* Transition: '<S1>:285' */
      //NetworkLayerServices_GF_DWork.N_PCItype = (uint8_T)((int16_T)
      //  (RXbuffer_u8a8_Sig[0] >> 4));
	  NetworkLayerServices_GF_DWork.N_PCItype = __byte(&RXbuffer_u8a8_Sig[0], LSB)>>4;
	  
      NetworkLayerService_CheckTatype();
      FrameSequ_u8_Sig = 0;
      FrameErr_u8_Sig = 0;
      SFLength_Ovrn_u8_Sig = 0;
      UDS_Timeout_u8_Sig = 0;
    }
    break;

   case NetworkLayerSe_IN_MultipleFrame:
    /* During 'MultipleFrame': '<S1>:223' */
    if (NetworkLayerServices_GF_DWork.sfEvent == NetworkLayerServic_event_CF_END)
    {
      /* Transition: '<S1>:232' */
      guard = TRUE;
    } else if (NetworkLayerServices_GF_DWork.Result != N_OK) {
      /* Transition: '<S1>:571' */
      UdsIndication.N_Result = NetworkLayerServices_GF_DWork.Result;
      guard = TRUE;
    } else {
      switch (NetworkLayerServices_GF_DWork.is_MultipleFrame) {
       case NetworkLaye_IN_ConsecutiveFrame:
        /* During 'ConsecutiveFrame': '<S1>:243' */
        /* Transition: '<S1>:246' */
        NetworkLayerServices_GF_DWork.is_MultipleFrame =
          NetworkLayerServices_GF_IN_Wait;
        NetworkLayerServices_GF_DWork.temporalCounter_i2 = 0U;
        break;

       case NetworkLayerServi_IN_FirstFrame:
        /* During 'FirstFrame': '<S1>:241' */
        /* Transition: '<S1>:244' */
        NetworkLayerServices_GF_DWork.is_MultipleFrame =
          NetworkLayerServices_GF_IN_Wait;
        NetworkLayerServices_GF_DWork.temporalCounter_i2 = 0U;
        break;

       case NetworkLayerServices_GF_IN_Wait:
        /* Constant: '<Root>/CrTime' */
        /* During 'Wait': '<S1>:242' */
        if ((NetworkLayerServices_GF_DWork.sfEvent ==
             NetworkLayerServices_CALL_EVENT) &&
            (NetworkLayerServices_GF_DWork.temporalCounter_i2 >=
             CrTime_Limited_u16_Par)) {
          /* Transition: '<S1>:577' */
          NetworkLayerServices_GF_DWork.Result = N_TIMEOUT_Cr;
          UDS_Timeout_u8_Sig = 2;
        } else {
          if (NetworkLayerServi_FrameReceived() != 0) {
            /* Transition: '<S1>:245' */
            /* Transition: '<S1>:688' */
            //NetworkLayerServices_GF_DWork.N_PCItype = (uint8_T)((int16_T)
            //  (RXbuffer_u8a8_Sig[0] >> 4));
            NetworkLayerServices_GF_DWork.N_PCItype = __byte(&RXbuffer_u8a8_Sig[0], LSB)>>4;
            if (NetworkLayerServices_GF_DWork.N_PCItype == 2) {
              /* Transition: '<S1>:690' */
              NetworkLayerServices_GF_DWork.is_MultipleFrame =
                NetworkLaye_IN_ConsecutiveFrame;

              /* Entry 'ConsecutiveFrame': '<S1>:243' */
              NetworkLayerServices_GF_DWork.rx_buffer_ptr = 1U;

              /* Entry Internal 'ConsecutiveFrame': '<S1>:243' */
              /* Transition: '<S1>:412' */
              /* comment */
              if (NetworkLayerServices_GF_DWork.SN_Check < 15) {
                /* Transition: '<S1>:416' */
                /* Transition: '<S1>:415' */
                NetworkLayerServices_GF_DWork.SN_Check = (uint8_T)
                  (NetworkLayerServices_GF_DWork.SN_Check + 1);

                /* Transition: '<S1>:414' */
              } else {
                /* Transition: '<S1>:413' */
                NetworkLayerServices_GF_DWork.SN_Check = 0U;
              }

              /* Transition: '<S1>:429' */
              //SN = (uint8_T)(((int16_T)RXbuffer_u8a8_Sig[0]) & 0x0F);
              SN = __byte(&RXbuffer_u8a8_Sig[0], LSB)&0x0F;
              if (SN == NetworkLayerServices_GF_DWork.SN_Check) {
                /* Transition: '<S1>:428' */
                /* Transition: '<S1>:427' */
                /* Transition: '<S1>:426' */
              } else {
                /* Transition: '<S1>:425' */
                NetworkLayerServices_GF_DWork.Result = N_WRONG_SN;
                NetworkLayerServices_GF_DWork.FF_DL = 0U;
              }

              /* Transition: '<S1>:454' */
              /* comment */
              guard_0 = FALSE;
              guard_1 = FALSE;
              if (NetworkLayerServices_GF_DWork.FF_DL < 7U) {
                /* Transition: '<S1>:458' */
                /* Transition: '<S1>:457' */
                NetworkLayerServ_CopyToRxbuffer((uint8_T)
                  NetworkLayerServices_GF_DWork.FF_DL);
                if ((CANLength_u8_Sig - 1) >=
                    NetworkLayerServices_GF_DWork.FF_DL) {
                  /* Transition: '<S1>:721' */
                  guard_0 = TRUE;
                } else {
                  /* Transition: '<S1>:723' */
                  guard_1 = TRUE;
                }
              } else {
                /* Transition: '<S1>:455' */
                NetworkLayerServ_CopyToRxbuffer(7U);
                if (CANLength_u8_Sig == 8) {
                  /* Transition: '<S1>:728' */
                  /* Transition: '<S1>:729' */
                  NetworkLayerServices_GF_DWork.FF_DL =
                    NetworkLayerServices_GF_DWork.FF_DL - ((uint16_T)7);
                } else {
                  /* Transition: '<S1>:730' */
                  guard_1 = TRUE;
                }
              }

              if (((int16_T)guard_1) == ((int16_T)TRUE)) {
                /* Transition: '<S1>:724' */
                NetworkLayerServices_GF_DWork.Result = N_ERROR;
                FrameErr_u8_Sig = 2;
                guard_0 = TRUE;
              }

              if (((int16_T)guard_0) == ((int16_T)TRUE)) {
                /* Transition: '<S1>:456' */
                NetworkLayerServices_GF_DWork.FF_DL = 0U;
              }

              /* Transition: '<S1>:459' */
              if (NetworkLayerServices_GF_DWork.FF_DL == 0U) {
                /* Transition: '<S1>:604' */
                CFCount_u8_Sig = 0;

                /* Transition: '<S1>:600' */
                /* Event: '<S1>:447' */
                b_previousEvent = NetworkLayerServices_GF_DWork.sfEvent;
                NetworkLayerServices_GF_DWork.sfEvent =
                  NetworkLayerServic_event_CF_END;
                if (NetworkLayerServices_GF_DWork.is_active_Indication == 0) {
                } else {
                  NetworkLayerServices_Indication();
                }

                NetworkLayerServices_GF_DWork.sfEvent = b_previousEvent;
              } else {
                /* Transition: '<S1>:602' */
                CFCount_u8_Sig = CFCount_u8_Sig + 1;
                if (CFCount_u8_Sig == 8) {
                  /* Transition: '<S1>:603' */
                  /* Transition: '<S1>:622' */
                  NetworkLayerServices_GF_DWork.N_PCItype = (uint8_T)((int16_T)
                    FlowControl);
                  NetworkLayerServices_GF_DWork.fc_buffer[0] = (uint8_T)
                    (((uint8_T)(NetworkLayerServices_GF_DWork.N_PCItype << 4)) +
                     ((uint8_T)ContinuedToSend));
                  NetworkLayerServices_GF_DWork.fc_buffer[1] = 8U;
                  NetworkLayerServices_GF_DWork.fc_buffer[2] = (uint8_T)
                    STmin_u8_Par;

                  /* Transition: '<S1>:621' */
                  UdsSend(3, NetworkLayerServices_GF_DWork.fc_buffer);
                  CFCount_u8_Sig = 0;

                  /* Transition: '<S1>:642' */
                } else {
                  /* Transition: '<S1>:646' */
                }
              }

              /* Transition: '<S1>:645' */
            } else if ((NetworkLayerServices_GF_DWork.N_PCItype == 0) ||
                       (NetworkLayerServices_GF_DWork.N_PCItype == 1)) {
              /* Transition: '<S1>:691' */
              NetworkLayerServices_GF_DWork.is_MultipleFrame =
                NetworkLayer_IN_NO_ACTIVE_CHILD;
              NetworkLayerServices_GF_DWork.is_Indication =
                NetworkLayerServices__IN_Switch;

              /* Entry 'Switch': '<S1>:215' */
              UdsIndication.N_Result = NetworkLayerServices_GF_DWork.Result;

              /* Entry Internal 'Switch': '<S1>:215' */
              /* Transition: '<S1>:285' */
              //NetworkLayerServices_GF_DWork.N_PCItype = (uint8_T)((int16_T)
              //  (RXbuffer_u8a8_Sig[0] >> 4));
			  NetworkLayerServices_GF_DWork.N_PCItype = __byte(&RXbuffer_u8a8_Sig[0],LSB)>>4;
			  
              NetworkLayerService_CheckTatype();
              FrameSequ_u8_Sig = 0;
              FrameErr_u8_Sig = 0;
              SFLength_Ovrn_u8_Sig = 0;
              UDS_Timeout_u8_Sig = 0;
            } else {
              /* Transition: '<S1>:709' */
              NetworkLayerServices_GF_DWork.is_MultipleFrame =
                NetworkLayerServices_GF_IN_Wait;
              NetworkLayerServices_GF_DWork.temporalCounter_i2 = 0U;
            }
          }
        }

        /* End of Constant: '<Root>/CrTime' */
        break;

       default:
        NetworkLayerServices_GF_DWork.is_MultipleFrame =
          NetworkLayer_IN_NO_ACTIVE_CHILD;
        break;
      }
    }
    break;

   case NetworkLayerServ_IN_SingleFrame:
    /* During 'SingleFrame': '<S1>:217' */
    /* Transition: '<S1>:230' */
    /* Transition: '<S1>:573' */
    IndicationCmd_u8_Sig = 2;

    /* Transition: '<S1>:233' */
    NetworkLayerServices_GF_DWork.is_Indication =
      NetworkLayerServices_GF_IN_Idle;

    /* Entry 'Idle': '<S1>:214' */
    NetworkLayerServices_GF_DWork.Result = N_OK;
    break;

   case NetworkLayerServices__IN_Switch:
    NetworkLayerServices_GF_Switch();
    break;

   default:
    NetworkLayerServices_GF_DWork.is_Indication =
      NetworkLayer_IN_NO_ACTIVE_CHILD;
    break;
  }

  if (((int16_T)guard) == ((int16_T)TRUE)) {
    /* Transition: '<S1>:573' */
    IndicationCmd_u8_Sig = 2;

    /* Transition: '<S1>:233' */
    /* Exit Internal 'MultipleFrame': '<S1>:223' */
    NetworkLayerServices_GF_DWork.is_MultipleFrame =
      NetworkLayer_IN_NO_ACTIVE_CHILD;
    NetworkLayerServices_GF_DWork.is_Indication =
      NetworkLayerServices_GF_IN_Idle;

    /* Entry 'Idle': '<S1>:214' */
    NetworkLayerServices_GF_DWork.Result = N_OK;
  }
}

/* Model step function */
void NetworkLayerServices_GF_step(void)
{
  int16_T i;
  int16_T i_0;

  /* BusCreator: '<Root>/BusConversion_InsertedFor_Chart_at_inport_0' incorporates:
   *  Inport: '<Root>/In1'
   */
  NetworkLayerServices_GF_DWork.BusConversion_InsertedFor_Chart.Mtype =
    UdsRequest.Mtype;
  NetworkLayerServices_GF_DWork.BusConversion_InsertedFor_Chart.N_SA =
    UdsRequest.N_SA;
  NetworkLayerServices_GF_DWork.BusConversion_InsertedFor_Chart.N_TA =
    UdsRequest.N_TA;
  NetworkLayerServices_GF_DWork.BusConversion_InsertedFor_Chart.N_TAtype =
    UdsRequest.N_TAtype;
  NetworkLayerServices_GF_DWork.BusConversion_InsertedFor_Chart.N_AE =
    UdsRequest.N_AE;
  //for (i = 0; i < 255; i = i + 1) {
  //  NetworkLayerServices_GF_DWork.BusConversion_InsertedFor_Chart.MessageData[i]
  //    = UdsRequest.MessageData[i];
  //}
  CopyMemory_WithNone_Byte(&NetworkLayerServices_GF_DWork.BusConversion_InsertedFor_Chart.MessageData[0],
  						   &UdsRequest.MessageData[0],
  						   LSB,
  						   LSB,
  						   256);

  NetworkLayerServices_GF_DWork.BusConversion_InsertedFor_Chart.Length =
    UdsRequest.Length;

  /* End of BusCreator: '<Root>/BusConversion_InsertedFor_Chart_at_inport_0' */

  /* Chart: '<Root>/Chart' */
  /* Gateway: Chart */
  NetworkLayerServices_GF_DWork.sfEvent = NetworkLayerServices_CALL_EVENT;
  if (NetworkLayerServices_GF_DWork.temporalCounter_i1 < MAX_uint16_T) {
    NetworkLayerServices_GF_DWork.temporalCounter_i1 =
      NetworkLayerServices_GF_DWork.temporalCounter_i1 + ((uint16_T)1);
  }

  if (NetworkLayerServices_GF_DWork.temporalCounter_i2 < MAX_uint16_T) {
    NetworkLayerServices_GF_DWork.temporalCounter_i2 =
      NetworkLayerServices_GF_DWork.temporalCounter_i2 + ((uint16_T)1);
  }

  /* During: Chart */
  if (NetworkLayerServices_GF_DWork.is_active_c1_NetworkLayerServic == 0) {
    /* Entry: Chart */
    NetworkLayerServices_GF_DWork.is_active_c1_NetworkLayerServic = 1U;

    /* Entry Internal: Chart */
    NetworkLayerServices_GF_DWork.is_active_Request = 1U;

    /* Entry 'Request': '<S1>:212' */
    NetworkLayerServices_GF_DWork.TransmissionType = 0U;
    NetworkLayerServices_GF_DWork.FF_DL_o = 0U;
    NetworkLayerServices_GF_DWork.MessageDataPtr = 0U;
    NetworkLayerServices_GF_DWork.FS = 0U;
    NetworkLayerServices_GF_DWork.STmin = 0U;
    NetworkLayerServices_GF_DWork.BS = 0U;
    NetworkLayerServices_GF_DWork.tx_buffer_ptr = 0U;
    for (i_0 = 0; i_0 < 8; i_0 = i_0 + 1) {
      NetworkLayerServices_GF_DWork.tx_buffer[i_0] = 0U;
    }

    NetworkLayerServices_GF_DWork.Result_k = N_OK;

    /* Entry Internal 'Request': '<S1>:212' */
    /* Transition: '<S1>:76' */
    if (NetworkLayerServices_GF_DWork.is_Request ==
        NetworkLayerServices_GF_IN_Idle) {
    } else {
      NetworkLayerServices_GF_DWork.is_Request = NetworkLayerServices_GF_IN_Idle;

      /* Entry 'Idle': '<S1>:74' */
    }

    NetworkLayerServices_GF_DWork.is_active_Indication = 1U;

    /* Entry 'Indication': '<S1>:213' */
    NetworkLayerServices_GF_DWork.N_PCItype = 0U;
    NetworkLayerServices_GF_DWork.RxMessageDataPtr = 0U;
    NetworkLayerServices_GF_DWork.rx_buffer_ptr = 0U;
    NetworkLayerServices_GF_DWork.Result = N_OK;

    /* Entry Internal 'Indication': '<S1>:213' */
    /* Transition: '<S1>:225' */
    if (NetworkLayerServices_GF_DWork.is_Indication ==
        NetworkLayerServices_GF_IN_Idle) {
    } else {
      NetworkLayerServices_GF_DWork.is_Indication =
        NetworkLayerServices_GF_IN_Idle;

      /* Entry 'Idle': '<S1>:214' */
    }
  } else {
    if (NetworkLayerServices_GF_DWork.is_active_Request == 0) {
    } else {
      NetworkLayerServices_GF_Request();
    }

    if (NetworkLayerServices_GF_DWork.is_active_Indication == 0) {
    } else {
      NetworkLayerServices_Indication();
    }
  }

  /* End of Chart: '<Root>/Chart' */

  /* Outport: '<Root>/Out1' */
  NetworkLayerServices_GF_Y.Out1 = NetworkLayerServices_GF_DWork.ffindication;
}

/* Model initialize function */
void NetworkLayerServices_GF_initialize(void)
{
  /* Registration code */
    NetworkLayerServices_GF_DWork.is_active_c1_NetworkLayerServic = 0U;
  /* block I/O */

  /* exported global signals */
  //UdsIndication = NetworkLayerServices_GF_rtZUSDATAINDICATION;
  UdsIndication.Mtype = diagnostics;
  UdsIndication.N_TAtype = physical;
  //UdsConfirm = NetworkLayerServices_GF_rtZUSDATACONFIRM;
  UdsIndication.Mtype = diagnostics;
  UdsIndication.N_TAtype = physical;

  /* states (dwork) */
  {
    //NetworkLayerServices_GF_DWork.BusConversion_InsertedFor_Chart =
    //  NetworkLayerServices_GF_rtZUSDATAREQUEST;

	NetworkLayerServices_GF_DWork.BusConversion_InsertedFor_Chart.Mtype = diagnostics;
	NetworkLayerServices_GF_DWork.BusConversion_InsertedFor_Chart.N_TAtype = physical;
    //NetworkLayerServices_GF_DWork.ffindication =
    //  NetworkLayerServices_GF_rtZUSDATAFFINDICATION;

	NetworkLayerServices_GF_DWork.ffindication.Mtype = diagnostics;
	NetworkLayerServices_GF_DWork.ffindication.N_TAtype = physical;
  }

  /* external inputs */
  //UdsRequest = NetworkLayerServices_GF_rtZUSDATAREQUEST;
  UdsRequest.Mtype = diagnostics;
  UdsRequest.N_TAtype = physical;

  /* external outputs */
  //NetworkLayerServices_GF_Y.Out1 = NetworkLayerServices_GF_rtZUSDATAFFINDICATION;
  NetworkLayerServices_GF_Y.Out1.Mtype = diagnostics;
  NetworkLayerServices_GF_Y.Out1.N_TAtype = physical;

  {
    int16_T i;

    /* InitializeConditions for Chart: '<Root>/Chart' */
    NetworkLayerServices_GF_DWork.sfEvent = NetworkLayerServices_CALL_EVENT;
    NetworkLayerServices_GF_DWork.Result = N_OK;
    NetworkLayerServices_GF_DWork.Result_k = N_OK;
    NetworkLayerServices_GF_DWork.ffindication.Mtype = diagnostics;
    NetworkLayerServices_GF_DWork.ffindication.N_SA = 0U;
    NetworkLayerServices_GF_DWork.ffindication.N_TA = 0U;
    NetworkLayerServices_GF_DWork.ffindication.N_TAtype = physical;
    NetworkLayerServices_GF_DWork.ffindication.N_AE = 0U;
    NetworkLayerServices_GF_DWork.ffindication.Length = 0U;
    UdsIndication.Mtype = diagnostics;
    UdsIndication.N_SA = 0U;
    UdsIndication.N_TA = 0U;
    UdsIndication.N_TAtype = physical;
    UdsIndication.N_AE = 0U;
    for (i = 0; i < 128; i = i + 1) {
      UdsIndication.MessageData[i] = 0U;
    }

    UdsIndication.Length = 0U;
    UdsIndication.N_Result = N_OK;
    UdsConfirm.Mtype = diagnostics;
    UdsConfirm.N_SA = 0U;
    UdsConfirm.N_TA = 0U;
    UdsConfirm.N_TAtype = physical;
    UdsConfirm.N_AE = 0U;
    UdsConfirm.N_Result = N_OK;

    /* End of InitializeConditions for Chart: '<Root>/Chart' */
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
