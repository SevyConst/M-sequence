cmake_minimum_required(VERSION 3.7)
project(M_sequence)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp  transmitterAndNoise.cpp inputJson.cpp)
add_executable(M_sequence ${SOURCE_FILES})

set(GEN_M_SEQ_TEST_FILES Tests/genMseqTest/genMseqTest.cpp Tests/genMseqTest/readValidMseq.cpp transmitterAndNoise.cpp)
add_executable (mytest ${GEN_M_SEQ_TEST_FILES})
enable_testing ()
add_test (mytest())