/*
 * fplyx_interpreter.h
 *
 *  Created on: 21 mar. 2021.
 *      Author: NobWow
 */

#ifndef FPLYX_INTERPRETER_H_
#define FPLYX_INTERPRETER_H_

#include "fplyx_type/interpreter.h"

/*
 * Allocates a new abstract interpreter data required to execute FPlyx byte-code
 * This function creates only mandatory data and DOES NOT attach virtual memory or devices to the interpreter
 */
fplyx_interpreter_t *fplyx_create_interpreter();

void fplyx_destroy_interpreter(fplyx_interpreter_t *interpreter);

#endif /* FPLYX_INTERPRETER_H_ */
