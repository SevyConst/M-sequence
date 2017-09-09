//
// Created by Konstantin Lopatko on 05.09.17.
//

#ifndef M_SEQUENCE_INPUTJSON_H
#define M_SEQUENCE_INPUTJSON_H

#include <vector>

// using external library for reading JSON file
#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/filereadstream.h"

class inputJson {

    unsigned int readNumBits() const;  // number of bits that will be sent
    unsigned int readLengthLFSR() const;
    std::vector<unsigned int> readTaps() const;
    double readSNRdB() const;  // read signal/noise ratio in decibels

    rapidjson::Document doc;
public:
    // open file with parameters
    inputJson(const char *path);

    // save all data from file to variables
    void readFile();

    unsigned int numBits;
    unsigned int lengthLFSR;
    std::vector<unsigned int> taps;
    double snrdB; // signal/noise dB
};


#endif //M_SEQUENCE_INPUTJSON_H
