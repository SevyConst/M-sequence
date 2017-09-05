#include <iostream>
#include <vector>

#include "transmitterAndNoise.h"
#include "readInput.h"

int main() {
    // Define parameters
    //-------------------------------------------------------------------------
    readInput param("../param.json");
    unsigned int numBits = param.getNumBits();
    unsigned int lengthLFSR = param.getLengthLFSR();
    std::vector<bool> taps = param.getTaps();


    // Transmitter
    //-------------------------------------------------------------------------

    // initial state for M-sequence in Transmitter
    // (generate seed for sent M-sequence)
    std::vector<bool> iniState = tn::randInitState(lengthLFSR);

    // generate emitted M-sequence
    std::vector<bool> mSeq = tn::genMseq(iniState, numBits, taps);

    // generate emitted signal (without carrier)
    std::vector<double> signal = tn::genSignal(mSeq);


    //-------------------------------------------------------------------------
    std::cout << "Done!" << std::endl;
    return 0;
}