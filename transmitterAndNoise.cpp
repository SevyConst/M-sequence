//
// Created by Konstantin Lopatko on 16.08.17.
//

#include "transmitterAndNoise.h"

#include <random>
#include <set>

namespace tn {
    // randomly generate some first bits (initial state) for M-sequence
    std::vector<bool> randInitState(unsigned int length) {
        // returned variable
        std::vector<bool> initState(length);

        srand(time(NULL));

        // At least one "true" required in initial state
        bool HasTrue = false;
        while (!HasTrue) {
            for (int i = 0; i < length; i++) {
                // generating bit
                initState[i] = rand() % 2;

                if (initState[i])
                    HasTrue = true;
            }
        }

        return initState;
    }


    // compute M-sequence
    std::vector<bool> genMseq(std::vector<bool> initState,
                              unsigned int numSamples,
                              std::vector<unsigned int> taps) {
        // check number of bits in initial seed of LFSR
        if (initState.empty() || initState.size() == 1)
            throw std::invalid_argument
                    ("Size of initial state must be more than 1 bit");

        unsigned int lengthLFSR = initState.size();

        std::vector<bool> mSeq;  // returned variable
        mSeq = initState;  // assign first bits
        mSeq.resize(numSamples);

        bool temp;

        // The algorithm is described at README.md
        for (int i = lengthLFSR; i < numSamples; i++) {
            temp = mSeq.at(i - lengthLFSR);
            for (unsigned j : taps)
                temp = temp ^ mSeq.at(i - lengthLFSR + j);

            mSeq[i] = temp;
        }

        return mSeq;
    }


    std::vector<bool> genMseq(unsigned int lengthLFSR,
                              unsigned int numSamples,
                              std::vector<unsigned int> taps) {

        // initial state for M-sequence
        // (generate seed for sent M-sequence)
        std::vector<bool> iniState = tn::randInitState(lengthLFSR);

        // generate emitted M-sequence
        std::vector<bool> mSeq = tn::genMseq(iniState, numSamples, taps);
    }


    // check, if taps is appropriate for lengthLFSR
    void checkTaps(std::vector<unsigned int> taps,
                   unsigned int lengthLFSR) {
        if (taps.size() == 0)
            throw std::invalid_argument("LFSR must have more than 1 taps");
        if (taps.size() > lengthLFSR - 2)
            throw std::invalid_argument("too much taps");

        // Check that entries don't repeat
        std::set<unsigned int> s(taps.begin(), taps.end());
        if (s.size() != taps.size())
            throw std::invalid_argument
                    ("entries in vector taps must be different!");

        if (!std::is_sorted(taps.begin(), taps.end()))
            throw std::invalid_argument
                    ("entries in vector taps must be sorted!");
        if (taps.back() >= lengthLFSR)
            throw std::invalid_argument
                    ("The LFSR isn't so long!");
    }


    // Emit signal without carrier and without noise.
    std::vector<double> transmit(std::vector<bool> mSeq) {
        std::vector<double> signal(mSeq.size());  // returned value

        // generate signal without noise
        // 1 as true and -1 as false (like BPSK constellation)
        for (int i = 0; i < mSeq.size(); i++)
            signal[i] = mSeq[i] ? 1 : -1;

        return signal;
    }
}
