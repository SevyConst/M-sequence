//
// Created by Konstantin Lopatko on 23.08.17.
//

#ifndef M_SEQUENCE_READVALIDMSEQ_H
#define M_SEQUENCE_READVALIDMSEQ_H

#include <vector>

// using external library
#include "../../rapidjson/include/rapidjson/document.h"
#include "../../rapidjson/include/rapidjson/filereadstream.h"

class readValidMseq {

    // Returns reference to i-th M-sequence. For example getPartOfDoc(3) returns
    // doc["No. 3"]
    const rapidjson::Value& getPartOfDoc(unsigned int i) const;

    // read map from Json file and convert this data to bool
    std::vector<bool> MapToBoolVector(const rapidjson::Value& obj) const;

    rapidjson::Document doc;

public:
    // open file
    readValidMseq(const char *path);

    // n - No. M-sequence in JSON file
    std::vector<bool> readIniState(unsigned int i) const;
    std::vector<unsigned int> readTaps(unsigned int i) const;
    std::vector<bool> readMseq(unsigned int i) const;

    // get number parts (get number of M-sequences)
    unsigned int getNumParts() const;
};


#endif //M_SEQUENCE_READVALIDMSEQ_H
