//
// Integration test: send signal with bits, receive and compare achieved bit
// error rate (BER) with theoretic constant (for BPSK)
//
//

#include <iostream>
#include <array>
#include <cmath>

#include "../mainFunctions.h"


namespace f = mainFunctions;


// return number of bit mismatches
unsigned int compareSeq(std::vector<bool> sentBits,
                         std::vector<bool> receivedBits);

// compute theoretic bit of errors
double theorBER(double snrdB);


void showBER(double achieved, double theoretic);


int main() {

    // number of Tests (number of repeats)
    const unsigned int NumTests = 3;

    const unsigned int LengthLFSR = 16;
    std::vector<unsigned int> taps = {15, 13, 4};

    // number of sent bits in one test
    const unsigned int NumBits = 10000000;

    // Tests are differ by SNR
    std::array<double, NumTests> snrdBarray = {-2, 0, 2};



    for (unsigned int i = 0; i < NumTests; i++) {

        unsigned long numErrors = 0;


        // M-sequence
        std::vector<bool> mSeq = f::genMseq(LengthLFSR,
                                         NumBits,
                                         taps);

        // Transmitter and noise
        std::vector<double> signal = f::transmit(mSeq, snrdBarray.at(i));

        // Receiver
        std::vector<bool> receivedBits = f::simplestReciever(signal);

        numErrors += compareSeq(mSeq, receivedBits);

        // compute achieved BER
        double ber = double (numErrors) / NumBits;

        // theoretic BER
        double validBER = theorBER(snrdBarray.at(i));



        std::cout << "Test No. " << i << std::endl;
        std::cout << "E_b/N_0 = " << snrdBarray.at(i) << "dB" << std::endl;
        showBER(validBER, ber);
    }
}


unsigned int compareSeq(std::vector<bool> sentBits,
                         std::vector<bool> receivedBits) {
    if (sentBits.size() != receivedBits.size()) {
        throw std::invalid_argument(
                "number of received bits != number of sent bits");
    }

    unsigned long numErrors = 0;
    for (unsigned int i = 0; i < sentBits.size(); i++) {
        if (sentBits.at(i) != receivedBits.at(i))
            numErrors++;
    }

    return numErrors;
}


void showBER(double achieved, double theoretic) {
    std::cout << "Achieved error probability: " << achieved << std::endl;
    std::cout << "Theoretic error probability: " << theoretic << std::endl;
    std::cout << std::endl;
}


double theorBER(double snrdB) {
    double snr = f::convertFromdB(snrdB);
    return 0.5 * erfc(sqrt(snr));
}



