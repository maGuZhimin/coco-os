/*
***************************************************************************************
***************************************************************************************
***
***     File: os_lists.c
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

#include <inttypes.h>
#include <interrupt.h>
#include "cocoos.h"


/* list_add(): Adds the tid to the list. It is assumed that the tid is not
in the list already */
void list_add(uint8_t tid,uint8_t *list) {
	uint8_t index = 0;
	disable_interrupts();

	/* Find an empty position in list */
	for ( index = 0; index < MAX_TASKS; ++index ) {
		if ( list[ index ] == NO_TID ) {
			list[ index ] = tid;
			break;
		}
	}
	
   enable_interrupts();
}


void list_remove(uint8_t tid,uint8_t *list) {
	uint8_t index;
	disable_interrupts();
	for (index=0;index<MAX_TASKS;index++)
	{
		if (list[index]==tid)
			list[index]=NO_TID;
		
	}
	enable_interrupts();
}


uint8_t list_tid_in_list( uint8_t tid, uint8_t *list) {
	uint8_t index;
	for ( index = 0; index < MAX_TASKS; ++index ) {
		if ( list[ index ] == tid ) {
			return 1;
		}
	}
	return 0;
}


uint8_t list_is_empty(uint8_t *list) {
   uint8_t index;
   uint8_t nr_empty=0;
   for (index=0;index<MAX_TASKS;index++)
      if (list[index]==NO_TID)
	     nr_empty++;
   if (nr_empty==MAX_TASKS)
      return 1;
   else
      return 0;
}

void list_move_highest_prio_to_ready(uint8_t *list) {
	uint8_t highest_prio=255;
	uint8_t index;
	uint8_t tid = 0;
    uint8_t taskPrio = 0;
	for (index=0;index<MAX_TASKS;index++) {
		if (list[index]!=NO_TID) {
            taskPrio = os_task_prio_get( list[ index ] );
			if ( taskPrio < highest_prio ) {
				tid = list[ index ];
				highest_prio = taskPrio;
			}
		}
	}

	if (highest_prio != 255) {
		list_remove(tid,list);
        os_task_ready_set( tid );
	}
}


