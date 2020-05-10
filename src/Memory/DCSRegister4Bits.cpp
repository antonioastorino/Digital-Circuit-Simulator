#include "DCSRegister4Bits.hpp"
#include "DCSLog.hpp"
#include "DCSRegister1Bit.hpp"

DCSRegister4Bits::DCSRegister4Bits(std::string name)
    : DCSComponent(name, false),
      registerArray(name + "-reg1Arr0_", 4),
      nodeArray({
          name + "-Clock",
          name + "-Clear",
          name + "-Preset",
          name + "-Load"}, 4) {
    // connect control signals
    for (uint16_t i = 0; i < 4; i++) {
        nodeArray.connect(registerArray[i], 0, 1);
        nodeArray.connect(registerArray[i], 1, 2);
        nodeArray.connect(registerArray[i], 2, 3);
        nodeArray.connect(registerArray[i], 3, 4);
    }

    timeDelay    = registerArray[0]->getTimeDelay();
    numOfInPins  = 8;
    numOfOutPins = 4;
}

DCSComponent* DCSRegister4Bits::getInComponent(uint16_t& inPinNum) {
    if (inPinNum < 4) { // Data 0 to 3
        uint16_t elementNumber = inPinNum;
        inPinNum = 0;
        return registerArray[elementNumber]->getInComponent(inPinNum);
    } else if (inPinNum < 8) { // control signals
        inPinNum -= 4;
        return nodeArray.getInComponent(inPinNum);
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}

DCSComponent* DCSRegister4Bits::getOutComponent(uint16_t outPinNum) {
    if (outPinNum < 4) {
        return registerArray.getOutComponent(outPinNum);
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

void DCSRegister4Bits::updateOut() { DCSLog::error(this->name, 0); }
