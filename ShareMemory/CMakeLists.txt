cmake_minimum_required(VERSION 3.24)
project(ShareMemory)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ShareMemory
        BaseShm.cpp
        BaseShm.h SecKeyShm.cpp)
