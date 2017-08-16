//
// Created by Konstantin Lopatko on 27.06.17.
//

#ifndef M_SEQUENCE_CONSTANTS_H
#define M_SEQUENCE_CONSTANTS_H

#include <cmath>

// number of sent bits
const int NumBits = 100000;

// length of linear-feedback shift register
const int LengthRegister = 10;

// feedback taps
// for more information see equation (1) in readme.md
const bool Taps[LengthRegister] =
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1};

#endif //M_SEQUENCE_CONSTANTS_H
