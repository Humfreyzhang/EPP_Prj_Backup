#ifndef ROM_CKECKSUM_H
#define ROM_CKECKSUM_H
#include "rtwtypes.h"
#include "t_types.h"

#define APP_ROM_StartAddress   (0x3E8000)
#define APP_ROM_EndAddress     (0x3F4000)
#define ROM_OneSection         (0x100)
extern void Rom_Checksum_init(void);
extern void Rom_Checksum_cal_10ms(void);

#endif