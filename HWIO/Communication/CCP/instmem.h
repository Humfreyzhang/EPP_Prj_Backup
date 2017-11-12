#ifndef INSTMEM_H
#define INSTMEM_H


#define MTA_Number_Is_Valid( MTA_number ) \
   ( 0 == (MTA_number))

typedef struct
{
   uint16_T memory_page;
   uint32_T* address;
} MTA_ptr_T;

typedef enum
{
   REGISTER,
   RAM,
   EEPROM_NON_FLASH,
   CAL_FLASH,
   UPPER_UNPAGED_FLASH,
   PAGED_FLASH,
   LOWER_UNPAGED_FLASH,
   OTHER
} memory_area_T;

typedef enum
{
   INST_CALIBRATION_PAGE_REFERENCE,
   INST_CALIBRATION_PAGE_WORKING
}  INST_Calibration_Page_T;


#define REGISTER_START_ADDRESS ((uint16_T*)0x0000)
#define REGISTER_STOP_ADDRESS   ((uint16_T*)0x0400)

#define EEPROM_START_ADDRESS  ((uint16_T*)0x0100) 
#define EEPROM_STOP_ADDRESS   ((uint16_T*)0x2000) 
#define EEPROM_MemeoyPage  ( (uint16_T*)0x10)

#define RAM_START_ADDRESS  ((uint16_T*)0x0000)      
#define RAM_STOP_ADDRESS   ((uint16_T*)0xA000)  
#define RAM_MemoryPage  (0x00)

#define FLASH_START_ADDRESS ((uint16_T*)0x003E8000) 
#define FLASH_STOP_ADDRESS  ((uint16_T*)0x003F7FFF) 

#define CAL_START_ADDRESS  ((uint16_T*)(0x0300))
#define CAL_STOP_ADDRESS   ((uint16_T*)(0x0400))  

#define CHK_SUM_LENGTH                    4

#define Memory_Page_Is_Valid( memory_page ) \
	(memory_page==0x3E||memory_page==0x3F||memory_page ==0x00)

#define Is_Within_CAL_Range(VarAddr, VarLength)                \
      (((VarAddr) >= CAL_START_ADDRESS ) &&                   \
      ((VarAddr)+(VarLength) <= (CAL_STOP_ADDRESS)))
      

#endif
