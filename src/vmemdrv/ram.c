//6jw
#include <limits.h>
#include <stddef.h>
#include <unistd.h>
#include <vmemdrv/ram.h>
#include <stdlib.h>
#include <fplyx_general.h>
#include <string.h>
#include <memory.h>
#include <stdint.h>
#include <math.h>

/*
typedef struct __fplyx_memdrv_impl_t
{
	const char* name;
	void (*prepare)(struct __fplyx_memdrv_impl_t *);
	void (*end)(struct __fplyx_memdrv_impl_t *);
	fplyx_vmem_t *(*obtain)();
} fplyx_memdrv_impl_t;
*/
/*
void del_element(size_t size, unsigned long id)
{
	target->end(target);
	free(target);
	assert((size_t) target == (size_t)((size_t)fplyx_vdevices + (ri) * sizeof(void *)));
	memmove(fplyx_vdevices + (ri) * sizeof(void *),
			fplyx_vdevices + (ri + 1) * sizeof(void *),
			(size_t)((fplyx_vdev_n - ri + 1) * sizeof(void *)));

	fplyx_vdevices = (fplyx_vdevice_impl_t **) realloc(fplyx_vdevices,
    (--fplyx_vdev_n)*sizeof(void *) );
}
*/

/* The reason of why this exists is memram_t instance has its separate nametable 
 * from subthr_t
 */

/*
struct fplyx_memram_ctxndata
{
    struct fplyx_memram_context *ctx;
    fplyx_memram_ndata_t* ndata;
};

struct fplyx_memram_ctxcdev
{
    struct fplyx_memram_context *ctx;
    fplyx_memram_cdev_t* cdev;
}; */

void fplyx_memram_prepare(fplyx_memdrv_impl_t* const self)
{
    self->name = "ram";
}
void fplyx_memram_end(fplyx_memdrv_impl_t* const self) {}
fplyx_vmem_t* fplyx_memram_obtain(fplyx_memdrv_impl_t* const self)
{
    fplyx_vmem_t * const result = malloc(sizeof(fplyx_vmem_t));
    if(!result) return NULL;
    memset(result, 0, sizeof(fplyx_vmem_t));
    result->memopts = ~FPLYX_VMEMOPT_ALLOCREADPTR; /*RAM-like*/
    result->_instance = (fplyx_memram_t *)malloc(sizeof(fplyx_memram_t));
    if(!result->_instance) return NULL;
    memset(result->_instance, 0, sizeof(fplyx_memram_t));
    /*FINAL: function setup.*/
    result->append_named_data = (char (*)(fplyx_vmem_t*, void*, char*, size_t))
        &__fplyx_memram_and;
    result->cdeviceid_valid = (char (*)(void*))
    &__fplyx_memram_cdeviceid_valid;
    result->cdevice_amount = (unsigned int (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_cdevamount;
    result->cdevice_at = (void (*)(fplyx_vmem_t*, unsigned int, void *, void *))
    &__fplyx_memram_cdev_at;
    result->cdevice_create = (char (*)(fplyx_vmem_t*, char*, char*, char*, char*, unsigned int, char*, unsigned int, void*, void*))
    &__fplyx_memram_cdevcreate;
    result->cdevice_delete = (char (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_cdevdel;
    result->cdevice_get = (char (*)(fplyx_vmem_t*, char*, void*, void*))
    &__fplyx_memram_cdevget;
    result->cdevice_getib = (char *(*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_cdevgetib;
    result->cdevice_getihnd = (char *(*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_cdevgihnd;
    result->cdevice_getob = (char *(*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_cdevgetob;
    result->cdevice_getohnd = (char *(*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_cdevgohnd;
    result->cdevice_id = (unsigned int (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_cdevid;
    result->cdevice_name = (char *(*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_cdevname;
    result->cdevice_reallocib = (char (*)(fplyx_vmem_t*, void*, size_t))
    &__fplyx_memram_cdevreallocib;
    result->cdevice_reallocob = (char (*)(fplyx_vmem_t*, void*, size_t))
    &__fplyx_memram_cdevreallocob;
    result->cdevice_setib = (char (*)(fplyx_vmem_t*, void*, char*))
    &__fplyx_memram_cdevsetib;
    result->cdevice_setihnd = (char (*)(fplyx_vmem_t*, void*, char*))
    &__fplyx_memram_cdevsihnd;
    result->cdevice_setohnd = (char (*)(fplyx_vmem_t*, void*, char*))
    &__fplyx_memram_cdevsohnd;
    result->cdevice_szofib = (size_t (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_cdevszofib;
    result->cdevice_szofob = (size_t (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_cdevszofob;
    result->create_reference_data = (char (*)(fplyx_vmem_t*, char, char*, void*, void*, void*))
    &__fplyx_memram_crefd;
    result->cut_named_data = (char (*)(fplyx_vmem_t*, void*, size_t, size_t))
    &__fplyx_memram_cnd;
    result->decrease_exec_stack = (void (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_dec_execstack;
    result->decrease_refcount = (void (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_decrefnd;
    result->destroy_named_data = (char (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_dnd;
    result->end = (char (*)(fplyx_vmem_t*))
    &__fplyx_memram_end;
    result->execstack_size = (unsigned long (*)(fplyx_vmem_t *, void *))
    &__fplyx_memram_exstacksz;
    result->get_allocated_size = (size_t (*)(fplyx_vmem_t*))
    &__fplyx_memram_getallocspace;
    result->get_cthriopos = (size_t (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_gthriopos;
    result->get_exec_pos = (size_t (*)(fplyx_vmem_t*, unsigned long, void*))
    &__fplyx_memram_gexecpos;
    result->get_iostate = (unsigned char (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_gthriostate;
    result->get_max_heap = (size_t (*)(fplyx_vmem_t*))
    &__fplyx_memram_getmaxheap;
    result->get_named_data = (void (*)(fplyx_vmem_t*, char*, unsigned long, void*, void*))
    &__fplyx_memram_getndata;
    result->get_named_data_at = (void (*)(fplyx_vmem_t*, unsigned long, unsigned long, void*, void*))
    &__fplyx_memram_getndata_at;
    result->get_ndata_refcount = (unsigned long (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_getrefnd;
    result->get_reference_finalcontext = (void (*)(fplyx_vmem_t*, void*, void*))
    &__fplyx_memram_greffinalctx;
    result->get_reference_finaltarget = (char (*)(fplyx_vmem_t*, void*, void*))
    &__fplyx_memram_greffinaltrg;
    result->get_reference_permissions = (char (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_grefperm;
    result->get_reference_target = (char (*)(fplyx_vmem_t*, void*, void*))
    &__fplyx_memram_greftrg;
    result->get_stackelement_mode = (unsigned char (*)(fplyx_vmem_t*, unsigned long, void*))
    &__fplyx_memram_gstackelmode;
    result->get_subthread = (char (*)(fplyx_vmem_t*, void*, char**, unsigned int, void*))
    &__fplyx_memram_getsubthr;
    result->increase_exec_stack = (char (*)(fplyx_vmem_t*, void*, void*, size_t, void*))
    &__fplyx_memram_inc_execstack;
    result->increase_refcount = (void (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_increfnd;
    result->insert_named_data = (char (*)(fplyx_vmem_t*, void*, char*, size_t, size_t))
    &__fplyx_memram_ind;
    result->ndataid_valid = (char (*)(void*))
    &__fplyx_memram_ndataid_valid;
    result->named_data_id = (unsigned long (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_ndid;
    result->named_data_name = (char *(*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_ndname;
    result->named_data_subthread = (void (*)(fplyx_vmem_t*, void*, void*))
    &__fplyx_memram_ndsubthr;
    result->named_data_stackdepth = (unsigned long (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_ndstackdepth;
    result->prepare = (char (*)(fplyx_vmem_t*))
    &__fplyx_memram_prepare;
    result->read_exec = (char *(*)(fplyx_vmem_t*, void*, unsigned long, unsigned char))
    &__fplyx_memram_rexec;
    result->read_named_data = (char *(*)(fplyx_vmem_t*, void*, size_t, size_t))
    &__fplyx_memram_rnd;
    result->replace_named_data = (char (*)(fplyx_vmem_t*, void*, char*, size_t, size_t))
    &__fplyx_memram_repnd;
    result->rewrite_named_data = (char (*)(fplyx_vmem_t*, void*, char*, size_t))
    &__fplyx_memram_rewnd;
    result->szofcdevid = (size_t (*)())
    &__fplyx_memram_szofcdevid;
    result->szofsubthrid = (size_t (*)())
    &__fplyx_memram_szofsubthrid;
    result->szofnamedataid = (size_t (*)())
    &__fplyx_memram_szofndataid;
    result->subthread_id = (unsigned int (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_thrid;
    result->set_cthriopos = (void (*)(fplyx_vmem_t*, unsigned long, void*))
    &__fplyx_memram_sthriopos;
    result->subthread_iter = (void (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_thriter;
    result->subthread_name = (char *(*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_thrname;
    result->subthread_size = (size_t (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_thrsz;
    result->subthrid_valid = (char (*)(void*))
    &__fplyx_memram_subthrid_valid;
    result->subthread_count = (unsigned int (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_thrcount;
    result->subthread_limit = (unsigned int (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_thrlim;
    result->subthread_create = (char (*)(fplyx_vmem_t*, char*, char, void*, void*))
    &__fplyx_memram_thrcreate;
    result->subthread_delete = (char (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_thrdel;
    result->subthread_devref = (char (*)(fplyx_vmem_t*, char*, char*, void*, void*))
    &__fplyx_memram_thrdevref;
    result->subthread_gcount = (unsigned long (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_thrgcount;
    result->subthread_suspend = (char (*)(fplyx_vmem_t*, void*, char))
    &__fplyx_memram_thrsus;
    result->subthread_devunref = (char (*)(fplyx_vmem_t*, char*, void*))
    &__fplyx_memram_thrdevunref;
    result->subthread_memlimit = (size_t (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_thrmemlim;
    result->subthread_devresolve = (char *(*)(fplyx_vmem_t*, char*, void*, void*))
    &__fplyx_memram_thrdevresolv;
    result->subthread_superflags = (char (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_thrsuperflags;
    result->set_max_heap = (void (*)(fplyx_vmem_t*, size_t))
    &__fplyx_memram_setmaxheap;
    result->set_last_mapid = (void (*)(fplyx_vmem_t*, unsigned long, void*))
    &__fplyx_memram_slmapid;
    result->sizeof_named_data = (size_t (*)(fplyx_vmem_t*, void*))
    &__fplyx_memram_sizeofnd;
    result->subthread_limit_set = (char (*)(fplyx_vmem_t*, void*, unsigned int))
    &__fplyx_memram_thrlimset;
    result->set_reference_permissions = (void (*)(fplyx_vmem_t*, char, void*))
    &__fplyx_memram_srefperm;
    result->set_stackelement_mode = (void (*)(fplyx_vmem_t*, unsigned char, unsigned long, void*))
    &__fplyx_memram_sstackelmode;
    result->subthread_memlimit_set = (char (*)(fplyx_vmem_t*, void*, size_t))
    &__fplyx_memram_thrmemlimset;
    result->write_named_data = (char (*)(fplyx_vmem_t*, char*, char*, size_t, void*, void*))
    &__fplyx_memram_wnd;
    return result;
}
/* Implementation of memram */
char __fplyx_memram_prepare(fplyx_vmem_t* const self)
{
    fplyx_memram_t * const instance = self->_instance;
    instance->ctx.max_nsubthr = UINT_MAX;
    instance->ctx.cdevs = NULL;
    instance->ctx.subthr = NULL;
    instance->ctx.execstack.refs = NULL;
    instance->ctx.watchers = NULL; /*iostate backtrace at memdrv side*/
    instance->subthrciter = NULL;
    if(1) return 1;
}
char __fplyx_memram_end(fplyx_vmem_t* const self) 
{
    fplyx_memram_t * const instance = self->_instance;
    struct __fplyx_memram_ndataid ndata;
    if(instance->ctx.nsubthr)
        for(unsigned int i = 0; i < instance->ctx.nsubthr; i++)
            self->subthread_delete(self, &instance->ctx.subthr[i]); /* pseudorecursion will be implemented later */
    /* clearing all the nametables */
    for(unsigned long i = 0; i < instance->ctx.execstack.nref; i++)
    {
        /* clear all the namedata */
        for(unsigned int j = 0; j < instance->ctx.execstack.refs[i]->ntab.ntabc; j++)
        {
            /* arrays are initialized with calloc, perform free operation on each namedata struct an its data itself */
            instance->ctx.execstack.refs[i]->cmdptr = 0;
            ndata.ctx = &instance->ctx;
            ndata.id = j;
            ndata.ndata = instance->ctx.execstack.refs[i]->ntab.ntabaddr[j];
            self->destroy_named_data(self, &ndata);
            free(instance->ctx.execstack.refs[i]->ntab.ntabaddr[j]);
            /* as above, char* names are allocated dynamically */
            free(instance->ctx.execstack.refs[i]->ntab.ntabname[j]);
        }
        free(instance->ctx.execstack.refs[i]->ntab.ntabaddr);
        free(instance->ctx.execstack.refs[i]->ntab.ntabname);
        free(instance->ctx.cdevs);
    }
    /* clear all the custom devices */
    for(unsigned int j = 0; j < instance->ctx.cdevc; j++)
    {
        free(instance->ctx.cdevs[j]->name);
        free(instance->ctx.cdevs[j]->ihndname);
        free(instance->ctx.cdevs[j]->ohndname);
        free(instance->ctx.cdevs[j]->ibuffname);
        free(instance->ctx.cdevs[j]->obuffname);
    }
    free(instance->ctx.cdevs);
    free(instance->ctx.subthr);
    free(instance->ctx.execstack.refs);
    free(instance->ctx.watchers);
    free(instance->subthrciter);
    free(instance);
    /* no need to zero all the bytes here */
    return 1;
}
size_t __fplyx_memram_getallocspace(fplyx_vmem_t* const self) 
{
    fplyx_memram_t* const instance = self->_instance;
    return instance->ctx.alloc;
}
size_t __fplyx_memram_getmaxheap(fplyx_vmem_t* const self)
{
    fplyx_memram_t* const instance = self->_instance;
    return instance->ctx.max;
}
void __fplyx_memram_setmaxheap(fplyx_vmem_t* const self, const size_t size)
{
    fplyx_memram_t* const instance = self->_instance;
    instance->ctx.max = size;
}
/* data operations */

/* resolve subthread path */
char __fplyx_memram_getsubthr(fplyx_vmem_t* const self, fplyx_memram_subthrid const subthrid, char** const subthr, const unsigned int nsubthr, fplyx_memram_subthrid const result)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context * const ctx = __fplyx_memram_getctx(instance, subthrid);
    if(nsubthr > ctx->nsubthr)
        return 2;
    unsigned int wrapped_i;
    unsigned int wrapped_ri;
    if(ctx->_last_subthrmapid >= ctx->nsubthr)
        ctx->_last_subthrmapid = ctx->nsubthr - 1;
    for(unsigned int i = 0; i < ctx->nsubthr; i++)
    {
        if(!strcmp(ctx->subthr[i]->name, subthr[0]))
        {
            result->ctx = &ctx->subthr[i]->ctx;
            result->subthr = ctx->subthr[i];
            result->id = i;
        }
    }
    if(!result->subthr) return 2;
    for(unsigned int i = 1; i < nsubthr; i++) /* index of requested name */
    {
        char found = 0;
        wrapped_i = result->ctx->_last_subthrmapid;
        wrapped_ri = result->ctx->_last_subthrmapid;
        if(result->ctx->nsubthr)
            for(unsigned int j = 0; j <= (result->subthr->ctx.nsubthr / 2); j++) /*index of subthrid in the current line*/
            {
                if(!j)
                {
                    if(!strcmp(result->subthr->ctx.subthr[wrapped_i]->name, subthr[i]))
                    {
                        result->subthr = result->subthr->ctx.subthr[wrapped_i];
                        result->ctx = &result->subthr->ctx;
                        result->id = j;
                        found = 1;
                        break;
                    }
                } else {
                    if(wrapped_i < result->ctx->nsubthr-1) wrapped_i++; else wrapped_i = 0;
                    if(wrapped_ri) wrapped_ri--; else wrapped_ri = result->ctx->nsubthr-1;
                    if(wrapped_i == wrapped_ri) break;
                    if(!strcmp(result->subthr->ctx.subthr[wrapped_i]->name, subthr[i]))
                    {
                        result->subthr = result->subthr->ctx.subthr[wrapped_i];
                        result->ctx = &result->subthr->ctx;
                        result->id = wrapped_i;
                        found = 1;
                        result->ctx->_last_subthrmapid = wrapped_i;
                        break;
                    }
                    if(!strcmp(result->subthr->ctx.subthr[wrapped_ri]->name, subthr[i]))
                    {
                        result->subthr = result->subthr->ctx.subthr[wrapped_ri];
                        result->ctx = &result->subthr->ctx;
                        result->id = wrapped_ri;
                        found = 1;
                        result->ctx->_last_subthrmapid = wrapped_ri;
                        break;
                    }
                }
            }
        if(!found) return 2;
    }

    return 1;
}

/* resolve subthread path, but create an array of pointers
void __fplyx_memram_getsubthrpath(fplyx_vmem_t* const self, char** const subthr, const unsigned int nsubthr, fplyx_memram_subthrpathid const result)
{
    fplyx_memram_t* const instance = self->_instance;
    char found = 0;
    if(nsubthr > instance->ctx.nsubthr)
        return;
    fplyx_memram_subthr_t** target = calloc(nsubthr, sizeof(void *));
    if(!target) return;
    for(unsigned int i = 0; i < instance->ctx.nsubthr; i++)
    {
        if(!strcmp(instance->ctx.subthr[i]->name, subthr[0]))
        {
            found = 1;
            target[0] = instance->ctx.subthr[i];
        }
    }
    if(!found)
    {
        free(target);
        return;
    }
    for(unsigned int i = 0; i < (nsubthr - 1); i++)
    {
        found = 0;
        for(unsigned int j = 0; j < target[i]->nsubthr; j++)
        {
            if(!strcmp(target[i]->subthr[j]->name, subthr[i]))
            {
                target[i+1] = target[i]->subthr[j];
                found = 1;
                break;
            }
        }
        if(!found)
        {
            free(target);
            return;
        }
    }
    result->nsubthr = nsubthr;
    result->subthr = target;
} */

/* cascade allocation limit scan */
size_t __fplyx_memram_cascademax(fplyx_memram_t* const instance, fplyx_memram_subthr_t* const subthr)
{
    size_t min = instance->ctx.max;
    fplyx_memram_subthr_t* current = subthr;
    if(!subthr)
        return instance->ctx.max;
    for(unsigned int ii = subthr->depth; ii >= 0; ii--)
    {
        if((current->flags&FPLYX_VMEMSUBTHR_FULLALLOC || current->ctx.max) && current->ctx.max < min)
            min = current->ctx.max;
        if(!ii)
        {
            if(instance->ctx.max && instance->ctx.max < min)
                return instance->ctx.max;
            else
                return min;
        }
        current = current->parent;
    }
    return 0;
}
/* Cascade allocation value modifier 
 * This function should always follow standard C memory management system calls (malloc, calloc, realloc and free)
 */
char __fplyx_memram_cascadealloc(fplyx_memram_t* const instance, const size_t diff, const char mod, fplyx_memram_subthr_t* const subthr)
{
    fplyx_memram_subthr_t* current = subthr;
    if(!mod && instance->ctx.max && instance->ctx.alloc + diff > instance->ctx.max)
        return 0+2;
    for(unsigned int ii = subthr?subthr->depth:0; ii >= 0; ii--)
    {
        if(current->ctx.max) /* memory is limited here */
        {
            if(!mod && current->ctx.alloc + diff > current->ctx.max)
                return 0+2;
        }
        if(!mod)
            current->ctx.alloc += diff;
        else
            current->ctx.alloc -= diff;
        if(current->flags&FPLYX_VMEMSUBTHR_FULLALLOC)
        {
            break;  /* superior context counts the entire max heap of this subthread */
        }
        if(!ii)
        {
            if(!mod)
                instance->ctx.alloc += diff;
            else
                instance->ctx.alloc -= diff;
            break;
        }
        current = current->parent;
    }
    return 1;
}
unsigned long __fplyx_memram_cascadethrmax(fplyx_memram_t* const instance, fplyx_memram_subthr_t* const subthr)
{   
    unsigned long min = instance->ctx.max; /*default is ULONG_MAX*/
    fplyx_memram_subthr_t* current = subthr;
    if(!subthr)
        return instance->ctx.max_nsubthr;
    for(unsigned int ii = subthr->depth; ii >= 0; ii--)
    {
        if(current->ctx.max_nsubthr && current->ctx.max_nsubthr < min)
            min = current->ctx.max_nsubthr;
        if(!ii)
        {
            if(instance->ctx.max_nsubthr && instance->ctx.max_nsubthr < min)
                return instance->ctx.max_nsubthr;
            else
                return min;
        }
        current = current->parent;
    }
    return 0;
}
char __fplyx_memram_cascadethrgmod(fplyx_memram_t* const instance, const unsigned long diff, const char mod, fplyx_memram_subthr_t* const subthr)
{
    fplyx_memram_subthr_t* current = subthr;
    if(!mod && instance->ctx.max_nsubthr && instance->ctx.gsubthr + diff > instance->ctx.max_nsubthr)
        return 0+2;
    for(unsigned int ii = subthr?subthr->depth:0; ii >= 0; ii--)
    {
        if(current->ctx.max_nsubthr) /* subthreads is limited here */
        {
            if(!mod && current->ctx.gsubthr + diff > current->ctx.max_nsubthr)
                return 0+2;
        }
        if(!mod)
            current->ctx.gsubthr += diff;
        else
            current->ctx.gsubthr -= diff;
        if(!ii)
        {
            if(!mod)
                instance->ctx.gsubthr += diff;
            else
                instance->ctx.gsubthr -= diff;
            break;
        }
        current = current->parent;
    }
    return 1;
}
struct fplyx_memram_context* __fplyx_memram_getctx(fplyx_memram_t* const instance, fplyx_memram_subthrid const subthrid)
{
    if(!subthrid)
        /* main thread context */
        return &instance->ctx;
    else if(subthrid->subthr)
        /* subthread: resolve context */
        return &subthrid->subthr->ctx;
    else 
        return &instance->ctx;
}
unsigned int __fplyx_memram_thrsctxid(struct fplyx_memram_context* const super_ctx, fplyx_memram_subthr_t* const subthr)
{
    for(unsigned int thrid = 0; thrid < super_ctx->nsubthr; thrid++)
        if(super_ctx->subthr[thrid] == subthr)
            return thrid;
    return 0;
}
unsigned char __fplyx_memram_updndataid(fplyx_memram_ndataid const ndataid)
{ /* This function performs rescan */
    if(ndataid->stackpos > ndataid->ctx->execstack.nref)
    {
        /*invalidate this ID immediately*/
        memset(ndataid, 0, sizeof(struct __fplyx_memram_ndataid));
        return 0;
    }
    char found;
    unsigned long wrapped_i;
    unsigned long wrapped_ri;
    wrapped_i = wrapped_ri = ndataid->ctx->_last_mapid;
    for(unsigned int i = 0; i <= ndataid->ctx->execstack.refs[ndataid->stackpos]->ntab.ntabc / 2; i++)
    { /*you can use shorter data types for half-iteration loops like this*/
        if(i)
        {
            if(wrapped_i < ndataid->ctx->execstack.refs[ndataid->stackpos]->ntab.ntabc)
                wrapped_i++;
            else
                wrapped_i = 0;
            if(wrapped_ri) wrapped_ri--;
            else
                wrapped_ri = ndataid->ctx->execstack.refs[ndataid->stackpos]->ntab.ntabc-1;
        }
        else if(wrapped_i == wrapped_ri) break;
        if(ndataid->ctx->execstack.refs[ndataid->stackpos]->ntab.ntabaddr[wrapped_i] == ndataid->ndata)
        {
            ndataid->id = wrapped_i;
            ndataid->ctx->_last_mapid = wrapped_i;
            found = 1;
        }
        else if(wrapped_i == wrapped_ri) break;
        if(ndataid->ctx->execstack.refs[ndataid->stackpos]->ntab.ntabaddr[wrapped_ri] == ndataid->ndata)
        {
            ndataid->id = wrapped_ri;
            ndataid->ctx->_last_mapid = wrapped_ri;
            found = 1;
        }
    }
    if(!found && ~ndataid->ndata->refopts&2) /*make sure it's not orphaned*/
    {
        /* since deletion of the elements that aren't in the end of the stack,
           elements should not be shifted and therefore this named data should be
           at the same stack node all the time */
        memset(ndataid, 0, sizeof(struct __fplyx_memram_ndataid));
        return 0;
    }
    return 1;
}
/* Note that this function DOESN'T resolve named data reference targets
   Flag fplyx_memram_ndata_t->refopts is set to 1 if this ndata is a data reference
   If this is a data reference then size is sizeof(fplyx_memram_dref_t) and data is
   the pointer to fplyx_memram_dref_t
*/
/*
 * Same as above, but scan other subthreads unless a restriction bit is set.
 */
void __fplyx_memram_getndata_at(fplyx_vmem_t* const self, unsigned long id, unsigned long pos, fplyx_memram_subthrid const subthrid, fplyx_memram_ndataid const result)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* ctx = __fplyx_memram_getctx(instance, subthrid);
    if(pos > ctx->execstack.nref - 1)
        pos = ctx->execstack.nref - 1;
    if(id > ctx->execstack.refs[pos]->ntab.ntabc - 1)
        id = ctx->execstack.refs[pos]->ntab.ntabc - 1;
    result->ndata = ctx->execstack.refs[pos]->ntab.ntabaddr[id];
    result->id = id;
    result->ctx = ctx;
    /*result->name = ctx->execstack.refs[pos]->ntab.ntabname[id];*/
    result->stackpos = pos;
    result->subthrid = *subthrid;
}
void __fplyx_memram_getndata(fplyx_vmem_t* const self, char* const name, unsigned long pos, fplyx_memram_subthrid const subthrid, fplyx_memram_ndataid const result)
{
    fplyx_memram_t* const instance = self->_instance;
    /* found a better way to define a context */
    unsigned long wrapped_i;
    unsigned long wrapped_ri;
    unsigned long *_last_mapid; /* double memory waste: each subthread has its own _last_mapid and _last_cdevmapid */
    struct fplyx_memram_context* super_ctx;
    fplyx_memram_ntab_t* ntab;
    result->subthrid = *subthrid;
    for(unsigned int j = subthrid?subthrid->subthr->depth:0; j >= 0; j--)
    {
        if(!j)
        {
            result->ctx = &instance->ctx;
            result->subthrid.ctx = &instance->ctx;
            result->subthrid.id = 0;
            result->subthrid.subthr = NULL;
            _last_mapid = &instance->ctx._last_mapid;
        } else if((j < result->subthrid.subthr->depth) && (result->subthrid.subthr->flags&FPLYX_VMEMSUBTHR_NAMESPACE)) /* if superior thread is reached and its namespace is restricted */
            return;
        else
        {
            result->ctx = &result->subthrid.subthr->ctx;
            result->subthrid.ctx = &result->subthrid.subthr->ctx;
            _last_mapid = &result->ctx->_last_mapid;
        }
        if(result->subthrid.subthr->parent)
            super_ctx = &result->subthrid.subthr->parent->ctx;
        else
            super_ctx = &instance->ctx;
        if(pos > result->ctx->execstack.nref - 1)
            pos = result->ctx->execstack.nref - 1;
        for(unsigned long k = pos; k >= 0; k--)
        { /* iterate over execstack nodes in the namestack */
            result->stackpos = k;
            if(*_last_mapid >= result->ctx->execstack.refs[k]->ntab.ntabc)
                *_last_mapid = result->ctx->execstack.refs[k]->ntab.ntabc - 1;
            for(unsigned char swt = 0; swt != 2; swt++)
            {
                ntab = swt ? &result->ctx->execstack.refs[k]->ntab : result->ctx->execstack.refs[k]->add_ntab;
                for(unsigned int i = 0; i <= (ntab->ntabc / 2); i++)
                { /* iterate over named datas in the execstack node */
                    wrapped_i = (i + *_last_mapid) % ntab->ntabc;
                    if(!i)
                    {
                        /* first iteration: perform single name comparison */
                        wrapped_ri = wrapped_i;
                        if(!strcmp(ntab->ntabname[wrapped_i], name))
                        {
                            result->ndata = ntab->ntabaddr[wrapped_i]; /* _last_mapid remains unchanged */
                            result->id = wrapped_i;
                            result->subthrid.id = __fplyx_memram_thrsctxid(super_ctx, result->subthrid.subthr);
                            return;
                        }
                    } else {
                        /* other iterations: two-way lookup */
                        if(!wrapped_ri) wrapped_ri = ntab->ntabc - 1; else wrapped_ri--; /* manual wrapped decrement ? */
                        /* double check */
                        if(!strcmp(ntab->ntabname[wrapped_i], name))
                        {
                            *_last_mapid = wrapped_i;
                            result->ndata = ntab->ntabaddr[wrapped_i];
                            /*result->name = ntab->ntabname[wrapped_i]; */
                            result->id = wrapped_i;
                            result->subthrid.id = __fplyx_memram_thrsctxid(super_ctx, result->subthrid.subthr);
                            return;
                        }
                        else if(!strcmp(ntab->ntabname[wrapped_ri], name))
                        {
                            *_last_mapid = wrapped_ri;
                            result->ndata = ntab->ntabaddr[wrapped_ri];
                            /*result->name = ntab->ntabname[wrapped_ri]; */
                            result->id = wrapped_ri;
                            result->subthrid.id = __fplyx_memram_thrsctxid(super_ctx, result->subthrid.subthr);
                            return;
                        }
                    }
                }
                if(!result->ctx->execstack.refs[k]->add_ntab) break;
            }
            if(!k) break;
        }
        if(!j) return;
        result->subthrid.subthr = result->subthrid.subthr->parent;
    }
    return; /* nothing was found */
}

void __fplyx_memram_increfnd(fplyx_vmem_t* const self, fplyx_memram_ndataid const ndataid)
{
    ndataid->ndata->refcounter++;
}
void __fplyx_memram_decrefnd(fplyx_vmem_t* const self, fplyx_memram_ndataid const ndataid) /* automatically destroy_named_data() if no more references are left */
{
    if(ndataid->ndata->refopts&2)
    {
        if(ndataid->ndata->refcounter > 0)
            ndataid->ndata->refcounter--;
        if(!ndataid->ndata->refcounter)
        {
            __fplyx_memram_cascadealloc(self->_instance, ndataid->ndata->size + sizeof(fplyx_memram_ndata_t), 1, ndataid->subthrid.subthr->parent);
            free(ndataid->ndata->data);
            free(ndataid->ndata);
            memset(ndataid, 0, sizeof(struct __fplyx_memram_ndataid));
        }
    } else if(ndataid->ndata->refcounter > 1)
            ndataid->ndata->refcounter--;
}
unsigned long __fplyx_memram_getrefnd(fplyx_vmem_t* const self, fplyx_memram_ndataid const ndataid)
{
    return ndataid->ndata->refcounter;
}
/* create named data */
char __fplyx_memram_wnd(fplyx_vmem_t* const self, char* const name, char* const data, const size_t size, fplyx_memram_subthrid const subthrid, fplyx_memram_ndataid const result)
{
    fplyx_memram_t* const instance = self->_instance;
    /* context */
    struct fplyx_memram_context* ctx = __fplyx_memram_getctx(instance, subthrid);
    struct __fplyx_memram_ndataid origin;
    if(!ctx)
        return 0+8;
    __fplyx_memram_getndata(self, name, ctx->execstack.nref-1, subthrid, &origin);
    if(origin.ndata)
        return 0+16;
    /* check if memory is available */
    const size_t total_size_allocated = strlen(name) + 1 + size + sizeof(fplyx_memram_ndata_t) + sizeof(void *)*2;
    const size_t max = __fplyx_memram_cascademax(instance, subthrid?subthrid->subthr:0);
    if((ctx->alloc + total_size_allocated) > max)
        /* error, not enough memory */
        return 0+2;
    const char res = __fplyx_memram_cascadealloc(instance, total_size_allocated, 0, subthrid?subthrid->subthr:0);
    if(~res&1)
        return res;
    fplyx_memram_ndata_t* target = malloc(sizeof(fplyx_memram_ndata_t));
    if(!target) return -128; /* system error */
    memset(target, 0, sizeof(fplyx_memram_ndata_t));
    target->size = size;
    /* No FPLYX_VMEMOPT_ALLOCREADPTR: assume that the data is allocated somewhere else */
    target->data = data;
    fplyx_memram_ntab_t* const ntab = &ctx->execstack.refs[ctx->execstack.nref-1]->ntab;
    /* add target to the table | also make sure to apply a new object */
    char** const ntabname = reallocarray(ntab->ntabname, ntab->ntabc + 1, sizeof(void *));
    if(!ntabname)
        //return -128; /* system error */
        abort();
    ntab->ntabname = ntabname;
    fplyx_memram_ndata_t** ntabaddr = reallocarray(
        ntab->ntabaddr,
        ntab->ntabc + 1, sizeof(void *));
    if(!ntabaddr)
        abort();
    __fplyx_memram_cascadealloc(instance, total_size_allocated, 0, subthrid?subthrid->subthr:0);
    ntab->ntabc++;
    ntab->ntabname = ntabname;
    ntab->ntabaddr = ntabaddr;
    ntabname[ntab->ntabc - 1] = name;
    ntabaddr[ntab->ntabc - 1] = target;
    ctx->_last_mapid = ntab->ntabc - 1;
    if(result)
    {
        result->ctx = ctx;
        result->id = ntab->ntabc - 1;
        result->ndata = target;
        result->subthrid = *subthrid;
    }
    return 1;
}
char __fplyx_memram_rewnd(fplyx_vmem_t* const self, fplyx_memram_ndataid const ndataid, char* const data, const size_t size)
{
    fplyx_memram_t* const instance = self->_instance;
    if(ndataid->ndata->refopts&1)
        return 0+64;
    /* check if memory is enough */
    const size_t max = __fplyx_memram_cascademax(instance, ndataid->subthrid.subthr);
    if((ndataid->ctx->alloc - ndataid->ndata->size + size) > max)
        return 0+2;
    /* free old resources */
    free(ndataid->ndata->data);
    /* deflate allocation */
    __fplyx_memram_cascadealloc(instance, ndataid->ndata->size, 1, ndataid->subthrid.subthr);
    /* assume new data is manually allocated: bit FPLYX_VMEMOPT_ALLOCREADPTR is unset */
    if(1&__fplyx_memram_cascadealloc(instance, size, 0, ndataid->subthrid.subthr))
    {
        ndataid->ndata->size = size;
        ndataid->ndata->data = data;
        return 1;
    }
    else
    {
        free(ndataid->ndata->data);
        return 0;
    }
}
char __fplyx_memram_dnd(fplyx_vmem_t* const self, fplyx_memram_ndataid const ndataid)
{
    fplyx_memram_t* const instance = self->_instance;
    /* resource ID in the nametable is ndataid->id */
    if(!ndataid->ndata)
        return 0+4;
    if(ndataid->ndata->refopts&1)
    {
        /* dref: free target identifier */
        /* this is possible legit C recursion, we cannot bypass that 
           therefore, it is impossible to create an infinite loop of references as 
           it is checked at set_reference_target anyway (using Floyd algorithm) */
        __fplyx_memram_decrefnd(self, ((fplyx_memram_dref_t *)ndataid->ndata->data)->ndataid);
    }
    /* ctxnd.ndata->data = (void *)0; -- not required because resource struct is about to be dropped with free();
                                         only if no references are left*/
    fplyx_memram_ntab_t * const ntab = &ndataid->ctx->execstack.refs[ndataid->stackpos]->ntab;
    if(~(ndataid->ndata->refopts)&2)
    {   /*since this function might be called twice, prevent double address deletion*/
        ntab->ntabname[ndataid->id] = (void *)0;
        ntab->ntabaddr[ndataid->id] = (void *)0;
        if(ndataid->id + 1 < ndataid->ctx->execstack.refs[ndataid->stackpos]->ntab.ntabc)
            /* not the last element in the array of pointers */
        {
            /* (*ctx.ntabname)[ndataid->id] == pointer to ctxnd.ndata' data */
            /* &(*ctx.ntabname)[ndataid->id] == address of pointer to ctxnd.ndata */
            /* is there any lvalue or rvalue in C? I hope that *ctx.ntabname is lvalue */
            memmove(&ntab->ntabname[ndataid->id],
                    &ntab->ntabname[ndataid->id + 1],
                    sizeof(void *) * (ntab->ntabc - ndataid->id - 1));
            /* assume: last two pointers at nametable are equal because memory has been moved */
            /* (*ctx.ntabname)[*ctx.ntabc] == (*ctx.ntabname)[*ctx.ntabc - 1] */
            /* (*ctx.ntabname)[*ctx.ntabc] = (void *)0; */
            memmove(&ntab->ntabaddr[ndataid->id],
                    &ntab->ntabaddr[ndataid->id + 1],
                    sizeof(void *) * (ntab->ntabc - ndataid->id - 1));
        }
        fplyx_memram_ndata_t** ntabaddr = realloc(
            ntab->ntabaddr,
            (ntab->ntabc - 1)*sizeof(void*));
        if(!ntabaddr)
            return -128;
        char** const ntabname = realloc(ntab->ntabname, (ntab->ntabc - 1)*sizeof(void*));
        if(!ntabname)
            return -128;
        ntab->ntabaddr = ntabaddr;
        ntab->ntabname = ntabname;
        ntab->ntabc--;
        ndataid->ctx->alloc -= ndataid->ndata->size /*do not cascade dealloc unless it doesn't have other references*/;
        __fplyx_memram_cascadealloc(instance, sizeof(void*), 1, ndataid->subthrid.subthr);
        ndataid->ndata->refopts |= 2; /*orphaned bit*/
        ndataid->ndata->refcounter--;
        if(ndataid->ndata->refcounter <= 1)
        {
            __fplyx_memram_cascadealloc(instance, ndataid->ndata->size + sizeof(fplyx_memram_ndata_t), 1, ndataid->subthrid.subthr->parent);
            free(ndataid->ndata->data);
            free(ndataid->ndata);
            memset(ndataid, 0, sizeof(struct __fplyx_memram_ndataid));
        }
    }
    return 1;
}
size_t __fplyx_memram_sizeofnd(fplyx_vmem_t* const self, fplyx_memram_ndataid const ndataid)
{
    fplyx_memram_t * const instance = self->_instance;
    return ndataid->ndata->size;
}
char* __fplyx_memram_rnd(fplyx_vmem_t* const self, fplyx_memram_ndataid const ndataid, const size_t size, const size_t offset)
{
    /* not allocating memory in RAM for return value as 1 bit memopts is not set */
    fplyx_memram_t * const instance = self->_instance;
    if(size+offset > ndataid->ndata->size)
        return (void *)0;
    return ndataid->ndata->data + offset;
}
char __fplyx_memram_repnd(fplyx_vmem_t* const self, fplyx_memram_ndataid const ndataid, char* const data, const size_t size, const size_t offset)
{
    fplyx_memram_t * const instance = self->_instance;
    if(ndataid->ndata->refopts&1)
        return 0+32;
    if(size+offset > ndataid->ndata->size)
        return 0+4; /* out of bounds */
    memmove(ndataid->ndata->data + offset, data, size);
    return 1;
}
char __fplyx_memram_and(fplyx_vmem_t* const self, fplyx_memram_ndataid const ndataid, char* const data, const size_t size)
{
    fplyx_memram_t * const instance = self->_instance;
    if(ndataid->ndata->refopts&1)
        return 0+32;
    if(ndataid->ctx->alloc + size > ndataid->ctx->max)
        return 0+8;
    void * const data_ = realloc(ndataid->ndata->data, ndataid->ndata->size + size);
    if(!data_)
        return -128;
    ndataid->ndata->data = data_;
    memmove(data_ + ndataid->ndata->size, data, size);
    ndataid->ndata->size += size;
    return 1;
}
char __fplyx_memram_ind(fplyx_vmem_t* const self, fplyx_memram_ndataid const ndataid, char* const data, const size_t size, const size_t offset)
{
    fplyx_memram_t * const instance = self->_instance;
    if(ndataid->ndata->refopts&1)
        return 0+4;
    if(ndataid->ctx->alloc + size > ndataid->ctx->max)
        return 0+8;
    if(size+offset > ndataid->ndata->size)
        return 0+32; /* out of bounds */
    if(size + ndataid->ctx->alloc > ndataid->ctx->max)
        return 0+2;
    void * const data_ = realloc(ndataid->ndata->data, ndataid->ndata->size + size);
    if(!data_)
        return -128;
    ndataid->ndata->data = data_;
    ndataid->ndata->size += size;
    memmove(ndataid->ndata->data + size + offset,
            ndataid->ndata->data + offset,
            ndataid->ndata->size - size - offset);
    memmove(ndataid->ndata->data + offset,
            data,
            size);
    return 1;
}
char __fplyx_memram_cnd(fplyx_vmem_t* const self, fplyx_memram_ndataid const ndataid, const size_t size, const size_t offset)
{
    fplyx_memram_t * const instance = self->_instance;
    if(ndataid->ndata->refopts&1)
        return 0+64;
    if(size+offset > ndataid->ndata->size)
        return 0+16;
    memset(ndataid->ndata->data + offset, 0, size);
    memmove(ndataid->ndata->data + offset,
            ndataid->ndata->data + offset + size,
            ndataid->ndata->size - size - offset);
    void * const data_ = realloc(ndataid->ndata->data, ndataid->ndata->size - size);
    if(!data_)
        return -128;
    ndataid->ndata->size -= size;
    ndataid->ndata->data = data_;
    return 1;
}

char* __fplyx_memram_rexec(fplyx_vmem_t* const self, fplyx_memram_subthrid const subthrid, const unsigned long jump, const char mod)
{
    fplyx_memram_t * const instance = self->_instance;
    struct fplyx_memram_context * const ctx = __fplyx_memram_getctx(instance, subthrid);
    fplyx_memram_ndataid const execndata = ctx->execstack.refs[ctx->execstack.nref-1]->namedataid;
    if(!mod && ( ctx->execstack.refs[ctx->execstack.nref-1]->cmdptr+jump < ctx->execstack.refs[ctx->execstack.nref-1]->cmdptr))
        return 0; /*integer overflow in the hell*/
    if(mod && ( ctx->execstack.refs[ctx->execstack.nref-1]->cmdptr-jump > ctx->execstack.refs[ctx->execstack.nref-1]->cmdptr ))
        return 0;
    if(mod && ctx->execstack.refs[ctx->execstack.nref-1]->cmdptr + jump > execndata->ndata->size)
    {
        return 0;
    }
    if(mod)
        ctx->execstack.refs[ctx->execstack.nref-1]->cmdptr -= jump;
    else
        ctx->execstack.refs[ctx->execstack.nref-1]->cmdptr += jump;
    return execndata->ndata->data + ctx->execstack.refs[ctx->execstack.nref-1]->cmdptr;
}
char __fplyx_memram_crefd(fplyx_vmem_t* const self, const char perms, char* const name, fplyx_memram_subthrid const subthrid, fplyx_memram_ndataid const target, fplyx_memram_ndataid const result)
{
    fplyx_memram_t * const instance = self->_instance;
    struct __fplyx_memram_ndataid origin;
    struct fplyx_memram_context* ctx = __fplyx_memram_getctx(instance, subthrid);
    __fplyx_memram_getndata(self, name, ctx->execstack.nref-1, subthrid, &origin);
    if(origin.ndata)
    {
        __fplyx_memram_decrefnd(self, &origin);
    }
    size_t size = sizeof(fplyx_memram_dref_t);
    /*this allocation is not counted here*/
    fplyx_memram_dref_t* data = malloc(sizeof(fplyx_memram_dref_t));
    if(!data) return -128;
    struct __fplyx_memram_ndataid refd;
    const char res = __fplyx_memram_wnd(self, name, (void *)data, size, subthrid, &refd);
    if(~res&1)
        return res;
    refd.ndata->refopts = 1;
    data->permissions = perms;
    data->ndataid = malloc(sizeof(struct __fplyx_memram_ndataid));
    __fplyx_memram_cascadealloc(instance, sizeof(void *), 1, subthrid?subthrid->subthr:0);
    if(!data->ndataid) return -128;
    *data->ndataid = *target;
    return 1;   
}
char __fplyx_memram_greftrg(fplyx_vmem_t * const self, fplyx_memram_ndataid const drefid, fplyx_memram_ndataid const result)
{
    if(1&~drefid->ndata->refopts)
        return 2;
    *result = *((fplyx_memram_dref_t *)drefid->ndata->data)->ndataid;
    return 1;
}
char __fplyx_memram_greffinaltrg(fplyx_vmem_t * const self, fplyx_memram_ndataid current, fplyx_memram_ndataid const result)
{
    for(unsigned int i = 1; i != 0; i++)
    {
        if(current->ndata->refopts&1)
            current = ((fplyx_memram_dref_t*)current->ndata->data)->ndataid;
        else
        {
            *result = *current;
            return 1;
        }
    }
    return 0;
}
char __fplyx_memram_greffinalperm(fplyx_vmem_t * self, fplyx_memram_ndataid current)
{
    char perms = CHAR_MAX; /*255 anyway*/
    for(unsigned int i = 1; i != 0; i++)
    {
        if(current->ndata->refopts&1)
        {
            perms &= ((fplyx_memram_dref_t*)current->ndata->data)->permissions;
            current = ((fplyx_memram_dref_t*)current->ndata->data)->ndataid;
        }
        else if(!perms)
            return 0;
        else
            return perms;
    }
    return 0;
}
void __fplyx_memram_greffinalctx(fplyx_vmem_t * self, fplyx_memram_ndataid current, fplyx_memram_subthrid result)
{
    for(unsigned int i = 1; i != 0; i++)
    {
        if(current->ndata->refopts&1)
        {
            if(~((fplyx_memram_dref_t*)current->ndata->data)->permissions&FPLYX_VMEMREFP_EXECSOURCESCOPE)
            {
                *result = current->subthrid;
                return;
            }
            current = ((fplyx_memram_dref_t*)current->ndata->data)->ndataid;
        } else {
            *result = current->subthrid;
            return;
        }
    }
    return;
}
void __fplyx_memram_sreftrg(fplyx_vmem_t * const self, fplyx_memram_ndataid const drefid, fplyx_memram_ndataid const ndataid)
{
    if(ndataid->ndata->refopts&1)
    {
        fplyx_memram_ndata_t* p1;
        fplyx_memram_ndata_t* p2;
        char exit;
        p1 = ndataid->ndata;
        p2 = ndataid->ndata;
        do 
        {
            p1 = ((fplyx_memram_dref_t *)p1->data)->ndataid->ndata;
            p2 = ((fplyx_memram_dref_t *)p2->data)->ndataid->ndata;
            if(!(p2->refopts&1))
            {
                exit = 1;
                break;
            }
            p2 = ((fplyx_memram_dref_t *)p2->data)->ndataid->ndata;
            if(!(p2->refopts&1))
            {
                exit = 1;
                break;
            }
        } while(p1 != p2 && !exit);
        if(!exit) return;
    }
    if(1&drefid->ndata->refopts)
        ((fplyx_memram_dref_t *) drefid->ndata->data)->ndataid = ndataid;
}
char __fplyx_memram_isref(fplyx_vmem_t * const self, fplyx_memram_ndataid const ndataid)
{
    return ndataid->ndata->refopts&1;
}
char __fplyx_memram_grefperm(fplyx_vmem_t * const self, fplyx_memram_ndataid const drefid)
{
    if(1&drefid->ndata->refopts)
        return ((fplyx_memram_dref_t *) drefid->ndata->data)->permissions;
    return 0;
}
void __fplyx_memram_srefperm(fplyx_vmem_t * const self, const char perms, fplyx_memram_ndataid const drefid)
{
    if(1&drefid->ndata->refopts)
        ((fplyx_memram_dref_t *)drefid->ndata->data)->permissions = perms;
}
/*
void __fplyx_memram_gstackelat(fplyx_vmem_t* const self, fplyx_memram_subthrid const subthrid, const unsigned long elemid, fplyx_memram_exstacknodeid const result)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    if(elemid < ctx->execstack.nref)
        result->exstacknode = ctx->execstack.refs[elemid];
}*/
size_t __fplyx_memram_gexecpos(fplyx_vmem_t* const self, const unsigned long pos, fplyx_memram_subthrid const subthrid)
{
    return subthrid->ctx->execstack.refs[pos]->cmdptr;
}
char __fplyx_memram_inc_execstack(fplyx_vmem_t* const self, fplyx_memram_ndataid const ndataid, fplyx_memram_ndataid const resyield, const size_t operator_start, fplyx_memram_subthrid const subthrid)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context * const ctx = __fplyx_memram_getctx(instance, subthrid);
    if(ctx->execstack.nref + 1 == 0)
        return 0+64; /* integer underflow */
    /* check if memory is available */
    const size_t max = __fplyx_memram_cascademax(instance, subthrid?subthrid->subthr:0);
    size_t total_needed = sizeof(fplyx_memram_exstacknode_t) + sizeof(struct __fplyx_memram_ndataid) + sizeof(fplyx_memram_exstacknode_t *);
    const char has_result = resyield?(resyield->ndata?1:0):0;
    if(has_result)
    {
        total_needed += sizeof(struct __fplyx_memram_ndataid);
    }
    if((ctx->alloc + total_needed) > max)
        /* error, not enough memory */
        return 0+2;
    fplyx_memram_exstacknode_t* target = malloc(sizeof(fplyx_memram_exstacknode_t));
    if(!target) return -128; /* system error */
    const char res = __fplyx_memram_cascadealloc(instance, total_needed, 0, subthrid?subthrid->subthr:0);
    if(~res&1)
        return 0+2;
    memset(target, 0, sizeof(fplyx_memram_exstacknode_t));
    target->cmdptr = operator_start;
    /* copy id */
    target->namedataid = malloc(sizeof(struct __fplyx_memram_ndataid));
    *((fplyx_memram_ndataid)target->namedataid) = *ndataid;
    if(has_result)
    {
        target->result_namedataid = malloc(sizeof(struct __fplyx_memram_ndataid));
        *((fplyx_memram_ndataid)target->result_namedataid) = *resyield;
    }
    target->ntab.ntabaddr = NULL;
    target->ntab.ntabname = NULL;
    fplyx_memram_exstacknode_t ** refs = reallocarray(
        ctx->execstack.refs, ctx->execstack.nref+1, sizeof(fplyx_memram_exstacknode_t *)
    );
    if(!refs) return -128;
    ctx->execstack.nref++;
    ctx->execstack.refs = refs;
    ctx->execstack.refs[ctx->execstack.nref-1] = target;
    return 1;
}
void __fplyx_memram_dec_execstack(fplyx_vmem_t* const self, fplyx_memram_subthrid const subthrid)
{
    fplyx_memram_t* const instance = self->_instance;
    struct __fplyx_memram_ndataid ndc;
    ndc.ctx = __fplyx_memram_getctx(instance, subthrid);
    if(!ndc.ctx->execstack.nref)
        return;
    fplyx_memram_exstacknode_t* const target = ndc.ctx->execstack.refs[ndc.ctx->execstack.nref-1];
    ndc.stackpos = ndc.ctx->execstack.nref;
    ndc.subthrid = *subthrid;
    for(unsigned long i = 0; i < target->ntab.ntabc; i++)
    {
        ndc.id = i;
        ndc.ndata = target->ntab.ntabaddr[i];
        __fplyx_memram_dnd(self, &ndc);
    }
    size_t to_free = sizeof(struct __fplyx_memram_ndataid) + sizeof(fplyx_memram_exstacknode_t);
    if(target->result_namedataid) to_free += sizeof(struct __fplyx_memram_ndataid);
    __fplyx_memram_cascadealloc(instance, to_free, 1, subthrid?subthrid->subthr:0);
    if(ndc.ctx->execstack.nref)
        ndc.ctx->_last_mapid = ndc.ctx->execstack.refs[ndc.ctx->execstack.nref-1]->ntab.ntabc-1;
    else
        ndc.ctx->_last_mapid = 0;
    free(target->namedataid);
    if(target->result_namedataid)
        free(target->result_namedataid);
    free(target);
    ndc.ctx->execstack.nref--;
    if(!ndc.ctx->execstack.nref)
    {
        free(ndc.ctx->execstack.refs);
        ndc.ctx->execstack.refs = NULL;
    } else {
        fplyx_memram_exstacknode_t ** refs = reallocarray(
            ndc.ctx->execstack.refs, ndc.ctx->execstack.nref, sizeof(fplyx_memram_exstacknode_t *)
        );
        if(!refs) {
            ndc.ctx->execstack.nref++;return; }
        ndc.ctx->execstack.refs = refs;
    }
}
unsigned long __fplyx_memram_exstacksz(fplyx_vmem_t* const self, fplyx_memram_subthrid const subthrid)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    return ctx->execstack.nref;
}
unsigned long __fplyx_memram_ntabsz(fplyx_vmem_t* self, unsigned long pos, fplyx_memram_subthrid subthrid)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    return ctx->execstack.refs[pos]->ntab.ntabc;
}
unsigned char __fplyx_memram_gstackelmode(fplyx_vmem_t * const self, const unsigned long pos, fplyx_memram_subthrid const subthrid)
{
    return subthrid->ctx->execstack.refs[pos]->mode;
}
void __fplyx_memram_sstackelmode(fplyx_vmem_t * const self, const unsigned char mode, const unsigned long pos, fplyx_memram_subthrid const subthrid)
{
    subthrid->ctx->execstack.refs[pos]->mode = mode;
}
void __fplyx_memram_slmapid(fplyx_vmem_t* const self, const unsigned long pos, fplyx_memram_subthrid const subthrid)
{
    fplyx_memram_t* const instance = self->_instance;
    if(subthrid?subthrid->subthr:0)
        subthrid->subthr->ctx._last_mapid = pos;
    else
        instance->ctx._last_mapid = pos;
}
unsigned long __fplyx_memram_gthriopos(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid)
{
    fplyx_memram_t* const instance = self->_instance;
    if(subthrid)
        return subthrid->subthr->ctx.iopos;
    else
        return instance->ctx.iopos;
}
void __fplyx_memram_sthriopos(fplyx_vmem_t * const self, const unsigned long pos, fplyx_memram_subthrid const subthrid)
{
    fplyx_memram_t* const instance = self->_instance;
    if(subthrid)
        subthrid->subthr->ctx.iopos = pos;
    else
        instance->ctx.iopos = pos;
}
unsigned int __fplyx_memram_thrcount(fplyx_vmem_t * self, fplyx_memram_subthrid subthrid)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context * const ctx = __fplyx_memram_getctx(instance, subthrid);
    return ctx->nsubthr;
}
unsigned long __fplyx_memram_thrgcount(fplyx_vmem_t * const self, fplyx_memram_subthrid subthrid)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context * const ctx = __fplyx_memram_getctx(instance, subthrid);
    return ctx->gsubthr;
}
void __fplyx_memram_thrrecurrent(fplyx_memram_t* const instance); /*neither used nor implemented*/
void __fplyx_memram_thriter(fplyx_vmem_t * const self, fplyx_memram_subthrid const result)
{
    /*almost the same thing as above*/
    fplyx_memram_t* const instance = self->_instance;
    fplyx_memram_subthr_t* const start = instance->current; /* prevent infinite loop */
    char ctrl;
    while(!ctrl)
    {
        if(!instance->subthrnciter)
        {
            /* first iteration or main thread queued */
            /* prepare first subthread if it exists to be pushed at next function call */
            if(instance->ctx.nsubthr)
            { /*has subthreads, prepare subthread handling next time*/
                instance->subthrciter = reallocarray(instance->subthrciter, 1, sizeof(unsigned int));
                if(!instance->subthrciter) return;
                instance->subthrnciter = 1;
                instance->subthrciter[0] = 0;
                instance->current = instance->ctx.subthr[0];
            }
            /* on first function call main context is pushed */
            if(!(instance->ctx.iostate&FPLYX_VMEMIOSTATE_FULLUNAVAIL) && instance->ctx.execstack.nref)
            {
                /*push main context*/
                result->id = 0;
                result->subthr = (void *)0;
                return;
            }
        } else {
            /*push the current subthread if it is available*/
            if(!(instance->current->ctx.iostate&FPLYX_VMEMIOSTATE_FULLUNAVAIL) && instance->current->ctx.execstack.nref)
            {
                result->id = instance->subthrciter[instance->subthrnciter-1];
                result->subthr = instance->current;
                ctrl &= ~2;
            }
            /*what is the next subthread?*/
            if(!(ctrl&2) && instance->current->ctx.nsubthr)
            { /*returned subthread has its own subthreads*/
                instance->subthrciter = reallocarray(instance->subthrciter, instance->subthrnciter+1, sizeof(unsigned int));
                if(!instance->subthrciter) return;
                instance->subthrnciter++;
                instance->subthrciter[instance->subthrnciter-1] = 0;
                /*next current is first subthread of prev current*/
                instance->current = instance->current->ctx.subthr[instance->subthrciter[instance->subthrnciter-1]];
            } else
              /*or it doesn't: in this case we move to the next subthread in its super context*/
            if(instance->subthrnciter == 1)
            { /*first depth subthread, next subthread at instance*/
                if(instance->subthrciter[0] < instance->ctx.nsubthr)
                {
                    ctrl &= ~2;
                    instance->subthrciter[0]++;
                    /*next current is one of the top subthreads*/
                    instance->current = instance->ctx.subthr[instance->subthrciter[0]];
                } else if(!(instance->ctx.iostate&FPLYX_VMEMIOSTATE_FULLUNAVAIL))
                { /*no subthreads left at the main thread, set the beginning*/
                    instance->subthrciter = realloc(instance->subthrciter, 0);
                    if(!instance->subthrciter) return;
                    instance->subthrnciter = 0;
                    instance->current = (void *)0;
                }
            } else
            { /*no subthreads of current, N-depth, N > 0, meaning that we have a parent subthread*/
                if(instance->subthrciter[instance->subthrnciter-1] < instance->current->parent->ctx.nsubthr)
                { /*select next subthread from its parent's subthreads list*/
                    ctrl &= ~2;
                    instance->subthrciter[instance->subthrnciter-1]++;
                    instance->current = instance->current->parent->ctx.subthr[instance->subthrnciter-1];
                } else { /*end of the list, returning back*/
                    instance->subthrciter = reallocarray(instance->subthrciter, instance->subthrnciter-1, sizeof(unsigned int));
                    if(!instance->subthrciter) return;
                    instance->subthrnciter--;
                    instance->current = instance->current->parent;
                    ctrl |= 2;
                }
            }
        }
        if(instance->current == start)
            break;
    }
}
char __fplyx_memram_iowreal(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    if(ctx->iostate&FPLYX_VMEMIOSTATE_FULLUNAVAIL)
        return 0;
    else
        ctx->iostate |= FPLYX_VMEMIOSTATE_REALPEND;
    return 1;
}
char __fplyx_memram_iowsubthr(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid, fplyx_memram_subthrid const target)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    if(ctx->iostate&FPLYX_VMEMIOSTATE_FULLUNAVAIL)
        return 0+16;
    if(!(target?target->subthr:0))
        return 0+4; /*waiting for main thread is invalid*/
    if((subthrid?subthrid->subthr:0) ==  (target?target->subthr:0))
        return 0+8; /*cannot wait itself*/
    if(!(target->subthr->ctx.nwatcher + 1))
        return 64;
    fplyx_memram_subthrid* watchers = reallocarray(target->subthr->ctx.watchers,
        target->subthr->ctx.nwatcher + 1, sizeof(void *));
    if(!watchers)
        return -128;
    target->subthr->ctx.nwatcher++;
    target->subthr->ctx.watchers = (void**) watchers;
    fplyx_memram_subthrid const copyid = malloc(sizeof(struct __fplyx_memram_subthrid));
    *copyid = *subthrid;
    if(!copyid) return -128;
    target->subthr->ctx.watchers[target->subthr->ctx.nwatcher-1] = copyid;
    ctx->iostate |= FPLYX_VMEMIOSTATE_SUBTHRPEND;
    return 1;
}
char __fplyx_memram_iowcdev(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid, fplyx_memram_cdevid const cdevid)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    if(ctx->iostate&FPLYX_VMEMIOSTATE_FULLUNAVAIL)
        return 0;
    if(cdevid->cdev)
        return 0;
    if(!cdevid->cdev)
        return 0+4;
    if(!(cdevid->cdev->nwatcher + 1))
        return 0+64;
    fplyx_memram_subthrid* watchers = reallocarray(cdevid->cdev->watchers,
        cdevid->cdev->nwatcher + 1, sizeof(void *));
    if(!watchers)
        return -128;
    cdevid->cdev->watchers = (void**) watchers;
    if(!(cdevid->cdev->nwatcher + 1))
        return 0+64;
    cdevid->cdev->nwatcher++;
    fplyx_memram_subthrid const copyid = malloc(sizeof(struct __fplyx_memram_subthrid));
    *copyid = *subthrid;
    cdevid->cdev->watchers[cdevid->cdev->nwatcher-1] = copyid;
    ctx->iostate |= FPLYX_VMEMIOSTATE_CDEVPEND;
    return 1;
}
char __fplyx_memram_iowextscope(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid, fplyx_memram_subthrid const target)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    struct fplyx_memram_context* const target_ctx = __fplyx_memram_getctx(instance, target);
    if(ctx->iostate&(FPLYX_VMEMIOSTATE_FULLUNAVAIL | FPLYX_VMEMIOSTATE_EXOSTACKPEND))
        return 0;
    if(ctx == target_ctx)
        return 0+4;
    if(!(target_ctx->nwatcher + 1))
        return 0+64;
    fplyx_memram_subthrid* watchers = reallocarray(target->subthr->ctx.watchers,
        target->subthr->ctx.nwatcher + 1, sizeof(void *));
    if(!watchers)
        return -128;
    target->subthr->ctx.nwatcher++;
    target->subthr->ctx.watchers = (void**) watchers;
    fplyx_memram_subthrid const copyid = malloc(sizeof(struct __fplyx_memram_subthrid));
    *copyid = *subthrid;
    target->subthr->ctx.watchers[target->subthr->ctx.nwatcher-1] = copyid;
    ctx->iostate |= FPLYX_VMEMIOSTATE_EXOSTACKPEND;
    return 1;
}
char __fplyx_memram_iounwextscope(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid, fplyx_memram_subthrid const target)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    struct fplyx_memram_context* const target_ctx = __fplyx_memram_getctx(instance, target);
    if(ctx->iostate&(FPLYX_VMEMIOSTATE_FULLUNAVAIL) || ~ctx->iostate&FPLYX_VMEMIOSTATE_EXOSTACKPEND)
        return 0; /*unwatch other things first*/
    if(ctx == target_ctx)
        return 0+4;
    if(!target_ctx->nwatcher)
        return 0+64;
    unsigned int id;
    for(unsigned int i = 0; i < target_ctx->nwatcher; i++)
    {
        if(((fplyx_memram_subthrid *)target_ctx->watchers)[i]->ctx == ctx)
        {
            id = i;
            break;
        }
    }
    if(!id) return 0+16;
    free(&target_ctx->watchers[id]);
    memmove(&target_ctx->watchers[id],
            &target_ctx->watchers[id+1],
            (target_ctx->nwatcher - 1 - id)*sizeof(void *));
    fplyx_memram_subthrid* watchers = reallocarray(target_ctx->watchers, target_ctx->nwatcher-1, sizeof(struct __fplyx_memram_subthrid));
    __fplyx_memram_cascadealloc(instance, sizeof(void *) + sizeof(struct __fplyx_memram_subthrid), 1, target?target->subthr:0);
    if(!watchers)
        return -128;
    target->subthr->ctx.nwatcher--;
    target->subthr->ctx.watchers = (void**) watchers;
    ctx->iostate &= ~FPLYX_VMEMIOSTATE_EXOSTACKPEND;
    return 1;
}
char __fplyx_memram_iounwsubthread(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid, fplyx_memram_subthrid const target)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    struct fplyx_memram_context* const target_ctx = __fplyx_memram_getctx(instance, target);
    if(~ctx->iostate&FPLYX_VMEMIOSTATE_SUBTHRPEND)
        return 0; /*not watching*/
    if(ctx == target_ctx)
        return 0+4;
    if(!target_ctx->nwatcher)
        return 0+64;
    unsigned int id;
    for(unsigned int i = 0; i < target_ctx->nwatcher; i++)
    {
        if(((fplyx_memram_subthrid *)target_ctx->watchers)[i]->ctx == ctx)
        {
            id = i;
            break;
        }
    }
    if(!id) return 0+16;
    free(&target_ctx->watchers[id]);
    memmove(&target_ctx->watchers[id],
            &target_ctx->watchers[id+1],
            (target_ctx->nwatcher - 1 - id)*sizeof(void *));
    fplyx_memram_subthrid* watchers = reallocarray(target_ctx->watchers, target_ctx->nwatcher-1, sizeof(struct __fplyx_memram_subthrid));
    __fplyx_memram_cascadealloc(instance, sizeof(void *) + sizeof(struct __fplyx_memram_subthrid), 1, target?target->subthr:0);
    if(!watchers)
        return -128;
    target->subthr->ctx.nwatcher--;
    target->subthr->ctx.watchers = (void**) watchers;
    ctx->iostate &= ~FPLYX_VMEMIOSTATE_SUBTHRPEND;
    return 1;
}
char __fplyx_memram_iounwcdev(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid, fplyx_memram_cdevid const cdevid)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    if(~ctx->iostate&FPLYX_VMEMIOSTATE_CDEVPEND)
        return 0;
    if(cdevid->cdev)
        return 0;
    if(!cdevid->cdev)
        return 0+4;
    if(!(cdevid->cdev->nwatcher))
        return 0+64;
    unsigned int id;
    for(unsigned int i = 0; i < cdevid->cdev->nwatcher; i++)
    {
        if(((fplyx_memram_subthrid *)cdevid->cdev->watchers)[i]->ctx == ctx)
        {
            id = i;
            break;
        }
    }
    if(!id) return 0+16;
    free(&cdevid->cdev->watchers[id]);
    memmove(&cdevid->cdev->watchers[id],
            &cdevid->cdev->watchers[id+1],
            (cdevid->cdev->nwatcher - 1 - id)*sizeof(void *));
    fplyx_memram_subthrid* watchers = reallocarray(cdevid->cdev->watchers,
        cdevid->cdev->nwatcher - 1, sizeof(void *));
    if(!watchers)
        return -128;
    cdevid->cdev->watchers = (void**) watchers;
    cdevid->cdev->nwatcher--;
    __fplyx_memram_cascadealloc(instance, sizeof(void *) + sizeof(struct __fplyx_memram_subthrid), 1, cdevid->subthr?cdevid->subthr:0);
    ctx->iostate &= ~FPLYX_VMEMIOSTATE_CDEVPEND;
    return 1;
}
char __fplyx_memram_iounwreal(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    if(~ctx->iostate&FPLYX_VMEMIOSTATE_REALPEND)
        return 0;
    else
        ctx->iostate &= ~FPLYX_VMEMIOSTATE_REALPEND;
    return 1;
}
unsigned int __fplyx_memram_iowcount(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    return ctx->nwatcher;
}
unsigned int __fplyx_memram_iocdevrcount(fplyx_vmem_t * const self, fplyx_memram_cdevid const cdevid)
{
    return cdevid->cdev->nwatcher;
}
void __fplyx_memram_iogwatcher(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid, const unsigned int id, fplyx_memram_subthrid const result)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    if(id > (ctx->nwatcher -1))
        return;
    if(subthrid?subthrid->subthr:0)
    {
        __fplyx_memram_thrsctxid(result->subthr->parent?&result->subthr->parent->ctx:&instance->ctx, subthrid->subthr);
        *result = *((fplyx_memram_subthrid *)ctx->watchers)[id];
    }
}
void __fplyx_memram_iogcdevreader(fplyx_vmem_t * const self, fplyx_memram_cdevid const cdevid, const unsigned int id, fplyx_memram_subthrid const result)
{
    if(id > (cdevid->cdev->nwatcher-1))
        return;
    *result = *((fplyx_memram_subthrid*)cdevid->cdev->watchers)[id];
}
char __fplyx_memram_thrcreate(fplyx_vmem_t * const self, char* const name, const char opts, fplyx_memram_subthrid const subthrid, fplyx_memram_subthrid const result)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    if(!ctx)
        return 0+8;
    unsigned long subthrmax = __fplyx_memram_cascadethrmax(instance, subthrid?subthrid->subthr:0);
    if(subthrmax && (ctx->gsubthr == subthrmax))
        return 0+4;
    /* check if memory is available */
    const size_t max = __fplyx_memram_cascademax(instance, subthrid?subthrid->subthr:0);
    const size_t total_size_allocated = sizeof(fplyx_memram_subthr_t)+sizeof(fplyx_memram_subthr_t*); 
    if((ctx->alloc + total_size_allocated) > max)
        /* error, not enough memory */
        return 0+2;
    if(ctx->nsubthr + 1 == 0)
        return 0; /*integer overflow*/
    fplyx_memram_subthr_t* const target = malloc(sizeof(fplyx_memram_subthr_t));
    if(!target) return -128;
    const char res = __fplyx_memram_cascadealloc(instance, total_size_allocated, 0, subthrid?subthrid->subthr:0);
    if(~res&1)
        return res;
    memset(target, 0, sizeof(fplyx_memram_subthr_t));
    target->name = name;
    if(subthrid)
    {
        target->depth = subthrid->subthr->depth + 1;
        target->parent = subthrid->subthr;
    }
    else
        target->depth = 1;
    target->flags = opts;
    target->ctx.cdevs = NULL;
    target->ctx.subthr = NULL;
    target->ctx.execstack.refs = NULL;
    target->ctx.watchers = NULL;
    /*inherit limits*/
    target->ctx.max = ctx->max;
    target->ctx.max_nsubthr = ctx->max_nsubthr;
    __fplyx_memram_cascadethrgmod(instance, 1, 0, subthrid?subthrid->subthr:0);
    fplyx_memram_subthr_t** const subthr = reallocarray(ctx->subthr, ctx->nsubthr + 1, sizeof(fplyx_memram_subthr_t *));
    if(!subthr) return -128;
    ctx->nsubthr++;
    ctx->subthr = subthr;
    subthr[ctx->nsubthr-1] = target;
    if(result)
    {
        result->id = 0;
        result->subthr = target;
    }
    return 1;
}
unsigned long __fplyx_memram_extstackat(struct fplyx_memram_context* const ctx, struct fplyx_memram_context* const target_ctx)
{
    for(unsigned long i = 0; i < ctx->execstack.nref; i++)
        for(unsigned long j = 0; j < target_ctx->execstack.nref; j++)
            if(&ctx->execstack.refs[i]->ntab == target_ctx->execstack.refs[j]->add_ntab)
                return j;
    return 0; /*it's impossible to have an additive ntab at first element in the stack*/
}
size_t __fplyx_memram_recurthrdel(fplyx_vmem_t* const self, fplyx_memram_subthrid const subthrid, const char recurring)
{
    fplyx_memram_t* const instance = self->_instance;
    struct __fplyx_memram_ndataid ndc;
    struct __fplyx_memram_cdevid cdc;
    struct __fplyx_memram_subthrid sbc;
    struct fplyx_memram_context* refctx;
    size_t total_free = sizeof(fplyx_memram_subthr_t);
    if(subthrid->subthr->ctx.nsubthr)
    {
        /*using native C recursion as it's unnecessary to avoid anyway*/
        fplyx_memram_subthr_t* backup;
        for(unsigned int i = 0; i < subthrid->subthr->ctx.nsubthr; i++)
        {
            sbc.id = i;
            sbc.subthr = subthrid->subthr->ctx.subthr[i];
            /* recurring should only be true at recursive call to prevent extra operations*/
            total_free += __fplyx_memram_recurthrdel(self, &sbc, 1);
        }
    } else {
        /*delete custom devices*/
        for(unsigned int i = 0; i < subthrid->subthr->ctx.cdevc; i++)
        {
            total_free += strlen(subthrid->subthr->ctx.cdevs[i]->ibuffname);
            total_free += strlen(subthrid->subthr->ctx.cdevs[i]->ihndname);
            total_free += strlen(subthrid->subthr->ctx.cdevs[i]->name);
            total_free += strlen(subthrid->subthr->ctx.cdevs[i]->obuffname);
            total_free += strlen(subthrid->subthr->ctx.cdevs[i]->ohndname);
            total_free += 5;
            free(subthrid->subthr->ctx.cdevs[i]->ibuffname);
            free(subthrid->subthr->ctx.cdevs[i]->ihndname);
            free(subthrid->subthr->ctx.cdevs[i]->name);
            free(subthrid->subthr->ctx.cdevs[i]->obuffname);
            free(subthrid->subthr->ctx.cdevs[i]->ohndname);
            total_free += sizeof(fplyx_memram_cdev_t);
            free(subthrid->subthr->ctx.cdevs[i]);
            total_free += sizeof(fplyx_memram_cdev_t *);
        }
        free(subthrid->subthr->ctx.cdevs);
        /*not counting ctx.cdevs because the whole context sizeof(struct fplyx_memram_context) is counted*/
        /*delete devrefkits*/
        for(unsigned int i = 0; i < subthrid->subthr->ctx.ndevkit; i++)
        {
            /*dereference ourselves from contexts that were sending devices here*/
            fplyx_memram_subthrid targetsubthr = subthrid->subthr->ctx.devkits[i]->subthrid;
            for(unsigned int j = 0; j < targetsubthr->subthr->ctx.nsharing; j++)
            { /*target contexts*/
                if(targetsubthr->subthr->ctx.dev_sharing_to[j] == &subthrid->subthr->ctx)
                { /*we are the target*/
                    if(j != targetsubthr->subthr->ctx.nsharing - 1)
                    { /*we do shift elements in the target recipients*/
                        memmove(&targetsubthr->subthr->ctx.dev_sharing_to[j],
                                &targetsubthr->subthr->ctx.dev_sharing_to[j+1],
                                (targetsubthr->subthr->ctx.nsharing - j - 1));
                    }
                    struct fplyx_memram_context** dev_sharing_to = reallocarray(
                        targetsubthr->subthr->ctx.dev_sharing_to,
                        --targetsubthr->subthr->ctx.nsharing,
                        sizeof(void *));
                    if(!dev_sharing_to) return total_free;
                    targetsubthr->subthr->ctx.dev_sharing_to = dev_sharing_to;
                    /* memory is freed somewhere else */
                    __fplyx_memram_cascadealloc(instance, sizeof(void *), 1, targetsubthr->subthr);
                }
            }
            /*free the name buffers here*/
            for(unsigned int j = 0; j < subthrid->subthr->ctx.devkits[i]->amount; j++)
            {
                total_free += strlen(subthrid->subthr->ctx.devkits[i]->names_from[j]) + 1;
                total_free += strlen(subthrid->subthr->ctx.devkits[i]->names_to[j]) + 1;
                free(subthrid->subthr->ctx.devkits[i]->names_from[j]);
                free(subthrid->subthr->ctx.devkits[i]->names_to[j]);
            }
            total_free += sizeof(struct __fplyx_memram_subthrid);
            free(subthrid->subthr->ctx.devkits[i]->subthrid);
            total_free += sizeof(fplyx_memram_devrefkit_t);
            free(subthrid->subthr->ctx.devkits[i]);
            total_free += sizeof(fplyx_memram_devrefkit_t *);
        }
        free(subthrid->subthr->ctx.devkits);
        /*delete execution stack*/
        for(unsigned int i = 0; i < subthrid->subthr->ctx.execstack.nref; i++)
        {
            free(subthrid->subthr->ctx.execstack.refs[i]->namedataid);
            if(subthrid->subthr->ctx.execstack.refs[i]->result_namedataid)
            {
                free(subthrid->subthr->ctx.execstack.refs[i]->result_namedataid);
                total_free += sizeof(struct __fplyx_memram_ndataid);
            }
            for(unsigned long j = 0; j < subthrid->subthr->ctx.execstack.refs[i]->ntab.ntabc; j++)
            {
                free(subthrid->subthr->ctx.execstack.refs[i]->ntab.ntabname[j]);
                ndc.ctx = &subthrid->subthr->ctx;
                ndc.id = j;
                ndc.ndata = subthrid->subthr->ctx.execstack.refs[i]->ntab.ntabaddr[j];
                ndc.stackpos = i;
                ndc.subthrid = *subthrid;
                ndc.ndata->refopts |= 2; /*don't perform ntab shift because ntab will be freed*/
                /* not counting: memory is freed explicitly*/
                __fplyx_memram_dnd(self, &ndc);
                total_free += sizeof(fplyx_memram_ndata_t *);
                total_free += sizeof(char*);
            }
            free(subthrid->subthr->ctx.execstack.refs[i]->ntab.ntabname);
            free(subthrid->subthr->ctx.execstack.refs[i]->ntab.ntabaddr);
        }
        free(subthrid->subthr->ctx.execstack.refs);
        free(subthrid->subthr->name);
        /*also unfreeze all the watchers*/
        struct fplyx_memram_context* ctx;
        for(unsigned int i = 0; i < subthrid->subthr->ctx.nwatcher; i++)
        { /*iterate over watchers*/
            sbc = *((fplyx_memram_subthrid*)subthrid->subthr->ctx.watchers)[i];
            ctx = __fplyx_memram_getctx(instance, &sbc);
            if(ctx->iostate&FPLYX_VMEMIOSTATE_EXOSTACKPEND)
            {
                /*lookup entire stack*/
                unsigned long stackfrom = __fplyx_memram_extstackat(&subthrid->subthr->ctx, ctx);
                if(stackfrom)
                {
                    for(unsigned long j = 0; j < (ctx->execstack.nref - stackfrom); j++)
                        __fplyx_memram_dec_execstack(self, &sbc);
                    /*unset everything except if this subthread is suspended*/
                    ctx->iostate &= (FPLYX_VMEMIOSTATE_SUSPEND);
                }
            }
            else if(ctx->iostate&FPLYX_VMEMIOSTATE_SUBTHRPEND)
                ctx->iostate &= ~FPLYX_VMEMIOSTATE_SUBTHRPEND;
            free(subthrid->subthr->ctx.watchers[i]);
            total_free += sizeof(struct __fplyx_memram_subthrid);
            total_free += sizeof(fplyx_memram_subthrid);
        }
        free(subthrid->subthr->ctx.watchers);
        /*also dereference devkits from contexts that were using our devices*/
        for(unsigned int i = 0; i < subthrid->ctx->nsharing; i++)
        { /*go through all of the recipient subthreads*/
            size_t local_free;
            refctx = subthrid->ctx->dev_sharing_to[i];
            for(unsigned int j = 0; j < refctx->ndevkit; j++)
            { /*look for devref that refers to this subthread*/
                if(((fplyx_memram_subthrid)refctx->devkits[j]->subthrid)->subthr == subthrid->subthr)
                { /*that's the devkit index we need*/
                    for(unsigned int k = 0; k < refctx->devkits[j]->amount; k++)
                    {
                        local_free += strlen(refctx->devkits[j]->names_from[k]) + 1;
                        local_free += strlen(refctx->devkits[j]->names_to[k]) + 1;
                        free(refctx->devkits[j]->names_from[k]);
                        free(refctx->devkits[j]->names_to[k]);
                        local_free += sizeof(char *)*2;
                    }
                    free(refctx->devkits[j]->subthrid);
                    local_free += sizeof(struct __fplyx_memram_subthrid);
                    free(refctx->devkits[j]);
                    if(j != refctx->ndevkit - 1)
                    {
                        memmove(&refctx->devkits[j],
                                &refctx->devkits[j+1],
                                (refctx->ndevkit - j - 1)*sizeof(void *));
                    }
                    fplyx_memram_devrefkit_t** devrefs = reallocarray(refctx->devkits, --refctx->ndevkit, sizeof(void *));
                    if(!devrefs) return total_free;
                    local_free += sizeof(fplyx_memram_devrefkit_t *);
                    refctx->devkits = devrefs;
                    break; /*cannot continue since iterable array is modified*/
                }
            }
        }
    }
    if(!recurring)
    { /*this function call is not recursive*/
        struct fplyx_memram_context* super_ctx; //only if recurring is 0
        if(!subthrid->subthr->parent)
            super_ctx = &instance->ctx;
        else
            super_ctx = &subthrid->subthr->parent->ctx;
        /*smash its pointer in super ctx subthr list*/
        memmove(&super_ctx->subthr[subthrid->id],
                &super_ctx->subthr[subthrid->id + 1],
                (super_ctx->nsubthr - subthrid->id - 1)*sizeof(void *));
        /*also shrink the list*/
        fplyx_memram_subthr_t** subthr = reallocarray(super_ctx->subthr, super_ctx->nsubthr-1, sizeof(void *));
        if(!subthr) return total_free;
        total_free += sizeof(void *);
        super_ctx->nsubthr--;
        super_ctx->subthr = subthr;
    }
    free(subthrid->subthr);
    return total_free;
}
char __fplyx_memram_thrdel(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid) { //NOTE: this does NOT remove subthread exec code, but removes this subthread from thread table
    size_t total_free = __fplyx_memram_recurthrdel(self, subthrid, 0);
    __fplyx_memram_cascadealloc(self->_instance, total_free, 1, subthrid->subthr->parent);
    memset(subthrid, 0, sizeof(struct __fplyx_memram_subthrid)); /*interpreters should be advised to unwatch this subthread before deletion*/
    return 1;
}
char __fplyx_memram_thrsus(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid, const char mode)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    if(!(mode ^ (ctx->iostate << FPLYX_VMEMIOSTATE_SUSPEND)))
        return 0;
    if(mode)
        ctx->iostate |= FPLYX_VMEMIOSTATE_SUSPEND;
    else
        ctx->iostate &= ~FPLYX_VMEMIOSTATE_SUSPEND;
    return 1;
}
unsigned char __fplyx_memram_gthriostate(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    return ctx->iostate;
}
//these functions does apply to encapsulated subthreads only!
unsigned int __fplyx_memram_thrlim(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid)
{
    if(!(subthrid?subthrid->subthr:0))
        return 0;
    return subthrid->subthr->ctx.max_nsubthr;
}
char __fplyx_memram_thrlimset(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid, const unsigned int amount)
{
    fplyx_memram_t* const instance = self->_instance;
    if(!(subthrid?subthrid->subthr:0))
    {
        struct fplyx_memram_context* const super_ctx = subthrid->subthr->parent ? &subthrid->subthr->parent->ctx : &instance->ctx;
        if((super_ctx->max_nsubthr && (amount > super_ctx->max_nsubthr)) || !amount)
            subthrid->subthr->ctx.max_nsubthr = super_ctx->max_nsubthr;
        else
            subthrid->subthr->ctx.max_nsubthr = amount;
    } else {
        instance->ctx.max_nsubthr = amount;
    }
    return 1;
}
unsigned long __fplyx_memram_thrmemlim(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    return ctx->max;
}
char __fplyx_memram_thrmemlimset(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid, size_t size)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    if(ctx == &instance->ctx)
    {
        ctx->max = size;
        return 1;
    }
    struct fplyx_memram_context* const super_ctx = subthrid->subthr->parent?&subthrid->subthr->parent->ctx:&instance->ctx;
    if(size > super_ctx->max)
        ctx->max = super_ctx->max;
    else
        ctx->max = size;
    return 1;
}
char __fplyx_memram_thrdevref(fplyx_vmem_t * const self, char* realdev, char* const virtualdev, fplyx_memram_subthrid const subthrid_from, fplyx_memram_subthrid const subthrid_to)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid_from);
    struct fplyx_memram_context* target_ctx = __fplyx_memram_getctx(instance, subthrid_to);
    if((ctx->ndevkit + 1))
        return 0+64;
    struct __fplyx_memram_subthrid target_subthrid;
    char* const realdev2 = __fplyx_memram_thrdevresolv(self, realdev, subthrid_to, &target_subthrid);
    if(realdev2)
    {
        target_ctx = target_subthrid.ctx;
        free(realdev);
        realdev = realdev2;
    }
    const size_t max = __fplyx_memram_cascademax(instance, subthrid_from?subthrid_from->subthr:0);
    const size_t target_max = __fplyx_memram_cascademax(instance, subthrid_to?subthrid_to->subthr:0);
    size_t total_needed = strlen(realdev) + strlen(virtualdev) + 2 + sizeof(char*)*2 /*real and virtual name are allocated somewhere else (ALLOCREADPTR off)*/;
    const size_t target_total_needed = sizeof(struct fplyx_memram_context *);
    unsigned int id;
    char found = 0; /* the kit does exist in the list */
    fplyx_memram_devrefkit_t* devkit;
    if(!ctx->ndevkit)
        total_needed += sizeof(fplyx_memram_devrefkit_t) + sizeof(fplyx_memram_devrefkit_t *);
    else
    {
        for(id = 0; id < ctx->ndevkit; id++)
        {
            if(((fplyx_memram_subthrid)ctx->devkits[id])->subthr == subthrid_to->subthr)
            {
                found = 1;
                break;
            }
        }
        if(!found)
            total_needed += sizeof(fplyx_memram_devrefkit_t *) + sizeof(fplyx_memram_devrefkit_t) + sizeof(struct __fplyx_memram_subthrid);
    }
    if(ctx->alloc + total_needed > max)
        return 0+2; /*not enough memory*/
    if(target_ctx->alloc + target_total_needed > target_max)
        return 0+16; /*not enough memory at target*/
    if(!(ctx->ndevkit + 1))
        return 0+64;
    if(!(target_ctx->nsharing + 1))
        return 0+64;
    for(unsigned int i = ctx->ndevkit - 1; i >= 0; i--)
    {
        for(unsigned int j = ctx->devkits[i]->amount - 1; j >= 0; i--)
        {
            if(!strcmp(ctx->devkits[i]->names_from[j], virtualdev))
                return 0+32;
            if(!j) break;
        }
        if(!i) break;
    }
    if(!target_ctx->nsharing)
    {
        target_ctx->dev_sharing_to = calloc(1, sizeof(struct fplyx_memram_context *));
        if(!ctx->dev_sharing_to) return -128;
        target_ctx->nsharing++;
    }
    if(!ctx->ndevkit)
    {
        ctx->devkits = calloc(1, sizeof(fplyx_memram_devrefkit_t*));
        if(!ctx->devkits) return -128;
        ctx->ndevkit++;
        devkit = malloc(sizeof(fplyx_memram_devrefkit_t));
        if(!devkit) return -128;
        memset(devkit, 0, sizeof(fplyx_memram_devrefkit_t));
    }
    else if(!found)
    {
        devkit = malloc(sizeof(fplyx_memram_devrefkit_t));
        if(!devkit) return -128;
        memset(devkit, 0, sizeof(fplyx_memram_devrefkit_t));
        fplyx_memram_devrefkit_t** devkits = reallocarray(ctx->devkits, ctx->ndevkit+1, sizeof(fplyx_memram_devrefkit_t *));
        if(!devkits) return -128;
        ctx->devkits = devkits;
        devkits[ctx->ndevkit] = devkit;
        ctx->ndevkit++;
        devkit->subthrid = malloc(sizeof(struct __fplyx_memram_subthrid));
        *((fplyx_memram_subthrid)devkit->subthrid) = *subthrid_to;
    }
    else
        devkit = ctx->devkits[id];
    if(!(devkit->amount + 1))
        return 0+64;
    if(1&~__fplyx_memram_cascadealloc(instance, total_needed, 0, subthrid_from?subthrid_from->subthr:0))
        return 0+2;
    /* ALLOCREADPTR 0: realdev and virtualdev pointers are taken under control */
    char** names_from = reallocarray(devkit->names_from, devkit->amount+1, sizeof(char*));
    if(!names_from) return -128;
    char** names_to = reallocarray(devkit->names_to, devkit->amount+1, sizeof(char*));
    if(!names_to) return -128;
    names_from[devkit->amount] = virtualdev;
    names_to[devkit->amount] = realdev;
    devkit->names_from = names_from;
    devkit->names_to = names_to;
    devkit->amount++;
    /* create a backreference */
    if(1&~__fplyx_memram_cascadealloc(instance, target_total_needed, 0, subthrid_to?subthrid_to->subthr:0))
        return 0+2;
    struct fplyx_memram_context** sharing = reallocarray(target_ctx->dev_sharing_to, target_ctx->nsharing + 1, sizeof(struct fplyx_memram_context*));
    if(!sharing) return -128;
    sharing[target_ctx->nsharing] = ctx;
    target_ctx->nsharing++;
    target_ctx->dev_sharing_to = sharing;
    return 1;
}
char __fplyx_memram_thrdevunref(fplyx_vmem_t * const self, char* virtualdev, fplyx_memram_subthrid const subthrid)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    size_t total_free = strlen(virtualdev) /* + strlen(realdev)*/ + 2 + sizeof(char*)*2;
    size_t target_total_free = sizeof(struct fplyx_memram_context *);
    if(!ctx->ndevkit)
        return 0+4;
    unsigned long devkit_id;
    unsigned int field_id;
    char found = 0;
    for(devkit_id = ctx->ndevkit - 1; devkit_id >= 0; devkit_id--)
    {
        for(field_id = ctx->devkits[devkit_id]->amount - 1; field_id >= 0; devkit_id--)
        {
            if(!strcmp(ctx->devkits[devkit_id]->names_from[field_id], virtualdev))
                found = 1;
            if(!field_id) break;
        }
        if(!devkit_id) break;
    }
    if(!found) return 0+4;
    fplyx_memram_subthr_t* const target_subthr = ((fplyx_memram_subthrid)ctx->devkits[devkit_id]->subthrid)->subthr;
    if(!target_subthr->ctx.nsharing)
        /*this shouldn't happen*/
        abort();
    unsigned int dsharing;
    for(dsharing = target_subthr->ctx.nsharing - 1; dsharing >= 0; dsharing--)
    {
        if(target_subthr->ctx.dev_sharing_to[dsharing] == ctx) break;
        if(!dsharing) break;
    }
    if(target_subthr->ctx.dev_sharing_to[dsharing] != ctx)
        abort();
    /* dereference */
    if(dsharing < target_subthr->ctx.nsharing - 1)
    {
        memmove(&target_subthr->ctx.dev_sharing_to[dsharing],
                &target_subthr->ctx.dev_sharing_to[dsharing + 1],
                (target_subthr->ctx.nsharing - dsharing - 1)*sizeof(struct fplyx_memram_context *)
                );
    }
    struct fplyx_memram_context ** const dev_sharing_to = reallocarray(target_subthr->ctx.dev_sharing_to, --target_subthr->ctx.nsharing, sizeof(struct fplyx_memram_context *));
    if(!dev_sharing_to) abort();
    target_subthr->ctx.dev_sharing_to = dev_sharing_to;
    /* remove names from devkit */ 
    free(ctx->devkits[devkit_id]->names_from[field_id]);
    free(ctx->devkits[devkit_id]->names_to[field_id]);
    if(field_id < ctx->devkits[devkit_id]->amount - 1)
    {
        memmove(&ctx->devkits[devkit_id]->names_from[field_id],
                &ctx->devkits[devkit_id]->names_from[field_id],
                (ctx->devkits[devkit_id]->amount - field_id - 1)*sizeof(char *)
                );
        memmove(&ctx->devkits[devkit_id]->names_to[field_id],
                &ctx->devkits[devkit_id]->names_to[field_id],
                (ctx->devkits[devkit_id]->amount - field_id - 1)*sizeof(char *)
                );
    }
    ctx->devkits[devkit_id]->names_from = reallocarray(ctx->devkits[devkit_id]->names_from, ctx->devkits[devkit_id]->amount-1, sizeof(char *));
    ctx->devkits[devkit_id]->names_from = reallocarray(ctx->devkits[devkit_id]->names_to, ctx->devkits[devkit_id]->amount-1, sizeof(char *));
    if(!(--ctx->devkits[devkit_id]->amount))
    {
        total_free += sizeof(fplyx_memram_devrefkit_t*) + sizeof(struct __fplyx_memram_subthrid) + sizeof(fplyx_memram_devrefkit_t);
        free(ctx->devkits[devkit_id]->subthrid);
        free(ctx->devkits[devkit_id]->names_from); /*size 0, not counted*/
        free(ctx->devkits[devkit_id]->names_to); /*size 0, not counted*/
        free(ctx->devkits[devkit_id]);
        if(devkit_id < ctx->ndevkit - 1)
            memmove(&ctx->devkits[devkit_id],
                    &ctx->devkits[devkit_id + 1],
                    (ctx->ndevkit - devkit_id - 1)*sizeof(fplyx_memram_devrefkit_t *)
                    );
        ctx->devkits = reallocarray(ctx->devkits, --ctx->ndevkit, sizeof(fplyx_memram_devrefkit_t*));
    }
    __fplyx_memram_cascadealloc(instance, total_free, 1, subthrid?subthrid->subthr:0);
    __fplyx_memram_cascadealloc(instance, target_total_free, 1, target_subthr);
    return 1;
}
char* __fplyx_memram_thrdevresolv(fplyx_vmem_t * self, char* name, fplyx_memram_subthrid subthrid, fplyx_memram_subthrid result)
{
    unsigned long devkit_id;
    unsigned int field_id;
    char found = 0;
    for(devkit_id = subthrid->ctx->ndevkit - 1; devkit_id >= 0; devkit_id--)
    {
        for(field_id = subthrid->ctx->devkits[devkit_id]->amount - 1; field_id >= 0; field_id--)
        {
            if(!strcmp(subthrid->ctx->devkits[devkit_id]->names_from[field_id], name))
            {
                found = 1;
                break;
            }
            if(!field_id) break;
        }
        if(!devkit_id) break;
    }
    if(!found) return (void *)0;
    *result = *((fplyx_memram_subthrid)subthrid->ctx->devkits[devkit_id]->subthrid);
    return subthrid->ctx->devkits[devkit_id]->names_to[field_id];
}
size_t __fplyx_memram_thrsz(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid)
{
    return subthrid->ctx->alloc;
}
char __fplyx_memram_thrsuperflags(fplyx_vmem_t* const self, fplyx_memram_subthrid const subthrid)
{
    if(!(subthrid?subthrid->subthr:0))
        return 0;
    fplyx_memram_subthr_t* current = subthrid->subthr;
    char sum = 0;
    for(unsigned int dp = subthrid->subthr->depth; dp > 0; dp--)
    {
        sum |= current->flags;
        if(!current->parent) break;
        current = current->parent;
    }
    return sum;
}
//Soft DEPRECATED: store annotations in the data
/*char* __fplyx_memram_rannot(fplyx_vmem_t * const self, fplyx_memram_ndataid const ndataid, const size_t limit);
char __fplyx_memram_sannot(fplyx_vmem_t * const self, fplyx_memram_ndataid const ndataid, char* data); */
//name, input handler, output handler, input buffer name, limit, output buffer name, limit, subthread data...
char __fplyx_memram_cdevcreate(fplyx_vmem_t * const self, char* const name, char* const ihnd, char* const ohnd, char* const ibuff, const unsigned int iblimit, char* const obuff, const unsigned int oblimit, fplyx_memram_subthrid const subthrid, fplyx_memram_cdevid const result)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    const size_t total_needed = sizeof(fplyx_memram_cdev_t *) + sizeof(fplyx_memram_cdev_t) +
                                strlen(name) + 1 +
                                strlen(ihnd) + 1 +
                                strlen(ohnd) + 1 +
                                strlen(ibuff) + 1 +
                                strlen(obuff) + 1;
    /*checks: does this cdevice exists?*/
    struct __fplyx_memram_cdevid cdevexists;
    __fplyx_memram_cdevget(self, name, subthrid, &cdevexists);
    if(cdevexists.cdev)
        return 0+4;
    /*checks: memory*/
    const size_t max = __fplyx_memram_cascademax(instance, subthrid?subthrid->subthr:0);
    if(total_needed > max)
        return 0+2;
    if(1&~__fplyx_memram_cascadealloc(instance, total_needed, 0, subthrid?subthrid->subthr:0))
        return 0+2;
    struct __fplyx_memram_ndataid ndexists;
    /*temporarily jump to the root exec stack to work with the global names*/
    __fplyx_memram_getndata(self, ihnd, 0, subthrid, &ndexists);
    if(!ndexists.ndata)
    {
        char* ibdata = malloc(iblimit);
        if(!ibdata) return -128;
        memset(ibdata, 0, iblimit);
        if(1&~__fplyx_memram_wnd(self, ibuff, ibdata, 0, subthrid, &ndexists))
        {
            free(ibdata);
            return 0+2;
        }
    }
    __fplyx_memram_getndata(self, ohnd, 0, subthrid, &ndexists);
    if(!ndexists.ndata)
    {
        char* obdata = malloc(oblimit);
        if(!obdata) return -128;
        memset(obdata, 0, oblimit);
        if(1&~__fplyx_memram_wnd(self, ibuff, obdata, 0, subthrid, &ndexists))
        {
            free(obdata);
            return 0+2;
        }
    }
    /*allocate*/
    fplyx_memram_cdev_t* const target = malloc(sizeof(fplyx_memram_cdev_t)); /*checked and counted*/
    if(!target) return -128;
    memset(target, 0, sizeof(fplyx_memram_cdev_t));
    /* ALLOCREADPTR 0: taking control over names on success */
    target->ibufflimit = iblimit;
    target->ibuffname = ibuff;
    target->ihndname = ihnd;
    target->name = name;
    target->obufflimit = oblimit;
    target->obuffname = obuff;
    target->ohndname = ohnd;
    /*appending to the list*/
    fplyx_memram_cdev_t** const cdevs = reallocarray(ctx->cdevs, ctx->cdevc + 1, sizeof(fplyx_memram_cdev_t *));
    if(!cdevs) return -128;
    ctx->cdevs = cdevs;
    cdevs[ctx->cdevc] = target;
    ctx->cdevc++;
    return 1;
}
unsigned int __fplyx_memram_cdevamount(fplyx_vmem_t * self, fplyx_memram_subthrid subthrid)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    return ctx->cdevc;
}
void __fplyx_memram_cdev_at(fplyx_vmem_t * self, unsigned int id, fplyx_memram_subthrid const subthrid, fplyx_memram_cdevid const result)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    result->ctx = ctx;
    if(id > ctx->cdevc - 1)
        id = ctx->cdevc - 1;
    result->cdev = ctx->cdevs[id];
}
char __fplyx_memram_cdevget(fplyx_vmem_t * self, char* name, fplyx_memram_subthrid subthrid, fplyx_memram_cdevid result)
{
    fplyx_memram_t* const instance = self->_instance;
    struct fplyx_memram_context* const ctx = __fplyx_memram_getctx(instance, subthrid);
    result->ctx = ctx;
    unsigned int wrapped_i = ctx->_last_cdevmapid;
    unsigned int wrapped_ri = ctx->_last_cdevmapid;
    if(ctx->_last_cdevmapid >= ctx->cdevc)
        ctx->_last_subthrmapid = ctx->nsubthr - 1;
    if(!result->subthr) return 2;
    char found = 0;
    unsigned int id;
    result->subthr = subthrid->subthr;
    unsigned int start = result->subthr?result->subthr->depth:0;
    for(unsigned int depth = start; depth >= 0; depth--)
    {
        if(result->subthr)
            result->ctx = &result->subthr->ctx;
        else
            result->ctx = &instance->ctx;
        if(depth != start && (result->subthr->flags&FPLYX_VMEMSUBTHR_DEVICES))
            return 0+4;
        for(id = 0; id <= (result->ctx->cdevc / 2); id++) /* index of requested name */
        {
            if(!id)
            {
                if(!strcmp(result->ctx->cdevs[wrapped_i]->name, name))
                {
                    result->id = id;
                    found = 1;
                    break;
                }
            } else {
                if(wrapped_i < result->ctx->cdevc-1) wrapped_i++; else wrapped_i = 0;
                if(wrapped_ri) wrapped_ri--; else wrapped_ri = result->ctx->cdevc-1;
                if(wrapped_i == wrapped_ri) break;
                if(!strcmp(result->ctx->cdevs[wrapped_i]->name, name))
                {
                    result->cdev = result->ctx->cdevs[wrapped_i];
                    result->id = wrapped_i;
                    found = 1;
                    result->ctx->_last_cdevmapid = wrapped_i;
                    break;
                }
                if(!strcmp(result->ctx->cdevs[wrapped_ri]->name, name))
                {
                    result->cdev = ctx->cdevs[wrapped_ri];
                    result->id = wrapped_ri;
                    found = 1;
                    result->ctx->_last_cdevmapid = wrapped_ri;
                    break;
                }
            }
        }
        if(!depth) break;
        result->subthr = result->subthr->parent;
    }
    if(!found) return 2;
    return 1;
}
char __fplyx_memram_cdevdel(fplyx_vmem_t * const self, fplyx_memram_cdevid const cdevid)
{
    fplyx_memram_t* const instance = self->_instance;
    size_t total_free = sizeof(fplyx_memram_cdev_t *) + sizeof(fplyx_memram_cdev_t) +
                        strlen(cdevid->cdev->ibuffname) + 1 +
                        strlen(cdevid->cdev->ihndname) + 1 +
                        strlen(cdevid->cdev->name) + 1 +
                        strlen(cdevid->cdev->obuffname) + 1 +
                        strlen(cdevid->cdev->ohndname) + 1 +
                        (sizeof(fplyx_memram_subthrid) + sizeof(struct __fplyx_memram_subthrid))*cdevid->cdev->nwatcher;
    if(1&~__fplyx_memram_cascadealloc(instance, total_free, 1, cdevid->subthr))
        return 0+2;
    /*unwatch subthreads*/
    for(unsigned int i = 0; i < cdevid->cdev->nwatcher; i++)
    {
        ((fplyx_memram_subthrid)cdevid->cdev->watchers[i])->ctx->iostate &= ~FPLYX_VMEMIOSTATE_CDEVPEND;
        free(cdevid->cdev->watchers[i]);
    }
    free(cdevid->cdev->watchers);
    free(cdevid->cdev->ibuffname);
    free(cdevid->cdev->ihndname);
    free(cdevid->cdev->obuffname);
    free(cdevid->cdev->ohndname);
    free(cdevid->cdev->name);
    free(cdevid->cdev);
    cdevid->cdev = NULL;
    if(cdevid->id < (cdevid->ctx->cdevc - 1))
    {
        memmove(&cdevid->ctx->cdevs[cdevid->id],
                &cdevid->ctx->cdevs[cdevid->id + 1],
                (cdevid->ctx->cdevc - cdevid->id - 1)*sizeof(fplyx_memram_cdev_t *));
    }
    fplyx_memram_cdev_t** const cdevs = reallocarray(cdevid->ctx->cdevs, cdevid->ctx->cdevc - 1, sizeof(fplyx_memram_cdev_t *));
    if(!cdevs) return -128;
    cdevid->ctx->cdevc--;
    return 1;
}
char* __fplyx_memram_cdevgihnd(fplyx_vmem_t * const self, fplyx_memram_cdevid const cdevid)
{
    return cdevid->cdev->ihndname;
}
char* __fplyx_memram_cdevgohnd(fplyx_vmem_t * const self, fplyx_memram_cdevid const cdevid)
{
    return cdevid->cdev->ohndname;
}
char __fplyx_memram_cdevsihnd(fplyx_vmem_t * const self, fplyx_memram_cdevid const cdevid, char* const ihnd)
{
    fplyx_memram_t* const instance = self->_instance;
    if(!(cdevid?cdevid->cdev:0))
        return 0;
    char mod;
    size_t diff;
    const unsigned long len1 = strlen(ihnd) + 1;
    const unsigned long len2 = strlen(cdevid->cdev->ihndname) + 1;
    if(!cdevid->cdev->ihndname)
    {
        __fplyx_memram_cascadealloc(instance, len1, 0, cdevid->subthr);
        cdevid->cdev->ihndname = ihnd;
        return 1;
    }
    if(len1 > len2)
    {
        diff = len1 - len2;
        mod = 0;
    }
    else if (len1 < len2) 
    {
        diff = len2 - len1;
        mod = 1;
    }
    else
    {
        /*no changes on the size*/
        free(cdevid->cdev->ihndname);
        cdevid->cdev->ihndname = ihnd;
        return 1;
    }
    __fplyx_memram_cascadealloc(instance, diff, mod, cdevid->subthr);
    /* ALLOCREADPTR 0: take ownership of the pointer on success */
    cdevid->cdev->ihndname = ihnd;
    return 1;
}
char __fplyx_memram_cdevsohnd(fplyx_vmem_t * const self, fplyx_memram_cdevid const cdevid, char* const ohnd)
{
    fplyx_memram_t* const instance = self->_instance;
    if(!(cdevid?cdevid->cdev:0))
        return 0;
    char mod;
    size_t diff;
    const unsigned long len1 = strlen(ohnd) + 1;
    const unsigned long len2 = strlen(cdevid->cdev->ohndname) + 1;
    if(!cdevid->cdev->ohndname)
    {
        __fplyx_memram_cascadealloc(instance, len1, 0, cdevid->subthr);
        cdevid->cdev->ohndname = ohnd;
        return 1;
    }
    if(len1 > len2)
    {
        diff = len1 - len2;
        mod = 0;
    }
    else if (len1 < len2) 
    {
        diff = len2 - len1;
        mod = 1;
    }
    else
    {
        /*no changes on the size*/
        free(cdevid->cdev->ohndname);
        cdevid->cdev->ohndname = ohnd;
        return 1;
    }
    __fplyx_memram_cascadealloc(instance, diff, mod, cdevid->subthr);
    /* ALLOCREADPTR 0: take ownership of the pointer on success */
    cdevid->cdev->ohndname = ohnd;
    return 1;
}
char __fplyx_memram_cdevreallocib(fplyx_vmem_t * const self, fplyx_memram_cdevid const cdevid, const size_t size)
{
    if(!(cdevid?cdevid->cdev:0))
        return 0;
    fplyx_memram_t* const instance = self->_instance;
    struct __fplyx_memram_ndataid ib;
    struct __fplyx_memram_subthrid ibsubthr;
    ibsubthr.ctx = cdevid->ctx;
    ibsubthr.subthr = cdevid->subthr;
    ibsubthr.id = __fplyx_memram_thrsctxid(cdevid->subthr?&cdevid->subthr->parent->ctx:&instance->ctx, cdevid->subthr);
    __fplyx_memram_getndata(self, cdevid->cdev->ibuffname, cdevid->ctx->execstack.nref - 1, &ibsubthr, &ib);
    char mod;
    size_t diff;
    const size_t sz2 = cdevid->cdev->ibufflimit;
    if(!sz2)
    {
        char* data = malloc(size);
        if(!data) return -128;
        __fplyx_memram_cascadealloc(instance, size, 0, cdevid->subthr);
        memset(data, 0, size);
        if(1&~__fplyx_memram_rewnd(self, &ib, data, size))
        {
            free(data);
            return 0+32;
        }
        cdevid->cdev->ibufflimit = size;
        return 1;
    }
    else if(size > sz2)
    {
        diff = size - sz2;
        mod = 0;
    }
    else if (size < sz2) 
    {
        diff = sz2 - size;
        mod = 1;
    }
    else if(sz2 > ib.ndata->size)
    {
        /*something weird is happened*/
        memset(ib.ndata->data, 0, ib.ndata->size);
        cdevid->cdev->ibufflimit = ib.ndata->size;
    }
    else
    {
        /*no changes on the size*/
        memset(ib.ndata->data, 0, sz2);
    }
    __fplyx_memram_cascadealloc(instance, diff, mod, cdevid->subthr);
    return 1;
}
char __fplyx_memram_cdevreallocob(fplyx_vmem_t * const self, fplyx_memram_cdevid const cdevid, const size_t size)
{
    if(!(cdevid?cdevid->cdev:0))
        return 0;
    fplyx_memram_t* const instance = self->_instance;
    struct __fplyx_memram_ndataid ob;
    struct __fplyx_memram_subthrid obsubthr;
    obsubthr.ctx = cdevid->ctx;
    obsubthr.subthr = cdevid->subthr;
    obsubthr.id = __fplyx_memram_thrsctxid(cdevid->subthr?&cdevid->subthr->parent->ctx:&instance->ctx, cdevid->subthr);
    __fplyx_memram_getndata(self, cdevid->cdev->obuffname, cdevid->ctx->execstack.nref - 1, &obsubthr, &ob);
    char mod;
    size_t diff;
    const size_t sz2 = cdevid->cdev->obufflimit;
    if(!sz2)
    {
        char* data = malloc(size);
        if(!data) return -128;
        __fplyx_memram_cascadealloc(instance, size, 0, cdevid->subthr);
        memset(data, 0, size);
        if(1&~__fplyx_memram_rewnd(self, &ob, data, size))
        {
            free(data);
            return 0+32;
        }
        cdevid->cdev->obufflimit = size;
        return 1;
    }
    else if(size > sz2)
    {
        diff = size - sz2;
        mod = 0;
    }
    else if (size < sz2) 
    {
        diff = sz2 - size;
        mod = 1;
    }
    else if(sz2 > ob.ndata->size)
    {
        /*something weird is happened*/
        memset(ob.ndata->data, 0, ob.ndata->size);
        cdevid->cdev->obufflimit = ob.ndata->size;
    }
    else
    {
        /*no changes on the size*/
        memset(ob.ndata->data, 0, sz2);
    }
    __fplyx_memram_cascadealloc(instance, diff, mod, cdevid->subthr);
    return 1;
}
size_t __fplyx_memram_cdevszofib(fplyx_vmem_t * const self, fplyx_memram_cdevid const cdevid)
{
    return cdevid->cdev->ibufflimit;
}
size_t __fplyx_memram_cdevszofob(fplyx_vmem_t * const self, fplyx_memram_cdevid const cdevid)
{
    return cdevid->cdev->obufflimit;
}
char* __fplyx_memram_cdevgetib(fplyx_vmem_t * const self, fplyx_memram_cdevid const cdevid)
{
    /*ALLOCREADPTR 0: no need to free returned pointer*/
    return cdevid->cdev->ibuffname;
}
char __fplyx_memram_cdevsetib(fplyx_vmem_t * const self, fplyx_memram_cdevid const cdevid, char* const ibuff)
{
    /*ALLOCREADPTR 0: take ownership on successful execution*/
    fplyx_memram_t* const instance = self->_instance;
    if(!(cdevid?cdevid->cdev:0))
        return 0;
    char mod;
    size_t diff;
    const unsigned long len1 = strlen(ibuff) + 1;
    const unsigned long len2 = strlen(cdevid->cdev->ibuffname) + 1;
    if(!cdevid->cdev->ibuffname)
    {
        __fplyx_memram_cascadealloc(instance, len1, 0, cdevid->subthr);
        cdevid->cdev->ibuffname = ibuff;
        return 1;
    }
    if(len1 > len2)
    {
        diff = len1 - len2;
        mod = 0;
    }
    else if (len1 < len2) 
    {
        diff = len2 - len1;
        mod = 1;
    }
    else
    {
        /*no changes on the size*/
        free(cdevid->cdev->ibuffname);
        cdevid->cdev->ibuffname = ibuff;
        return 1;
    }
    __fplyx_memram_cascadealloc(instance, diff, mod, cdevid->subthr);
    /* ALLOCREADPTR 0: take ownership of the pointer on success */
    cdevid->cdev->ibuffname = ibuff;
    return 1;
}
char* __fplyx_memram_cdevgetob(fplyx_vmem_t * const self, fplyx_memram_cdevid const cdevid)
{
    /*ALLOCREADPTR 0: no need to free returned pointer*/
    return cdevid->cdev->obuffname;
}
char __fplyx_memram_cdevsetob(fplyx_vmem_t * const self, fplyx_memram_cdevid const cdevid, char* const obuff)
{
    fplyx_memram_t* const instance = self->_instance;
    if(!(cdevid?cdevid->cdev:0))
        return 0;
    char mod;
    size_t diff;
    const unsigned long len1 = strlen(obuff) + 1;
    const unsigned long len2 = strlen(cdevid->cdev->obuffname) + 1;
    if(!cdevid->cdev->obuffname)
    {
        __fplyx_memram_cascadealloc(instance, len1, 0, cdevid->subthr);
        cdevid->cdev->obuffname = obuff;
        return 1;
    }
    if(len1 > len2)
    {
        diff = len1 - len2;
        mod = 0;
    }
    else if (len1 < len2) 
    {
        diff = len2 - len1;
        mod = 1;
    }
    else
    {
        /*no changes on the size*/
        free(cdevid->cdev->obuffname);
        cdevid->cdev->obuffname = obuff;
        return 1;
    }
    __fplyx_memram_cascadealloc(instance, diff, mod, cdevid->subthr);
    /* ALLOCREADPTR 0: take ownership of the pointer on success */
    cdevid->cdev->obuffname = obuff;
    return 1;
}
size_t __fplyx_memram_szofsubthrid()
{
    return sizeof(struct __fplyx_memram_subthrid);
}
size_t __fplyx_memram_szofndataid()
{
    return sizeof(struct __fplyx_memram_ndataid);
}
size_t __fplyx_memram_szofcdevid()
{
    return sizeof(struct __fplyx_memram_cdevid);
}
char __fplyx_memram_subthrid_valid(fplyx_memram_subthrid const subthrid)
{
    if(subthrid?subthrid->subthr:0)
        if(subthrid->ctx)
            return 1;
    return 0;
}
char __fplyx_memram_ndataid_valid(fplyx_memram_ndataid const ndataid)
{
    if(ndataid?ndataid->ndata:0)
        if(ndataid->ctx)
            return 1;
    return 0;
}
char __fplyx_memram_cdeviceid_valid(fplyx_memram_cdevid const cdevid)
{
    if(cdevid?cdevid->cdev:0)
        if(cdevid->ctx)
            return 1;
    return 0;
}
char* __fplyx_memram_ndname(fplyx_vmem_t * const self, fplyx_memram_ndataid const namedataid)
{
    return namedataid->ctx->execstack.refs[namedataid->stackpos]->ntab.ntabname[namedataid->id];
}
unsigned long __fplyx_memram_ndid(fplyx_vmem_t * const self, fplyx_memram_ndataid const namedataid)
{
    return namedataid->id;
}
void __fplyx_memram_ndsubthr(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid, fplyx_memram_ndataid const namedataid)
{
    *subthrid = namedataid->subthrid;
}
unsigned long __fplyx_memram_ndstackdepth(fplyx_vmem_t * const self, fplyx_memram_ndataid const namedataid)
{
    return namedataid->stackpos;
}
char* __fplyx_memram_thrname(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid)
{
    return subthrid->subthr->name;
}
unsigned int __fplyx_memram_thrid(fplyx_vmem_t * const self, fplyx_memram_subthrid const subthrid)
{
    return subthrid->id;
}
char* __fplyx_memram_cdevname(fplyx_vmem_t * const self, fplyx_memram_cdevid const cdevid)
{
    return cdevid->cdev->name;
}
unsigned int __fplyx_memram_cdevid(fplyx_vmem_t * const self, fplyx_memram_cdevid const cdevid)
{
    return cdevid->id;
}
