#ifndef OS_TASK_H__
#define OS_TASK_H__

/** @file os_task.h Task header file*/

#include "os_defines.h"

typedef struct tcb tcb;

void os_task_create( taskproctype taskproc, uint8_t prio );
uint8_t os_task_highest_prio_ready_task( void );
void os_task_ready_set( uint8_t tid );
void os_task_pending_set( uint8_t tid );
uint8_t os_task_prio_get( uint8_t tid );
taskproctype os_task_taskproc_get( uint8_t tid );
void os_task_clear_wait_queue( uint8_t tid );
void os_task_wait_time_set( uint8_t tid, uint16_t time );
void os_task_wait_event( uint8_t tid, uint8_t eventId, uint8_t waitSingleEvent );
void os_task_tick( void );
void os_task_signal_event( uint8_t evId );




#endif
