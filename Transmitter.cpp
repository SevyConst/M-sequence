//
// Created by Konstantin Lopatko on 05.07.17.
//

#include "Transmitter.h"

#include "Constants.h"

#include <random>

// Generate signal for BPSK
// for information about COEF see README.txt
Transmitter::Transmitter(const bool COEF[]) {
    mSequence.resize(NumBits);    // allocating memory for M-sequence
    signal.resize(NumBits);  // Allocating memory for signal


    // Generating M-sequence
    //----------------------------------------------------------------

    // Generating initial mSequence
    firstBits();

    // This temporary variable store i-th bit (in other words it is mSequence[i])
    // of M-sequence. It needs for simplification of "appearance" of code
    // in the next loop
    bool temp;

    // Generating M-sequence recurrence equation.
    // It is described at Description.pdf
    for (int i = M; i < NumBits; i++)
    {
        temp = false;

        // For more information see equation (1) in README.txt
        for (int j = 0; j < M; j++)
        {
            temp = temp ^ (COEF[j] && mSequence[i - M + j]);
        }

        mSequence[i] = temp;
    }


    // Generating signal.
    //----------------------------------------------------------
    // 1 as true and -1 as false (like BPSK constellation)
    for (int i = 0; i < NumBits; i++)
        signal[i] = mSequence[i] ? 1 : -1;
}

// Random generate initial mSequence for M-sequence
// In other words random initial mSequence for Linear SHI
void Transmitter::firstBits() {
    srand(time(NULL));

    // At least one "true" required in initial mSequence
    bool HasTrue = false;
    while (!HasTrue)
    {
        for (int i = 0; i < M; i++)
        {
            // generating bit
            mSequence[i] = rand() % 2;

            if (mSequence[i])
                HasTrue = true;
        }
    }
}
