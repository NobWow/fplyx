#include <fplyx.h>
#include <fplyx_exti.h>
#include <fplyx_type/interpreter.h>
#include <fplyx_type/vdev.h>
#include <fplyx_type/vmem.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    puts("Hello to FPlyx!");
    fplyx_interpreter_t* interpreter = fplyx_interpreter_init(NULL, NULL);
    if(interpreter) puts("Yay! The library works!");
    else puts("Unfortunately, the library is used in wrong way :(");
    fplyx_interpreter_destroy(interpreter);
    return 0;
}
