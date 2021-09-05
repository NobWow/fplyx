/*
 * reference_pos.h
 *
 *  Created on: 29 mar. 2021.
 *      Author: NobWow
 */

#ifndef FPLYX_TYPE_REFERENCE_POS_H_
#define FPLYX_TYPE_REFERENCE_POS_H_
#include <stddef.h>

/*
 * The way FPlyx Code interpreted is: its got 2 things: the entrypoint with main command pointer that is bound to it
 * at the start of execution and the LIFO sequence of those pointer that increases on each function call
 * or any scoped code
 * The leading command(s) of any FPlyx "main" entrypoint are "feature" commands that defines the requirements of
 * the program to function without errors. For example: FPlyx min or max version, function existance, device existance etc.
 * These structures are used directly in RAM virtual memory driver and allocated manually in others.
 */

#endif /* FPLYX_TYPE_REFERENCE_POS_H_ */
