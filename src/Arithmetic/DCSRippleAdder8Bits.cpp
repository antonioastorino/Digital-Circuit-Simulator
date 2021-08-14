#include "DCSRippleAdder8Bits.hpp"
#include "DCSFullAdder.hpp"
#include "DCSLog.hpp"
#include "DCSCommon.hpp"

DCSRippleAdder8Bits::DCSRippleAdder8Bits(std::string name)
    : DCSComponent(name, false), faArray("FA", 8) {
    for (uint16_t i = 1; i < 8; i++) {
        faArray[i - 1]->connect(faArray[i], 1, 2);
    }
    timeDelay    = 14;
    numOfInPins  = 17;
    numOfOutPins = 9;
}

DCSComponent* DCSRippleAdder8Bits::getInComponent(uint16_t& inPinNum) {
    uint16_t elementNumber;
    if (inPinNum < 8) {
        elementNumber = inPinNum;
        inPinNum      = 0;
        return faArray[elementNumber]->getInComponent(inPinNum);
    } else if (inPinNum < 16) {
        elementNumber = inPinNum - 8;
        inPinNum      = 1;
        return faArray[elementNumber]->getInComponent(inPinNum);
    }
    if (inPinNum == 16) {
        inPinNum = 2;
        return faArray[0]->getInComponent(inPinNum);
    }
    DCSLog::error(name, 11);
    return nullptr;
}

DCSComponent* DCSRippleAdder8Bits::getOutComponent(uint16_t outPinNum) {
    if (outPinNum < 8) {
        uint16_t elementNumber = outPinNum;
        outPinNum              = 0;
        return faArray[elementNumber]->getOutComponent(outPinNum);
    }
    if (outPinNum == 8) {
        outPinNum = 1;
        return faArray[7]->getOutComponent(outPinNum);
    }
    DCSLog::error(name, 10);
    return nullptr;
}

void DCSRippleAdder8Bits::updateOut() { DCSLog::error(this->name, 0); }

#if TEST == 1
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"

void rippleAdderTest()
{
    DCSLog::printTestName("8-bit ripple adder");
    uint16_t hp = 2;
    DCSEngine::initialize(hp);

    DCSComponentArray<DCSInput> inArray("In", 17);
    DCSRippleAdder8Bits ra0("RA");
    DCSDisplayNBits disp0("A", 8);
    DCSDisplayNBits disp1("B", 8);
    DCSDisplayNBits disp2("SUM", 8);
    DCSDisplayNBits disp3("Cout", 1);

    inArray[0]->makeSignal(1);
    inArray[1]->makeSignal(0);
    inArray[2]->makeSignal(0);
    inArray[3]->makeSignal(0);
    inArray[4]->makeSignal(0);
    inArray[5]->makeSignal(0);
    inArray[6]->makeSignal(0);
    inArray[7]->makeSignal(0);

    inArray[8]->makeSignal(1);
    inArray[9]->makeSignal(1);
    inArray[10]->makeSignal(1);
    inArray[11]->makeSignal(1);
    inArray[12]->makeSignal(1);
    inArray[13]->makeSignal(1);
    inArray[14]->makeSignal(1);
    inArray[15]->makeSignal(1);

    inArray[16]->makeSignal(0);
    inArray.connect(&disp0, {0, 7}, {0, 7});
    inArray.connect(&disp1, {8, 15}, {0, 7});
    ra0.connect(&disp2, {0, 7}, {0, 7});
    ra0.connect(&disp3, 8, 0);

    inArray.connect(&ra0);

    DCSEngine::run(16, false);
}

#endif