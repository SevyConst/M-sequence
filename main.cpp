#include <iostream>
#include <vector>

#include "mainFunctions.h"
#include "inputJson.h"

int main() {

    // Define parameters
    //-------------------------------------------------------------------------

    // open JSON file with parameters
    inputJson param("../param.json");

    // read parameters and save to variables in object param
    param.readFile();



    // Transmitter
    //-------------------------------------------------------------------------

    // generate M-sequence with random initial seed of LFSR
    std::vector<bool> mSeq = genMseq(param.lengthLFSR,
                                     param.numBits,
                                     param.taps);

    // Received signal (without carrier) with noise.
    // Second argument snr - Signal/Noise Ratio in dB. Actually it is
    // E_b/N_0 - the energy per bit to d ratio.
    // Suppose power of signal = 1 by default
    std::vector<double> signal = transmit(mSeq, param.snrdB);



    // Simplest receiver
    //-------------------------------------------------------------------------
    std::vector<bool> recievedBits = simplestReciever(signal);



    //-------------------------------------------------------------------------
    std::cout << "Done!" << std::endl;
    return 0;
}