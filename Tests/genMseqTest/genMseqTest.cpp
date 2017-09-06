//
// Created by Konstantin Lopatko on 16.08.17.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include "readValidMseq.h"
#include "../../transmitterAndNoise.h"


bool compareMSeq(const std::vector<bool> m1, const std::vector<bool> m2);

int main(){
    readValidMseq check("../Tests/genMseqTest/M-sequences.json");

    bool testPassed = true;

    // i - No. of M-sequence in file)
    for (int i = 0; i <= 4; i++) {
        std::vector<bool> iniState = check.iniState(i);
        unsigned int lengthRegister = iniState.size();
        std::vector<unsigned int> taps = check.readTaps(i);
        std::vector<bool> validMseq = check.readMseq(i);

        // number of samples of M-sequences
        unsigned int numSamples = validMseq.size();

        std::vector<bool> Mseq = tn::genMseq(iniState, numSamples, taps);
        if (!compareMSeq(Mseq, validMseq)) {
            std::cout << "No. " << i << ". Don't equal!" << std::endl;
            testPassed = false;
        }
    }

    if (testPassed)
        std::cout << "Test passed!" << std::endl;
}

// return true if sequences is equal
bool compareMSeq(const std::vector<bool> m1, const std::vector<bool> m2){
    for (unsigned int i = 0; i < m1.size(); i++){
        if (m1.at(i) != m2.at(i))
            return false;
    }
    return true;
}


