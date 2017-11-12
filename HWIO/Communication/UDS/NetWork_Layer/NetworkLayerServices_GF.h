/*
 * File: NetworkLayerServices_GF.h
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

#ifndef RTW_HEADER_NetworkLayerServices_GF_h_
#define RTW_HEADER_NetworkLayerServices_GF_h_
#ifndef NetworkLayerServices_GF_COMMON_INCLUDES_
# define NetworkLayerServices_GF_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* NetworkLayerServices_GF_COMMON_INCLUDES_ */

#include "NetworkLayerServices_GF_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((void*) 0)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((void) 0)
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((void*) 0)
#endif

/* user code (top of header file) */
#include "networklayer_interface.h"

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
  USDATAREQUEST BusConversion_InsertedFor_Chart;
  USDATAFFINDICATION ffindication;     /* '<Root>/Chart' (Output 1)  */
  int32_T sfEvent;                     /* '<Root>/Chart' (DWork 1)  */
  E_N_Result Result;                   /* '<Root>/Chart' (DWork 13)  */
  E_N_Result Result_k;                 /* '<Root>/Chart' (DWork 25)  */
  uint16_T FF_DL;                      /* '<Root>/Chart' (DWork 16)  */
  uint16_T FF_DL_o;                    /* '<Root>/Chart' (DWork 18)  */
  uint16_T CF_DL;                      /* '<Root>/Chart' (DWork 26)  */
  uint16_T temporalCounter_i1;         /* '<Root>/Chart' (DWork 28)  */
  uint16_T temporalCounter_i2;         /* '<Root>/Chart' (DWork 29)  */
  uint8_T fc_buffer[8];                /* '<Root>/Chart' (DWork 14)  */
  uint8_T tx_buffer[8];                /* '<Root>/Chart' (DWork 24)  */
  uint8_T is_active_c1_NetworkLayerServic;/* '<Root>/Chart' (DWork 2)  */
  uint8_T is_MultipleFrameTransmission;/* '<Root>/Chart' (DWork 3)  */
  uint8_T is_ConsecutiveFrame;         /* '<Root>/Chart' (DWork 4)  */
  uint8_T is_active_Request;           /* '<Root>/Chart' (DWork 5)  */
  uint8_T is_Request;                  /* '<Root>/Chart' (DWork 6)  */
  uint8_T is_active_Indication;        /* '<Root>/Chart' (DWork 7)  */
  uint8_T is_Indication;               /* '<Root>/Chart' (DWork 8)  */
  uint8_T is_MultipleFrame;            /* '<Root>/Chart' (DWork 9)  */
  uint8_T N_PCItype;                   /* '<Root>/Chart' (DWork 10)  */
  uint8_T RxMessageDataPtr;            /* '<Root>/Chart' (DWork 11)  */
  uint8_T rx_buffer_ptr;               /* '<Root>/Chart' (DWork 12)  */
  uint8_T SN_Check;                    /* '<Root>/Chart' (DWork 15)  */
  uint8_T TransmissionType;            /* '<Root>/Chart' (DWork 17)  */
  uint8_T MessageDataPtr;              /* '<Root>/Chart' (DWork 19)  */
  uint8_T FS;                          /* '<Root>/Chart' (DWork 20)  */
  uint8_T STmin;                       /* '<Root>/Chart' (DWork 21)  */
  uint8_T BS;                          /* '<Root>/Chart' (DWork 22)  */
  uint8_T tx_buffer_ptr;               /* '<Root>/Chart' (DWork 23)  */
  uint8_T SN;                          /* '<Root>/Chart' (DWork 27)  */
} D_Work_NetworkLayerServices_GF;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  USDATAFFINDICATION Out1;             /* '<Root>/Out1' */
} ExternalOutputs_NetworkLayerSer;

/* Block signals and states (auto storage) */
extern D_Work_NetworkLayerServices_GF NetworkLayerServices_GF_DWork;

/* External outputs (root outports fed by signals with auto storage) */
extern ExternalOutputs_NetworkLayerSer NetworkLayerServices_GF_Y;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern USDATAREQUEST UdsRequest;       /* '<Root>/In1' */
extern USDATAINDICATION UdsIndication; /* '<Root>/Chart' (Output 2)  */
extern USDATACONFIRM UdsConfirm;       /* '<Root>/Chart' (Output 3)  */

/* External data declarations for dependent source files */
extern const USDATAREQUEST NetworkLayerServices_GF_rtZUSDATAREQUEST;/* USDATAREQUEST ground */
extern const USDATAFFINDICATION NetworkLayerServices_GF_rtZUSDATAFFINDICATION;/* USDATAFFINDICATION ground */
extern const USDATAINDICATION NetworkLayerServices_GF_rtZUSDATAINDICATION;/* USDATAINDICATION ground */
extern const USDATACONFIRM NetworkLayerServices_GF_rtZUSDATACONFIRM;/* USDATACONFIRM ground */

/* Model entry point functions */
extern void NetworkLayerServices_GF_initialize(void);
extern void NetworkLayerServices_GF_step(void);

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
 * '<Root>' : 'NetworkLayerServices_GF'
 * '<S1>'   : 'NetworkLayerServices_GF/Chart'
 */

/*-
 * Requirements for '<Root>': NetworkLayerServices_GF
 */
#endif                                 /* RTW_HEADER_NetworkLayerServices_GF_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
