/*
 * fplyx_general.h
 *
 *  Created on: 22 apr. 2021.
 *      Author: NobWow
 */

#ifndef FPLYX_GENERAL_H_
#define FPLYX_GENERAL_H_
#include <stddef.h>
#include <stdint.h>

void fplyxg_pushptr(void ***arr, unsigned int* const narr, void *item);
void fplyxg_dev_allocbuffer(char** buf, unsigned int* const nbuf, const unsigned int size);
void fplyxg_dev_deallocbuf(char** buf, unsigned int* const nbuf);
#endif /* FPLYX_GENERAL_H_ */
