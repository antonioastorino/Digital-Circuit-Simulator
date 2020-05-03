#include "DCSRegister8Bits.hpp"
#include "DCSLog.hpp"
#include "DCSRegister1Bit.hpp"

DCSRegister8Bits::DCSRegister8Bits(std::string name)
    : DCSComponent(name, false),
      registerArray(name + "-reg", 8),
      nodeArray({
          name + "-OE",
          name + "-Clock",
          name + "-Clear",
          name + "-Preset",
          name + "-Load"}, 5) {
    // connect control signals
    for (uint16_t i = 0; i < 8; i++) {
        nodeArray.connect(registerArray[i], 0, 0);
        nodeArray.connect(registerArray[i], 1, 1);
        nodeArray.connect(registerArray[i], 2, 2);
        nodeArray.connect(registerArray[i], 3, 3);
        nodeArray.connect(registerArray[i], 4, 4);
    }

    timeDelay    = registerArray[0]->getTimeDelay();
    numOfInPins  = 13;
    numOfOutPins = 8;
}

DCSComponent* DCSRegister8Bits::getOutComponent(uint16_t outPinNum) {
    if (outPinNum < 8) {
        return registerArray.getOutComponent(outPinNum);
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSRegister8Bits::getInComponent(uint16_t& inPinNum) {
    if (inPinNum < 5) {
        return nodeArray.getInComponent(inPinNum);
    } else if (inPinNum < 13) {
        uint16_t elementNumber = inPinNum - 5;
        inPinNum               = 5;
        return registerArray[elementNumber]->getInComponent(inPinNum);
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}

void DCSRegister8Bits::updateOut() { DCSLog::error(this->name, 0); }
