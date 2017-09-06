//
// Created by Konstantin Lopatko on 16.08.17.
//

#ifndef M_SEQUENCE_TRANSMITTERANDNOISE_H
#define M_SEQUENCE_TRANSMITTERANDNOISE_H

#include <vector>

namespace tn
{
    // randomly generate initial state
    std::vector<bool> randInitState(unsigned int length);

    // generate M-sequence
    //
    // iniState - initial state.
    // numSamples - number of samples that will be return (length of
    // returned vector
    std::vector<bool> genMseq(std::vector<bool> iniState,
                              unsigned int numSamples,
                              std::vector<unsigned int> taps);

    // generate M-sequence
    // The same function but initial state is random
    std::vector<bool> genMseq(unsigned int lengthLFSR,
                              unsigned int numSamples,
                              std::vector<unsigned int> taps);

    // function throws exceptions if vector taps isn't suitable for this
    // length of LFSR. It is quite simple and don't ensure that these taps
    // allow to generate M-sequence.
    void checkTaps(std::vector<unsigned int> taps,
                   unsigned int lengthLFSR);

    // generate signal without carrier
    std::vector<double> transmit(std::vector<bool> mSeq);


}

#endif //M_SEQUENCE_TRANSMITTERANDNOISE_H
