//
// generating M-sequence and other functions
// These function are stateless. So the namespace is used, not class
//
//

#ifndef M_SEQUENCE_MAINFUNCTIONS_H
#define M_SEQUENCE_MAINFUNCTIONS_H

#include <vector>

namespace mainFunctions {
    // randomly generate initial state
    std::vector<bool> randInitState(unsigned int length);

    // generate M-sequence
    //
    // iniState - initial state.
    // numSamples - number of bits that will be generated (length of
    // returned vector
    std::vector<bool> genMseq(std::vector<bool> iniState,
                              unsigned int numSamples,
                              std::vector<unsigned int> taps);

    // generate M-sequence
    // The same function as above but initial state is random
    std::vector<bool> genMseq(unsigned int lengthLFSR,
                              unsigned int numSamples,
                              std::vector<unsigned int> taps);

    // function throws exceptions if vector taps isn't suitable for this
    // length of LFSR. It is quite simple and don't ensure that these taps
    // allow to generate M-sequence.
    void checkTaps(std::vector<unsigned int> taps,
                   unsigned int lengthLFSR);

    // produce received signal
    std::vector<double> transmit(std::vector<bool> mSeq,
                                 double snrdB,
                                 unsigned int signalPower = 1);

    // compute standard deviation of noise
    double computeSigmaNoise(double snrdB, double signalPower = 1);

    // convert from decibels (power quantity ratio)
    double convertFromdB(double dB);

    // Achieve bits from signal
    // Simplest receiver - not optimized for M-sequence
    std::vector<bool> simplestReciever(std::vector<double> signal);
}


#endif //M_SEQUENCE_MAINFUNCTIONS_H
