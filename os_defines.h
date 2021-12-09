#ifndef _os_defs
#define _os_defs

#include <interrupt.h>
#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

#define MAX_TASKS 6
#define NO_TID	255

#define enable_interrupts()		sei()
#define disable_interrupts()	cli()

typedef uint8_t		Bool;



typedef int (*taskproctype) (void);





#endif
