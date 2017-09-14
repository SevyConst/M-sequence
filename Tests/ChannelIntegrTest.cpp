//
// Integration test: send signal with bits, receive and compare achieved error
// probability with theoretic probability (BPSK)
//
//

#include <iostream>
#include <array>
#include <cmath>

#include "../mainFunctions.h"


// return number of bit errors;
unsigned int compareSeq(std::vector<bool> sentBits,
                         std::vector<bool> receivedBits);

void showErrorProbability(double achieved, double theoretic);


int main() {

    // number of Tests (number of repeats)
    const unsigned int NumTests = 3;

    const unsigned int LengthLFSR = 16;
    std::vector<unsigned int> taps = {15, 13, 4};

    // number of sent bits in one test
    const unsigned int NumBits = 10000000;

    // Tests are differ by SNR
    std::array<double, NumTests> SNRdB = {-2, 0, 2};



    for (unsigned int i = 0; i < NumTests; i++) {

        unsigned long numErrors = 0;

        // M-sequence
        std::vector<bool> mSeq = genMseq(LengthLFSR,
                                         NumBits,
                                         taps);

        // Transmitter and noise
        std::vector<double> signal = transmit(mSeq, SNRdB.at(i));

        // Receiver
        std::vector<bool> receivedBits = simplestReciever(signal);

        numErrors += compareSeq(mSeq, receivedBits);

        // compute achieved error probability
        double ErrorProbab = double (numErrors) / NumBits;

        // theoretic error probability
        double snr = pow(10, SNRdB.at(i)/10);  // convert from dB
        double theoretic = 0.5 * erfc(sqrt(snr));



        std::cout << "Test No. " << i << std::endl;
        std::cout << "E_b/N_0 = " << SNRdB.at(i) << "dB" << std::endl;
        showErrorProbability(ErrorProbab, theoretic);
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


void showErrorProbability(double achieved, double theoretic) {
    std::cout << "Achieved error probability: " << achieved << std::endl;
    std::cout << "Theoretic error probability: " << theoretic << std::endl;
    std::cout << std::endl;
}



