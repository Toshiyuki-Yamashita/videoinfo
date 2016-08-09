#
#

cmake_minimum_required(VERSION 2.6)

project(videoinfo)
set(OpenCV_RUNTIME vc11)
find_package(OpenCV)
set(CMAKE_USE_RELATIVE_PATHS true)
set(CMAKE_VERBOSE_MAKEFILE true)
include_directories(OpenCV_INCLUDE_DIRS)
add_executable(videoinfo "main.cpp")
target_link_libraries(videoinfo ${OpenCV_LIBS})

add_executable(videocat "main.cpp")
target_link_libraries(videocat ${OpenCV_LIBS})
