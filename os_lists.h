#ifndef OS_LISTS_H
#define OS_LISTS_H

#include "os_defines.h"


void list_add(uint8_t tid,uint8_t *list);
void list_remove(uint8_t tid,uint8_t *list);
uint8_t list_tid_in_list( uint8_t tid, uint8_t *list);
uint8_t list_is_empty(uint8_t *list);
void list_move_highest_prio_to_ready(uint8_t *list);
void list_set_task_wait_event( uint8_t tid, uint8_t id, uint8_t waitSingleEvent );
void list_clear_wait_event( uint8_t tid, uint8_t id );

#endif
