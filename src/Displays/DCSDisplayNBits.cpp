#include "DCSDisplayNBits.hpp"
#include "DCSEngine.hpp"
#include "DCSCommon.hpp"

DCSDisplayNBits::DCSDisplayNBits(std::string name, uint16_t numOfBits)
    : DCSComponent(name, false), numOfBits(numOfBits), numOfDecimalDigits(1) {
    
    if (numOfBits > 32) // 32 bits should not be exceeded not to cause visualization issues
        DCSLog::error(this->name, 16);
    
    DCSEngine::addDisplay(this);
    initialized     = true; // Ensures no signal propagation from the output
    uint64_t maxNum = (uint64_t(1) << numOfBits) - 1;

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
    message << "0b";
    for (uint16_t i = 0; i < numOfBits; i++) {
        message << ((in >> (numOfBits - 1 - i)) & 1);
    }
    message << " ";
    uint64_t n = 10;
    for (uint16_t i = 1; i < numOfDecimalDigits; i++) {
        if (in < n)
            message << ' ';
        n *= 10;
    }
    message << ' ' << in << "d";
    DCSLog::output(name, message.str());
}

#if TEST == 1
#include "DCSComponentArray.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"

void displayTest()
{
    DCSLog::printTestName("Display");
    uint16_t hp = 1;
    DCSEngine::initialize(hp);

    DCSComponentArray<DCSInput> inArray("In", 8);

    DCSDisplayNBits disp0("Display", 8);

    for (int i = 0; i < 8; i++)
    {
        inArray[i]->makeSquareWave(i + 1, 0);
    }
    inArray.connect(&disp0);

    DCSEngine::run(16, false);
}
#endif