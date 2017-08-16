#include <iostream>
#include <vector>

#include "transmitterAndNoise.h"
#include "constants.h"


int main() {
    // initial state for M-sequence in Transmitter
    std::vector<bool> iniState = tn::randInitState(LengthRegister);

    // generate emitted M-sequence
    std::vector<bool> mSeq = tn::genMseq(iniState, NumBits, Taps);

    // generate emitted signal (without carrier)
    std::vector<double> signal = tn::genSignal(mSeq);

    std::cout << "Done!" << std::endl;
    return 0;
}