target_sources(fplyx
    PUBLIC
        fplyx.c
        fplyx_exti.c
        fplyx_general.c
)
target_sources(fplyxdbg
    PUBLIC
        fplyx.c
        fplyx_test.c
        fplyx_exti.c
        fplyx_general.c
)
target_sources(fplyxuser PUBLIC fplyx_user.c)
add_subdirectory(dev)
add_subdirectory(vmemdrv)
add_subdirectory(interp)
