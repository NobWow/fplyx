#include <stdio.h>

#include <dev/stdout.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fplyx_general.h>
#include <string.h>

fplyx_vdevice_impl_t* fplyx_devstdout_create()
{
    fplyx_vdevice_impl_t* extension = malloc(sizeof(fplyx_vdevice_impl_t));
    memset((void *)extension, 0, sizeof(fplyx_vdevice_impl_t));
    extension->name = "stdout";
    extension->prepare = &fplyx_devstdout_prepare;
    extension->end = &fplyx_devstdout_end;
    return extension;
}

void fplyx_devstdout_prepare(fplyx_vdevice_impl_t *self)
{
    self->vdevice = (fplyx_vdevice_t *) malloc(sizeof(fplyx_vdevice_t));
    memset(self->vdevice, 0, sizeof(fplyx_vdevice_t));
    if(self->vdevice)
    {
        self->vdevice->name = "stdout";
        /*allocate all the stuff here, TODO: all core functions*/ 
        /* stdout is write-only */
        self->vdevice->alloc_rbuf = 0;
        self->vdevice->alloc_wbuf = 0;

        /* No need to allocate buffer: since subthread suspends before writing, all the data is stored
           outside of the buffers and will be pushed partially
           or fully to the RAM when stdout becomes available
           Partial IO is implemented by interpreters
        fplyxg_dev_allocbuffer(self->vdevice->wbuf, &self->vdevice->alloc_wbuf, 8192);*/
        self->vdevice->rbuf = NULL;
        self->vdevice->wbuf = NULL;
        /* bit 2, 5 are set: writable, has file descriptor */
        self->vdevice->iomode =
            FPLYX_VDEV_IOMODE_WRITABLE  +
            FPLYX_VDEV_IOMODE_FD;
        self->vdevice->iostate =
            FPLYX_VDEV_IOSTATE_WOPEN;
        self->vdevice->handle = stdout;
        self->vdevice->read_available = &__fplyx_devstdout_rav;
        self->vdevice->write_available = &__fplyx_devstdout_wav;
        self->vdevice->open_read = &__fplyx_devstdout_opr;
        self->vdevice->open_write = &__fplyx_devstdout_opw;
        self->vdevice->seek_read = &__fplyx_devstdout_sr;
        self->vdevice->seek_write = &__fplyx_devstdout_sw;
        self->vdevice->read = &__fplyx_devstdout_r;
        self->vdevice->write = &__fplyx_devstdout_w;
        self->vdevice->close_read = &__fplyx_devstdout_clr;
        self->vdevice->close_write = &__fplyx_devstdout_clw;
        self->vdevice->flush_read = &__fplyx_devstdout_fr;
        self->vdevice->flush_write = &__fplyx_devstdout_fw;
    }
}

void fplyx_devstdout_end(fplyx_vdevice_impl_t *self)
{
    /* deallocate all the things that we made in fplyx_devstdout_prepare */
    /*
    if(self->vdevice->alloc_wbuf && self->vdevice->wbuf)
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
/* when _fd and pollfd are unset */
char __fplyx_devstdout_rav (fplyx_vdevice_t *self)
{
    return 0;
}
char __fplyx_devstdout_wav (fplyx_vdevice_t *self)
{
    if(self->iostate & FPLYX_VDEV_IOSTATE_WAVAIL)
        return 1;
    else
        return 0;
}
char __fplyx_devstdout_opr (fplyx_vdevice_t *self)
{
    self->iostate |= FPLYX_VDEV_IOSTATE_RERR;
    return 0;
}
char __fplyx_devstdout_opw (fplyx_vdevice_t *self)
{
    if(!(self->iostate & FPLYX_VDEV_IOSTATE_WOPEN))
    {
        self->iostate |= FPLYX_VDEV_IOSTATE_WOPEN;
        return 1;
    } else {
        return 0;
    }
}
char __fplyx_devstdout_clr (fplyx_vdevice_t *self)
{
    return 0;
}
char __fplyx_devstdout_clw (fplyx_vdevice_t *self)
{
    if(self->iostate & FPLYX_VDEV_IOSTATE_WOPEN)
    {
        self->iostate &= ~FPLYX_VDEV_IOSTATE_WOPEN;
        return 1;
    } else {
        return 0;
    }
}
char __fplyx_devstdout_sr (fplyx_vdevice_t *self, int offset)
{
    return 0;
}
char __fplyx_devstdout_sw (fplyx_vdevice_t *self, int offset)
{
    return 0;
}
char __fplyx_devstdout_r(fplyx_vdevice_t *self, char* target_ptr, size_t amount)
{
    self->iostate |= FPLYX_VDEV_IOSTATE_RERR;
    return 0;
}
char __fplyx_devstdout_w (fplyx_vdevice_t *self, const char* data_ptr, size_t amount)
{
    if(
        (self->iostate & FPLYX_VDEV_IOSTATE_WAVAIL) &&
        (self->iostate & FPLYX_VDEV_IOSTATE_WOPEN)
    )
    {
        fwrite(data_ptr, sizeof(char), amount, stdout);
        self->iostate &= ~FPLYX_VDEV_IOSTATE_WAVAIL;
        return 1;
    }
    else
        return 0;
}
char __fplyx_devstdout_fr (fplyx_vdevice_t *self)
{
    return 0;
}
char __fplyx_devstdout_fw (fplyx_vdevice_t *self)
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
