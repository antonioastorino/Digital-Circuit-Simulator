#include "DCSAnd8.hpp"
#include "DCSLog.hpp"

DCSAnd8::DCSAnd8(std::string name)
    : DCSComponent(name, false), m_and4Array(name + "-m_and8Array", 2), m_and0(name + "-m_and0") {
    m_and4Array.connect(&m_and0);

    timeDelay    = 2; 
    numOfInPins  = 8;
    numOfOutPins = 1;
}

DCSComponent* DCSAnd8::getOutComponent(uint16_t outPinNum) {
    if (outPinNum == 0)
        return &m_and0;
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSAnd8::getInComponent(uint16_t& inPinNum) {
    if (inPinNum < 8)
        return m_and4Array.getInComponent(inPinNum);
    DCSLog::error(this->name, 11);
    return nullptr;
}

void DCSAnd8::updateOut() { DCSLog::error(this->name, 0); }
