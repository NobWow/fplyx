#include <fplyx_type/interpreter.h>
#include <interp/win32.h>

void fplyx_interpposix_prepare(fplyx_interpreter_impl_t* self);
void fplyx_interpposix_end(fplyx_interpreter_impl_t* self);
fplyx_interpreter_t * fplyx_interpposix_obtain(fplyx_interpreter_impl_t* self);

char __fplyx_interpposix_tick(fplyx_interpreter_t* self);
char __fplyx_interpposix_tickchain(fplyx_interpreter_t* self);
char __fplyx_interpposix_xavail(fplyx_interpreter_t* self);
char __fplyx_interpposix_xchunkmrk(fplyx_interpreter_t* self);
char __fplyx_interpposix_xall(fplyx_interpreter_t* self);
