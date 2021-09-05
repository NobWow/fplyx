# WIP (work in progress)
The library and/or documentation is not yet complete nor debugged. Feel free to post an issues if you found some.
# fplyx
FPlyx (Flexible Programming language with Yieldable eXecution) - multipurpose procedure-oriented scripting engine that can be integrated into other apps with native support. It's modular structure allows other developers to write custom devices, memory interfaces (vmemdrv) and interpreters.
# Concept
The idea of making fplyx is to create a scripting engine that works like an emulator and bytecode interpreter:
* Code can be executed partially (invoke a single statement and jump to another one)
* 2 in 1: Sandboxing features & concurrency implemented as cooperative tasks *(aka subthreads)*
* IO is performed through *virtual devices* that can also be shadowed by *custom devices* in the code.
* Variables are stored as *named data* and automatically destroyed by __reference counting__ GC scheme
* Memory management is done through *virtual memory* interface *(or vmemdrv)*, allowing the runtime data (e.g. execution stack, variables, tasks) to be processed in a filesystem, but depending on the IO speed of this filesystem the performance might significantly drop.
* Both memory usage and subthread amount can be limited.
