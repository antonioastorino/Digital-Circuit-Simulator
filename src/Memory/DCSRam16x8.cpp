#include "DCSRam16x8.hpp"
#include "DCSLog.hpp"
#include "DCSRegister1Bit.hpp"
#include "DCSRegister8Bits.hpp"

DCSRam16x8::DCSRam16x8(std::string name)
    : DCSComponent(name, false),
      regArray(name + "-Reg8Arr0_", 16),
      andArray0(name + "-ENAndArr0_", 16),
      andArray1(name + "-WRAndArr1_", 16),
      ctrlNodeArray({name + "-Enable", // 0
                     name + "-Clock",  // 1
                     name + "-Clear",  // 2
                     name + "-Preset", // 3
                     name + "-Write"}, // 4
                    5),
      dataNodeArray(name + "-dataNodeArr0_", 8),
      outNodeArray(name + "-outNodeArr0_", 8),
      dec0(name + "-dec0") {
    for (uint16_t regNum = 0; regNum < 16; regNum++) {
        // connect each decoder output pin to and gates at input 0
        // either for anding the Enable signal or the Write signal
        /* Enable */
        dec0.connect(andArray0[regNum], regNum, 0);
        ctrlNodeArray.connect(andArray0[regNum], 0, 1);
        andArray0.connect(regArray[regNum], regNum, 0);
        /* Write */
        dec0.connect(andArray1[regNum], regNum, 0);
        ctrlNodeArray.connect(andArray1[regNum], 4, 1);
        andArray1.connect(regArray[regNum], regNum, 4);
        // connect to register control pins

        ctrlNodeArray.connect(regArray[regNum], 1, 1); // Clock
        ctrlNodeArray.connect(regArray[regNum], 2, 2); // Clear
        ctrlNodeArray.connect(regArray[regNum], 3, 3); // Preset

        for (uint16_t j = 0; j < 8; j++) {
            // connect data in to all register data ins
            dataNodeArray.connect(regArray[regNum], j, 5 + j); // Data
        }
        regArray[regNum]->connect(&outNodeArray);
    }

    timeDelay    = dec0.getTimeDelay() + regArray[0]->getTimeDelay();
    numOfInPins  = 17;
    numOfOutPins = 8;
}

DCSComponent* DCSRam16x8::getOutComponent(uint16_t outPinNum) {
    if (outPinNum < 8) {
        return outNodeArray.getOutComponent(outPinNum);
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSRam16x8::getInComponent(uint16_t& inPinNum) {
    if (inPinNum < 5) {
        return ctrlNodeArray.getInComponent(inPinNum);
    } else if (inPinNum < 13) {
        inPinNum -= 5;
        return dataNodeArray.getInComponent(inPinNum);
    } else if (inPinNum < 17) {
        inPinNum -= 13;
        return dec0.getInComponent(inPinNum);
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}

void DCSRam16x8::updateOut() { DCSLog::error(name, 0); }

void DCSRam16x8::disconnect() {
    // clearing the state of the input components
    for (int i = 0; i < this->numOfInPins; i++) {
        uint16_t inPinNum = i;
        DCSComponent* c   = this->getInComponent(inPinNum);
        c->connectedIn    = 0;
        c->fromTristateIn = 0;
        c->initialized    = false;
        c->reachableIn    = 0;
        for (int j = 0; j < c->getNumOfInPins(); c++) {
            c->updatedByVector[j] = nullptr;
        }
    }
    // removing connections from the output components
    for (int i = 0; i < this->numOfOutPins; i++) {
        DCSComponent* c = this->getOutComponent(i);
        c->wireVector.clear();
    }
}
