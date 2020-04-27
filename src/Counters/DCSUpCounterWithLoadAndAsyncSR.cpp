#include "DCSUpCounterWithLoadAndAsyncSR.hpp"
#include "DCSLog.hpp"

DCSUpCounterWithLoadAndAsyncSR::DCSUpCounterWithLoadAndAsyncSR(std::string name, uint16_t numOfBits)
    : DCSComponent(name, false),
      dividerArray(name + "-divArray", numOfBits),
      nodeArray({name + "-Load", name + "-Clock", name + "-Clear", name + "-Preset"}, 4),
      numOfBits(numOfBits) {
    for (uint16_t i = 0; i < numOfBits; i++) {
        for (uint16_t j = 0; j < 4; j++) {
            /*
             connect nodes to internal inputs of dividers:
             1 = Load
             2 = Clock
             3 = Clear
             4 = Preset
             Node that inputs 0 and 5 of dividers are not shared
             */
            nodeArray[j]->connect(dividerArray[i], 0, j + 1);
        }
    }
    for (uint16_t i = 0; i < numOfBits - 1; i++) {
        // cascade dividers
        dividerArray[i]->connect(dividerArray[i + 1],
                                 2, // Count out
                                 5  // Count in
        );
    }
    // NOTE: The Count in of dividerArray[0] is an array input.
    //       The Count out of dividerArray[numOfElements-1] is an array output.

    timeDelay    = 7 + numOfBits;
    numOfInPins  = 5 + numOfBits;
    numOfOutPins = 1 + numOfBits;
}
DCSComponent* DCSUpCounterWithLoadAndAsyncSR::getOutComponent(uint16_t outPinNum) {
    if (outPinNum >= 0 & outPinNum < numOfBits) {
        uint16_t arrayElement = outPinNum;
        outPinNum             = 0;
        return dividerArray[arrayElement]->getOutComponent(outPinNum);
    } else if (outPinNum == numOfBits) {
        outPinNum = 2;
        return dividerArray[numOfBits - 1]->getOutComponent(outPinNum);
    } else
        DCSLog::error(this->name, 10);
    return nullptr;
}
DCSComponent* DCSUpCounterWithLoadAndAsyncSR::getInComponent(uint16_t& inPinNum) {
    if (inPinNum == 0) {
        inPinNum = 5;
        return dividerArray[0]->getInComponent(inPinNum); // Count in
    } else if (inPinNum < 5) {
        uint16_t arrayElement = inPinNum - 1;
        inPinNum              = 0;
        return nodeArray[arrayElement];
    } else if (inPinNum < 5 + numOfBits) {
        uint16_t arrayElement = inPinNum - 5;
        inPinNum              = 0; // Data
        return dividerArray[arrayElement]->getInComponent(inPinNum);
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}

void DCSUpCounterWithLoadAndAsyncSR::updateOut() { DCSLog::error(name, 0); }
