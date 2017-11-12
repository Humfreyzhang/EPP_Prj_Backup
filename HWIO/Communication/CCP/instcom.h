#ifndef INSTCOM_H
#define INSTCOM_H
#include "rtwtypes.h"
#include "DSP2803x_Device.h"

/* ============================================================================ *\
 * Exported preprocessor #define commands.
\* ============================================================================ */

#define NUMBER_OF_INST_COMMAND_BYTES           8

#define PC_MDS 0x0000
#define GEN3RCV 0x0001
#define MONFLR 0x0002

#define PACKET_ID_CODE 0xFF
#define EVENT_MESSAGE  0xfe

/* This is used for clearing memory and CAN messages. */
#define CLEAR_DATA 0x00

/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */

typedef enum
{
   NO_ERROR                =       0x00, /* ACKNOWLEDGE_NO_ERROR */
   COMMAND_PROCESSOR_BUSY =        0x10,
   DAQ_PROCESSOR_BUSY =            0x11,
   FUNC_NOTSUPPORT_INVALIDFORMAT = 0x12,
   KEY_REQUEST =                   0x18,
   SESSION_STATUS_REQUEST =        0x19,
   COLD_START_REQUEST =            0x20,
   CAL_DATA_INIT_REQUEST =         0x21,
   DAQ_LIST_INIT_REQUEST =         0x22,
   CODE_UPDATE_REQUEST =           0x23,
   UNKNOWN_COMMAND =               0x30,
   COMMAND_SYNTAX =                0x31,
   PARAMETERS_OUT_OF_RANGE=        0x32,
   ACCESS_DENIED =                 0x33,
   OVERLOAD =                      0x34,
   ACCESS_LOCKED =                 0x35,
   FUNCTION_NOT_AVAILABLE =        0x36,
   FLASH_CHECKSUM_ERROR          = 0x70,
   EEPROM_CHECKSUM_ERROR         = 0x71,
   MESSAGE_SEQUENCE_ERROR        = 0x72,
   FLASH_WRITE_FAILURE           = 0x80,
   FLASH_ERASE_FAILURE           = 0x81,
   EEPROM_WRITE_FAILURE          = 0x82,
   INVALID_DAQ_REFERENCE         = 0x91,
   END_OF_DAQ_LIST               = 0x92,
   INVALID_MTA_NUMBER            = 0x93,
   INVALID_MEMORY_PAGE           = 0x94,
   INVALID_ADDRESS               = 0x95,
   ADDRESS_AND_PAGE_MISMATCH     = 0x96,
   ILLEGAL_ADDRESS               = 0x97,
   ILLEGAL_EEPROM_ADDRESS        = 0x98,
   ILLEGAL_FLASH_ADDRESS         = 0x99,
   ILLEGAL_UNPAGED_FLASH_ADDRESS = 0x9A,
   INVALID_SIZE                  = 0x9B,
   CMD_FIFO_FULL                 = 0x9C,
   INVALID_MESSAGE               = 0x9D,
   CONDITION_NOT_MET             = 0x9E

}command_return_code_T;

typedef enum
{
   ERASE_FLASH_MEMORY_ACTION_SERVICE = 0,
   END_OF_PROGRAMM_DOWNLOAD_ACTION_SERVICE = 1,
   PROGRAM_EEPROM_ACTION_SERVICE = 2,
   END_PROGRAM_EEPROM_ACTION_SERVICE = 3,
   EXECUTE_ACTION_SERVICE = 4,
   RESET_ECM_ACTION_SERVICE = 5,
   ECU_REPROGRAM_REQUEST = 7,
   SET_RAM_OVERLAY = 0x15,
   GET_RAM_OVERLAY = 0x16,
   GET_DEV_FLASH_COPY_OVERLAY_STATUS = 0x16FB,
   PROD_INST_COPY = 0x15FC
}action_service_number_T;

typedef struct
{
   uint16_T packet_ID:8;
   uint16_T data[3];
} data_acquisition_T;

typedef struct
{
#if BigEnd == 0
   uint16_T parameters1:16;
   uint16_T command_counter:8;
   uint16_T command_code:8;
   uint16_T parameters[ 2 ];
#else
   uint16_T command_code:8;
   uint16_T command_counter:8;
   uint16_T parameters[ 3 ];
#endif

} received_command_message_T;

typedef struct
{
   uint16_T command_code:8;
   uint16_T command_counter:8;
   uint16_T data_block_size:8;
   uint32_T program_data:32;
}program_message_T;

typedef struct
{
   uint16_T  command_code:8;
   uint16_T  command_counter:8;
   uint16_T action_service_number:16;
   uint16_T  unused_1:8;
   uint16_T	mem_page:8;
   uint16_T address_16Bit:16;
}action_service_message_T;

typedef struct
{
   uint16_T command_code:8;
   uint16_T command_counter:8;
   uint16_T program_data[3];
}program6_message_T;

typedef struct
{
#if BigEnd == 0
   uint16_T station_address:16;
   uint16_T command_counter:8;
   uint16_T command_code:8;
   uint32_T parameters:32;
#else
   uint16_T command_code:8;
   uint16_T command_counter:8;
   uint16_T station_address:16;
   uint32_T parameters:32;
#endif
} connect_command_T;

typedef struct
{
   uint16_T     command_code:8;
   uint16_T     counter:8;
   uint16_T     MTA_number:8;
   uint16_T     memory_page:8;
   uint32_T     *address_ptr;
}set_MTA_message_T;


typedef struct
{
#if BigEnd ==0
   uint16_T memory_page:8;
   uint16_T length:8;
   uint16_T error:8;
   uint16_T ID:8;
   uint32_T address_location:32;
#else
	uint16_T ID:8;
	uint16_T error:8;
	uint16_T length:8;
	uint16_T memory_page:8;
	uint32_T address_location:32;
#endif
} CAN_message_T;

typedef struct
{
   uint16_T Byte0:8;
   uint16_T Byte1:8;
   uint16_T Byte2:8;
   uint16_T Byte3:8;
   uint16_T Byte4:8;
   uint16_T Byte5:8;
   uint16_T Byte6:8;
   uint16_T Byte7:8;
} DAQ_Msg_T;

typedef struct
{
   uint16_T unused_1:16;
   uint16_T number:8;
   uint16_T unused_2;
} MTA_number_T;

typedef struct
{
   uint16_T unused_1:16;
   uint16_T number_of_bytes_Low:16;
   uint16_T number_of_bytes_High:16;
   uint16_T unused_2:16;
} CAN_checksum_T;

typedef struct
{
   uint16_T unused_1:16;
   uint16_T unused_2:8;
   uint16_T length:8;
   uint32_T size:32;
} return_checksum_T;

typedef struct
{
   uint16_T unused_1:16;
   uint16_T number:8;
   uint16_T number_of_ODTs:8;
   uint16_T first_ODT:8;
   uint16_T unused_2:8;
   uint16_T message_ID:16;
} DAQ_number_T;

typedef struct
{
   uint16_T unused_1:16;
   uint32_T mem_size:32;
   uint16_T unused_2:16;
} move_command_T;

 
typedef struct
{
   uint16_T unused_1:16;
   uint16_T status:8;
   uint16_T DAQ_number:8;
   uint16_T last_ODT:8;
   uint16_T event_channel_ID:8;
   uint16_T transmit_rate:16;
} start_stop_message_T;

typedef struct
{
   uint16_T unused_1:16;
   uint16_T unused_2:8;
   uint16_T protection:8;
   uint32_T unused_3:32;
} seed_protection_T;

typedef struct
{
   uint16_T unused_1:16;
   uint16_T unused_2:8;
   uint16_T privilege_level:8;
   uint16_T ID:16;
   uint16_T unused_3:16;
} ECU_status_T;

typedef struct
{
   uint16_T unused_1:16;
   uint16_T receive_status:8;
   uint16_T send_status:8;
   uint16_T additional_information:8;
   uint16_T DAQ_number:8;
   uint16_T unused_2:16;
} session_status_T;

typedef struct
{
   uint16_T partition_PID:8;
   uint16_T operation:8;
   uint16_T PID:8;
   uint16_T parameter_data:8;
   uint32_T unused:32;
} parameter_data_T;

typedef struct
{
   uint16_T command_code:8;
   uint16_T command_counter:8;
   uint16_T data_block_size:8;
}upload_command_T;

typedef struct
{
   uint16_T  command_code:8;
   uint16_T  command_counter:8;
   uint16_T  data_block_size:8;
   uint16_T  memory_page:8;
   uint16_T unused:16;
   uint16_T  *memory_address_ptr;
}short_upload_command_T;

typedef struct
{
#if BigEnd == 0
   uint16_T			MTA0_extension:8;
   uint16_T            echo_command_counter:8;
   command_return_code_T  command_return_code:8;
   uint16_T            packet_ID:8;
   uint16_T            *new_MTA_address_ptr;
   uint16_T            new_MTA_memory_page:8;
   uint16_T            unused:8;
#else
	uint16_T			packet_ID:8;
	command_return_code_T  command_return_code:8;
	uint16_T			echo_command_counter:8;
	uint16_T		 MTA0_extension:8;
	uint16_T			unused:8;
	uint16_T			new_MTA_memory_page:8;
	uint16_T			*new_MTA_address_ptr;
#endif
} command_return_message_T;

typedef struct
{
   uint16_T            packet_ID;
   command_return_code_T  command_return_code;
   uint16_T            command_counter;
   uint16_T            upload_data[5];
}upload_return_T;

typedef struct
{
   uint16_T  packet_ID;
   uint16_T  inst_error;
   uint16_T  echo_command_counter;
   uint16_T  last_valid_command_counter;
   uint16_T  data[4];
}event_message_T;

typedef union
{
   command_return_message_T command_return_message;
   event_message_T          event_message;
   upload_return_T          upload_return;
}inst_response_T;

typedef struct
{
   uint16_T            packet_ID:8;
   command_return_code_T  command_return_code:8;
   uint16_T            command_counter:8;
   uint16_T            ccp_version_main:8;
   uint16_T            ccp_version_release:8;
   uint32_T            unused_1:24;
}ccp_version_return_T;


typedef union
{
   uint16_T                   data_byte[ 4 ];
   DAQ_Msg_T                  Daq_msg;
   CAN_message_T              message;
   MTA_number_T               MTA;
   CAN_checksum_T             checksum;
   return_checksum_T          return_checksum;
   DAQ_number_T               DAQ;
   start_stop_message_T       start_stop;
   seed_protection_T          seed;
   ECU_status_T               ECU;
   session_status_T           session_status;
   parameter_data_T           parameter_data;
   data_acquisition_T         data_acquisition_message;
   received_command_message_T received_command_message;
   connect_command_T          connect;
   set_MTA_message_T          set_MTA_message;
   program_message_T          program_message;
   program6_message_T         program6_message;
   command_return_message_T   command_return_message;
   upload_command_T           upload_command;
   move_command_T             move_command;
   action_service_message_T   action_service_message;
   short_upload_command_T     short_upload_command;
   ccp_version_return_T       ccp_version;
} inst_command_T;


typedef command_return_code_T inst_error_T;

/* ============================================================================ *\
 * Exported INLINE functions and #define function-like macros.
\* ============================================================================ */

/*.**************************************************************************
*.  Name: Inst_Command_Msg_ID_V MACRO
*.    This macro returns the value of Inst_Command_Msg_ID_V
*.    Used as the message ID the test equipment sends to request
*.    instrumentation commands/info
*****************************************************************************/
extern uint16_T Inst_Command_Msg_ID_V; /* Private use Macro */
#define Inst_Command_Msg_ID() (Inst_Command_Msg_ID_V)

/*.**************************************************************************
*.  Name: Inst_Response_Msg_ID_V MACRO
*.    This macro returns the value of Inst_Response_Msg_ID_V
*.    Used as the message ID the embedded system uses to respond to
*.    instrumentation requests
*****************************************************************************/
extern uint16_T Inst_Response_Msg_ID_V; /* Private use Macro */
#define Inst_Response_Msg_ID() (Inst_Response_Msg_ID_V)

/* ============================================================================ *\
 * Exported Function prototypes
 * ============================================================================ */

/* ============================================================================ *\
 * FUNCTION: Output_To_Com
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   message_number
 *   inst_response_ptr
 *
 * EXTERNAL REFERENCES:
 *   none
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * This function sends the CAN message response to the master.
 *
\* ============================================================================ */
void Output_To_Com( uint16_T  CAN_xmit_message_ID,
                    inst_command_T* inst_response_ptr );
/* ============================================================================ *\
 * FUNCTION: Input_From_Com
 * ============================================================================
 * RETURN VALUE:
 *   true: if message received
 *   false: if no message received.
 *
 * PARAMETERS:
 *   inst_command_ptr
 *
 * EXTERNAL REFERENCES:
 *   none
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * This function receive the Command Return Object (CRO) CAN message.
 *
\* ============================================================================ */
extern void Input_From_Com(uint16_T *destbuffer, uint16_T *source_buffer);

/* ============================================================================ *\
 * FUNCTION: Inst_Com_Reset_Init
 * ============================================================================
 * RETURN VALUE:
 *   none
 *
 * PARAMETERS:
 *   none
 *
 * EXTERNAL REFERENCES:
 *   none
 *
 * Shared Variables: Inst_Command_Msg_ID_V, Inst_Response_Msg_ID_V
 *
 * ----------------------------------------------------------------------------
 * ABSTRACT:
 * ----------------------------------------------------------------------------
 * This function initialize the instrumentation communication variables
 *
\* ============================================================================ */
void Inst_Com_Reset_Init( void );


#endif

