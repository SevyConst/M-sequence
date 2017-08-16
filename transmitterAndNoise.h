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
                              const bool taps []);

    // generate signal without noise and without carrier
    std::vector<double> genSignal(std::vector<bool> mSeq);

    // add noise to signal
}

#endif //M_SEQUENCE_TRANSMITTERANDNOISE_H
