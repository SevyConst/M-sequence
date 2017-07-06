//
// Created by Konstantin Lopatko on 27.06.17.
//

#ifndef M_SEQUENCE_CONSTANTS_H
#define M_SEQUENCE_CONSTANTS_H

#include <cmath>

// number of sent bits
const int NumBits = 100000;

// length of linear-feedback shift register
// For emphasizing const qualifier it is named "M", not "m" as in a lot of
// books and papers
const int M = 10;

// feedback taps
// for more information see equation (1) in README.txt
const bool Taps[M] =
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1};

#endif //M_SEQUENCE_CONSTANTS_H
