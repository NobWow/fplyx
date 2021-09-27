/*
 * vdev.h
 *
 *  Created on: 21 mar. 2021.
 *      Author: NobWow
 */

#ifndef FPLYX_TYPE_VDEV_H_
#define FPLYX_TYPE_VDEV_H_
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>

#define FPLYX_VDEV_IOMODE_READABLE  1
#define FPLYX_VDEV_IOMODE_WRITABLE  2
#define FPLYX_VDEV_IOMODE_SEEKABLE  4
#define FPLYX_VDEV_IOMODE_BLOCKING  8
#define FPLYX_VDEV_IOMODE_FD        16
#define FPLYX_VDEV_IOMODE_BUFFER    32
#define FPLYX_VDEV_IOSTATE_ROPEN    1
#define FPLYX_VDEV_IOSTATE_WOPEN    2
#define FPLYX_VDEV_IOSTATE_RAVAIL   4
#define FPLYX_VDEV_IOSTATE_WAVAIL   8
#define FPLYX_VDEV_IOSTATE_RERR     16
#define FPLYX_VDEV_IOSTATE_WERR     32
#define FPLYX_VDEV_IOSTATE_RBUFFER  64
#define FPLYX_VDEV_IOSTATE_WBUFFER  128
typedef struct __fplyx_vdevice_t
{
	//basic stuff
	/*
	 * iomode sets 8 bits to describe features for this device
	 * 1. readable (can provide data to the interpreter)
	 * 2. writable (interpreter can provide data to the device)
	 * 3. seekable io (random access, allows the interpreter alter the read-write position)
	 * 4. blocking (blocks virtual thread's execution when performing an IO until it is ready)
	 * 5. non-zero fd (has its own file descriptor, allowing the interpreter to ppoll the device)
	 * 6. bufferized (some portion of data, once gathered from the outside-world or pushed into by the interpreter, stored in the RAM)
	 * 	  If this bit is set to 0, rbuf and wbuf points to NULL and alloc_rbuf, same as alloc_wbuf are set to 0.
	 * 7. custom (not explicitly defined)
	 * 8. custom (not explicitly defined)
	 */
	char 			iomode;
	unsigned long	iopos;
	/*
	 * iostate sets 8 bits to define its current state
	 * 1. device is opened for reading
	 * 2. device is opened for writing
	 * 3. reading from this device is possible in this current moment.
	 * 4. writing into this device is possible in this current moment.
	 *    3 and 4 are not modified by device itself, but only by the interpreter.
	 * 5. error occurred while trying to read data.
	 * 6. error occurred while trying to write data.
     * 7. rbuf is not empty
     * 8. wbuf is not empty
	 */
	char			iostate;
	FILE*           handle;
	unsigned int 	alloc_rbuf;
	char* 			rbuf;
	unsigned int	alloc_wbuf;
	char*			wbuf;
	char*	    	name; //null-terminated
	char 			(*read_available)(struct __fplyx_vdevice_t *);
	char 			(*write_available)(struct __fplyx_vdevice_t *);
	/* In most cases, these pointers point to the predefined implementations using poll() with null timeout */
	char			(*open_read)(struct __fplyx_vdevice_t *);
	char			(*open_write)(struct __fplyx_vdevice_t *);
	char			(*close_read)(struct __fplyx_vdevice_t *);
	char			(*close_write)(struct __fplyx_vdevice_t *);
    char            (*seek_read)(struct __fplyx_vdevice_t *, int);
    char            (*seek_write)(struct __fplyx_vdevice_t *, int);
	char			(*read)(struct __fplyx_vdevice_t *, char * /*data to read into*/, size_t);
	char			(*write)(struct __fplyx_vdevice_t *, char * /*data to write from*/, size_t);
	char			(*flush_read)(struct __fplyx_vdevice_t *);
	char			(*flush_write)(struct __fplyx_vdevice_t *);

} fplyx_vdevice_t;

#endif /* FPLYX_TYPE_VDEV_H_ */
