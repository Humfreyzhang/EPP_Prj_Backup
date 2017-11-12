/*
 * File: NetworkLayerServices_GF_types.h
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

#ifndef RTW_HEADER_NetworkLayerServices_GF_types_h_
#define RTW_HEADER_NetworkLayerServices_GF_types_h_
#include "rtwtypes.h"
#ifndef _DEFINED_TYPEDEF_FOR_E_Mtype_
#define _DEFINED_TYPEDEF_FOR_E_Mtype_

typedef enum {
  diagnostics = 1,                     /* Default value */
  remote_diagnostics
} E_Mtype;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_E_N_TAtype_
#define _DEFINED_TYPEDEF_FOR_E_N_TAtype_

typedef enum {
  physical = 1,                        /* Default value */
  functional
} E_N_TAtype;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_E_N_Result_
#define _DEFINED_TYPEDEF_FOR_E_N_Result_

typedef enum {
  N_OK = 0,                            /* Default value */
  N_TIMEOUT_A,
  N_TIMEOUT_Bs,
  N_TIMEOUT_Cr,
  N_WRONG_SN,
  N_INVALID_Fs,
  N_UNEXP_PDU,
  N_WFT_OVRN,
  N_BUFFER_OVFLW,
  N_ERROR
} E_N_Result;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_E_N_PCItype_
#define _DEFINED_TYPEDEF_FOR_E_N_PCItype_



#endif

#ifndef _DEFINED_TYPEDEF_FOR_USDATAREQUEST_
#define _DEFINED_TYPEDEF_FOR_USDATAREQUEST_

typedef struct {
  E_Mtype Mtype;
  uint8_T N_SA;
  uint8_T N_TA;
  E_N_TAtype N_TAtype;
  uint8_T N_AE;
  uint16_T MessageData[128];
  uint16_T Length;
} USDATAREQUEST;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_USDATAFFINDICATION_
#define _DEFINED_TYPEDEF_FOR_USDATAFFINDICATION_

typedef struct {
  E_Mtype Mtype;
  uint8_T N_SA;
  uint8_T N_TA;
  E_N_TAtype N_TAtype;
  uint8_T N_AE;
  uint16_T Length;
} USDATAFFINDICATION;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_USDATAINDICATION_
#define _DEFINED_TYPEDEF_FOR_USDATAINDICATION_

typedef struct {
  E_Mtype Mtype;
  uint8_T N_SA;
  uint8_T N_TA;
  E_N_TAtype N_TAtype;
  uint8_T N_AE;
  uint8_T MessageData[128];
  uint16_T Length;
  E_N_Result N_Result;
} USDATAINDICATION;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_USDATACONFIRM_
#define _DEFINED_TYPEDEF_FOR_USDATACONFIRM_

typedef struct {
  E_Mtype Mtype;
  uint8_T N_SA;
  uint8_T N_TA;
  E_N_TAtype N_TAtype;
  uint8_T N_AE;
  E_N_Result N_Result;
} USDATACONFIRM;

#endif
#endif                                 /* RTW_HEADER_NetworkLayerServices_GF_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
