/*
 * filemem.h
 *
 *  Created on: 16 apr. 2021.
 *      Author: NobWow
 */

#ifndef VMEMDRV_FILEMEM_H_
#define VMEMDRV_FILEMEM_H_
#include <fplyx_type/extension.h>

void fplyx_filemem_prepare(fplyx_memdrv_impl_t* self);
void fplyx_filemem_end(fplyx_memdrv_impl_t* self);
fplyx_vmem_t* fplyx_filemem_obtain(fplyx_memdrv_impl_t* self);
char __fplyx_filemem_prepare(fplyx_vmem_t* self);
char __fplyx_filemem_end(fplyx_vmem_t* self);
size_t __fplyx_filemem_getallocspace(fplyx_vmem_t* self);
size_t __fplyx_filemem_getmaxheap(fplyx_vmem_t* self);
void __fplyx_filemem_setmaxheap(fplyx_vmem_t* self, size_t size);
/* data operations */
char __fplyx_filemem_wnd(fplyx_vmem_t* self, char* name, char* data, size_t size, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_rewnd(fplyx_vmem_t* self, char* name, char* data, size_t size, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_dnd(fplyx_vmem_t* self, char* name, char** subthr, unsigned int nsubthr);
size_t __fplyx_filemem_sizeofnd(fplyx_vmem_t* self, char* name, char** subthr, unsigned int nsubthr);
char* __fplyx_filemem_rnd(fplyx_vmem_t* self, char* name, size_t size, size_t offset, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_and(fplyx_vmem_t* self, char* name, char* data, size_t size, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_cnd(fplyx_vmem_t* self, char* name, size_t size, size_t offset, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_exnd(fplyx_vmem_t* self, char* name, char** subthr, unsigned int nsubthr);
char* __fplyx_filemem_rexec(fplyx_vmem_t* self, char* name, long int jump, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_crefd(fplyx_vmem_t* self, char perms, char* name, char* target, char** subthr, unsigned int nsubthr, char** target_subthr, unsigned int target_nsubthr);
fplyx_reference_data_t fplyx_filemem_greftrg(fplyx_vmem_t *, char* name, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_sreftrg(fplyx_vmem_t * self, char* name, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_isref(fplyx_vmem_t * self, char* name, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_grefperm(fplyx_vmem_t * self, char* name, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_srefperm(fplyx_vmem_t * self, char perms, char* name, char** subthr, unsigned int nsubthr);
fplyx_reference_data_t __fplyx_filemem_greftrg(fplyx_vmem_t * self, char* name, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_sexecpos(fplyx_vmem_t * self, fplyx_reference_stack_t * pos, char** subthr, unsigned long nsubthr);
fplyx_reference_stack_t * __fplyx_filemem_gsp(fplyx_vmem_t* self, char** subthr, unsigned int nsubthr);
void __fplyx_filemem_llmapid(fplyx_vmem_t* self, char** subthr, unsigned int nsubthr);
void __fplyx_filemem_slmapid(fplyx_vmem_t* self, unsigned long pos, char** subthr, unsigned int nsubthr);
unsigned long __fplyx_filemem_gthriopos(fplyx_vmem_t * self, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_sthriopos(fplyx_vmem_t * self, unsigned long pos, char** subthr, unsigned int nsubthr);
unsigned int __fplyx_filemem_thrgcount(fplyx_vmem_t * self);
unsigned int __fplyx_filemem_thriterval(fplyx_vmem_t * self);
void __fplyx_filemem_thrsiter(fplyx_vmem_t * self, unsigned int interval);
char** __fplyx_filemem_thrnarr(fplyx_vmem_t * self, size_t limit, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_thrcreate(fplyx_vmem_t * self, char opts, char** subthr, unsigned int nsubthr); //first argument:
// first bit: blank out superior namespace
// second bit: blank out devices
char __fplyx_filemem_thrsus(fplyx_vmem_t * self, char mode, char** subthr, unsigned int nsubthr); //last argument is 0 or 1
char __fplyx_filemem_thrdel(fplyx_vmem_t * self, char** subthr, unsigned int nsubthr); //NOTE: this does NOT remove subthread exec code, but removes it from thread table
//these functions does apply to encapsulated subthreads only!
unsigned int __fplyx_filemem_thrlim(fplyx_vmem_t * self, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_thrlimset(fplyx_vmem_t * self, unsigned int amount, char** subthr, unsigned int nsubthr);
unsigned long __fplyx_filemem_thrmemlim(fplyx_vmem_t * self, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_thrmemlimset(fplyx_vmem_t * self, unsigned long size, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_thrdevref(fplyx_vmem_t * self, char* realdev, char* virtualdev, char** subthr_from, unsigned int nsubthr_from, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_thrdevunref(fplyx_vmem_t * self, char* virtualdev, char** subthr, unsigned int nsubthr);
size_t __fplyx_filemem_thrsz(fplyx_vmem_t * self, char** subthr, unsigned int nsubthr);
char* __fplyx_filemem_rannot(fplyx_vmem_t * self, char* name, size_t limit, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_sannot(fplyx_vmem_t * self, char* name, char* data, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_cdevcreate(fplyx_vmem_t * self, char* name, char*, char*, char*, unsigned int, char*, unsigned int, char**, unsigned int);
char __fplyx_filemem_cdevdel(fplyx_vmem_t * self, char*, char**, unsigned int);
char* __fplyx_filemem_cdevgihnd(fplyx_vmem_t * self, char* name, char** subthr, unsigned int nsubthr);
char* __fplyx_filemem_cdevgohnd(fplyx_vmem_t * self, char* name, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_cdevsihnd(fplyx_vmem_t * self, char* name, char* data, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_cdevsohnd(fplyx_vmem_t * self, char* name, char* data, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_cdevreallocib(fplyx_vmem_t * self, char* name, size_t size, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_cdevreallocob(fplyx_vmem_t * self, char* name, size_t size, char** subthr, unsigned int nsubthr);
size_t __fplyx_filemem_cdevszofib(fplyx_vmem_t * self, char* name, char** subthr, unsigned int nsubthr);
size_t __fplyx_filemem_cdevszofob(fplyx_vmem_t * self, char* name, char** subthr, unsigned int nsubthr);
char* __fplyx_filemem_cdevgetib(fplyx_vmem_t * self, char* name, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_cdevsetib(fplyx_vmem_t * self, char* name, char* data, char** subthr, unsigned int nsubthr);
char* __fplyx_filemem_cdevgetob(fplyx_vmem_t * self, char* name, char** subthr, unsigned int nsubthr);
char __fplyx_filemem_cdevsetob(fplyx_vmem_t * self, char* name, char* data, char** subthr, unsigned int nsubthr);



#endif /* VMEMDRV_FILEMEM_H_ */
