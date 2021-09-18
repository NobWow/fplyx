cmake_minimum_required(VERSION 3.19.6)
project(fplyx)
#for YCM generator
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# deps
include(ExternalProject)

add_library(fplyx SHARED "")
set_property(TARGET fplyx PROPERTY POSITION_INDEPENDENT_CODE ON)
add_executable(fplyxdbg "")
target_include_directories(fplyx PUBLIC "include")
target_include_directories(fplyxdbg PUBLIC "include")
add_subdirectory(src)

