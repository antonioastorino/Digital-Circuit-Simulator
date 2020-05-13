#include "DCSAddressDecoder8Bits.hpp"
#include "DCSAnd8.hpp"
#include "DCSLog.hpp"

DCSAddressDecoder8Bits::DCSAddressDecoder8Bits(std::string name)
    : DCSComponent(name, false),
      m_nodeArray(name + "-In_", 8),
      m_notArray(name + "-Not_", 8),
      m_delArray(name + "-Del_", 8),
      m_and8Array(name + "-And8_", 256) {
    for (uint16_t i = 0; i < 8; i++) {
        m_nodeArray.connect(&m_delArray, i, i);
        m_nodeArray.connect(&m_notArray, i, i);
        for (uint16_t IN = 0; IN < 256; IN++) {
            if ((IN >> i) & 1) {
                m_delArray.connect(m_and8Array[IN], i, i);
            } else {
                m_notArray.connect(m_and8Array[IN], i, i);
            }
        }
    }

    timeDelay    = 3;
    numOfInPins  = 8;
    numOfOutPins = 256;
}

DCSComponent* DCSAddressDecoder8Bits::getOutComponent(uint16_t outPinNum) {
    if (outPinNum < 256) {
        return m_and8Array.getOutComponent(outPinNum);
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSAddressDecoder8Bits::getInComponent(uint16_t& inPinNum) {
    if (inPinNum < 8) {
        return m_nodeArray.getInComponent(inPinNum);
    }
    DCSLog::error(name, 11);
    return nullptr;
}

void DCSAddressDecoder8Bits::updateOut() { DCSLog::error(name, 0); }
