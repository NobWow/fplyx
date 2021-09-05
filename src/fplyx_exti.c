/*
 * fplyx_exti.c
 *
 *  Created on: 17 apr. 2021.
 *      Author: NobWow
 */

#include <fplyx_exti.h>
#include <fplyx_general.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


fplyx_vdevice_impl_t ** fplyx_vdevices;
unsigned int fplyx_vdev_n;
fplyx_memdrv_impl_t ** fplyx_memdrvs;
unsigned int fplyx_memdrvs_n;
fplyx_interpreter_impl_t ** fplyx_interpreters;
unsigned int fplyx_interp_n;

void fplyx_exti_start()
{
	fplyx_vdev_n = 0;
	/*fplyx_vdevices = (fplyx_vdevice_impl_t **) calloc(1, sizeof(void *));*/
	fplyx_vdevices = NULL;
	fplyx_memdrvs_n = 0;
	/*fplyx_memdrvs = (fplyx_memdrv_impl_t **) calloc(1, sizeof(void *));*/
	fplyx_memdrvs = NULL;
}
void fplyx_exti_end()
{
	if(fplyx_vdevices)
	{
		for(unsigned int i = 0; i < fplyx_vdev_n; i++)
		{
			fplyx_vdevices[i]->end(fplyx_vdevices[i]); // @suppress("Method cannot be resolved")
		}
		free(fplyx_vdevices);
	}
	if(fplyx_memdrvs)
	{
		for(unsigned int i = 0; i < fplyx_memdrvs_n; i++)
		{
			fplyx_memdrvs[i]->end(fplyx_memdrvs[i]);
		}
		free(fplyx_memdrvs);
	}
	if(fplyx_interpreters)
	{
		for(unsigned int i = 0; i < fplyx_interp_n; i++)
		{
			fplyx_interpreters[i]->end(fplyx_interpreters[i]);
		}
		free(fplyx_interpreters);
	}
	fplyx_vdevices = NULL;
	fplyx_memdrvs = NULL;
	fplyx_interpreters = NULL;
}

void fplyx_exti_vdevadd(fplyx_vdevice_impl_t * const device)
{
	if(!fplyx_exti_vdevfetch(device->name, NULL))
		fplyxg_pushptr((void***)&fplyx_vdevices, &fplyx_vdev_n, device);
}

fplyx_vdevice_impl_t *fplyx_exti_vdevfetch(const char* const name, unsigned int* const ri)
{
	if(fplyx_vdev_n == 0) {
		if(ri)
			*ri = 0;
		return NULL;
	}
	for(unsigned int i = 0; i < fplyx_vdev_n; i++)
	{
		if(fplyx_vdevices[i]->name == name) {
			if(ri)
				*ri = i;
			return fplyx_vdevices[i];
		}
	}
	if(ri)
		*ri = 0;
	return NULL;
}

void fplyx_exti_vdevdel(const char* const name)\
{
	unsigned int ri = 0;
	fplyx_vdevice_impl_t * const target =fplyx_exti_vdevfetch(name, &ri);
	if(!target)
		return;
	target->end(target);
	free(target);
	/* assert((void *) target == (void *)((void *)fplyx_vdevices + (ri) * sizeof(void *))); */
	memmove(fplyx_vdevices + ((ri) * sizeof(void *)),
			fplyx_vdevices + (ri + 1) * sizeof(void *),
			(size_t)((fplyx_vdev_n - ri + 1) * sizeof(void *)));
	fplyx_vdevices = (fplyx_vdevice_impl_t **) realloc(fplyx_vdevices,
    (--fplyx_vdev_n)*sizeof(void *) );
}
void fplyx_exti_vmemadd(fplyx_memdrv_impl_t * const memdrv)
{
	if(!fplyx_exti_vmemfetch(memdrv->name, NULL))
		fplyxg_pushptr((void ***) &fplyx_memdrvs, &fplyx_memdrvs_n, memdrv);
}

fplyx_memdrv_impl_t *fplyx_exti_vmemfetch(const char* const name, unsigned int* const ri)
{
	if(fplyx_memdrvs_n == 0) {
		if(ri)
			*ri = 0;
		return NULL;
	}
	for(unsigned int i = 0; i < fplyx_memdrvs_n; i++)
	{
		if(fplyx_memdrvs[i]->name == name) {
			if(ri)
				*ri = i;
			return fplyx_memdrvs[i];
		}
	}
	if(ri)
		*ri = 0;
	return NULL;
}

void fplyx_exti_vmemdel(const char* const name)
{
	unsigned int ri = 0;
	fplyx_memdrv_impl_t *target =fplyx_exti_vmemfetch(name, &ri);
	if(!target)
		return;
	target->end(target);
	free(target);
	/* assert((size_t) target == (size_t)((size_t)fplyx_memdrvs + (ri) * sizeof(void *))); */
	memmove(fplyx_memdrvs + (ri) * sizeof(void *),
			fplyx_memdrvs + (ri + 1) * sizeof(void *),
			(size_t)((fplyx_memdrvs_n - ri + 1) * sizeof(void *)));
	fplyx_memdrvs = (fplyx_memdrv_impl_t **) realloc(fplyx_memdrvs,
    (--fplyx_memdrvs_n)*sizeof(void *) );
}

void fplyx_exti_interpadd(fplyx_interpreter_impl_t * const interp)
{
	if(!fplyx_exti_interpfetch(interp->name, NULL))
		fplyxg_pushptr((void ***) &fplyx_interpreters, &fplyx_memdrvs_n, interp);
}

fplyx_interpreter_impl_t *fplyx_exti_interpfetch(const char* const name, unsigned int* const ri)
{
	if(fplyx_interp_n == 0) {
		if(ri)
			*ri = 0;
		return NULL;
	}
	for(unsigned int i = 0; i < fplyx_interp_n; i++)
	{
		if(fplyx_interpreters[i]->name == name) {
			if(ri)
				*ri = i;
			return fplyx_interpreters[i];
		}
	}
	if(ri)
		*ri = 0;
	return NULL;
}

void fplyx_exti_interpdel(const char* const name)
{
	unsigned int ri = 0;
	fplyx_interpreter_impl_t *target =fplyx_exti_interpfetch(name, &ri);
	if(!target)
		return;
	target->end(target);
	free(target);
	/* assert((void *) target == (size_t)((size_t)fplyx_interpreters + (ri) * sizeof(void *))); */
	memmove(fplyx_interpreters + (ri) * sizeof(void *),
			fplyx_interpreters + (ri + 1) * sizeof(void *),
			(size_t)((fplyx_interp_n - ri + 1) * sizeof(void *)));
	fplyx_interpreters = (fplyx_interpreter_impl_t **) realloc(fplyx_interpreters,
    (--fplyx_interp_n)*sizeof(void *) );
}

