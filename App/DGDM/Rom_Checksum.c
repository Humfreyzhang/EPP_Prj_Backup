
#include "Rom_checksum.h"
#include "interface_file.h"
#include "DSP2803x_function.h"

uint8_T ROM_Cal_Finished;
uint16_T ROM_Checksum;
uint16_T *Rom_Address_Ptr;

void Rom_Checksum_init(void)
{
	ROM_Cal_Finished = false;
	ROM_Checksum  = 0x0000;
	Rom_Address_Ptr = APP_ROM_StartAddress;

}


void Rom_Checksum_cal_10ms(void)
{

	if(ROM_Cal_Finished == false)
	{
		ROM_Checksum += Checksum(Rom_Address_Ptr, ROM_OneSection);
		Rom_Address_Ptr += ROM_OneSection;
	}

	if(Rom_Address_Ptr >= APP_ROM_EndAddress )
	{
		ROM_Cal_Finished = true;
		Rom_Address_Ptr = APP_ROM_StartAddress;
		if(ROM_Checksum != 0)
		{
			File_Diag.APP_CksumErr = 1;
		}
	}

}
