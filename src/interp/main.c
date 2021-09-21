#include <interp/main.h>
#include <memory.h>
#include <poll.h>
#include <stdio.h>
#include <fplyx_type/vdev.h>
#include <fplyx_type/extension.h>

void fplyx_interpmain_prepare(fplyx_interpreter_t* self);
void fplyx_interpmain_end(fplyx_interpreter_t* self);
fplyx_interpreter_t * fplyx_interpmain_obtain(fplyx_interpreter_t* self);

char __fplyx_interpmain_tick(fplyx_interpreter_t* self);
char __fplyx_interpmain_tickchain(fplyx_interpreter_t* self);
char __fplyx_interpmain_xavail(fplyx_interpreter_t* self);
char __fplyx_interpmain_xchunkmrk(fplyx_interpreter_t* self);
char __fplyx_interpmain_xall(fplyx_interpreter_t* self);

