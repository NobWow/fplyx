/*
 * template_interpreter.h
 * A template interpreter is a template engine implementation
 * that is representing an FPlyx code in the exact same functionality
 * on a different programming languages or any other data model
 * The way that the FPlyx code is interpreted is a bit different:
 * for example it most likely won't lock up in the loops,
 * but instead it will render these loops in their complementary model.
 * 
 */

#ifndef FPLYX_TYPE_TMPLINTERP_H_
#define FPLYX_TYPE_TMPLINTERP_H_

#include "vdev.h"
#include "vmem.h"

typedef struct __fplyx_tmplinterpreter_t
{
    void * _instance;
    char state;
    fplyx_vmem_t * vmem;
    fplyx_vdevice_t ** devices;
    unsigned int ndev;
    unsigned int tick_interval_msec;
    char (*connect_device)(struct __fplyx_tmplinterpreter_t *, fplyx_vdevice_t*);
    char (*disconnect_device)(struct __fplyx_tmplinterpreter_t *, fplyx_vdevice_t*);
    fplyx_vdevice_t* (*get_device)(struct __fplyx_tmplinterpreter_t *, char*);

} fplyx_tmplinterpreter_t;

#endif /* FPLYX_TYPE_TMPLINTERP_H_ */
