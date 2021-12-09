#include <io.h>
#include <interrupt.h>
#include <inttypes.h>
#include <stdlib.h>
#include "cocoos.h"

#include "clock.h"







static void system_init(void);



static int led_task(void)
{
	OS_BEGIN;	
	
		PORTB ^= 0x01;

		/* Wait 200ms */
		OS_WAIT_TICKS( 200 );

	OS_END;

	return 0;
}




int main(void)
{
	system_init();
	os_init();
	
	
	os_task_create( led_task, 1 );
	

	/* Setup clock with 1 ms tick */
    clock_init(1000);

	os_start();
    return 0;
}



static void system_init(void)
{
   DDRB=0xff;
   PORTB=0xff;
   DDRA=0x00;
   PORTA=0xff;
}








