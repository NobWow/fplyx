/*
 * fplyx.h
 * Main header file for the library
 *  Created on: 21 mar. 2021.
 *      Author: NobWow
 */

#ifndef FPLYX_H_
#define FPLYX_H_

#include "fplyx_type/interpreter.h"
#include <stddef.h>

#ifndef FPLYX_DEFAULT_INTERPRETER

#if defined(_WIN32) || defined(__CYGWIN__)
#   define FPLYX_DEFAULT_INTERPRETER "win32"
#else
#   define FPLYX_DEFAULT_INTERPRETER "posix"
#endif

#endif /*FPLYX_DEFAULT_INTERPRETER*/


#ifndef FPLYX_DEFAULT_VMEMDRV
#   define FPLYX_DEFAULT_VMEMDRV "ram"
#endif /*FPLYX_DEFAULT_VMEMDRV*/

fplyx_interpreter_t* fplyx_interpreter_init(char* interpname, char* vmemname);

#endif /* FPLYX_H_ */
