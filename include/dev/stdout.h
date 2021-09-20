/*
 * stdout.h
 * This file contains stdout device implementation functions
 *  Created on: 8 apr. 2021.
 *      Author: NobWow
 */

#ifndef DEV_STDOUT_H_
#define DEV_STDOUT_H_

#include "../fplyx_type/extension.h"

fplyx_vdevice_impl_t * fplyx_devstdout_create();
void fplyx_devstdout_prepare(fplyx_vdevice_impl_t *self);
void fplyx_devstdout_end(fplyx_vdevice_impl_t *self);
struct pollfd __fplyx_devstdout_mkpfd(fplyx_vdevice_t *self);
char __fplyx_devstdout_rav (fplyx_vdevice_t *self);
char __fplyx_devstdout_wav (fplyx_vdevice_t *self);
char __fplyx_devstdout_opr (fplyx_vdevice_t *self);
char __fplyx_devstdout_opw (fplyx_vdevice_t *self);
char __fplyx_devstdout_clr (fplyx_vdevice_t *self);
char __fplyx_devstdout_clw (fplyx_vdevice_t *self);
char __fplyx_devstdout_sr (fplyx_vdevice_t *self, int offset);
char __fplyx_devstdout_sw (fplyx_vdevice_t *self, int offset);
char __fplyx_devstdout_r (fplyx_vdevice_t *self, char* target_ptr, size_t amount);
char __fplyx_devstdout_w (fplyx_vdevice_t *self, const char* data_ptr, size_t amount);
char __fplyx_devstdout_fr (fplyx_vdevice_t *self);
char __fplyx_devstdout_fw (fplyx_vdevice_t *self);


#endif /* DEV_STDOUT_H_ */
