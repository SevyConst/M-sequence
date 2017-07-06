//
// Created by Konstantin Lopatko on 05.07.17.
//

#ifndef M_SEQUENCE_TRANSMITTER_H
#define M_SEQUENCE_TRANSMITTER_H

#include "Constants.h"

#include <vector>

// Generate signal (Binary Phase Shift Keying - BPSK) without carrier
class Transmitter {

    // Generate first M mSequence of M-sequence
    void firstBits();
public:
    // Generate signal without carrier wave
    // nondefault argument for tests only
    Transmitter(const bool COEF[]);

    // sent bits (M-sequence)
    std::vector<bool> mSequence;

    // Sent signal which contains M-sequence.
    // Without noise.
    std::vector<double> signal;
};

#endif //M_SEQUENCE_TRANSMITTER_H
