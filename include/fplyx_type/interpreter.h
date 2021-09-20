/*
 * fplyx_interpreter.h
 *
 *  Created on: 21 apr. 2021.
 *      Author: NobWow
 */

#ifndef FPLYX_TYPE_INTERPRETER_H_
#define FPLYX_TYPE_INTERPRETER_H_
#include "vdev.h"
#include "vmem.h"
#include <time.h>

/*
 * FPlyx Interpreter is a single execution thread (with virtual sub-thread handling) that operates on an virtual memory
 * There is different solutions of how to execute FPlyx code.
 * If our goal is to integrate the interpreter into another event loop, the library provides an
 * interpreter function that does 1 single tick of FPlyx code at the stack(s) and returns. This gives an opportunity to run code at
 * arbitrary speed and avoid unwanted CPU overload.
 * However, the library implements its own event loop if the code is used in real system
 */
typedef struct
{
	fplyx_vdevice_t*	vdevice;
	/*
	 * 1. waiting to read
	 * 2. waiting to write
	 */
	char				events;
} fplyx_interp_devwait_t;

typedef struct __fplyx_interpreter_t
{
	/*
	 * state has 8 bits:
	 * 1. complete (when position value is reached the end and the real thread is complete)
	 * 2. error (when real thread fails to execute and stops)
	 * If either 1 or 2 is set, in case if this interpreter is called again,
	 * all the data will be reset, including main stack position pointer.
	 * 3. ready (has the execution code in main scope)
	 * 4. real pending (some threads execution suspended due to device blocking)
	 *     In this case file descriptors of pending virtual devices will be put on ppoll() syscall
	 * 5. fast execution (no delay between ticks)
	 *     In this case tick_interval_nsec is ignored by built-in looped interpreter
     *     
	 * 6. no subthreads
	 *     In this case other subthreads are not handled by the interpreter
     *     functions
     * 7. sync virtual stack (all the virtual stacks will be executed in one tick and not sequenced)
	 *     If this stack has sub-stacks, they will be handled in one tick call
	 * 8. no virtual subthreads (virtual subthreads are disabled)
	 *     In this case virtual subthreads are not handled even if they are present in virtual memory
	 */
	void *					_instance; /* implementation */
	char 					state; /* above */
	fplyx_vmem_t *			vmem; /* data, subthread and execution management engine (almost everything is handled here) */
	fplyx_vdevice_t **		devices; /* input and output */
	fplyx_interp_devwait_t**pending; /* waiting on dev */
	unsigned int 			ndev;
	unsigned int			npend;
	//execution options is either used by a third-party software or by built-in interpreter function
	unsigned int			tick_interval_nsec; //is an interval between each execution in nanoseconds
	unsigned long			sleep_remaining_nsec; //if sleep command is called, how much time is remaining to timeout the ppoll call (or any third-party implementations)
    /* 
     * Implementations should provide at least 1 function: exec_tick
     * exec_tick performs exactly single tick of the code and is used
     * to execute potentially untrusted code safely. This is not a good
     * solution to execute code that requires fast execution, since
     * the speed depends on subthread amount and the executor loop.
     * To execute trusted code use exec_chunkmrk or exec_tick_chain
     * to perform single tick of code for all subthreads at the same time
     */
    char (*exec_tick)(struct __fplyx_interpreter_t *); /* execute a single statement and prepare vmem to the next iter*/
    char (*exec_tick_chain)(struct __fplyx_interpreter_t *); /* execute every single available subthread */
    char (*exec_available)(struct __fplyx_interpreter_t *); /* whether or not there is subthreads that is not pending */
    char (*exec_chunkmrk)(struct __fplyx_interpreter_t *, unsigned int); /*idk what does it mean*/
    /* Potentially dangerous for running untrusted code! Blocks until all the code is dispatched*/
    char (*exec_all)(struct __fplyx_interpreter_t *);
} fplyx_interpreter_t;


#endif /* FPLYX_TYPE_INTERPRETER_H_ */
