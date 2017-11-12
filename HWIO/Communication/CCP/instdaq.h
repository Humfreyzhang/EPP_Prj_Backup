#ifndef INSTDAQ_H
#define INSTDAQ_H
#include "rtwtypes.h"
#include "instcom.h"

#define CCP_2_0                    0
#define CCP_2_1                    1
#define CCP_PROTOCOL               CCP_2_1
/* #defines for the 'dimensions' of the DAQs */
#define NUMBER_OF_SMALL_DAQ_LISTS 3
#define NUMBER_OF_DAQ_LISTS ( NUMBER_OF_SMALL_DAQ_LISTS )
#define LARGE_DAQ_LIST_INDEX 3

#define SIZES_Byte      (1)
#define SIZES_Word      (2)
#define SIZES_DWord     (4)
/* this enumerated type defines the possible trigger states */
typedef enum trigger_code_status_tag
{
   ITS_TRIGGER = 0x00,
   SINGLE_TRANSMISSION = 0x01,
   PATH_TRIGGER = 0x02,
   TRACK_TRIGGER = 0x03,
   FFT_TRIGGER = 0x04,
   IF_TRIGGER = 0x05,
   DATA_CAPTURE_TRIGGER = 0x06,
   NO_TRIGGER_CODE = 0xFF
} trigger_code_status_T;

typedef enum
{
   EVENT_1MSEC_LOOP = 0x00,
   EVENT_10MSEC_LOOP = 0x01,
   EVENT_100MSEC_LOOP = 0x02
} Event_Channel_Number_T;


typedef struct
{
   uint16_T message_id:8;
   //uint16_T message_number:8;
   //uint16_T transmit_rate:8;
   uint16_T transmit_enable:8;
   uint16_T last_ODT_to_transmit:8;
   //trigger_code_status_T trigger_code:8;
   Event_Channel_Number_T event_channel_ID:8;
} DAQ_list_status_T;

typedef enum
{
   FAST_AS_POSSIBLE = 0x00,
   EVENT_DRIVEN = 0xFF
} trigger_code_states_T;

typedef enum
{
   MESSAGE_ID_NOT_SET = 0x00
} DAQ_list_status_states_T;



#define DAQ_Transmit_Event_Channel( DAQ_number ) \
   DAQ_List_Status[ ( DAQ_number ) ].event_channel_ID

#define DAQ_Transmit_Enable( DAQ_number ) \
   DAQ_List_Status[ ( DAQ_number ) ].transmit_enable

//#define DAQ_Transmit_Rate( DAQ_number ) \
//   DAQ_List_Status[ ( DAQ_number ) ].transmit_rate

//#define DAQ_Trigger_Code( DAQ_number ) \
//   DAQ_List_Status[ ( DAQ_number ) ].trigger_code
   
#endif
