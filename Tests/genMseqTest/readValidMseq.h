//
// Created by Konstantin Lopatko on 23.08.17.
//

#ifndef M_SEQUENCE_READJSON_H
#define M_SEQUENCE_READJSON_H

#include <vector>

// using external library
#include "../../rapidjson/include/rapidjson/document.h"
#include "../../rapidjson/include/rapidjson/filereadstream.h"

class readValidMseq {

    std::vector<bool> MapToBoolVector(const rapidjson::Value& obj);

    // Returns reference to i-th M-sequence. For example getPartOfDoc(3) returns
    // doc["No. 3"]
    const rapidjson::Value& getPartOfDoc(unsigned int i);

    rapidjson::Document doc;

public:
    readValidMseq(const char *path);

    // n - No. M-sequence in JSON file
    std::vector<bool> iniState(unsigned int i);
    std::vector<int> readTaps(unsigned int i);
    std::vector<bool> readMseq(unsigned int i);

    // get number parts (get number of M-sequences)
    unsigned int getNumParts() const;
};


#endif //M_SEQUENCE_READJSON_H
