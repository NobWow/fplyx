# WIP (work in progress)
The library and/or documentation is not yet complete nor debugged. Feel free to post an issues if you found some.
# fplyx
FPlyx (Flexible Programming language with Yieldable eXecution) - multipurpose procedure-oriented scripting engine that can be integrated into other apps with native support. It's modular structure allows other developers to write custom devices, memory interfaces (vmemdrv) and interpreters.
# Concept
The idea of making fplyx is to create an easily integrable, reimplementable, portable platform for universal FPlyx programs:
* The FPlyx program is the bytecode - unlike any other bytecodes, this one is position independent:
  * this, however, may reduce execution performance, but lets the implementation to realign the data without influence.
* As Simple as Possible:
  * refrain from using a lot of complex bytecode semantics.
  * simplier the code = more portability.
  * simplier the FPlyx implementation = less work required for other developers.
* Asynchronous API (invoke a single statement and jump to another one) doesn't block the thread for an entire code.
* 2 in 1: Sandboxing features & concurrency implemented as cooperative tasks *(aka subthreads)*
* IO is performed through *virtual devices* that can also be shadowed by *custom devices* in the code.
* Variables are stored as *named data* and automatically destroyed by __reference counting__ GC scheme
* Memory management is done through *virtual memory* interface *(or vmemdrv)*, allowing the runtime data (e.g. execution stack, variables, tasks) to be processed in a filesystem, but depending on the IO speed of this filesystem the performance might significantly drop.
* Both memory usage and subthread amount can be limited.
# Building on Windows (WIP)
* This is not yet been tested under Windows since this project has been developed under Linux/FreeBSD platforms.
1. Make sure that CMake is installed. If it isn't, download and install CMake from their official site: https://cmake.org/download/
  * CMake Installer for 64-bit Windows: https://github.com/Kitware/CMake/releases/download/v3.21.2/cmake-3.21.2-windows-x86_64.msi
  * CMake Installer for 32-bit Windows: https://github.com/Kitware/CMake/releases/download/v3.21.2/cmake-3.21.2-windows-i386.msi
2. Clone this repository: Open up the git command line in the suitable directory and then enter
  * `git clone --recursive https://github.com/NobWow/fplyx.git`
  * Option `--recursive` will automatically download all the submodules into the `deps` folder
3. Open CMake GUI in the project folder.
4. Make sure that the source folder points to the repository's root.
5. Browse Build directory and create a `build` folder inside of the repository's root.
6. Press `Configure` button
7. Then, the CMake should create a configured Visual Studio project. Open this project in the Visual Studio and build.
8. *more coming soon...*
# Building on Linux/Unix (GNU/Linux, FreeBSD, OpenBSD etc.)
1. Make sure that a GCC is installed in your system
2. Make sure that CMake is also installed.
## CMake under Ubuntu, Debian, ZorinOS etc...
  * `$ sudo apt-get install gcc cmake`
## CMake under Fedora, RHEL, CentOS...
  * `$ sudo yum install gcc cmake`
## Arch based GNU/Linux distro
  * `$ sudo pacman -Sy gcc cmake`
## FreeBSD
  * `$ sudo pkg install gcc cmake`
## OpenBSD/NetBSD
  * `# pkg_add -i gcc cmake`
3. Create a build directory in a repository's folder
  * `mkdir build && cd build`
4. Run CMake configuration
  * `cmake ..`
5. Build the libraries
  * `make -jN` where N is the number of CPU threads. Omit the `-jN` parameter if you're unsure.
6. On successful build, the dynamic library and test executable will be in the build folder. `make install` feature is not yet implemented
