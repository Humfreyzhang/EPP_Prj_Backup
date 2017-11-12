#include "rtwtypes.h"

#pragma DATA_SECTION(APP_Vision, "ID_CAL");
#pragma DATA_SECTION(EcuAppSwNumb_u16a6_Par, "SWPN_Section");

#define App_LEVEL                                      0x01
#define REVISION_LEVEL                                 0x03
#define APP_VERSION                                  (( App_LEVEL << 8) + REVISION_LEVEL )


const uint16_T APP_Vision = APP_VERSION;
const uint16_T EcuAppSwNumb_u16a6_Par[3]={0x6945, 0x6200, 0x3102};/*DID:F1A0*/