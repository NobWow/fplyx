/*
 * extension.h
 * Used for third-party applications for creating custom devices and publishing it to the library
 *  Created on: 8 apr. 2021.
 *      Author: NobWow
 */

#ifndef FPLYX_TYPE_EXTENSION_H_
#define FPLYX_TYPE_EXTENSION_H_
#include <fplyx_type/vdev.h>
#include <fplyx_type/vmem.h>
#include <fplyx_type/interpreter.h>
/*
 * There are 2 struct typedefs: for devices and for virtual memory drivers
 * Note that all devices are global for all interpreters, meaning that interpreters could share the same device
 * and memory drivers should provide obtain() method that creates an unique memory instance (unprepared) that
 * is used only by 1 interpreter.
 */

typedef struct __fplyx_vdevice_impl_t
{
	const char* name;
	void (*prepare)(struct __fplyx_vdevice_impl_t *);
	void (*end)(struct __fplyx_vdevice_impl_t *);
	fplyx_vdevice_t *vdevice;
} fplyx_vdevice_impl_t;

/* prepare & end might be deprecated for mem and interpreter since these functions are embed into instance */
typedef struct __fplyx_memdrv_impl_t
{
	const char* name;
	void (*prepare)(struct __fplyx_memdrv_impl_t *);
	void (*end)(struct __fplyx_memdrv_impl_t *);
	fplyx_vmem_t *(*obtain)();
} fplyx_memdrv_impl_t;

typedef struct __fplyx_interpreter_impl_t
{
	const char* name;
	void (*prepare)(struct __fplyx_interpreter_impl_t *);
	void (*end)(struct __fplyx_interpreter_impl_t *);
	fplyx_interpreter_t *(*obtain)();
} fplyx_interpreter_impl_t;
#endif /* FPLYX_TYPE_EXTENSION_H_ */
