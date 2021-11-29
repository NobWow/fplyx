/*
 * fplyx_exti.h
 * Extension Interface
 * Implements the behavior of extensive platform, it contains global variables that
 * contains all known devices and vmem drivers
 * Extension interface allows the third-party applications to push its own device implementations
 *  Created on: 8 apr. 2021.
 *      Author: NobWow
 */

#ifndef FPLYX_EXTI_H_
#define FPLYX_EXTI_H_

#include "fplyx_type/extension.h"

extern fplyx_vdevice_impl_t ** fplyx_vdevices;
extern fplyx_memdrv_impl_t ** fplyx_memdrvs;
extern fplyx_interpreter_impl_t ** fplyx_interpreters;
extern fplyx_tmplinterpreter_impl_t ** fplyx_tmplinterpreters;
extern unsigned int fplyx_vdev_n;
extern unsigned int fplyx_memdrvs_n;
extern unsigned int fplyx_interp_n;

void fplyx_exti_start();
void fplyx_exti_end();
void fplyx_exti_vdevadd(fplyx_vdevice_impl_t *device);
fplyx_vdevice_impl_t *fplyx_exti_vdevfetch(const char *name, unsigned int *ri);
void fplyx_exti_vdevdel(const char *name);
void fplyx_exti_vmemadd(fplyx_memdrv_impl_t *memdrv);
fplyx_memdrv_impl_t *fplyx_exti_vmemfetch(const char *name, unsigned int *ri);
void fplyx_exti_vmemdel(const char *name);
void fplyx_exti_interpadd(fplyx_interpreter_impl_t *memdrv);
fplyx_interpreter_impl_t *fplyx_exti_interpfetch(const char *name, unsigned int *ri);
void fplyx_exti_interpdel(const char *name);
void fplyx_exti_tmplinterpadd(fplyx_interpreter_impl_t *memdrv);
fplyx_interpreter_impl_t *fplyx_exti_tmplinterpfetch(const char *name, unsigned int *ri);
void fplyx_exti_tmplinterpdel(const char *name);

#endif /* FPLYX_EXTI_H_ */
