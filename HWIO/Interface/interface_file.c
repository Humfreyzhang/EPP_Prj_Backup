#include "rtwtypes.h"
#include "interface_file.h"
#include "Flash2803x_API.h"
#include "hwiocald.h"

//#include "DSP2803x_function.h"
#pragma DATA_SECTION(EEPROM_Cksum,     "EE_CKSUM");

extern uint16_T CALTablesLoadStart;
extern uint16_T CALTablesLoadEnd;
extern uint16_T CALWorkingpageStart;
extern uint16_T CALTablesLoadSize;
extern void Copydata(uint16_T *Dest, uint16_T *Source, uint16_T Sizes );

File_Stauts_T File_Diag;

uint16_T EEPROM_Cksum;
void Cal_Workspace_Init(void)
{

	Copydata((uint16_T *)&CALWorkingpageStart,(uint16_T *)&CALTablesLoadStart, (unsigned long)&CALTablesLoadSize);
	if(((uint16_T *)CAL_pattern_addr) != CAL_pattern)
	{
		// ((uint16_T *)CAL_pattern) = CAL_pattern;
		File_Diag.CalPattern_error = 1;
	}


}

static uint8_T Mem_BlankTest(uint16_T *in_address, uint16_T in_size)
{
   uint16_T index;
   uint8_T result = true;

   for (index = 0; (index < in_size) && (result == true); index++)
   {
      if (*in_address++ != BLANK_PAGE_DATA) result = false;
   }

   return result;
}

uint8_T EEPROM_ActivePage(void)
{
	uint8_T index;
	uint16_T *StartAddress;

	for(index=0; index < (EEPROM_FlashSize/EEPROM_Size); index++)
	{
		StartAddress = EEPROM_FlashAddress + index*EEPROM_Size;
		
	    if (Mem_BlankTest(StartAddress, EEPROM_Size) == true)
	    {
	    	if(index == 0)
    		{
				return (0x40);
			}
			else
			{
				return (index -1);
			}
	    }
		else if (index == (EEPROM_FlashSize/EEPROM_Size -1)) /* at last page */
		{
	        return (0x80);
		}
		else
		{
			//return (0xFF);
		}
	}

	return 0xFF;
}

void EEPROM_Clear(uint16_T *Source, uint16_T Sizes)
{
	uint8_T *Address_Start, size;

	size = 0;
	for(Address_Start = Source; size < Sizes; size++)
	{
		*Address_Start++ = 0;
	}

}

void EEPROM_Restore(void)
{
	uint8_T ActivePage;
	uint16_T checksum;

	ActivePage = EEPROM_ActivePage();
	
	if(ActivePage == 0x80)
		ActivePage = EEPROM_FlashSize/EEPROM_Size -1;
	else if(ActivePage == 0x40)
		ActivePage = 0;
	
	if(ActivePage != 0xFF)
	{
		Copydata((uint16_T *)EEPROM_StartAddress, (uint16_T *)(EEPROM_FlashAddress + ActivePage*EEPROM_Size), (uint16_T)EEPROM_Size);

		checksum = Checksum((uint16_T *)EEPROM_StartAddress, (EEPROM_Size -1));
		if(EEPROM_Cksum !=checksum)
		{
			File_Diag.EEPROM_error = TRUE;
			EEPROM_Cksum = checksum;
			
			if(K_EEPROM_ErrorErase_Enable == TRUE)
			{
				EEPROM_Clear((uint16_T *)EEPROM_StartAddress, (uint16_T)EEPROM_Size);
				EEPROM_Cksum = Checksum((uint16_T *)EEPROM_StartAddress, (EEPROM_Size -1));
			}
		}
		else
		{
			File_Diag.EEPROM_error = FALSE;
		}
	}
}

void EEPROM_Backup(void)
{
	uint16_T *StartAddress;
	uint8_T ActivePage;
	uint16_T EepromCksum;

	EepromCksum = Checksum((uint16_T *)EEPROM_StartAddress, (EEPROM_Size -1));

	if(EEPROM_Cksum == EepromCksum)
	{
		/*The EEPROM was not update, so it do not need reflash the data*/
		return;
	}
	else
	{
		EEPROM_Cksum = EepromCksum;
	}

	ActivePage = EEPROM_ActivePage();

	if(ActivePage < 0x80)
	{
		if(ActivePage ==0x40)
		{
			/*Flash was empty*/
			StartAddress = EEPROM_FlashAddress;
		}
		else
		{
			StartAddress = EEPROM_FlashAddress + (ActivePage+1)*EEPROM_Size;
		}
		DINT;
		API_Flash_Program(StartAddress, (uint16_T *)EEPROM_StartAddress, EEPROM_Size);
		EINT;
	}
	else
	{
		/*Flash was full, should be erased all data and write the active ram data into first page*/
		DINT;
		API_Flash_Erase(EEPROM_SECTOR);
		API_Flash_Program((uint16_T *)EEPROM_FlashAddress, (uint16_T *)EEPROM_StartAddress, EEPROM_Size);
		EINT;

	}

}


