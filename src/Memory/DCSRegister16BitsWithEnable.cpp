#include "DCSRegister16BitsWithEnable.hpp"
#include "DCSLog.hpp"
#include "DCSRegister1BitWithEnable.hpp"

DCSRegister16BitsWithEnable::DCSRegister16BitsWithEnable(std::string name)
    : DCSComponent(name, false),
      registerArray(name + "-reg1Arr_", 16),
      nodeArray({name + "-Clock", name + "-Clear", name + "-Preset", name + "-Load", name + "-OE"},
                5) {
    // connect control signals
    for (uint16_t i = 0; i < 16; i++) {
        nodeArray.connect(registerArray[i], 0, 1);
        nodeArray.connect(registerArray[i], 1, 2);
        nodeArray.connect(registerArray[i], 2, 3);
        nodeArray.connect(registerArray[i], 3, 4);
        nodeArray.connect(registerArray[i], 4, 5);
    }

    timeDelay    = registerArray[0]->getTimeDelay();
    numOfInPins  = 21;
    numOfOutPins = 16;
}

DCSComponent* DCSRegister16BitsWithEnable::getOutComponent(uint16_t outPinNum) {
    if (outPinNum < 16) {
        return registerArray.getOutComponent(outPinNum);
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSRegister16BitsWithEnable::getInComponent(uint16_t& inPinNum) {
    if (inPinNum < 16) { // Data 0 to 15
        uint16_t elementNumber = inPinNum;
        inPinNum = 0;
        return registerArray[elementNumber]->getInComponent(inPinNum);
    } else if (inPinNum < 21) { // control signals
        inPinNum -= 16;
        return nodeArray.getInComponent(inPinNum);
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}

void DCSRegister16BitsWithEnable::updateOut() { DCSLog::error(this->name, 0); }
