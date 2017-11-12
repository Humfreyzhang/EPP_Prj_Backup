#ifndef INTERFACE_FILE_H
#define INTERFACE_FILE_H
#include "rtwtypes.h"

#define CAL_pattern_addr  (0x300)
#define CAL_pattern       (0x3223)

#define EEPROM_StartAddress (0x8700)
#define EEPROM_Size        (0x200)

#define EEPROM_FlashAddress (0x3F4000)
#define EEPROM_FlashSize    (0x2000)

#define BLANK_PAGE_DATA     (0xFFFF)
#define VALID_PAGE_DATA     (0xA55A)

#define EEPROM_SECTOR       (SECTORB)

typedef struct File_Status_Tag
{
	uint16_T CalPattern_error:1;
	uint16_T EEPROM_error:1;
	uint16_T APP_CksumErr:1;
	uint16_T Unused:13;
}File_Stauts_T;

extern File_Stauts_T File_Diag;

extern void Cal_Workspace_Init(void);
extern void EEPROM_Restore(void);
extern void EEPROM_Backup(void);
#endif
