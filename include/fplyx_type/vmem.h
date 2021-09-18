/*
 * vmem.h
 *
 *  Created on: 22 mar. 2021.
 *      Author: NobWow
 */

#ifndef FPLYX_TYPE_VMEM_H_
#define FPLYX_TYPE_VMEM_H_
#include <stddef.h>

#define FPLYX_VMEMOPT_ALLOCREADPTR 1 /* after read_named_data or read_exec or any other read function, returned pointer needs to be free() d
Basically, setting this bit to false means that this memory type is RAM-like and stores the most info in the RAM*/
/* #define FPLYX_VMEMOPT_FOREIGNLMID 2  last mapid needs to be loaded/saved in order to use it */
/*
#define FPLYX_VMEMOPT_
*/

/* Reference data interaction permissions system */
#define FPLYX_VMEMREFP_DEFAULT 57
/* read-only reference, write-only reference or both? */
#define FPLYX_VMEMREFP_GETVAL 1
#define FPLYX_VMEMREFP_ASSIGNVAL 2
#define FPLYX_VMEMREFP_DELVAL 4
#define FPLYX_VMEMREFP_ARRAPP 8
#define FPLYX_VMEMREFP_ARRREM 16
#define FPLYX_VMEMREFP_EXEC 32 /* function referenced to another subthread' namespace will be executed with namespace of the subthread that is invoked this function. If reference contains multiple values then this applied to all subvalues of this reference*/
#define FPLYX_VMEMREFP_EXECSOURCESCOPE 64 /* function referenced to another subthread' namespace will be executed with namespace of the subthread that is defined this function. Requires previous bit to be set */
#define FPLYX_VMEMREFP_EDITANNOT 128
/* Subthread options */
#define FPLYX_VMEMSUBTHR_NAMESPACE 1 /* superior namespace is inaccessible (on resolving context) */
#define FPLYX_VMEMSUBTHR_DEVICES 2 /* superior devices are inaccessible (on resolving devname) */
#define FPLYX_VMEMSUBTHR_FULLALLOC 4 /* max memory limit will be entirely counted into superior allocation value */
#define FPLYX_VMEMSUBTHR_NOSUBTHR 8 /* this subthread cannot have its own sub-subthreads */
/* IO asynchronous lock of main thread or sub-thread. These are the values of iostate and watcher variant */
#define FPLYX_VMEMIOSTATE_REALPEND 1 /* the main thread or subthread is waiting on real event. Its executing iteration is skipped until this bit is unset, presumably other information will be stored in the interpreter for dispatch and none in the watcher info */
#define FPLYX_VMEMIOSTATE_SUBTHRPEND 2 /* the main thread or subthread is waiting on other subthread (the moment when it reaches the end of execution). In this case, this subthread is unavailable and watcher is placed into the context of other subthread */
#define FPLYX_VMEMIOSTATE_CDEVPEND 4 /* the subthread is reading on the custom device. If nothing is written on custom device rbuff yet, this subthread is unavailable. In this case, watcher is placed into this custom device watchers list*/
#define FPLYX_VMEMIOSTATE_EXOSTACKPEND 8 /* the subthread invoked a reference function that has EXECSOURCESCOPE enabled. It means that the stack node has an additive scope attached to it. Does not block the subthread but if another subthread gets deleted during execution of this reference function, it immediately destructs (and throws an error interpreter-specific) to prevent undefined behavior */
#define FPLYX_VMEMIOSTATE_SUSPEND 16 /* the subthread is suspended and not iterated until it is resumed. No watcher is assumed */
#define FPLYX_VMEMIOSTATE_FULLUNAVAIL (FPLYX_VMEMIOSTATE_REALPEND | FPLYX_VMEMIOSTATE_SUBTHRPEND | FPLYX_VMEMIOSTATE_CDEVPEND | FPLYX_VMEMIOSTATE_SUSPEND) /* this is the shortcut value of the context that is not available to dispatch
It is used in subthread_iter() function, for example, quickly check if this context is blocked: !(instance->ctx.iostate&FPLYX_VMEMIOSTATE_FULLNAVAIL)
*/
/* Stack node modes: used by interpreter */
#define FPLYX_VMEMSTACK_EXSTACKTRY 1 /* node in the stack will stop error from popping the rest of the stack and will be dispatched according to the stack onerror clause */
/*
 * FPlyx Virtual Memory is a bunch of functions that is used for manipulating and storing FPlyx's environment
 * independently during execution.
 * For example, it gives us an opportunity to run FPlyx's bytecode without operating all the data in RAM.
 * Instead, all the variables, execution stacks, virtual devices, custom functions etc. could be stored
 * and processed in HDD/SSD filesystem instead, which is useful in low-RAM environment. But this reduces the speed of
 * FPlyx execution and also may lower the data storage's resource.
 * FPlyx bytecode, variables etc. are stored as "named data",
 * meaning that it could be accessed only by passing its name and not the address. The address might be drastically changed
 * during the execution, which allows the interpreter to shift and sort the data heap space
 * Note that subthread's data names is prefixed (see below) and may contain magic symbols that should not be used in FPlyx Source code but FPlyx Bytecode
 * The first sizeof(unsigned long) bytes are used to store 
 */

/*
 * Note: vmem sometimes uses arguments with unknown typedef (void *) that are defined by custom implementations
 * They are custom data that is required to instantly acquire FPlyx objects and were added for optimization purposes
 * List of possible custom type definitions:
 *     cdevid
 *     namedataid
 *     subthrid
 *     subthrpathid -- may be deprecated since subthrid is supposed to have a pointer to "parent" subthread
 *                     and depth value
 *     execnodeid
 * The reason of why am I using return-to-pointer is to avoid unnecessary malloc() and free() calls upon execution
 * Example of making a good use out of it:
    void* some_obj;
    char example_get_func(void* object, int arg1, char arg2, void* result)
    {
        if(exists(object) && arg1 == arg2)
        {
            *result = object->some_stuff[123456789];
            return 1;
        } else {
            *result = (void *)0;
            return 0;
        }
    }
    if(!example_get_func(center, 127, 127, some_obj))
    {
        puts("Hey! Success!");
    } else {
        puts("No..")
    }
 */

typedef struct __fplyx_vmem_t
{
	void * _instance; /* this refers to the implementation-dependent structure object */
    /* near-field fetch algorithm for accessing named data */
    unsigned int thrmaxdepth;
    char memopts;
    char (*prepare)(struct __fplyx_vmem_t *); //allocate a new _instance object
	char (*end)(struct __fplyx_vmem_t *); //cleanup operations and deallocate _instance object
	size_t (*get_allocated_size)(struct __fplyx_vmem_t *);
	size_t (*get_max_heap)(struct __fplyx_vmem_t *);
	void (*set_max_heap)(struct __fplyx_vmem_t *, size_t /*new size*/);
	//name is the first argument as null-terminated string
    char (*get_subthread)(struct __fplyx_vmem_t *, void* /*subthrid (start point)*/, char** /*subthreads*/, unsigned int /*nsubthr*/, void* /*result to*/); 
    void (*get_named_data)(struct __fplyx_vmem_t *, char* /*name*/, unsigned long /*execstack node pos*/, void* /*subthrid*/, void* /*result*/); 
    /* need for iterating over named data */
    unsigned long (*name_tab_size)(struct __fplyx_vmem_t *, unsigned long pos, void* /*subthrid*/);
    void (*get_named_data_at)(struct __fplyx_vmem_t *, unsigned long /*id*/, unsigned long /*pos*/, void* /*subthrid*/, void* /*result namedataid*/);
    char (*write_named_data)(struct __fplyx_vmem_t *, char* /*name*/, char* /*data*/ , size_t /*size*/, void* /*subthrpathid*/, void* /*result namedataid*/); 
    char (*append_named_data)(struct __fplyx_vmem_t *, void* /*namedataid*/, char* /*data*/, size_t /*size*/); 
    char (*cut_named_data)(struct __fplyx_vmem_t *, void* /*namedataid*/, size_t /*size*/, size_t /*offset*/); 
    char (*insert_named_data)(struct __fplyx_vmem_t *, void* /*namedataid*/, char* /*inserting data*/, size_t /*data size*/, size_t /*offset*/);
    char (*replace_named_data)(struct __fplyx_vmem_t *, void* /*namedataid*/, char* /*replacing data*/, size_t /*data size*/, size_t /*offset*/);
    char (*destroy_named_data)(struct __fplyx_vmem_t *, void* /*namedataid*/);
    size_t (*sizeof_named_data)(struct __fplyx_vmem_t *, void* /*namedata*/);
    char* (*read_named_data)(struct __fplyx_vmem_t *, void* /*namedataid*/, size_t /*portion size*/, size_t /*offset*/); /* portion size only appends to non-RAM virtual memory implementations and returns allocated pointer that needs to be freed somewhere else (only for non-RAM vmem implementations) */
    /*Simple GC (refcounting): this is usually called inside of the vmem implementation*/
    void (*increase_refcount)(struct __fplyx_vmem_t *, void* /*namedataid*/); /*protect the named data against implicit deletion by increasing its reference counter, this function is usually called at reference data creation
    NOTE: this is not guaranteed for the named data to stay existant: for example, deinitializing this vmem will result in a deletion regardless of amount of references, beware. This way it only prevents implicit deletions through decrease_refcount()*/
    void (*decrease_refcount)(struct __fplyx_vmem_t *, void* /*namedataid*/); /*decrease the named data reference counter, but if it reaches zero, automatically call destroy_named_data(namedataid) at this invocation*/
    unsigned long (*get_ndata_refcount)(struct __fplyx_vmem_t *, void* /*namedataid*/); /*return how many times it is referenced*/
    char (*rewrite_named_data)(struct __fplyx_vmem_t *, void* /*namedataid*/, char* /*new data*/, size_t /*data size*/);
	/* DEPRECATED: use get_named_data to check existance of any named data.
    char (*exists_named_data)(struct __fplyx_vmem_t *, char*, char**, unsigned int);
	*/ /**/
    char* (*read_exec)(struct __fplyx_vmem_t *, void* /*subthrid*/, unsigned long /*jump offset*/, unsigned char /*mod*/); // -> position or null pointer (end reached)
	//main thread operations
    unsigned long (*execstack_size)(struct __fplyx_vmem_t*, void* /*subthrid*/);
    //void (*get_stackelement_at)(struct __fplyx_vmem_t *, void* /*subthrid*/, unsigned long /*element id in stack*/, void* /*execnodeid result*/);
    size_t (*get_exec_pos)(struct __fplyx_vmem_t*, unsigned long /*execstackpos*/, void* /*subthrid*/);
	char (*increase_exec_stack)(struct __fplyx_vmem_t *, void* /*runnable namedataid*/, void* /*yielder namedataid (write result in it)*/, size_t /*operator start*/, void* /*subthrid*/); /*adds a new scope to the stack (main function, condition, loop, switch, other namedata being called by "main" etc.) so the next execution read_exec() will be done at this new scope. Note that the stack might also */
	void (*decrease_exec_stack)(struct __fplyx_vmem_t *, void* /*subthrid*/); /* removes the most highest element in the stack and returns the pointer to a previous location, also automatically destroying all of the namedata */
    unsigned char (*get_stackelement_mode)(struct __fplyx_vmem_t *, unsigned long /*execstackpos*/, void* /*subthrid*/);
    void (*set_stackelement_mode)(struct __fplyx_vmem_t *, unsigned char /*mode*/, unsigned long, void* /*subthrid*/);
    /* DEPRECATED: redundant function
    void (*load_last_mapid)(struct __fplyx_vmem_t *, );*/
    /**/
    void (*set_last_mapid)(struct __fplyx_vmem_t *, unsigned long /*new element id*/, void* /*subthrid*/);
    size_t (*get_cthriopos)(struct __fplyx_vmem_t *, void* /*subthrid*/);
    void (*set_cthriopos)(struct __fplyx_vmem_t *, size_t /*new io stream position*/, void* /*subthrid*/);
    //iostate functions (control thread blocking and watchers)
    /*
     * IOState is an internal non-device event system that suspends the subthread execution
     * and lets to asynchronously watch on subthread or cdevice. Also prevents an undefined behavior when some object
     * gets deleted while being watched by something else.
     */
    unsigned char (*get_iostate)(struct __fplyx_vmem_t *, void* /*subthrid*/); /*retrieve an iostate value for specific context*/
    char (*iostate_watch_real)(struct __fplyx_vmem_t *, void* /*subthrid*/); /*enables REALPEND on its iostate assuming that the interpreter will handle this event.*/
    char (*iostate_watch_subthread)(struct __fplyx_vmem_t *, void* /*subthrid*/, void* /*target subthrid*/); /*enables SUBTHRPEND on its iostate and adds this subthread on target's list. Automatically resets the bit when a target either gets deleted or its execution stack runs out of instructions.
        Notice that the subthread cannot watch main thread because the main thread should be always active during
        the program execution. Also don't forget to unwatch the subthread before deletion
        TODO: read_exec need to unset the bit in this condition*/
    char (*iostate_watch_cdevice)(struct __fplyx_vmem_t *, void* /*subthrid*/, void* /*cdevid*/); /*enables CDEVPEND bit on its iostate and adds this subthread on target cdevice's watchers list. Automatically resets the bit when a target either gets deleted or its read buffer gets updated*/
    char (*iostate_watch_externalscope)(struct __fplyx_vmem_t *, void* /*subthrid*/, void* /*target subthrid*/); /*enables EXOSTACKPEND bit on its iostate and adds this subthread on target's watchers list. Prevents an undefined behavior when target gets deleted during execution */
    char (*iostate_unwatch_externalscope)(struct __fplyx_vmem_t *, void* /*subthrid*/, void* /*target subthrid*/); /*does the opposite of above*/
    char (*iostate_unwatch_subthread)(struct __fplyx_vmem_t *, void* /*subthrid*/, void* /*target subthrid*/); /*unsets the SUBTHRPEND bit from its iostate and removes this watcher from the target's list*/
    char (*iostate_unwatch_cdevice)(struct __fplyx_vmem_t *, void* /*subthrid*/, void* /*target cdevid*/); /*unsets the CDEVPEND bit from its iostate and removes this subthread from target's watchers list*/
    char (*iostate_unwatch_real)(struct __fplyx_vmem_t *, void* /*subthrid*/); /*simply unsets the REALPEND bit from its iostate and does nothing else*/
    unsigned int (*iostate_watchers_count)(struct __fplyx_vmem_t *, void* /*subthrid*/); /*get amount of contexts that are currently watching on this subthread (on main thread only watchers is external scope executors)*/
    unsigned int (*iostate_cdevreaders_count)(struct __fplyx_vmem_t *, void* /*cdevid*/); /*similar concept of above but get amount of readers of custom device*/
    void (*iostate_get_watcher)(struct __fplyx_vmem_t *, void* /*subthrid*/, unsigned int /*id*/, void* /*target subthrid*/); /*fetches the id+1-th watcher in the watchers list */
    void (*iostate_get_cdevreader)(struct __fplyx_vmem_t *, void* /*cdevid*/, unsigned int /*id*/, void* /*target subthrid*/); /*fetches the id+1-th reader in the cdevice watchers list */
	//subthread operations
	/*
	 * Subthreads are allocated as named data in the main thread
	 * There is a pointer in the header of the vmem to the subthread table
	 */
    unsigned int (*subthread_count)(struct __fplyx_vmem_t *, void* /*subthrid*/); /*total amount of (sub-n)subthreads on specified level */
	unsigned long (*subthread_gcount)(struct __fplyx_vmem_t *, void* /*subthrid*/); /*count total amount of all subthreads in every level using pseudorecursion*/
	/* DEPRECATED: iteration is managed by using depth-array
    unsigned int (*subthread_iter_value)(struct __fplyx_vmem_t *); Subthread ID that will be processed on this iteration of interpreter event loop
	void (*subthread_set_iter)(struct __fplyx_vmem_t *, unsigned int *new iteration*); Set subthread ID that will be processed...*/
    unsigned long (*subthread_iter)(struct __fplyx_vmem_t *, void * /*result subthrid*/); /*performs an iteration of subthread queue and returns the first available subthread to dispatch. Sets null result if current iteration refers to main thread. If none of the subthreads are available at the moment and the returned value will be the least sleepms value (result will be that subthread with the least sleepms)*/
	//char** (*subthread_namearr)(struct __fplyx_vmem_t *, size_t, char**, unsigned int);
	char (*subthread_create)(struct __fplyx_vmem_t *, char* /*name*/, char /*options*/, void* /*parent subthrid*/, void* /*result subthrid*/); 
	char (*subthread_suspend)(struct __fplyx_vmem_t *, void* /*subthrid*/, char /*bool 0/1*/); 
	char (*subthread_delete)(struct __fplyx_vmem_t *, void* /*subthrid*/); //NOTE: this does NOT remove subthread exec code, but removes it from thread table and associated namedata
	//these functions does apply to encapsulated subthreads only!
	unsigned int (*subthread_limit)(struct __fplyx_vmem_t *, void* /*subthrid*/);
	char (*subthread_limit_set)(struct __fplyx_vmem_t *, void* /*subthrid*/, unsigned int /*subsubthread limit*/);
	size_t (*subthread_memlimit)(struct __fplyx_vmem_t *, void* /*subthrid*/);
	char (*subthread_memlimit_set)(struct __fplyx_vmem_t *, void* /*subthrid*/, size_t /*max allocation allowed*/);
	char (*subthread_devref)(struct __fplyx_vmem_t *, char* /*refname_from*/, char* /*refname_to*/, void* /*subthrid_from*/, void* /*subthrid_to*/); /*registers a virtual device reference to the context*/
	char (*subthread_devunref)(struct __fplyx_vmem_t *, char* /*refname*/, void* /*subthrid*/);
    char* (*subthread_devresolve)(struct __fplyx_vmem_t *, char* /*name*/, void* /*subthrid*/, void* /*result subthrid*/); /*show */
	size_t (*subthread_size)(struct __fplyx_vmem_t *, void* /*subthrid*/);
    char (*subthread_superflags)(struct __fplyx_vmem_t*, void* /*subthrid*/); /*sum all the subthread flags up to the primary subthread*/
    /* Each subthread can be suspended temporarily, so lets operate with the timers */
    unsigned long (*subthread_get_sleep)(struct __fplyx_vmem_t*, void* /*subthrid*/); /*set sleepms value for this subthread. Notice that it doesn't set the iostate flag for the subthread */
    void (*subthread_set_sleep)(struct __fplyx_vmem_t*, unsigned long msec, void* /*subthrid*/); /*set sleepms value for this subthread. Notice that it doesn't set the iostate flag for the subthread */
    void (*subthread_gdecsleep)(struct __fplyx_vmem_t*, unsigned long msec); /*Globally decrease a sleepms value for every single subthread that does exist. Usually a copypaste from subthread_iter, but the algorithm is used differently*/
	/*
     * References is yet more efficient way of two-way interaction with subthread in isolated mode.
     * They could be used for either providing the access to a data from the outside
     * or provide the access to the data of own subthread.
     * References are treated as named data so they can be deleted by destroy_named_data()
     * as it was regular named data.
     * Therefore it is possible to create read-only reference (or write-only for special cases)
     */
	char (*create_reference_data)(struct __fplyx_vmem_t *, char /*permissions*/, char* /*name*/, void* /*subthrid*/, void* /*namedataid_to*/, void* /*result namedataid*/); //permissions, name of link, target name, subthread of link, subthread of the target
    char (*get_reference_target)(struct __fplyx_vmem_t *, void* /*namedataid*/, void* /*result namedataid*/);
    char (*get_reference_finaltarget)(struct __fplyx_vmem_t *, void* /*namedataid*/, void* /*result_namedataid*/); /*almost the same as above, but it takes to the count that the target of this reference might be another reference creating some N-length reference chain, so it resolves them all*/
    //TODO: cycle check (Floyd is suggested) on set_reference_target
    void (*set_reference_target)(struct __fplyx_vmem_t *, void* /*namedataid*/, void* /*target namedataid*/);
    char (*is_reference)(struct __fplyx_vmem_t *, void* /*namedataid*/);
    char (*get_reference_permissions)(struct __fplyx_vmem_t *, void* /*namedataid*/);
    char (*get_reference_finalpermissions)(struct __fplyx_vmem_t *, void* /*namedataid*/); /*same concept as get_reference_finaltarget, but also perform a permission cast over nested references. Note that it might lose the EXECSOURCESCOPE permission so it's necessary to use the function below to acquire the context*/
    void (*get_reference_finalcontext)(struct __fplyx_vmem_t *, void* /*namedataid*/, void* /*result subthrid*/); /*same concept of final results, but skip the last N references in the chain that has EXECSOURCESCOPE enabled. Result is the subthread of the reference (or final named data) that doesn't have this permission enabled*/
    void (*set_reference_permissions)(struct __fplyx_vmem_t *, char /*permissions*/, void* /*namedataid*/);
    /*
	 * Annotations is an additive data that can be applied to any named data.
	 * Usually, it does not affect the code execution unless the other behavior is specified.
	 * Annotations are used for code lookup, code conversion, analysis etc.
     * Pre-deprecated: Store annotations in the data instead
	 */
	//char* (*read_named_annot)(struct __fplyx_vmem_t *, void* /*namedataid*/, size_t /*read limit*/);
	//char (*set_named_annot)(struct __fplyx_vmem_t *, void* /*namedataid*/, char* /*annot*/);
	/*
	 * Custom virtual devices and device overlaying inside subthreads
	 */
    /*cdevice_create*/
	char (*cdevice_create)(struct __fplyx_vmem_t *, char* /*name*/, char* /*ihnd*/, char* /*ohnd*/, char* /*ibname*/, unsigned int /*iblimit*/, char* /*obname*/, unsigned int /*oblimit*/, void* /*subthrid*/, void* /*result cdevid*/); /* will create custom device with virtual buffers as named datas. Also possible to use references as buffers */
    char (*cdevice_get)(struct __fplyx_vmem_t *, char* /*name*/, void* /*subthrid*/, void* /*result*/);
	char (*cdevice_delete)(struct __fplyx_vmem_t *, void* /*cdevid*/);
    unsigned int (*cdevice_amount)(struct __fplyx_vmem_t *, void* /*subthrid*/);
    void (*cdevice_at)(struct __fplyx_vmem_t *, unsigned int /*id*/, void* /*subthrid*/, void* /*result */);
    char* (*cdevice_getihnd)(struct __fplyx_vmem_t *, void* /*cdevid*/);
    char* (*cdevice_getohnd)(struct __fplyx_vmem_t *, void* /*cdevid*/);
	char (*cdevice_setihnd)(struct __fplyx_vmem_t *, void* /*cdevid*/, char* /*ihnd name*/);
	char (*cdevice_setohnd)(struct __fplyx_vmem_t *, void* /*cdevid*/, char* /*ohnd name*/);
	char (*cdevice_reallocib)(struct __fplyx_vmem_t *, void* /*cdevid*/, size_t /*size*/);
	char (*cdevice_reallocob)(struct __fplyx_vmem_t *, void* /*cdevid*/, size_t /*size*/);
	size_t (*cdevice_szofib)(struct __fplyx_vmem_t *, void* /*cdevid*/);
	size_t (*cdevice_szofob)(struct __fplyx_vmem_t *, void* /*cdevid*/);
	char* (*cdevice_getib)(struct __fplyx_vmem_t *, void* /*cdevid*/);
	char (*cdevice_setib)(struct __fplyx_vmem_t *, void* /*cdevid*/, char* /*input buffer name*/);
	char* (*cdevice_getob)(struct __fplyx_vmem_t *, void* /*cdevid*/);
	char (*cdevice_setob)(struct __fplyx_vmem_t *, void* /*cdevid*/, char* /*output buffer name*/);
    /* Mandatory static functions */
    size_t (*szofsubthrid)();
    size_t (*szofnamedataid)();
    size_t (*szofcdevid)();
    /*Return 1 if the ID is not null*/
    char (*subthrid_valid)(void* /*subthrid*/);
    char (*ndataid_valid)(void* /*namedataid*/);
    char (*cdeviceid_valid)(void* /*cdevid*/);
    char (*exstacknodeid_valid)(void* /*exstacknodeid*/);
    /* Unknown purpose / may be removed */
    void (*free_named_data)(struct __fplyx_vmem_t *, void* /*namedataid*/);
    void (*free_subthread)(void* /*subthrid*/);
    void (*cdevice_free)(void* /*cdevid*/);
    char* (*named_data_name)(struct __fplyx_vmem_t *, void* /*namedataid*/);
    unsigned long (*named_data_id)(struct __fplyx_vmem_t *, void* /*namedataid*/);
    void (*named_data_subthread)(struct __fplyx_vmem_t *, void* /*result subthrid*/, void* /*namedataid*/);
    unsigned long (*named_data_stackdepth)(struct __fplyx_vmem_t *, void* /*namedataid*/);
    char* (*subthread_name)(struct __fplyx_vmem_t *, void* /*subthrid*/);
    unsigned int (*subthread_id)(struct __fplyx_vmem_t *, void* /*subthrid*/);
    char* (*cdevice_name)(struct __fplyx_vmem_t *, void* /*cdevid*/);
    unsigned int (*cdevice_id)(struct __fplyx_vmem_t *, void* /*cdevid*/);
} fplyx_vmem_t;

#endif /* FPLYX_TYPE_VMEM_H_ */
