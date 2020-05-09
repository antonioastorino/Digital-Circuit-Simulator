#include "DCSTriStateBuffer8Bits.hpp"
#include "DCSLog.hpp"

DCSTriStateBuffer8Bits::DCSTriStateBuffer8Bits(std::string name)
    : DCSComponent(name, false), bufferArray(name, 8), node0(name + "-Enable") {
    // Connect global enable to that of all buffers
    for (uint16_t i = 0; i < 8; i++) {
        node0.connect(bufferArray[i], 0, 1);
    }
    this->timeDelay    = 1;
    this->numOfInPins  = 9;
    this->numOfOutPins = 8;
}

DCSComponent* DCSTriStateBuffer8Bits::getInComponent(uint16_t& inPinNum) {
    if (inPinNum < 8) {
        uint16_t elementNumber = inPinNum;
        inPinNum               = 0;
        // TODO: check if the buffer element can be directly returned
        return bufferArray[elementNumber]->getInComponent(inPinNum);
    } else if (inPinNum == 8) {
        inPinNum = 0;
        return &node0;
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}

DCSComponent* DCSTriStateBuffer8Bits::getOutComponent(uint16_t outPinNum) {
    if (outPinNum >= 8)
        DCSLog::error(name, 10);
    uint16_t elementNumber = outPinNum;
    outPinNum              = 0;
    return bufferArray[elementNumber]->getOutComponent(outPinNum);
}

void DCSTriStateBuffer8Bits::enable() {
    for (uint16_t i = 0; i < 8; i++) {
        bufferArray[i]->enable();
    }
}

void DCSTriStateBuffer8Bits::disable() {
    for (uint16_t i = 0; i < 8; i++) {
        bufferArray[i]->disable();
    }
}

void DCSTriStateBuffer8Bits::updateOut() { DCSLog::error(name, 0); }
