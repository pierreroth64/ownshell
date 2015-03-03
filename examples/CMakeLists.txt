cmake_minimum_required (VERSION 2.8)

project(examples)

set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(${PROJECT_SOURCE_DIR}/../src)

add_definitions(-Wall -Wextra)

# reference libshell archive
set(OWNSHELL_ARCHIVE "${PROJECT_SOURCE_DIR}/../libownshell.a")
add_library(libownshell STATIC IMPORTED)
set_property(TARGET libownshell PROPERTY IMPORTED_LOCATION ${OWNSHELL_ARCHIVE})

# simple shell
add_executable(simple_shell.bin simple_shell.cc)
target_link_libraries(simple_shell.bin libownshell)

