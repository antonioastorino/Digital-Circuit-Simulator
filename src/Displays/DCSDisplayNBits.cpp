#include "DCSDisplayNBits.hpp"
#include "DCSEngine.hpp"


DCSDisplayNBits::DCSDisplayNBits(std::string name, unsigned short numOfBits)
    : DCSComponent(name, false), numOfBits(numOfBits), numOfDecimalDigits(1) {
    DCSEngine::addDisplay(this);
    initialized     = true; // Ensures no signal propagation from the output
    uint64_t maxNum = (1 << numOfBits) - 1;
 
    while (maxNum > 9) {
        maxNum /= 10;
        numOfDecimalDigits++;
    }

    timeDelay    = 0;
    numOfInPins  = numOfBits;
    numOfOutPins = 0;
}

void DCSDisplayNBits::updateOut() {
    std::stringstream message;
    for (unsigned short i = 0; i < numOfBits; i++) {
        message << ((in >> (numOfBits - 1 - i)) & 1);
    }
    message << "b ";
    uint64_t n = 10;
    for (unsigned short i = 1; i < numOfDecimalDigits; i++) {
        if (in < n)
            message << ' ';
        n *= 10;
    }
    message << in << "d  ";
    DCSLog::output(name, message.str());
}