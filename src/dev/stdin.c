#include <dev/stdin.h>
#include <poll.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fplyx_general.h>
#include <string.h>

fplyx_vdevice_impl_t* fplyx_stdin_create()
{
    fplyx_vdevice_impl_t* extension = (fplyx_vdevice_impl_t*) malloc(sizeof(fplyx_vdevice_impl_t));
    memset(extension, 0, sizeof(fplyx_vdevice_impl_t));
    extension->name = "stdin";
    extension->prepare = &fplyx_devstdin_prepare;
    extension->end = &fplyx_devstdin_end;
    return extension;
}

void fplyx_devstdin_prepare(fplyx_vdevice_impl_t *self)
{
    self->vdevice = (fplyx_vdevice_t *) malloc(sizeof(fplyx_vdevice_t));
    memset(self->vdevice, 0, sizeof(fplyx_vdevice_t));
    if(self->vdevice)
    {
        self->vdevice->name = "stdin";
        /*allocate all the stuff here, TODO: all core functions*/ 
        /* stdout is write-only */
        self->vdevice->alloc_rbuf = 0;
        self->vdevice->alloc_wbuf = 0;

        /* No need to allocate buffer: since subthread suspends before reading, all the data is stored
           outside of the buffers and will be pushed partially
           or fully to the RAM when stdout becomes available
           Partial IO is implemented by interpreters
        fplyxg_dev_allocbuffer(self->vdevice->rbuf, &self->vdevice->alloc_rbuf, 8192);*/
        self->vdevice->rbuf = NULL;
        self->vdevice->wbuf = NULL;
        /* bit 1, 5 are set: readable, has file descriptor */
        self->vdevice->iomode =
            FPLYX_VDEV_IOMODE_READABLE |
            FPLYX_VDEV_IOMODE_FD;
        self->vdevice->iostate =
            FPLYX_VDEV_IOSTATE_ROPEN;
        self->vdevice->_fd = STDIN_FILENO;
        self->vdevice->make_pollfd = &__fplyx_devstdin_mkpfd; 
        self->vdevice->read_available = &__fplyx_devstdin_rav;
        self->vdevice->write_available = &__fplyx_devstdin_wav;
        self->vdevice->open_read = &__fplyx_devstdin_opr;
        self->vdevice->open_write = &__fplyx_devstdin_opw;
        self->vdevice->seek_read = &__fplyx_devstdin_sr;
        self->vdevice->seek_write = &__fplyx_devstdin_sw;
        self->vdevice->read = &__fplyx_devstdin_r;
        self->vdevice->write = &__fplyx_devstdin_w;
        self->vdevice->close_read = &__fplyx_devstdin_clr;
        self->vdevice->close_write = &__fplyx_devstdin_clw;
        self->vdevice->flush_read = &__fplyx_devstdin_fr;
        self->vdevice->flush_write = &__fplyx_devstdin_fw;
    }
}

void fplyx_devstdin_end(fplyx_vdevice_impl_t *self)
{
    /* deallocate all the things that we made in fplyx_devstdout_prepare */
    /*
    if(self->vdevice->alloc_rbuf && self->vdevice->rbuf)
    {
        if(self->vdevice->iostate & FPLYX_VDEV_IOSTATE_WBUFFER) 
        {
            unsigned int len = strlen(self->vdevice->wbuf);
            printf("stdout: unflushed buffer (%d): \n%s", len,
            self->vdevice->wbuf);
            self->vdevice->iostate -= FPLYX_VDEV_IOSTATE_WBUFFER;
        }
    }*/
    self->vdevice->iomode = 0;
    free(self->vdevice);
}

struct pollfd __fplyx_devstdin_mkpfd(fplyx_vdevice_t *self)
{
    struct pollfd pfd;
    pfd.fd = STDIN_FILENO;
    pfd.events =
        POLLIN     |
        POLLRDBAND;
    return pfd;
}

/* when _fd and pollfd are unset */
char __fplyx_devstdin_rav (fplyx_vdevice_t *self)
{
    if(self->iostate & FPLYX_VDEV_IOSTATE_RAVAIL)
        return 1;
    else
        return 0;
}
char __fplyx_devstdin_wav (fplyx_vdevice_t *self)
{
    return 0;
}
char __fplyx_devstdin_opr (fplyx_vdevice_t *self)
{
    if(!(self->iostate & FPLYX_VDEV_IOSTATE_ROPEN))
    {
        self->iostate |= FPLYX_VDEV_IOSTATE_ROPEN;
        return 1;
    } else
        return 0;
}
char __fplyx_devstdin_opw (fplyx_vdevice_t *self)
{
    if(!(self->iostate & FPLYX_VDEV_IOSTATE_WERR))
        self->iostate |= FPLYX_VDEV_IOSTATE_WERR;
    return 0;
}
char __fplyx_devstdin_clr (fplyx_vdevice_t *self)
{
    if(self->iostate & FPLYX_VDEV_IOSTATE_ROPEN)
    {
        self->iostate &= ~FPLYX_VDEV_IOSTATE_ROPEN;
        return 1;
    } else
        return 0;
}
char __fplyx_devstdin_clw (fplyx_vdevice_t *self)
{
    return 0;
}
char __fplyx_devstdin_sr (fplyx_vdevice_t *self, int offset)
{
    return 0;
}
char __fplyx_devstdin_sw (fplyx_vdevice_t *self, int offset)
{
    return 0;
}
char __fplyx_devstdin_r(fplyx_vdevice_t *self, char* target_ptr, size_t amount)
{
    if(
        (self->iostate & FPLYX_VDEV_IOSTATE_RAVAIL) &&
        (self->iostate & FPLYX_VDEV_IOSTATE_ROPEN)
    )
    {
        fread(target_ptr, sizeof(char), amount, stdin);
        self->iostate &= ~FPLYX_VDEV_IOSTATE_RAVAIL;
        return 1;
    }
    else
        return 0;
}
char __fplyx_devstdin_w(fplyx_vdevice_t *self, const char* data_ptr, size_t amount)
{

    if(!(self->iostate & FPLYX_VDEV_IOSTATE_WERR))
        self->iostate |= FPLYX_VDEV_IOSTATE_WERR;
    return 0;
}
char __fplyx_devstdin_fr(fplyx_vdevice_t *self)
{
    return 0;
}
char __fplyx_devstdin_fw(fplyx_vdevice_t *self)
{
    return 0;
}

/*	char 			(*read_available)(struct __fplyx_vdevice_t *);
	char 			(*write_available)(struct __fplyx_vdevice_t *);
	 In most cases, these pointers point to the predefined implementations using poll() with null timeout
	char			(*open_read)(struct __fplyx_vdevice_t *);
	char			(*open_write)(struct __fplyx_vdevice_t *);
	char			(*close_read)(struct __fplyx_vdevice_t *);
	char			(*close_write)(struct __fplyx_vdevice_t *);
	char			(*read)(struct __fplyx_vdevice_t *, char * , size_t);
	char			(*write)(struct __fplyx_vdevice_t *, const char * , size_t);
	char			(*flush_read)(struct __fplyx_vdevice_t *);
	char			(*flush_write)(struct __fplyx_vdevice_t *);
*/
