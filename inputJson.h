//
// Created by Konstantin Lopatko on 05.09.17.
//

#ifndef M_SEQUENCE_READPARAM_H
#define M_SEQUENCE_READPARAM_H

#include <vector>

// using external library for reading JSON file
#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/filereadstream.h"

class inputJson {
    rapidjson::Document doc;

    unsigned int numBits;  // number of samples in M-sequence
    unsigned int lengthLFSR;
    std::vector<unsigned int> taps;

    // These functions save the parameters from file to the variables above
    void readNumBits();
    void readLengthLFSR();
    void readTaps();
public:
    // open file with parameters
    inputJson(const char *path);

    void saveDataFromFile();

    unsigned int getNumBits() const;
    unsigned int getLengthLFSR() const;
    std::vector<unsigned int> getTaps() const;
};


#endif //M_SEQUENCE_READPARAM_H
