#include "DCSAnd6.hpp"
#include "DCSLog.hpp"

DCSAnd6::DCSAnd6(std::string name)
    : DCSComponent(name, false), and3array(name + "-and3array", 2), and0(name + "-and0") {
    and3array.connect(&and0);

    timeDelay    = 2;
    numOfInPins  = 6;
    numOfOutPins = 1;
}

DCSComponent* DCSAnd6::getOutComponent(uint16_t& outPinNum) {
    if (outPinNum == 0)
        return &and0;
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSAnd6::getInComponent(uint16_t& inPinNum) {
    if (inPinNum < 6)
        return and3array.getInComponent(inPinNum);
    DCSLog::error(this->name, 11);
    return nullptr;
}

void DCSAnd6::updateOut() { DCSLog::error(this->name, 0); }
