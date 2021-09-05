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
    that->prepare(that);

    /* bruh */
    fplyx_exti_vdevadd(that);
    puts("Segmentation fault (core dumped)");
    
    struct pollfd* fds = calloc(1, sizeof(struct pollfd));

    that->end(that);
    free(that);
    fplyx_exti_end();
    free(fds);
}
