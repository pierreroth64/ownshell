cmake_minimum_required (VERSION 2.8)

project(examples)

include_directories(${PROJECT_SOURCE_DIR}/../src)

add_definitions(-Wall -Wextra)

# reference libshell archive
set(LIBSHELL_ARCHIVE "${PROJECT_SOURCE_DIR}/../libshell.a")
add_library(libshell STATIC IMPORTED)
set_property(TARGET libshell PROPERTY IMPORTED_LOCATION ${LIBSHELL_ARCHIVE})

add_executable(my_shell.bin my_shell.cc)
target_link_libraries(my_shell.bin libshell)

