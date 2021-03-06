//
// Brief Description of these functions is given in mainFunctions.h
//

#include "mainFunctions.h"

#include <random>
#include <set>

namespace mainFunctions {
    // randomly generate some first bits (initial state) for M-sequence
    std::vector<bool> randInitState(unsigned int length) {
        std::vector<bool> initState(length);  // returned variable

        srand(time(NULL));

        // At least one "true" is required in initial state
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

        // check number of bits in initial state of LFSR
        if (initState.empty() || initState.size() == 1)
            throw std::invalid_argument
                    ("Size of initial state must be more than 1 bit");

        // get length of seed
        unsigned int lengthLFSR = initState.size();

        // check that taps is suitable for generating M-sequence
        checkTaps(taps, lengthLFSR);

        std::vector<bool> mSeq;  // returned variable
        mSeq = initState;  // assign first bits
        mSeq.resize(numSamples);  // resize vector with return value

        bool temp;

        // Generate M-sequence
        for (int i = lengthLFSR; i < numSamples; i++) {

            // 0-th bit is tap
            temp = mSeq.at(i - lengthLFSR);

            // sum (XOR) only taps
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
        std::vector<bool> iniState = randInitState(lengthLFSR);

        // generate emitted M-sequence
        return genMseq(iniState, numSamples, taps);

    }


    // check, if taps is appropriate for lengthLFSR
    void checkTaps(std::vector<unsigned int> taps,
                   unsigned int lengthLFSR) {
        if (taps.size() == 0)
            throw std::invalid_argument(
                    "LFSR must have taps!");
        if (taps.size() > lengthLFSR - 2)
            throw std::invalid_argument("too much taps!");

        // Check that entries don't repeat
        // the shortest way - to create a set
        std::set<unsigned int> setTaps(taps.begin(), taps.end());
        if (setTaps.size() != taps.size())
            throw std::invalid_argument(
                    "entries in vector taps must be different!");

        // Check that entries of vector taps aren't too big
        unsigned int max = *std::max_element(taps.begin(), taps.end());
        if (max >= lengthLFSR)
            throw std::invalid_argument(
                    "Register is smaller!");


        // bit No. 0 is tap by default, so vector taps must not contain it
        std::vector<unsigned int>::iterator itr;
        itr = std::find(taps.begin(), taps.end(), 0);
        if (itr != taps.end())
            throw std::invalid_argument(
                    "The 0-th is always a tap - remove it from the argument!");

    }


    // transmit signal without carrier but with noise.
    std::vector<double> transmit(std::vector<bool> mSeq,
                                 double snrdB,
                                 unsigned int signalPower) {
        std::vector<double> signal(mSeq.size());  // returned value

        // generate signal without noise
        // 1 as true and -1 as false (like BPSK constellation)
        for (int i = 0; i < mSeq.size(); i++)
            signal[i] = mSeq[i] ? 1 : -1;

        double sigmaNoise = computeSigmaNoise(snrdB);

        // Add noise
        std::default_random_engine randGauss(time(NULL));
        std::normal_distribution<double> distr(0, sigmaNoise);
        for (int i = 0; i < mSeq.size(); i++)
            signal[i] = signal[i] + distr(randGauss);

        return signal;
    }


    double computeSigmaNoise(double snrdB, double signalPower) {

        double snr = convertFromdB(snrdB);

        // compute noise. Actualy, noise power spectral density
        double N0 = signalPower / snr;

        return sqrt(N0 / 2);
    }

    // convert from dB
    double convertFromdB(double dB) {
        return pow(10, dB / 10);
    }


    // get bits from signal - the simplest way
    std::vector<bool> simplestReciever(std::vector<double> signal) {
        std::vector<bool> bits;  // Bits that will be detect from signal
        unsigned int numBits = signal.size();
        bits.resize(numBits);

        // determine if signal is positive
        for (int i = 0; i < numBits; i++)
            bits[i] = signal[i] > 0.0;
        return bits;
    }
}



