cmake_minimum_required(VERSION 3.7)
project(M_sequence)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp mainFunctions.cpp inputJson.cpp)
add_executable(M_sequence ${SOURCE_FILES})

set(GEN_M_SEQ_TEST_FILES Tests/genMseqTest/genMseqTest.cpp Tests/genMseqTest/readValidMseq.cpp mainFunctions.cpp)
add_executable (gen_Mseq_test ${GEN_M_SEQ_TEST_FILES})
enable_testing ()
add_test (gen_Mseq_test())


set(CHANNEL_TEST_FILES Tests/ChannelIntegrTest.cpp mainFunctions.cpp inputJson.cpp)
add_executable (Channel_test ${CHANNEL_TEST_FILES})
enable_testing ()
add_test (Channel_test())