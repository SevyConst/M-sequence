#include <iostream>
#include <vector>

#include "transmitterAndNoise.h"


int main() {

    // number of sent bits
    const int numBits = 100000;

    // length of linear-feedback shift register
        const int lengthRegister = 10;

    // feedback taps
    // for more information see equation (1) in readme.md
        std::vector<bool> taps =
                { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1};

    // initial state for M-sequence in Transmitter
    std::vector<bool> iniState = tn::randInitState(lengthRegister);

    // generate emitted M-sequence
    std::vector<bool> mSeq = tn::genMseq(iniState, numBits, taps);

    // generate emitted signal (without carrier)
    std::vector<double> signal = tn::genSignal(mSeq);

    std::cout << "Done!" << std::endl;
    return 0;
}