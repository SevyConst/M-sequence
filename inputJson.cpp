//
// Created by Konstantin Lopatko on 05.09.17.
//

#include "inputJson.h"

#include <iostream>


inputJson::inputJson(const char *path) {
    FILE* fp = fopen(path, "r");
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    doc.ParseStream(is);
}


void inputJson::readNumBits() {

    // use assert() as in rapidjson tutorial
    assert(doc.HasMember("Number of sent bits"));
    numBits = doc["Number of sent bits"].GetInt();
}


void inputJson::readLengthLFSR() {
    assert(doc.HasMember("length of LFSR"));
    lengthLFSR = doc["length of LFSR"].GetInt();
}


void inputJson::readTaps() {
    assert(doc.HasMember("taps"));

    const rapidjson::Value& refTaps = doc["taps"];

    unsigned int temp;
    for (rapidjson::Value::ConstValueIterator itr = refTaps.Begin();
         itr != refTaps.End(); ++itr){
        taps.push_back(itr->GetInt());
    }
}


void inputJson::saveDataFromFile() {
    readNumBits();
    readLengthLFSR();
    readTaps();
}


unsigned int inputJson::getNumBits() const {
    return numBits;
}


unsigned int inputJson::getLengthLFSR() const {
    return lengthLFSR;
}


std::vector<unsigned int> inputJson::getTaps() const {
    return taps;
}








