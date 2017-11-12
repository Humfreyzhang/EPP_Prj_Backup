#ifndef INSTMODE_H
#define INSTMODE_H

#include "rtwtypes.h"
#include "instmain.h" /* Needed for error messages. */
// #include "instmem.h"  /* Uses Move_MTA. */
#include "instcom.h"  /* Uses Output_To_Com. */

/* ============================================================================ *\
 * Exported preprocessor #define commands.
\* ============================================================================ */

#define NO_INSTRUMENTATION_APPLICATIONS_PRESENT 0
#define INITIAL_SESSION_STATUS_STATE 0

#define MTA0_POINTER 0
#define OUT_OF_PAGED_FLASH (0xfd)


/* ============================================================================ *\
 * Exported type declarations.
\* ============================================================================ */

typedef enum
{
   INST_ONLINE = 1,
   INST_OFFLINE = 0
} instrumentation_mode_states_T;

typedef enum
{
   NO_DISCONNECT_REQUEST = 0x00,
   DISCONNECT_REQUEST = 0x01
} disconnect_states_T;

typedef struct
{
   instrumentation_mode_states_T instrumentation_mode;
   disconnect_states_T disconnect_request_status;
   uint8_T enter_instrumentation_mode_counter;
   uint8_T session_status;
} instrumentation_status_T;

/* ============================================================================ *\
 * Exported variables.
\* ============================================================================ */

extern instrumentation_status_T instrumentation_status;

#endif

