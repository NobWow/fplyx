/*
 * fplyx_general.c
 *
 *  Created on: 22 apr. 2021.
 *      Author: NobWow
 */


#include <fplyx_general.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void fplyxg_pushptr(void *** const arr, unsigned int* const narr, void * const item)
{
	*arr = (void **) reallocarray(*arr, *narr + 1, sizeof(void *));
    if(!(*arr)) return;
    (*narr)++;
	*arr[*narr - 1] = item;
}
void fplyxg_dev_allocbuffer(char** const buf, unsigned int* const nbuf, const unsigned int size)
{
    *buf = (char *) malloc(size);
    memset(*buf, 0, size);
    if(*buf)
        *nbuf = size;
    else
        *nbuf = 0;
}
void fplyxg_dev_deallocbuf(char** buf, unsigned int* const nbuf)
{
    if(*buf)
    {
        free(*buf);
        *(nbuf) = 0;
        *buf = NULL;
    }
}
