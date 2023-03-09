cmake_minimum_required(VERSION 3.24)
project(CryptoTest)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CryptoTest
        Hash.cpp
        Hash.h RsaCrypto.h RsaCrypto.cpp AesCrypto.h AesCrypto.cpp)
