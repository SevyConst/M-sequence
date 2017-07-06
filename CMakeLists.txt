cmake_minimum_required(VERSION 3.7)
project(M_sequence)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp  Transmitter.cpp Transmitter.h Constants.h)
add_executable(M_sequence ${SOURCE_FILES})