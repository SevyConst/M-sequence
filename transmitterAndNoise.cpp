//
// Created by Konstantin Lopatko on 16.08.17.
//

#include "transmitterAndNoise.h"

#include <random>

namespace tn
{
    // randomly generate some first bits (initial state) for M-sequence
    std::vector<bool> randInitState(unsigned int length)
    {
        // returned variable
        std::vector<bool> initState(length);

        srand(time(NULL));

        // At least one "true" required in initial state
        bool HasTrue = false;
        while (!HasTrue)
        {
            for (int i = 0; i < length; i++)
            {
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
                              const bool taps [])
    {
        std::vector<bool> mSeq;  // returned variable
        mSeq = initState;  // assign first bits
        mSeq.resize(numSamples);

        unsigned int lengthRegister = initState.size();

        bool temp;

        // The algorithm is described at readme.md
        for (int i = lengthRegister; i < numSamples; i++) {
            temp = false;

            // the recurrence equation
            for (int j = 0; j < lengthRegister; j++) {
                temp = temp ^ (taps[j] && mSeq[i - lengthRegister + j]);
            }

            mSeq[i] = temp;
        }

        return mSeq;
    }

    // Emit signal without carrier and without noise.
    // 1 as true and -1 as false (like BPSK constellation)
    std::vector<double> genSignal(std::vector<bool> mSeq)
    {
        // returned value
        std::vector<double> signal(mSeq.size());

        for (int i = 0; i < mSeq.size(); i++)
            signal[i] = mSeq[i] ? 1 : -1;

        return signal;
    }
}
