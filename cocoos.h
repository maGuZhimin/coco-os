#ifndef COCOOS_H
#define COCOOS_H

/** @file cocoos.h cocoOS kernel header file*/

#include <inttypes.h>
#include "os_defines.h"
#include "os_event.h"
#include "os_lists.h"
#include "os_sem.h"
#include "os_task.h"


#define OS_BEGIN            static uint8_t state = 0; switch ( state ) { case 0:
#define OS_END	            state = 0; }
#define OS_SCHEDULE         running_tid = NO_TID;\
					        state = __LINE__;\
					        return 0;\
					        case __LINE__:


/*********************************************************************************/
/*  OS_WAIT_TICKS(x)                                                 *//**
*   
*   Macro for suspending a task a specified amount of ticks.
*
*		@param x Number of ticks to wait.
*
*		@remarks \b Usage: @n 
* @code 


static int myTask(void) {
 OS_BEGIN;	
  ...
  OS_WAIT_TICKS( 10 );
  ...
 OS_END;
 return 0;
}
 @endcode 
 *******************************************************************************/
#define OS_WAIT_TICKS(x)    OS_WAIT_TICKS_(x)
#define OS_WAIT_TICKS_(x)	do {\
								os_task_wait_time_set( running_tid, x );\
								OS_SCHEDULE;\
						   	   } while ( 0 )


#define OS_GET_TID()        running_tid

uint8_t running_tid;
void os_init( void );
void os_start( void );
void os_tick( void );

#endif
