//
// Created by Konstantin Lopatko on 05.09.17.
//

#include "readInput.h"

readInput::readInput(const char *path) {
    FILE* fp = fopen(path, "r");
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    doc.ParseStream(is);

    readNumBits();
    readLengthLFSR();
    readTaps();
}

void readInput::readNumBits() {
    assert(doc.HasMember("Number of sent bits"));
    numBits = doc["Number of sent bits"].GetInt();
}

void readInput::readLengthLFSR() {
    assert(doc.HasMember("length of LFSR"));
    lengthLFSR = doc["length of LFSR"].GetInt();
}

void readInput::readTaps() {
    assert(doc.HasMember("taps"));

    const rapidjson::Value& refTaps = doc["taps"];
    for (rapidjson::Value::ConstValueIterator itr = refTaps.Begin();
         itr != refTaps.End(); ++itr){
        taps.push_back(itr->GetInt());
    }

    assert(lengthLFSR == taps.size());
}

unsigned int readInput::getNumBits() const {
    return numBits;
}

unsigned int readInput::getLengthLFSR() const {
    return lengthLFSR;
}

std::vector<bool> readInput::getTaps() const {
    return taps;
}






