cmake_minimum_required (VERSION 2.8)

project(shell)

# uncomment this line to activate makefile verbose mode
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(${PROJECT_SOURCE_DIR}/src)

# lib google test (for unit tests)
set(LIBGTEST_DIR "${PROJECT_SOURCE_DIR}/tests/libgtest")
add_subdirectory(${LIBGTEST_DIR})

set(UTEST_DIR "${PROJECT_SOURCE_DIR}/tests")
add_subdirectory(${UTEST_DIR})
add_custom_target(utests
    COMMAND "${UTEST_DIR}/shelllib_unittests.bin"
    WORKING_DIRECTORY "${UTEST_DIR}"
    COMMENT "Running unit tests")

add_definitions(-Wall -Wextra)

set(SOURCES
    src/shell_env.cc
    src/shell_cmd.cc
)

set(LIBSHELL_NAME "\"Shell Library\"")
set(LIBSHELL_VERSION_MAJOR 0)
set(LIBSHELL_VERSION_MINOR 3)
set(LIBSHELL_VERSION_PATCH 0)
set(LIBSHELL_VERSION_EXTRA_RAW -dev)
set(LIBSHELL_VERSION_EXTRA "\"${LIBSHELL_VERSION_EXTRA_RAW}\"")

set(LIBSHELL_VERSION_FULL ${LIBSHELL_VERSION_MAJOR}.${LIBSHELL_VERSION_MINOR}.${LIBSHELL_VERSION_PATCH}${LIBSHELL_VERSION_EXTRA_RAW})
set(LIBSHELL_COPYRIGHT "\"Copyright 2015 Legrand France\"")

configure_file (
  "${PROJECT_SOURCE_DIR}/src/shell_info.h.in"
  "${PROJECT_SOURCE_DIR}/src/shell_info.h_generated"
  )

add_library(shell ${SOURCES})
