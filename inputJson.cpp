//
// Read initial parameters from file
//

#include "inputJson.h"


inputJson::inputJson(const char *path) {
    FILE* fp = fopen(path, "r");
    const int sizeBuffer = 65536;
    char readBuffer[sizeBuffer];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    doc.ParseStream(is);
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


double inputJson::getSNRdB() const {
    return snrdB;
}


void inputJson::readFile() {
    numBits = readNumBits();
    lengthLFSR = readLengthLFSR();
    taps = readTaps();
    snrdB = readSNRdB();
}


unsigned int inputJson::readNumBits() const {

    // use assert() as in rapidjson tutorial
    assert(doc.HasMember("Number of sent bits"));
    return doc["Number of sent bits"].GetInt();
}


unsigned int inputJson::readLengthLFSR() const {
    assert(doc.HasMember("length of LFSR"));
    return doc["length of LFSR"].GetInt();
}


std::vector<unsigned int> inputJson::readTaps() const {
    assert(doc.HasMember("taps"));

    const rapidjson::Value &refTaps = doc["taps"];
    std::vector<unsigned int> taps;

    for (rapidjson::Value::ConstValueIterator itr = refTaps.Begin();
         itr != refTaps.End(); ++itr) {
        taps.push_back(itr->GetInt());
    }

    return taps;
}


double inputJson::readSNRdB() const {
    assert(doc.HasMember("signal/noise ratio, dB"));
    return doc["signal/noise ratio, dB"].GetDouble();
}












