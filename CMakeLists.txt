cmake_minimum_required (VERSION 2.8)

project(ownshell)

# uncomment this line to activate makefile verbose mode
#set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(${PROJECT_SOURCE_DIR}/src)

# lib google test (for unit tests)
set(LIBGTEST_DIR "${PROJECT_SOURCE_DIR}/tests/libgtest")
add_subdirectory(${LIBGTEST_DIR})

set(UTEST_DIR "${PROJECT_SOURCE_DIR}/tests")
add_subdirectory(${UTEST_DIR})
add_custom_target(test
    COMMAND "${UTEST_DIR}/ownshelllib_unittests.bin"
    WORKING_DIRECTORY "${UTEST_DIR}"
    COMMENT "Running unit tests")

# examples
add_subdirectory(${PROJECT_SOURCE_DIR}/examples)

add_definitions(-Wall -Wextra)

set(SOURCES
    src/shell_env.cc
    src/shell_cmd.cc
    src/shell_module.cc
    src/shell_component.cc
    src/shell_app.cc
)

set(OWNSHELL_NAME "\"ownShell Library\"")
set(OWNSHELL_VERSION_MAJOR 0)
set(OWNSHELL_VERSION_MINOR 3)
set(OWNSHELL_VERSION_PATCH 0)
set(OWNSHELL_VERSION_EXTRA_RAW -dev)
set(OWNSHELL_VERSION_EXTRA "\"${LIBSHELL_VERSION_EXTRA_RAW}\"")

set(OWNSHELL_VERSION_FULL ${LIBSHELL_VERSION_MAJOR}.${LIBSHELL_VERSION_MINOR}.${LIBSHELL_VERSION_PATCH}${LIBSHELL_VERSION_EXTRA_RAW})
set(OWNSHELL_COPYRIGHT "\"Copyright 2015 Peio Roth\"")

configure_file (
  "${PROJECT_SOURCE_DIR}/src/shell_info.h.in"
  "${PROJECT_SOURCE_DIR}/src/shell_info.h_generated"
  )

add_library(ownshell ${SOURCES})
