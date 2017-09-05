//
// Created by Konstantin Lopatko on 05.09.17.
//

#ifndef M_SEQUENCE_READPARAM_H
#define M_SEQUENCE_READPARAM_H

#include <vector>

// using external library for reading JSON file
#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/filereadstream.h"

class readInput {
    rapidjson::Document doc;

    unsigned int numBits;  // number of samples in M-sequence
    unsigned int lengthLFSR;
    std::vector<bool> taps;

    // These function read the parameters to the variables above
    void readNumBits();
    void readLengthLFSR();
    void readTaps();
public:
    readInput(const char *path);

    unsigned int getNumBits() const;
    unsigned int getLengthLFSR() const;
    std::vector<bool> getTaps() const;
};


#endif //M_SEQUENCE_READPARAM_H
