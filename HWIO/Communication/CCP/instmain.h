#ifndef INSTMAIN_H
#define INSTMAIN_H

#include "instcom.h"
#include "instdaq.h"

#define CCP_Command_CAN_MailBox  (MailBox21)

typedef enum
{
   CONNECT_CODE         = 0x01,
   SET_MTA_CODE         = 0x02,
   DNLOAD_CODE          = 0x03,
   UPLOAD_CODE          = 0x04,
   START_STOP_CODE      = 0x06,
   DISCONNECT_CODE      = 0x07,
   SET_S_STATUS_CODE    = 0x0C,
   GET_S_STATUS_CODE    = 0x0D,
   BUILD_CHKSUM_CODE    = 0x0E,
   SHORT_UP_CODE        = 0x0F,
   CLEAR_MEMORY_CODE    = 0x10,
   SELECT_CAL_PAGE_CODE = 0x11,
   GET_SEED_CODE        = 0x12,
   UNLOCK_CODE          = 0x13,
   GET_DAQ_SIZE_CODE    = 0x14,
   SET_DAQ_PTR_CODE     = 0x15,
   WRITE_DAQ_CODE       = 0x16,
   EXCHANGE_ID_CODE     = 0x17,
   PROGRAM_CODE         = 0x18,
   MOVE_CODE       		= 0x19,
   GET_CCP_VERSION      = 0x1B,  /*G ADDED FOR ETAS G*/
   ACTION_SERVICE_CODE  = 0x21,
   PROGRAM_6_CODE       = 0x22,
   DNLOAD_6_CODE        = 0x23,
   INVALID_COMMAND_CODE = 0xFE,
   SEND_2_DSP_CODE      = 0xFF /* Defined in Communications Design */
} command_code_T;


void inst_resetkeyon(void);
void Instrumentation_Update(void);
inst_error_T Check_If_Time_To_Transmit_DAQ_Lists( Event_Channel_Number_T  event_channel_no);


#endif
