#
#

cmake_minimum_required(VERSION 2.6)

project(videoinfo)
set(OpenCV_RUNTIME vc11)
find_package(OpenCV)

ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
#set(Bzip2_INCLUDE_DIRS "${CMAKE_BINARY_DIR}/../external/bzip2/include")
#FIND_LIBRARY(Bzip2_LIB_RELEASE name "libbz2" HINTS "${CMAKE_BINARY_DIR}/../external/bzip2/lib")
#FIND_LIBRARY(Bzip2_LIB_DEBUG name "libbz2d" HINTS "${CMAKE_BINARY_DIR}/../external/bzip2/lib")
#SET(Bzip2_LIB optimized ${Bzip2_LIB_RELEASE}  debug ${Bzip2_LIB_DEBUG})
SET (bzlibs bzlib.h blocksort.c huffman.c crctable.c randtable.c compress.c decompress.c bzlib.c)
set(CMAKE_USE_RELATIVE_PATHS true)
set(CMAKE_VERBOSE_MAKEFILE true)
#include_directories(${Bzip2_INCLUDE_DIRS})
add_executable(videoinfo main.cpp ${bzlibs})
target_link_libraries(videoinfo ${OpenCV_LIBS} )
