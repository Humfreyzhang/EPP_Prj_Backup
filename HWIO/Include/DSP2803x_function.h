#ifndef DSP2803X_FUNCTION_H
#define DSP2803X_FUNCTION_H

#define MSB  (1)
#define LSB  (0)

#define Get_Byte(s, msb) (__byte(s,msb))
#define Set_Byte(s, msb, value) (__byte(s,msb) = value)

extern void Copydata(uint16_T *Dest, uint16_T *Source, uint16_T Sizes );
extern void Ramclear(void);
void CopyMemory_WithNone_Byte(uint16_T *Dest, uint16_T *Source, uint8_T MSB_Dest, uint8_T MSB_Source, uint16_T Sizes);
void CopyMemory_Byte(uint16_T *Dest, uint16_T *Source, uint8_T MSB_Dest, uint8_T MSB_Source, uint16_T Sizes, uint16_T *After_Address, uint8_T *Odd_Next);
void Delay_us(uint16_T us);
void CopyMemory_With_SourceByte(uint16_T *Dest, uint16_T *Source, uint8_T MSB_Dest, uint16_T Sizes);
void CopyMemory_With_DestByte(uint16_T *Dest, uint16_T *Source, uint8_T MSB_Source, uint16_T Sizes);
extern uint16_T Checksum(uint16_T *Source, uint16_T Sizes);




#endif

