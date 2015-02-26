# Copyright (C) 2015 Legrand
# All rights reserved
#
# CCTV Library

# cmake file for shelllin unittests

cmake_minimum_required(VERSION 2.8)
project(shelllib_unittests)

include_directories("${PROJECT_SOURCE_DIR}/libgtest/include")
include_directories("${PROJECT_SOURCE_DIR}/../src")
add_definitions(-Wall -Wextra -std=c++0x)

set(UNITTEST_FILES
    test_shell_env.cc
)

# libraries...
# ... libshell
set(LIBSHELL_ARCHIVE "${PROJECT_SOURCE_DIR}/../libshell.a")
add_library(libshell STATIC IMPORTED)
set_property(TARGET libshell PROPERTY IMPORTED_LOCATION ${LIBSHELL_ARCHIVE})
# ... libgtest
set(LIBGTEST_ARCHIVE "${PROJECT_SOURCE_DIR}/libgtest/libgtest.a")
add_library(libgtest STATIC IMPORTED)
set_property(TARGET libgtest PROPERTY IMPORTED_LOCATION ${LIBGTEST_ARCHIVE})

# gtest framework needs the pthread lib
set(PTHREAD_LINK_FLAG "-pthread")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${PTHREAD_LINK_FLAG}" )
add_executable(shelllib_unittests.bin shelllib_unittests_main.cc ${UNITTEST_FILES})
target_link_libraries(shelllib_unittests.bin libgtest libshell)
