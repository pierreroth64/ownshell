cmake_minimum_required (VERSION 2.8)

project(ownshell)

# uncomment this line to activate makefile verbose mode
#set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/help_formatters)
include_directories(${PROJECT_SOURCE_DIR}/src/iterators)

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
    src/shell_info.cc
    src/help_formatters/shell_default_help_formatter.cc
    src/help_formatters/shell_colored_help_formatter.cc
    src/iterators/shell_module_default_iterator.cc
)

set(OWNSHELL_NAME "\"ownShell Library\"")
set(OWNSHELL_VERSION_MAJOR 0)
set(OWNSHELL_VERSION_MINOR 2)
set(OWNSHELL_VERSION_PATCH 0)
set(OWNSHELL_VERSION_EXTRA_RAW -dev)
set(OWNSHELL_VERSION_EXTRA "\"${OWNSHELL_VERSION_EXTRA_RAW}\"")

set(OWNSHELL_VERSION_FULL ${OWNSHELL_VERSION_MAJOR}.${OWNSHELL_VERSION_MINOR}.${OWNSHELL_VERSION_PATCH}${OWNSHELL_VERSION_EXTRA_RAW})
set(OWNSHELL_COPYRIGHT "\"Copyright 2015 Peio Roth\"")

configure_file (
  "${PROJECT_SOURCE_DIR}/src/shell_info_defines.h.in"
  "${PROJECT_SOURCE_DIR}/src/shell_info_defines.h_generated"
  )

add_library(ownshell ${SOURCES})

add_custom_command(TARGET ownshell
                   POST_BUILD
                   COMMENT "ownShell library version: ${OWNSHELL_VERSION_FULL}")
