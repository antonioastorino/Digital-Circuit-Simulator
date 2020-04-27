#include "DCSAddressDecoder4Bits.hpp"
#include "DCSAnd4.hpp"
#include "DCSLog.hpp"

DCSAddressDecoder4Bits::DCSAddressDecoder4Bits(std::string name)
    : DCSComponent(name, false),
      nodeArray(name + "-In", 4),
      notArray(name + "-Not", 4),
      delArray(name + "-Del", 4),
      and4Array(name + "-And4", 16) {
    for (uint16_t i = 0; i < 4; i++) {
        nodeArray.connect(&delArray, i, i);
        nodeArray.connect(&notArray, i, i);
        for (uint16_t IN = 0; IN < 16; IN++) {
            if ((IN >> i) & 1) {
                delArray.connect(and4Array[IN], i, i);
            } else {
                notArray.connect(and4Array[IN], i, i);
            }
        }
    }

    timeDelay    = 2;
    numOfInPins  = 4;
    numOfOutPins = 16;
}

DCSComponent* DCSAddressDecoder4Bits::getOutComponent(uint16_t outPinNum) {
    if (outPinNum < 16) {
        return and4Array.getOutComponent(outPinNum);
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSAddressDecoder4Bits::getInComponent(uint16_t& inPinNum) {
    if (inPinNum < 4) {
        return nodeArray.getInComponent(inPinNum);
    }
    DCSLog::error(name, 11);
    return nullptr;
}

void DCSAddressDecoder4Bits::updateOut() { DCSLog::error(name, 0); }
