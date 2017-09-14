//
// For now this is example of use functions from mainFunctions.h
// Acquisition of M-sequence in simulated receiver will be added in future.
//

#include <iostream>
#include <vector>

#include "mainFunctions.h"
#include "inputJson.h"

int main() {

    // Define parameters
    //-------------------------------------------------------------------------

    // Open JSON file with parameters
    inputJson param("../param.json");

    // Read parameters and save to variables in object param
    param.readFile();

    // Length of LFSR - linear-feedback shift register which generates M-sequence
    unsigned lengthLFSR = param.getLengthLFSR();

    // Total number of transmitted bits
    unsigned numBits = param.getNumBits();

    // Taps of register. Bit No. 0 is always tap.
    std::vector<unsigned int> taps= param.getTaps();

    // SNR - Signal/Noise Ratio in dB. Actually it is
    // E_b/N_0 - the energy per bit to noise power spectral density ratio.
    double snrdB = param.getSNRdB();


    // Transmitter
    //-------------------------------------------------------------------------

    // generate M-sequence with random initial seed of LFSR
    std::vector<bool> mSeq = genMseq(lengthLFSR,
                                     numBits,
                                     taps);

    // Received signal (without carrier) with noise.
    // Suppose power of signal = 1 by default
    std::vector<double> signal = transmit(mSeq, snrdB);



    // Simplest receiver. It will be replaced with receiver optimized for
    // M-sequence
    //-------------------------------------------------------------------------
    std::vector<bool> receivedBits = simplestReciever(signal);



    //-------------------------------------------------------------------------
    std::cout << "Done!" << std::endl;
    return 0;
}