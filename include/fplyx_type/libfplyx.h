/*
 * libfplyx.h
 * This header file is shadow header file, meaning that it isn't included in any of the FPlyx library code
 * The only purpose of this header file is to provide the library itself to the applications
 *
 * Type headers:
 * These header file might be provided to third-party's software
 * and contains only type definitions, macros and some source code
 * for loading the library that is used by the software.
 *
 *  Created on: 21 mar. 2021.
 *      Author: NobWow
 */

#ifndef FPLYX_TYPE_LIBFPLYX_H_
#define FPLYX_TYPE_LIBFPLYX_H_

#include <dlfcn.h>
#include <fplyx_type/interpreter.h>
#include <fplyx_type/vdev.h>

// function symbols

#define FPLYX_INTERPRETER_CREATE_SYM "fplyx_create_interpreter"
#define FPLYX_INTERPRETER_DESTROY_SYM "fplyx_destroy_interpreter"

// source code

void* fplyx_dl_handle;

fplyx_interpreter_t* (*fplyx_create_interpreter)(/* TODO: arguments from fplyx_interpreter.h */);
void (*fplyx_destroy_interpreter)(fplyx_interpreter_t*);

int libfplyx_load(void)
{
	fplyx_dl_handle = dlopen("libfplyx.so", RTLD_LAZY); // @suppress("Symbol is not resolved")
	fplyx_create_interpreter = dlsym(fplyx_dl_handle, FPLYX_INTERPRETER_CREATE_SYM);
	fplyx_destroy_interpreter= dlsym(fplyx_dl_handle, FPLYX_INTERPRETER_DESTROY_SYM);

	return 0;
}
int libfplyx_unload(void)
{
	//WARNING: all used interpreters should be destroyed before library unload
	//unset pointers
	fplyx_create_interpreter = 0;
	fplyx_destroy_interpreter = 0;
	return dlclose(fplyx_dl_handle);
}

#endif /* FPLYX_TYPE_LIBFPLYX_H_ */
