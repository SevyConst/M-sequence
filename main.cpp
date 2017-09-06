#include <iostream>
#include <vector>

#include "transmitterAndNoise.h"
#include "inputJson.h"

int main() {

    // Define parameters
    //-------------------------------------------------------------------------

    inputJson param("../param.json");
    param.saveDataFromFile();

    // number of bits that will be sent
    unsigned int numBits = param.getNumBits();
    unsigned int lengthLFSR = param.getLengthLFSR();
    std::vector<unsigned int> taps = param.getTaps();



    // Transmitter
    //-------------------------------------------------------------------------

    // generate M-sequence with random initial seed of LFSR
    std::vector<bool> mSeq = tn::genMseq(lengthLFSR, numBits, taps);

    // generate emitted signal (without carrier)
    std::vector<double> signal = tn::transmit(mSeq);


    //-------------------------------------------------------------------------
    std::cout << "Done!" << std::endl;
    return 0;
}