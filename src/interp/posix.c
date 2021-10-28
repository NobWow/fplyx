#include <fplyx_type/interpreter.h>
#include <interp/posix.h>
#include <memory.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <fplyx_type/vdev.h>
#include <fplyx_type/extension.h>
#include <string.h>

void fplyx_interpposix_prepare(fplyx_interpreter_impl_t* const self)
{
    self->name = "main";
}
fplyx_interpreter_t * fplyx_interpposix_obtain(fplyx_interpreter_impl_t* const self)
{
    fplyx_interpposix_t* const instance = calloc(1, sizeof(fplyx_interpposix_t));
    if(!instance) return 0;
    fplyx_interpreter_t* const result = calloc(1, sizeof(fplyx_interpreter_t));
    if(!result) return 0;
    result->devices = malloc(0);
    result->pending = malloc(0);
    result->_instance = instance;
    return result;
}
void __fplyx_interpposix_end(fplyx_interpreter_t* const self)
{
    fplyx_interpposix_t* const instance = self->_instance;
}
unsigned int __fplyx_interpposix_getdevid(fplyx_interpreter_t* const self, char* const name)
{
    fplyx_interpposix_t* const instance = self->_instance;
    unsigned int wrapped_i = instance->_last_devid;
    unsigned int wrapped_ri = instance->_last_devid;
    for(unsigned int i = 0; i <= (self->ndev / 2); i++)
    {
        if(!i && !strcmp(name, self->devices[wrapped_i]->name))
            return wrapped_i;
        else
        {
            if(wrapped_i == self->ndev - 1) wrapped_i = 0; else wrapped_i++;
            if(!wrapped_ri) wrapped_ri = self->ndev - 1; else wrapped_ri--;
            if(!strcmp(name, self->devices[wrapped_i]->name))
            {
                instance->_last_devid = wrapped_i;
                return wrapped_i;
            }
            if(wrapped_i == wrapped_ri)
                break;
            if(!strcmp(name, self->devices[wrapped_ri]->name))
            {
                instance->_last_devid = wrapped_ri;
                return wrapped_ri;
            }
        }
    }
    return 0;
}
unsigned int __fplyx_interpposix_getdevptrid(fplyx_interpreter_t* const self, fplyx_vdevice_t* const dev)
{
    fplyx_interpposix_t* const instance = self->_instance;
    unsigned int wrapped_i = instance->_last_devid;
    unsigned int wrapped_ri = instance->_last_devid;
    for(unsigned int i = 0; i <= (self->ndev / 2); i++)
    {
        if(!i && (self->devices[wrapped_i] == dev))
            return wrapped_i;
        else
        {
            if(wrapped_i == self->ndev - 1) wrapped_i = 0; else wrapped_i++;
            if(!wrapped_ri) wrapped_ri = self->ndev - 1; else wrapped_ri--;
            if(dev == self->devices[wrapped_i])
            {
                instance->_last_devid = wrapped_i;
                return wrapped_i;
            }
            if(wrapped_i == wrapped_ri)
                break;
            if(dev == self->devices[wrapped_ri])
            {
                instance->_last_devid = wrapped_ri;
                return wrapped_ri;
            }
        }
    }
    return 0;
}
char __fplyx_interpposix_conndev(fplyx_interpreter_t* const self, fplyx_vdevice_t* const dev)
{
    /*TODO: push event to master device*/
    /*lookup for this device if it doesn't already exist*/
    if(self->ndev)
    {
        if(!strcmp(dev->name, self->devices[0]->name))
            return 0+8;
        if(__fplyx_interpposix_getdevid(self, dev->name))
            return 0+8;
    }
    fplyx_vdevice_t** devices = reallocarray(self->devices, self->ndev + 1, sizeof(fplyx_vdevice_t*));
    if(!devices) return -128;
    devices[self->ndev] = dev;
    self->ndev++;
    return 1;
}
char __fplyx_interpposix_disconndev(fplyx_interpreter_t* const self, fplyx_vdevice_t* const dev)
{
    /*TODO: push event to master device*/
    if(!self->ndev)
        return 0+8;
    unsigned int id = __fplyx_interpposix_getdevptrid(self, dev);
    if(!id && (self->devices[0] != dev))
        return 0+8;
    /*do NOT destruct the device! Just remove it from the list*/
    if(id < (self->ndev - 1))
        memmove(&self->devices[id],
                &self->devices[id+1],
                (self->ndev - id - 1)*sizeof(fplyx_vdevice_t*)
                );
    self->devices = reallocarray(self->devices, --self->ndev, sizeof(fplyx_vdevice_t*));
    return 1;
}



char __fplyx_interpposix_tick(fplyx_interpreter_t* const self);
char __fplyx_interpposix_tickchain(fplyx_interpreter_t* const self);
char __fplyx_interpposix_xavail(fplyx_interpreter_t* const self);
char __fplyx_interpposix_xchunkmrk(fplyx_interpreter_t* const self, unsigned int);
char __fplyx_interpposix_xall(fplyx_interpreter_t* const self);

