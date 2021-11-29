/* interp/all.h - the platform-independent part of the FPlyx Interpreter
 * Contains some general functions for interpreter implementations that is not platform-specific
 */

#ifndef FPLYX_INTERP_ALL_H_
#define FPLYX_INTERP_ALL_H_

#include "../fplyx_type/interpreter.h"

char __fplyx_interpmain_tick(fplyx_interpreter_t* self);
char __fplyx_interpmain_tickchain(fplyx_interpreter_t* self);

#endif /* FPLYX_INTERP_ALL_H_ */
