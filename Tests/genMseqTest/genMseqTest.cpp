//
// Test for generating M-sequences. Read from JSON file parameters
// (taps, initial state, etc.) and corresponding M-sequences generated
// in SciPy using built-in function (genMseqTest.py file in this directory).
// Compare it with results by genMseq()
//

#include <iostream>
#include <vector>

#include "readValidMseq.h"
#include "../../mainFunctions.h"


// compare sequences
bool equalSequences(const std::vector<bool> seq1, const std::vector<bool> seq2);

int main(){
    readValidMseq check("../Tests/genMseqTest/M-sequences.json");

    // i - No. of M-sequence in file
    for (int i = 0; i < check.getNumParts(); i++) {

        // read from file directly
        std::vector<bool> iniState = check.readIniState(i);
        unsigned int lengthRegister = iniState.size();
        std::vector<unsigned int> taps = check.readTaps(i);
        std::vector<bool> validMseq = check.readMseq(i);

        // number of samples of M-sequences
        unsigned int numSamples = validMseq.size();

        std::vector<bool> Mseq = mainFunctions::genMseq(iniState, numSamples, taps);
        if (!equalSequences(Mseq, validMseq)) {
            std::cout << "M-sequence No. " << i << ". Don't equal!";
            return -1;

        }
    }
    std::cout << "Test passed!" << std::endl;
}


bool equalSequences(const std::vector<bool> seq1, const std::vector<bool> seq2){
    for (unsigned int i = 0; i < seq1.size(); i++){
        if (seq1.at(i) != seq2.at(i))
            return false;
    }
    return true;
}


