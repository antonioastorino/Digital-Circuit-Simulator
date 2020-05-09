#include "DCSRegister1BitWithEnable.hpp"
#include "DCSLog.hpp"

DCSRegister1BitWithEnable::DCSRegister1BitWithEnable(std::string name)
    : DCSComponent(name, false), reg0(name + "-Reg0"), tris0(name + "-OutTris") {
    reg0.connect(&tris0, 0, 0); // tri-state buffer

    timeDelay    = 7;
    numOfInPins  = 6;
    numOfOutPins = 1;
}

DCSComponent* DCSRegister1BitWithEnable::getOutComponent(uint16_t outPinNum) {
    if (outPinNum == 0)
        return &tris0;
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSRegister1BitWithEnable::getInComponent(uint16_t& inPinNum) {
    if (inPinNum < 5) { // same connections as for the register without enable
        return reg0.getInComponent(inPinNum);
    } else if (inPinNum == 5) {
        inPinNum = 1;
        return &tris0;
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}
void DCSRegister1BitWithEnable::updateOut() { DCSLog::error(name, 0); }
