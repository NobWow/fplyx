#include <fplyx_general.h>
#include <fplyx_exti.h>
#include <stdio.h>
#include <stdlib.h>
#include <dev/stdout.h>
#include <poll.h>

int main(int argc, char** argv) {
    puts("Is everything compiled?");
    fplyx_exti_start();
    puts("Allocated!");
    fplyx_vdevice_impl_t* that = fplyx_devstdout_create();
    printf("AAAAA\n");
    printf("Device pointer -> %p\n", that);
    printf("BBBB\n");
    that->prepare(that);
    printf("segfault here?\n");
    /* bruh */
    fplyx_exti_vdevadd(that);
    puts("Segmentation faulted (core dumpet)");
    /* stdout is already open */
    that->vdevice->iostate |= FPLYX_VDEV_IOSTATE_WAVAIL; /* this should be assigned every time stdout becomes available for writing (in case of testing, it is just every time) */
    that->vdevice->write(that->vdevice, "Hello WOrld!\n", 10);
    that->vdevice->flush_write(that->vdevice); /*not needed as it isn't a buffered device*/
    struct pollfd* fds = calloc(1, sizeof(struct pollfd));
    /* that->end() is not called here, instead use fplyx_exti_vdevdel, as it calls that->end() as well as removing the element from the array */
    fplyx_exti_vdevdel("stdout");
    fplyx_exti_end();
    free(fds);
}
