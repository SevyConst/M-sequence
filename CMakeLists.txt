cmake_minimum_required(VERSION 3.7)
project(M_sequence)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp  transmitterAndNoise.cpp transmitterAndNoise.h constants.h)
add_executable(M_sequence ${SOURCE_FILES})

set(GEN_M_SEQ_TEST_FILES Tests/genMseqTest/genMseqTest.cpp Tests/genMseqTest/readJson.cpp Tests/genMseqTest/readJson.h transmitterAndNoise.cpp transmitterAndNoise.h)
add_executable (mytest ${GEN_M_SEQ_TEST_FILES})
enable_testing ()
add_test (mytest())