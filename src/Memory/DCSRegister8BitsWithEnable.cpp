#include "DCSRegister8BitsWithEnable.hpp"
#include "DCSLog.hpp"
#include "DCSRegister1BitWithEnable.hpp"

DCSRegister8BitsWithEnable::DCSRegister8BitsWithEnable(std::string name)
    : DCSComponent(name, false),
      registerArray(name + "-reg1Arr_", 8),
      nodeArray({name + "-Clock", name + "-Clear", name + "-Preset", name + "-Load", name + "-OE"},
                5) {
    // connect control signals
    for (uint16_t i = 0; i < 8; i++) {
        nodeArray.connect(registerArray[i], 0, 1);
        nodeArray.connect(registerArray[i], 1, 2);
        nodeArray.connect(registerArray[i], 2, 3);
        nodeArray.connect(registerArray[i], 3, 4);
        nodeArray.connect(registerArray[i], 4, 5);
    }

    timeDelay    = registerArray[0]->getTimeDelay();
    numOfInPins  = 13;
    numOfOutPins = 8;
}

DCSComponent* DCSRegister8BitsWithEnable::getOutComponent(uint16_t outPinNum) {
    if (outPinNum < 8) {
        return registerArray.getOutComponent(outPinNum);
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSRegister8BitsWithEnable::getInComponent(uint16_t& inPinNum) {
    if (inPinNum < 8) { // Data 0 to 7
        uint16_t elementNumber = inPinNum;
        inPinNum = 0;
        return registerArray[elementNumber]->getInComponent(inPinNum);
    } else if (inPinNum < 13) { // control signals
        inPinNum -= 8;
        return nodeArray.getInComponent(inPinNum);
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}

void DCSRegister8BitsWithEnable::updateOut() { DCSLog::error(this->name, 0); }
