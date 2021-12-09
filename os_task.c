/*
***************************************************************************************
***************************************************************************************
***
***     File: os_task.c
***
***     Project: cocoOS
***
***     Author: Peter Eckstrand
***
***************************************************************************************
***************************************************************************************


    Version: 1.0.0

    Change log:
    2009-07-06: 1.0.0 First release


***************************************************************************************
*/


#include "cocoos.h"
#include "os_defines.h"
#include <stdlib.h>

typedef enum {
    RUNNING,
    WAITING_TIME,
    WAITING_EVENT,
    READY,
    PENDING
} TaskState_t;


struct tcb {
    uint8_t tid;
    uint8_t prio;
    TaskState_t state;
    uint8_t eventQueue;
    uint8_t waitSingleEvent;
    uint16_t time;
    taskproctype taskproc;
};

static tcb* task_list[ MAX_TASKS ];
static uint8_t nTasks = 0;


/*********************************************************************************/
/*  void os_task_create()                                              *//**
*   
*   Creates a task scheduled by the os. The task is put in the ready state.
*
*		@param taskproc Pointer to the task procedure.
*
*		@param prio Task priority on a scale 0-255 where 0 is the highest priority.
*
*		@return None.
*
*		@remarks \b Usage: @n Should be called early in system setup, before starting the task 
*       execution
*	
*		
*       @code
int main(void) {
	system_init();
	os_init();
	os_create_task( myTaskProc, 1 );
	...
}
*		@endcode
*       
*/
/*********************************************************************************/
void os_task_create( taskproctype taskproc, uint8_t prio ) {
    tcb *task = (tcb*)malloc( sizeof(tcb) );
    task->tid = nTasks;
    task->prio = prio;
    task->state = READY;
    task->eventQueue = 0;
    task->waitSingleEvent = 0;
    task->time = 0;
    task->taskproc = taskproc;
    task_list[ nTasks ] = task;
    nTasks++;
}


uint8_t os_task_highest_prio_ready_task( void ) {
    uint8_t index;
    uint8_t highest_prio_task = NO_TID;
    uint8_t highest_prio = 255;
    disable_interrupts();
    
    for ( index = 0; index != nTasks; ++index ) {
	    if ( task_list[ index ]->state == READY ) {
            if ( task_list[ index ]->prio < highest_prio ) {
                highest_prio = task_list[ index ]->prio;
                highest_prio_task = index;
            }
        }
    }
	
	enable_interrupts();
    return highest_prio_task;
}

void os_task_ready_set( uint8_t tid ) {
    task_list[ tid ]->state = READY;
}

void os_task_pending_set( uint8_t tid ) {
    task_list[ tid ]->state = PENDING;
}


uint8_t os_task_prio_get( uint8_t tid ) {
    return task_list[ tid ]->prio;
}


taskproctype os_task_taskproc_get( uint8_t tid ) {
    return task_list[ tid ]->taskproc;
}




void os_task_clear_wait_queue( uint8_t tid ) {
    task_list[ tid ]->waitSingleEvent = 0;
    task_list[ tid ]->eventQueue = 0;
    if ( task_list[ tid ]->state == WAITING_EVENT ) {
        task_list[ tid ]->state = READY;
    }
}


void os_task_wait_time_set( uint8_t tid, uint16_t time ) {
    task_list[ tid ]->time = time;
    task_list[ tid ]->state = WAITING_TIME;
}

void os_task_wait_event( uint8_t tid, uint8_t eventId, uint8_t waitSingleEvent ) {
    task_list[ tid ]->eventQueue |= eventId;
    task_list[ tid ]->waitSingleEvent = waitSingleEvent;
    task_list[ tid ]->state = WAITING_EVENT;
}




void os_task_tick( void ) {
    uint8_t index;

    /* Search all tasks and decrement time for waiting tasks */
    for ( index = 0; index != nTasks; ++index ) {
		if ( task_list[ index ]->state == WAITING_TIME ) {

            /* Found a waiting task, is it ready? */
            if ( --task_list[ index ]->time == 0) {
			    task_list[ index ]->state = READY;	
			}
		}
	}
}

void os_task_signal_event( uint8_t evId ) {
    uint8_t index;
    uint8_t taskWaitingForEvent;

    for ( index = 0; index != nTasks; index++ ) {

        taskWaitingForEvent = task_list[ index ]->eventQueue & evId;
        
        if ( taskWaitingForEvent ) {
            
            task_list[ index ]->eventQueue &= ~evId;
            
            if ( task_list[ index ]->waitSingleEvent || ( task_list[ index ]->eventQueue == 0 ) ) {
                os_task_clear_wait_queue( index );
            }
        }
    }
}
