/* interp/main.h - the main upstream interpreter for the FPlyx bytecode
 * Dispatches the code in the virtual memory. Interacts with the virtual devices.
 * Shipped with one-tick interpreter and single thread event loop
 * Multithreaded event loop in the progress...
 */

#ifndef FPLYX_INTERP_MAIN_H_
#define FPLYX_INTERP_MAIN_H_

#include "../fplyx_type/extension.h"
#include <time.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#ifdef __linux__
#include <linux/time.h>
#elif __FreeBSD__
#include <sys/timespec.h>
#endif
/*

	void (*prepare)(struct __fplyx_interpreter_impl_t *);
	void (*end)(struct __fplyx_interpreter_impl_t *);
	fplyx_interpreter_t *(*obtain)();

    char (*exec_tick)(struct __fplyx_interpreter_t *); execute a single statement and prepare vmem to the next iter
    char (*exec_tick_chain)(struct __fplyx_interpreter_t *);  execute every single available subthread
    char (*exec_available)(struct __fplyx_interpreter_t *);  whether or not there is subthreads that is not pending
    char (*exec_chunkmrk)(struct __fplyx_interpreter_t *, unsigned int); execute a chain of non-blocking fplyx code, until none of the subthreads are available left.
     Potentially dangerous for running untrusted code! Blocks until all the code is dispatched
    char (*exec_all)(struct __fplyx_interpreter_t *);
*/


typedef struct __fplyx_interpmain_t
{
    unsigned int _last_devid; /*for accessing device for IO*/
    unsigned int _last_polldevid; /*for reading revents*/
    struct timespec ppollsleep;
} fplyx_interpmain_t;


void fplyx_interpmain_prepare(fplyx_interpreter_t* self);
void fplyx_interpmain_end(fplyx_interpreter_t* self);
fplyx_interpreter_t * fplyx_interpmain_obtain(fplyx_interpreter_t* self);

char __fplyx_interpmain_tick(fplyx_interpreter_t* self);
char __fplyx_interpmain_tickchain(fplyx_interpreter_t* self);
char __fplyx_interpmain_xavail(fplyx_interpreter_t* self);
char __fplyx_interpmain_xchunkmrk(fplyx_interpreter_t* self);
char __fplyx_interpmain_xall(fplyx_interpreter_t* self);

#endif /* FPLYX_INTERP_MAIN_H_ */
