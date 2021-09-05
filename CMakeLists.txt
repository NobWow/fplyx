cmake_minimum_required(VERSION 3.19.6)
project(fplyx)
#for YCM generator
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )



add_library(libfplyx SHARED "")
set_property(TARGET libfplyx PROPERTY POSITION_INDEPENDENT_CODE ON)
add_executable(fplyxdbg "")
target_include_directories(libfplyx PUBLIC "include")
target_include_directories(fplyxdbg PUBLIC "include")
add_subdirectory(src)

