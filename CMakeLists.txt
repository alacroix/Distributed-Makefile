cmake_minimum_required(VERSION 3.3)
project(distributed_makefile)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Rule.cpp Rule.h)
add_executable(distributed_makefile ${SOURCE_FILES})