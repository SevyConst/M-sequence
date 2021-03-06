//
// Created by Konstantin Lopatko on 23.08.17.
//

#include "readValidMseq.h"

#include <string>

readValidMseq::readValidMseq(const char *path) {
    FILE* fp = fopen(path, "r");
    const int sizeBuffer = 65536;
    char readBuffer[sizeBuffer];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    doc.ParseStream(is);
}


// argument: No. of M-seq.
std::vector<bool> readValidMseq::readIniState(unsigned int i) const {
    const rapidjson::Value& partDoc = getPartOfDoc(i);
    assert(partDoc.HasMember("initial state"));
    return MapToBoolVector(partDoc["initial state"]);
}


std::vector<unsigned int> readValidMseq::readTaps(unsigned int i) const {
    const rapidjson::Value& partDoc = getPartOfDoc(i);
    assert(partDoc.HasMember("taps"));
    const rapidjson::Value& refTaps = partDoc["taps"];
    std::vector<unsigned int> taps;
    for (rapidjson::Value::ConstValueIterator itr = refTaps.Begin();
         itr != refTaps.End(); ++itr){
        taps.push_back(itr->GetInt());
    }
    return taps;
}


std::vector<bool> readValidMseq::readMseq(unsigned int i) const {
    const rapidjson::Value& partDoc = getPartOfDoc(i);
    assert(partDoc.HasMember("samples of M-sequence"));
    return MapToBoolVector(partDoc["samples of M-sequence"]);
}


unsigned int readValidMseq::getNumParts() const {
    return doc.MemberCount();
}


// i --> doc["No. i"]
const rapidjson::Value& readValidMseq::getPartOfDoc(unsigned int i) const {
    std::string str = "No. " + std::to_string(i);
    const char * cstr = str.c_str();
    assert(doc.HasMember(cstr));
    return doc[cstr];
}


std::vector<bool> readValidMseq::MapToBoolVector(const rapidjson::Value& obj) const {
    std::vector<bool> boolVec;
    for(int i = 0; i < obj.MemberCount(); i++) {

        // convert integer i to C-style string
        const char *index = std::to_string(i).c_str();

        // value in file is integer, not bool
        // because for me it is more convenient.
        assert(obj[index].IsInt());

        boolVec.push_back(obj[index].GetInt());
    }

    return boolVec;
}






