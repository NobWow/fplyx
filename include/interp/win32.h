/* interp/win32.h - the Windows/ReactOS implementation of the FPlyx Interpreter
 * This implementation is TODO
 */

#ifndef FPLYX_INTERP_WIN32_H_
#define FPLYX_INTERP_WIN32_H_

#include "../fplyx_type/extension.h"
#include "all.h"

typedef struct __fplyx_interpposix_t
{
    unsigned int _last_devid; /*for accessing device for IO*/
    unsigned int _last_polldevid; /*for reading revents*/
} fplyx_interpposix_t;


void fplyx_interpposix_prepare(fplyx_interpreter_impl_t* self);
void fplyx_interpposix_end(fplyx_interpreter_impl_t* self);
fplyx_interpreter_t * fplyx_interpposix_obtain(fplyx_interpreter_impl_t* self);

void __fplyx_interpposix_end(fplyx_interpreter_t* self);
char __fplyx_interpposix_tick(fplyx_interpreter_t* self);
char __fplyx_interpposix_tickchain(fplyx_interpreter_t* self);
char __fplyx_interpposix_xavail(fplyx_interpreter_t* self);
char __fplyx_interpposix_xchunkmrk(fplyx_interpreter_t* self, unsigned int);
char __fplyx_interpposix_xall(fplyx_interpreter_t* self);
#endif /* FPLYX_INTERP_WIN32_H_ */
