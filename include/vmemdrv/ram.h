/*
 * ram.h
 *
 *  Created on: 16 apr. 2021.
 *      Author: NobWow
 */

#ifndef VMEMDRV_RAM_H_
#define VMEMDRV_RAM_H_

#include <fplyx_type/extension.h>
#include <sys/cdefs.h>


typedef struct __fplyx_memram_ndata_t
{
    size_t size;
    void* data; /*could be a pointer to fplyx_memdrv_dref_t*/
    /*size_t annot_size;
    char* annot;*/
    unsigned long refcounter; /* shared access counter */
    unsigned char refopts; /* this flag ensures that any random access to the void* data is altered */
} fplyx_memram_ndata_t;

/*
typedef struct __fplyx_memdrv_impl_t
{
	char* name;
	void (*prepare)(struct __fplyx_memdrv_impl_t *);
	void (*end)(struct __fplyx_memdrv_impl_t *);
	fplyx_vmem_t *(*obtain)();
} fplyx_memdrv_impl_t; */

typedef struct __fplyx_memram_cdev_t
{
    char* name;
    char* ihndname;
    char* ohndname;
    char* ibuffname;
    char* obuffname;
    size_t ibufflimit;
    size_t obufflimit;
    void** watchers; /*subthrids of currently blocking on this custom device*/
    unsigned int nwatcher;
} fplyx_memram_cdev_t;

typedef struct __fplyx_memram_ntab_t
{
    /* Index must correspond to an existing name in ntabname */
    fplyx_memram_ndata_t** ntabaddr;
    /* Name:Address correlated arrays */
    char** ntabname;
    unsigned long ntabc; /* associated length for ntabname and ntabaddr: i hope for stability */
} fplyx_memram_ntab_t;


typedef struct __fplyx_memram_exstacknode_t
{
    fplyx_memram_ntab_t ntab; /* Local scope of named data */
	size_t cmdptr;
	void* namedataid; /* executable (if first element then "main")*/
    void* result_namedataid; /* namedata that will hold the result. Can be null */
    fplyx_memram_ntab_t* add_ntab; /* usually it is null unless a function reference with 
                                      EXECSOURCESCOPE is called. This namespace won't be
                                      cleared on stack node destruction */
    unsigned char mode; /* values are set above */
} fplyx_memram_exstacknode_t;

typedef struct __fplyx_memram_exstack_t
{
    fplyx_memram_exstacknode_t** refs;
    unsigned long nref;
} fplyx_memram_exstack_t;

typedef struct __fplyx_memram_devrefkit_t
{
    void* subthrid;
    char** names_from;
    char** names_to;
    unsigned int amount;
} fplyx_memram_devrefkit_t;

/* Context: those options are shared between memram and subthreads */
struct fplyx_memram_context
{
    fplyx_memram_exstack_t execstack;
    /* Allocated RAM = sizeof(__fplyx_memram_t) + sum(malloc(...)) */
    size_t alloc;
    /* Limit on sum(malloc(ndata_t)) */
    size_t max;
    struct __fplyx_memram_subthr_t** subthr;
    fplyx_memram_cdev_t** cdevs;
    fplyx_memram_devrefkit_t** devkits; /*receive devices (cdevices) from other threads. Useful in restricted mode and can work as whitelist but usually works as mapper*/
    unsigned long gsubthr;
    unsigned long iopos;
    unsigned long _last_mapid;
    unsigned long _last_cdevmapid;
    unsigned long _last_subthrmapid;
    unsigned long ndevkit;
    unsigned long nsharing;
    void** watchers; /*subthrids of currently watching on this context, these does have iostate enabled on their context*/
    struct fplyx_memram_context** dev_sharing_to; /*contexts that are using this context's devices by reference*/
    unsigned int nsubthr;
    unsigned int nwatcher;
    unsigned int max_nsubthr; /*this value should be lower than superior subtracted by amount of already existing subthread running*/
    /* custom devices aren't supposed to be local */
    unsigned int cdevc;
    unsigned char iostate; /*whether or not we are currently blocked and watching on something*/ 
};

typedef struct __fplyx_memram_subthr_t
{
    struct fplyx_memram_context ctx;
    struct __fplyx_memram_subthr_t *parent;
    char* name;
    /* Allocated RAM = sizeof(__fplyx_memram_t) + sum(malloc(...)) */
    /* Memory saving at todo:ram.c */
    /* depth starts from 1. highest subthreads in the instance should have depth = 1*/
    unsigned int depth;
    char flags; /* 1=do not search namedata in a superior (subthread)
                 * 2=do not search devices in a superior (subthread)
                 * 4=subthread uses all the memory so ctx.alloc == ctx.max
                 * 8=do not permit creating child subthreads
                 */
} fplyx_memram_subthr_t;

/* copypaste some contents from __fplyx_memram_t since this is a shallow copy */

typedef struct __fplyx_memram_subthrp_t
{
    fplyx_memram_subthr_t** subthr;
    unsigned int nsubthr;
} fplyx_memram_subthrpath_t;

typedef struct __fplyx_memram_t
{
    /* Memory saving at todo:ram.c */
    struct fplyx_memram_context ctx;
    /* Execution info */
    unsigned int* subthrciter; //it is better to store ids rather than storing pointers
    fplyx_memram_subthr_t *current;
    unsigned int subthrnciter;
} fplyx_memram_t;

/* Library custom data type for IDs
 * Those types will be used by third-party software as void*
 * and the only information will be given is sizeof(customid) for
 * dynamic allocation
 */

typedef struct __fplyx_memram_subthrid
{
    /* Store ID in the parent subthread list */
    struct fplyx_memram_context* ctx;
    fplyx_memram_subthr_t* subthr;
    unsigned int id;
}* fplyx_memram_subthrid;

typedef struct __fplyx_memram_ndataid
{
    struct __fplyx_memram_subthrid subthrid;
    fplyx_memram_ndata_t* ndata;
    struct fplyx_memram_context* ctx;
    unsigned long stackpos;
    unsigned long id;
}* fplyx_memram_ndataid;

typedef struct __fplyx_memram_dref_t
{
    fplyx_memram_ndataid ndataid;
    unsigned char permissions; 
} fplyx_memram_dref_t;

typedef struct __fplyx_memram_cdevid
{
    fplyx_memram_cdev_t* cdev;
    fplyx_memram_subthr_t* subthr;
    struct fplyx_memram_context* ctx;
    unsigned long id;
}* fplyx_memram_cdevid;

typedef struct __fplyx_memram_exstacknodeid
{
    struct fplyx_memram_context* ctx;
    fplyx_memram_exstacknode_t* exstacknode;
}* fplyx_memram_exstacknodeid;

void fplyx_memram_prepare(fplyx_memdrv_impl_t* self);
void fplyx_memram_end(fplyx_memdrv_impl_t* self);
fplyx_vmem_t* fplyx_memram_obtain(fplyx_memdrv_impl_t* self);
char __fplyx_memram_prepare(fplyx_vmem_t* self);
char __fplyx_memram_end(fplyx_vmem_t* self);
size_t __fplyx_memram_getallocspace(fplyx_vmem_t* self);
size_t __fplyx_memram_getmaxheap(fplyx_vmem_t* self);
void __fplyx_memram_setmaxheap(fplyx_vmem_t* self, size_t size);

/* namedata simple GC */
void __fplyx_memram_increfnd(fplyx_vmem_t* self, fplyx_memram_ndataid ndataid);
void __fplyx_memram_decrefnd(fplyx_vmem_t* self, fplyx_memram_ndataid ndataid); /* automatically free() if no more references are left */
unsigned long __fplyx_memram_getrefnd(fplyx_vmem_t* self, fplyx_memram_ndataid ndataid);
/**/

struct fplyx_memram_context* __fplyx_memram_getctx(fplyx_memram_t* instance, fplyx_memram_subthrid subthrid);
char __fplyx_memram_getsubthr(fplyx_vmem_t* self, fplyx_memram_subthrid subthrid, char** subthreads, unsigned int nsubthr, fplyx_memram_subthrid result);
//char __fplyx_memram_freesubthr(fplyx_memram_subthrid subthrid);
/*void __fplyx_memram_getsubthrpath(fplyx_vmem_t* self, char** subthreads, unsigned int nsubthr, fplyx_memram_subthrpathid result);
void __fplyx_memram_freesubthrpath(fplyx_memram_subthrpathid subthrpathid);
void __fplyx_memram_subthrfrompath(fplyx_vmem_t* self, fplyx_memram_subthrpathid subthrpathid, fplyx_memram_subthrid result);*/
void __fplyx_memram_getndata(fplyx_vmem_t* self, char* name, unsigned long pos, fplyx_memram_subthrid subthrid, fplyx_memram_ndataid result);
void __fplyx_memram_getndata_at(struct __fplyx_vmem_t *, unsigned long id, unsigned long pos, fplyx_memram_subthrid subthrid, fplyx_memram_ndataid result);
//void __fplyx_memram_freendata(fplyx_memram_ndataid ndataid);
char __fplyx_memram_wnd(fplyx_vmem_t* self, char* name, char* data, size_t size, fplyx_memram_subthrid subthrid, fplyx_memram_ndataid result);
char __fplyx_memram_rewnd(fplyx_vmem_t* self, fplyx_memram_ndataid ndata, char* data, size_t size);
char __fplyx_memram_dnd(fplyx_vmem_t* self, fplyx_memram_ndataid ndata);
size_t __fplyx_memram_sizeofnd(fplyx_vmem_t* self, fplyx_memram_ndataid ndata);
char* __fplyx_memram_rnd(fplyx_vmem_t* self, fplyx_memram_ndataid ndata, size_t size, size_t offset);
char __fplyx_memram_repnd(fplyx_vmem_t* self, fplyx_memram_ndataid ndata, char* data, size_t size, size_t offset);
char __fplyx_memram_and(fplyx_vmem_t* self, fplyx_memram_ndataid ndata, char* data, size_t size);
char __fplyx_memram_cnd(fplyx_vmem_t* self, fplyx_memram_ndataid ndata, size_t size, size_t offset);
char __fplyx_memram_ind(fplyx_vmem_t* self, fplyx_memram_ndataid ndata, char* data, size_t size, size_t offset);
char* __fplyx_memram_rexec(fplyx_vmem_t* self, fplyx_memram_subthrid subthrid, unsigned long jump, char mod);
char __fplyx_memram_crefd(fplyx_vmem_t* self, char perms, char* name, fplyx_memram_subthrid subthrid, fplyx_memram_ndataid target, fplyx_memram_ndataid result);
char __fplyx_memram_greftrg(fplyx_vmem_t *, fplyx_memram_ndataid drefid, fplyx_memram_ndataid result);
char __fplyx_memram_greffinaltrg(fplyx_vmem_t *, fplyx_memram_ndataid drefid, fplyx_memram_ndataid result);
void __fplyx_memram_sreftrg(fplyx_vmem_t * self, fplyx_memram_ndataid drefid, fplyx_memram_ndataid ndataid);
char __fplyx_memram_isref(fplyx_vmem_t * self, fplyx_memram_ndataid ndataid);
char __fplyx_memram_grefperm(fplyx_vmem_t * self, fplyx_memram_ndataid drefid);
char __fplyx_memram_greffinalperm(fplyx_vmem_t * self, fplyx_memram_ndataid drefid);
void __fplyx_memram_srefperm(fplyx_vmem_t * self, char perms, fplyx_memram_ndataid drefid);
void __fplyx_memram_greffinalctx(fplyx_vmem_t * self, fplyx_memram_ndataid drefid, fplyx_memram_subthrid result);
//void __fplyx_memram_gstackelat(fplyx_vmem_t* self, fplyx_memram_subthrid subthrid, unsigned long elemid, fplyx_memram_exstacknodeid result);
size_t __fplyx_memram_gexecpos(fplyx_vmem_t* self, unsigned long pos, fplyx_memram_subthrid subthrid);
char __fplyx_memram_inc_execstack(fplyx_vmem_t* self, fplyx_memram_ndataid ndataid, fplyx_memram_ndataid resyield, size_t operator_start, fplyx_memram_subthrid subthrid);
void __fplyx_memram_dec_execstack(fplyx_vmem_t* self, fplyx_memram_subthrid subthrid);
unsigned long __fplyx_memram_exstacksz(fplyx_vmem_t* self, fplyx_memram_subthrid subthrid);
unsigned long __fplyx_memram_ntabsz(fplyx_vmem_t* self, unsigned long pos, fplyx_memram_subthrid subthrid);
unsigned char __fplyx_memram_gstackelmode(fplyx_vmem_t * self, unsigned long pos, fplyx_memram_subthrid subthrid);
void __fplyx_memram_sstackelmode(fplyx_vmem_t * self, unsigned char mode, unsigned long pos, fplyx_memram_subthrid subthrid);
void __fplyx_memram_slmapid(fplyx_vmem_t* self, unsigned long pos, fplyx_memram_subthrid subthrid);
size_t __fplyx_memram_gthriopos(fplyx_vmem_t * self, fplyx_memram_subthrid subthrid);
void __fplyx_memram_sthriopos(fplyx_vmem_t * self, unsigned long pos, fplyx_memram_subthrid subthrid);
unsigned int __fplyx_memram_thrcount(fplyx_vmem_t * self, fplyx_memram_subthrid subthrid);
unsigned long __fplyx_memram_thrgcount(fplyx_vmem_t * self, fplyx_memram_subthrid subthrid);
void __fplyx_memram_thriter(fplyx_vmem_t * self, fplyx_memram_subthrid result); /*easy for iterating through subthread queue*/
char __fplyx_memram_iowreal(fplyx_vmem_t * self, fplyx_memram_subthrid subthrid);
char __fplyx_memram_iowsubthr(fplyx_vmem_t * self, fplyx_memram_subthrid subthrid, fplyx_memram_subthrid target);
char __fplyx_memram_iowcdev(fplyx_vmem_t * self, fplyx_memram_subthrid /*subthrid*/, fplyx_memram_cdevid cdevid);
char __fplyx_memram_iowextscope(fplyx_vmem_t * self, fplyx_memram_subthrid /*subthrid*/, fplyx_memram_subthrid subthrid);
char __fplyx_memram_iounwextscope(fplyx_vmem_t * self, fplyx_memram_subthrid /*subthrid*/, fplyx_memram_subthrid subthrid);
char __fplyx_memram_iounwsubthread(fplyx_vmem_t * self, fplyx_memram_subthrid /*subthrid*/, fplyx_memram_subthrid subthrid);
char __fplyx_memram_iounwcdev(fplyx_vmem_t * self, fplyx_memram_subthrid subthrid, fplyx_memram_cdevid cdevid);
char __fplyx_memram_iounwreal(fplyx_vmem_t * self, fplyx_memram_subthrid subthrid);
unsigned int __fplyx_memram_iowcount(fplyx_vmem_t * self, fplyx_memram_subthrid subthrid);
unsigned int __fplyx_memram_iocdevrcount(fplyx_vmem_t * self, fplyx_memram_cdevid cdevid);
void __fplyx_memram_iogwatcher(fplyx_vmem_t *, fplyx_memram_subthrid subthrid, unsigned int id, fplyx_memram_subthrid result);
void __fplyx_memram_iogcdevreader(fplyx_vmem_t *, fplyx_memram_cdevid cdevid, unsigned int id, fplyx_memram_subthrid result);
//unsigned long __fplyx_memram_thriterval(fplyx_vmem_t * self);
//void __fplyx_memram_thrsiter(fplyx_vmem_t * self, unsigned long ival);
//char** __fplyx_memram_thrnarr(fplyx_vmem_t * self, size_t limit, fplyx_memram_subthrid subthrid);
char __fplyx_memram_thrcreate(fplyx_vmem_t * self, char* name, char opts, fplyx_memram_subthrid parent, fplyx_memram_subthrid result); //first argument:
// first bit: blank out superior namespace
// second bit: blank out devices
char __fplyx_memram_thrsus(fplyx_vmem_t * self, fplyx_memram_subthrid subthrid, char mode); //last argument is 0 or 1
char __fplyx_memram_thrdel(fplyx_vmem_t * self, fplyx_memram_subthrid subthrid); //NOTE: this does NOT remove subthread exec code, but removes the subthread from thread table
unsigned char __fplyx_memram_gthriostate(fplyx_vmem_t * self, fplyx_memram_subthrid subthrid);
//these functions does apply to encapsulated subthreads only!
unsigned int __fplyx_memram_thrlim(fplyx_vmem_t * self, fplyx_memram_subthrid subthrid);
char __fplyx_memram_thrlimset(fplyx_vmem_t * self, fplyx_memram_subthrid subthrid, unsigned int amount);
unsigned long __fplyx_memram_thrmemlim(fplyx_vmem_t * self, fplyx_memram_subthrid subthrid);
char __fplyx_memram_thrmemlimset(fplyx_vmem_t * self, fplyx_memram_subthrid subthrid, size_t size);
char __fplyx_memram_thrdevref(fplyx_vmem_t * self, char* dev_from, char* dev_to, fplyx_memram_subthrid subthrid_from, fplyx_memram_subthrid subthrid_to);
char __fplyx_memram_thrdevunref(fplyx_vmem_t * self, char* dev_from, fplyx_memram_subthrid subthrid);
char* __fplyx_memram_thrdevresolv(fplyx_vmem_t * self, char* name, fplyx_memram_subthrid subthrid, fplyx_memram_subthrid result);
size_t __fplyx_memram_thrsz(fplyx_vmem_t * self, fplyx_memram_subthrid subthrid);
char __fplyx_memram_thrsuperflags(fplyx_vmem_t * self, fplyx_memram_subthrid subthrid);
//char* __fplyx_memram_rannot(fplyx_vmem_t * self, fplyx_memram_ndataid ndataid, size_t limit);
//char __fplyx_memram_sannot(fplyx_vmem_t * self, fplyx_memram_ndataid ndataid, char* data);
char __fplyx_memram_cdevcreate(fplyx_vmem_t * self, char* name, char* ihnd, char* ohnd, char* ibuff, unsigned int ibufflimit, char* obuff, unsigned int obufflimit, fplyx_memram_subthrid subthrid, fplyx_memram_cdevid result);
unsigned int __fplyx_memram_cdevamount(fplyx_vmem_t * self, fplyx_memram_subthrid subthrid);
char __fplyx_memram_cdevget(fplyx_vmem_t * self, char* name, fplyx_memram_subthrid subthrid, fplyx_memram_cdevid result);
void __fplyx_memram_cdev_at(fplyx_vmem_t * self, unsigned int id, fplyx_memram_subthrid subthrid, fplyx_memram_cdevid result);
char __fplyx_memram_cdevdel(fplyx_vmem_t * self, fplyx_memram_cdevid cdevid);
char* __fplyx_memram_cdevgihnd(fplyx_vmem_t * self, fplyx_memram_cdevid cdevid);
char* __fplyx_memram_cdevgohnd(fplyx_vmem_t * self, fplyx_memram_cdevid cdevid);
char __fplyx_memram_cdevsihnd(fplyx_vmem_t * self, fplyx_memram_cdevid cdevid, char* ihnd);
char __fplyx_memram_cdevsohnd(fplyx_vmem_t * self, fplyx_memram_cdevid cdevid, char* ohnd);
char __fplyx_memram_cdevreallocib(fplyx_vmem_t * self, fplyx_memram_cdevid cdevid, size_t size);
char __fplyx_memram_cdevreallocob(fplyx_vmem_t * self, fplyx_memram_cdevid cdevid, size_t size);
size_t __fplyx_memram_cdevszofib(fplyx_vmem_t * self, fplyx_memram_cdevid cdevid);
size_t __fplyx_memram_cdevszofob(fplyx_vmem_t * self, fplyx_memram_cdevid cdevid);
char* __fplyx_memram_cdevgetib(fplyx_vmem_t * self, fplyx_memram_cdevid cdevid);
char __fplyx_memram_cdevsetib(fplyx_vmem_t * self, fplyx_memram_cdevid cdevid, char* ibuff);
char* __fplyx_memram_cdevgetob(fplyx_vmem_t * self, fplyx_memram_cdevid cdevid);
char __fplyx_memram_cdevsetob(fplyx_vmem_t * self, fplyx_memram_cdevid name, char* obuff);

size_t __fplyx_memram_szofsubthrid();
size_t __fplyx_memram_szofndataid();
size_t __fplyx_memram_szofcdevid();
//size_t __fplyx_memram_szofexstacknodeid();

char __fplyx_memram_subthrid_valid(fplyx_memram_subthrid subthrid);
char __fplyx_memram_ndataid_valid(fplyx_memram_ndataid ndataid);
char __fplyx_memram_cdeviceid_valid(fplyx_memram_cdevid cdevid);
//char __fplyx_memram_exstacknodeid_valid(fplyx_memram_exstacknodeid exstacknodeid);
char* __fplyx_memram_ndname(fplyx_vmem_t *, fplyx_memram_ndataid namedataid);
unsigned long __fplyx_memram_ndid(fplyx_vmem_t *, fplyx_memram_ndataid namedataid);
void __fplyx_memram_ndsubthr(fplyx_vmem_t *, fplyx_memram_subthrid subthrid, fplyx_memram_ndataid namedataid);
unsigned long __fplyx_memram_ndstackdepth(fplyx_vmem_t *, fplyx_memram_ndataid namedataid);
char* __fplyx_memram_thrname(fplyx_vmem_t *, fplyx_memram_subthrid subthrid);
unsigned int __fplyx_memram_thrid(fplyx_vmem_t *, fplyx_memram_subthrid subthrid);
char* __fplyx_memram_cdevname(fplyx_vmem_t *, fplyx_memram_cdevid cdevid);
unsigned int __fplyx_memram_cdevid(fplyx_vmem_t *, fplyx_memram_cdevid cdevid);


#endif /* VMEMDRV_RAM_H_ */
