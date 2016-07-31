#
#

cmake_minimum_required(VERSION 2.6)

project(cmake-test)

set(CMAKE_USE_RELATIVE_PATHS true)
set(CMAKE_VERBOSE_MAKEFILE true)
add_executable(cmake-test "test.cpp")
