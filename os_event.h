#ifndef OS_EVENT_H
#define OS_EVENT_H

/** @file os_event.h Event header file*/

#include "cocoos.h"
#include "stdarg.h"


/*********************************************************************************/
/*  OS_WAIT_SINGLE_EVENT(pEvent)                                                 *//**
*   
*   Macro for wait for a single event.
*
*		@param pEvent Pointer to an event.
*
*		@remarks \b Usage: @n 
* @code 
os_event_type* myEvent;
main() {
 ...
 myEvent = os_create_event();
 ...
}

static int myTask(void) {
 OS_BEGIN;	
  ...
  OS_WAIT_SINGLE_EVENT( myEvent );
  ...
 OS_END;
 return 0;
}
 @endcode 
 *******************************************************************************/
#define OS_WAIT_SINGLE_EVENT(pEvent) OS_WAIT_SINGLE_EVENT_(pEvent)
#define OS_WAIT_SINGLE_EVENT_(x)	do {\
								os_wait_event(running_tid,x,1);\
								OS_SCHEDULE;\
							   } while (0)




/*********************************************************************************/
/*  OS_WAIT_MULTIPLE_EVENTS(waitAll, args...)                                                 *//**
*   
*   Macro for wait for multiple events.
*
*		@param waitAll 1 if wait for all, 0 if wait for any event
*       @param args... list of os_event_type pointers
*
*		@remarks \b Usage: @n 
* @code 
os_event_type* myEvent1;
os_event_type* myEvent2;
os_event_type* myEvent3;
main() {
 ...
 myEvent1 = os_create_event();
 myEvent2 = os_create_event();
 myEvent3 = os_create_event();
 ...
}

static int myTask(void) {
 OS_BEGIN;	
  ...
  OS_WAIT_MULTIPLE_EVENTS(1, myEvent1, myEvent2, myEvent3);
  ...
 OS_END;
 return 0;
}
 @endcode 
 *******************************************************************************/
#define OS_WAIT_MULTIPLE_EVENTS( waitAll, args...) OS_WAIT_MULTIPLE_EVENTS_( waitAll, args...)
#define OS_WAIT_MULTIPLE_EVENTS_( waitAll, args...)	do {\
								os_wait_multiple(waitAll, args, 0);\
								OS_SCHEDULE;\
							   } while (0)




/*********************************************************************************/
/*  OS_SIGNAL_EVENT(pEvent)                                                 *//**
*   
*   Macro for signalling an event.
*
*		@param pEvent Pointer to an event.
*       
*
*		@remarks \b Usage: @n 
* @code 
os_event_type* myEvent;
main() {
 ...
 myEvent = os_create_event();
 ...
}

static int myTask(void) {
 OS_BEGIN;	
  ...
  OS_SIGNAL_EVENT( myEvent );
  ...
 OS_END;
 return 0;
}
 @endcode 
 *******************************************************************************/
#define OS_SIGNAL_EVENT(pEvent) OS_SIGNAL_EVENT_(pEvent)
#define OS_SIGNAL_EVENT_(pEvent)	do {\
								os_signal_event(pEvent);\
								os_event_set_signaling_tid( pEvent, running_tid );\
								OS_SCHEDULE;\
								} while (0)



/*********************************************************************************/
/*  OS_INT_SIGNAL_EVENT(pEvent)                                                 *//**
*   
*   Macro for signalling an event from an ISR
*
*		@param pEvent Pointer to an event.
*       
*
*		@remarks \b Usage: @n 
* @code 
os_event_type* myEvent;
main() {
 ...
 evRxChar = os_create_event();
 ...
}

ISR (SIG_UART_RECV)
{
	rx.data[ rx.head ] = UDR;
	OS_INT_SIGNAL_EVENT( evRxChar );
	
}
 @endcode 
 *******************************************************************************/
#define OS_INT_SIGNAL_EVENT(pEvent) OS_INT_SIGNAL_EVENT_(pEvent)
#define OS_INT_SIGNAL_EVENT_(pEvent)	do {\
									os_signal_event(pEvent);\
									} while (0)


typedef struct event os_event_type;



os_event_type* os_create_event( void );
void os_wait_event( uint8_t tid, os_event_type *ev, uint8_t waitSingleEvent );
void os_wait_multiple( uint8_t waitAll, ...);
void os_signal_event( os_event_type *ev );
void os_event_set_signaling_tid( os_event_type *ev, uint8_t tid );
uint8_t os_event_get_signaling_tid( os_event_type *ev );


#endif
