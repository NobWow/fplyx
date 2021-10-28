cmake_minimum_required(VERSION 3.19.6)
project(fplyx)
#for YCM generator
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# deps

add_library(fplyx SHARED "")
add_executable(fplyxuser "")
set_property(TARGET fplyx PROPERTY POSITION_INDEPENDENT_CODE ON)
add_executable(fplyxdbg "")
target_link_libraries(fplyx utf8proc)
target_link_libraries(fplyxuser fplyx)
target_include_directories(fplyx PUBLIC include)
target_include_directories(fplyxdbg PUBLIC include)
include_directories(deps/utf8proc)
add_subdirectory(src)
add_subdirectory(deps/utf8proc)
