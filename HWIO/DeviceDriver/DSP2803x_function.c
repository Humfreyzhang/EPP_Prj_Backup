
#include "rtwtypes.h"
#include "DSP2803x_Device.h"
#include "DSP2803x_function.h"

#define Ram1_StartAddress  (0x258)
#define Ram1_Size         (0x5A8)

#define Ram2_StartAddress  (0x8000)
#define Ram2_Size         (0x2000)

#define Ram3_StartAddress  (0x1480)
#define Ram3_Size         (0x100)

uint16_T Checksum(uint16_T *Source, uint16_T Sizes)
{
	uint16_T index, checksum;

	checksum =0;
	for(index =0; index < Sizes; index ++)
	{
		checksum += *Source++;
	}

	return (checksum);
}


void Copydata(uint16_T *Dest, uint16_T *Source, uint16_T Sizes )
{
	uint16_T index;
	for(index =0; index < Sizes; index ++)
	{
		*Dest ++ = *Source ++;
	}
}

void Ramclear(void)
{
	uint8_T *Address_Start, size;

	size = 0;
	for(Address_Start = Ram1_StartAddress; size < Ram1_Size; size++)
	{
		*Address_Start++ = 0;
	}
	
	size = 0;
	for(Address_Start = Ram2_StartAddress; size < Ram2_Size; size++)
	{
		*Address_Start++ = 0;
	}
	
	size = 0;
	for(Address_Start = Ram3_StartAddress; size < Ram3_Size; size++)
	{
		*Address_Start++ = 0;
	}

}

 void CopyMemory_With_SourceByte(uint16_T *Dest, uint16_T *Source, uint8_T MSB_Dest, uint16_T Sizes)
{

	uint16_T index;
	uint16_T mod;
	uint8_T odd;

	mod = (uint16_T)(Sizes/2);
	odd = Sizes - mod*2;
	
	for(index=0; index < mod; index ++)
	{
		__byte(Dest,index*2 + MSB_Dest) = *Source++;
		__byte(Dest,index*2 +1 + MSB_Dest) =  *Source++;
	}

	if(odd == 1)
	{
		__byte(Dest,index*2 + MSB_Dest) = *Source++;
	}

}

 void CopyMemory_With_DestByte(uint16_T *Dest, uint16_T *Source, uint8_T MSB_Source, uint16_T Sizes)
{

	uint16_T index;
	uint16_T mod;
	uint8_T odd;

	mod = (uint16_T)(Sizes/2);
	odd = Sizes - mod*2;
	
	for(index=0; index < mod; index ++)
	{
		*Dest = __byte(Source, index*2 + MSB_Source);
		Dest++;
		*Dest =  __byte(Source, index*2 +1 + MSB_Source);
		Dest++;
	}

	if(odd == 1)
	{
		*Dest++ = __byte(Source,index*2 + MSB_Source);	
	}

}
  
 void CopyMemory_WithNone_Byte(uint16_T *Dest, uint16_T *Source, uint8_T MSB_Dest, uint8_T MSB_Source, uint16_T Sizes)
{

	uint16_T index;
	uint16_T mod;
	uint8_T odd;

	mod = (uint16_T)(Sizes/2);
	odd = Sizes - mod*2;
	
	for(index=0; index < mod; index ++)
	{
		__byte(Dest,index*2 + MSB_Dest) = __byte(Source, index*2 + MSB_Source);
		__byte(Dest,index*2 +1 + MSB_Dest) =  __byte(Source, index*2 +1 + MSB_Source);
	}

	if(odd == 1)
	{
		__byte(Dest,index*2 + MSB_Dest) = __byte(Source,index*2 + MSB_Source);	
	}

}

/************************************************************************************************/
/* After_Address -------- after copy the data where the source address shloud be here
   Odd_Next -------- after copy the data the source address should be at the MSB or LSB of a word
*************************************************************************************************/
 void CopyMemory_Byte(uint16_T *Dest, uint16_T *Source, uint8_T MSB_Dest, uint8_T MSB_Source, uint16_T Sizes, uint16_T *After_Address, uint8_T *Odd_Next)
{

	uint16_T index;
	uint16_T mod;
	uint8_T odd;

	mod = (uint16_T)(Sizes/2);
	odd = Sizes - mod*2;
	
	for(index=0; index < mod; index ++)
	{
		__byte(Dest,index*2 + MSB_Dest) = __byte(Source, index*2 + MSB_Source);
		__byte(Dest,index*2 +1 + MSB_Dest) =  __byte(Source, index*2 +1 + MSB_Source);
	}

	*After_Address = Source + mod + odd*MSB_Source;
	if(odd == 1)
	{
		__byte(Dest,index*2 + MSB_Dest) = __byte(Source,index*2 + MSB_Source);

	}
	*Odd_Next = odd ^ MSB_Source;
}

void Delay_us(uint16_T us)
{
	uint32_T CPUtimer, timer;

	CPUtimer = CpuTimer2Regs.TIM.all;
	do{
	timer = CpuTimer2Regs.TIM.all;
	}while((uint32_T)(timer - CPUtimer) < us );
}
