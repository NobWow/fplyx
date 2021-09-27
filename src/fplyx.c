/*
 * fplyx.c
 * This code implements a front functions of an FPlyx One-shot Interpreter that is described in out-of-scope fplyx.h
 *
 *  Created on: 21 mar. 2021.
 *      Author: NobWow
 */
#include <fplyx.h>
#include <fplyx_type/interpreter.h>
#include <fplyx_exti.h>
#include <stdlib.h>

fplyx_interpreter_t* fplyx_interpreter_init(char* name, char* vmemname)
{
    fplyx_interpreter_impl_t* interpbase;
    fplyx_memdrv_impl_t* vmembase;
    /*obtain an interpreter*/
    if(!name)
        interpbase = fplyx_exti_interpfetch(FPLYX_DEFAULT_INTERPRETER, NULL);
    else
        interpbase = fplyx_exti_interpfetch(name, NULL);
    interpbase->prepare(interpbase);
    fplyx_interpreter_t* interpreter = interpbase->obtain();
    if(!interpreter) return 0;
    /*connect all available devices*/
    for(unsigned int i = 0; i < fplyx_vdev_n; i++)
        interpreter->connect_device(interpreter, fplyx_vdevices[i]->vdevice);
    /*obtain and attach a virtual memory driver*/
    if(!vmemname)
        vmembase = fplyx_exti_vmemfetch(FPLYX_DEFAULT_VMEMDRV, NULL);
    else
        vmembase = fplyx_exti_vmemfetch(vmemname, NULL);
    fplyx_vmem_t* vmem = vmembase->obtain();
    if(!vmem) return 0;
    interpreter->vmem = vmem;
    return interpreter;
}
