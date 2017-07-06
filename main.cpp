#include <iostream>

#include "Transmitter.h"

int main() {
    // Generating M-sequence. Generating signal, which contains M-sequence
    Transmitter transm(Taps);

    std::cout << "Done!" << std::endl;
    return 0;
}