#include "DCSDFlipFlopAsyncSR.hpp"
#include "DCSLog.hpp"

DCSDFlipFlopAsyncSR::DCSDFlipFlopAsyncSR(std::string name) : DCSComponent(name, false) {
    not0.connect(&not1, 0, 0);
    not0.connect(&and0, 0, 0);
    not1.connect(&del0, 0, 0);
    del0.connect(&and0, 0, 1);
    and0.connect(&dLatSR0, 0, 1);

    timeDelay    = 4;
    numOfInPins  = 4;
    numOfOutPins = 2;
}

DCSComponent* DCSDFlipFlopAsyncSR::getOutComponent(uint16_t outPinNum) {
    return dLatSR0.getOutComponent(outPinNum);
}

DCSComponent* DCSDFlipFlopAsyncSR::getInComponent(uint16_t& inPinNum) {
    // Input pin 1 is the clock, connected to the node at pin 0 \
     The other inputs (0, 2, and 3) are mapped by the D-Latch with SR
    if (inPinNum == 0 || inPinNum == 2 || inPinNum == 3)
        return dLatSR0.getInComponent(inPinNum);
    else if (inPinNum == 1) {
        inPinNum = 0;
        return &not0;
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}

void DCSDFlipFlopAsyncSR::updateOut() {
    DCSLog::error(name, 0);
}
