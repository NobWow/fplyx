#ifndef DEV_STDIN_H_
#define DEV_STDIN_H_

#include "../fplyx_type/extension.h"
fplyx_vdevice_impl_t * fplyx_devstdin_create();
void fplyx_devstdin_prepare(fplyx_vdevice_impl_t *self);
void fplyx_devstdin_end(fplyx_vdevice_impl_t *self);
struct pollfd __fplyx_devstdin_mkpfd(fplyx_vdevice_t *self);
char __fplyx_devstdin_rav (fplyx_vdevice_t *self);
char __fplyx_devstdin_wav (fplyx_vdevice_t *self);
char __fplyx_devstdin_opr (fplyx_vdevice_t *self);
char __fplyx_devstdin_opw (fplyx_vdevice_t *self);
char __fplyx_devstdin_clr (fplyx_vdevice_t *self);
char __fplyx_devstdin_clw (fplyx_vdevice_t *self);
char __fplyx_devstdin_sr (fplyx_vdevice_t *self, int offset);
char __fplyx_devstdin_sw (fplyx_vdevice_t *self, int offset);
char __fplyx_devstdin_r (fplyx_vdevice_t *self, char* target_ptr, size_t amount);
char __fplyx_devstdin_w (fplyx_vdevice_t *self, const char* data_ptr, size_t amount);
char __fplyx_devstdin_fr (fplyx_vdevice_t *self);
char __fplyx_devstdin_fw (fplyx_vdevice_t *self);



#endif
