#include "DCSDLatch.hpp"
#include "DCSLog.hpp"
#include "DCSCommon.hpp"

DCSDLatch::DCSDLatch(std::string name) : DCSComponent(name, false) {
    node0.connect(&del0, 0, 0);
    node0.connect(&not0, 0, 0);
    node1.connect(&and0, 0, 1);
    node1.connect(&and1, 0, 0);
    not0.connect(&and0, 0, 0);
    del0.connect(&and1, 0, 1);
    and0.connect(&srLatch0, 0, 0);
    and1.connect(&srLatch0, 0, 1);

    timeDelay    = 4;
    numOfInPins  = 2;
    numOfOutPins = 2;
}

DCSComponent* DCSDLatch::getOutComponent(uint16_t outPinNum) {
    return srLatch0.getOutComponent(outPinNum);
}

DCSComponent* DCSDLatch::getInComponent(uint16_t& inPinNum) {
    if (inPinNum == 0)
        return &node0;
    else if (inPinNum == 1) {
        inPinNum = 0; // pin 1 in D latch is EN pin 0
        return &node1;
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}

void DCSDLatch::updateOut() { DCSLog::error(name, 0); }

#if TEST == 1
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"

void dLatchTest()
{
    DCSLog::printTestName("D-Latch");
    DCSEngine::initialize(5);

    DCSDLatch dLatch0("DLatch0");
    DCSInput I0("In0");
    DCSInput I1("In1");

    I0.makeSignal({3, 7, 3, 3, 3}, 0, false);
    I1.makeSignal({4, 2, 5, 2, 6}, 0, false);

    DCSOutput O0("Out0");
    DCSOutput O1("Out1");

    I0.connect(&dLatch0, 0, 0, "DATA");
    I1.connect(&dLatch0, 0, 1, "EN");

    dLatch0.connect(&O0, 0, 0, " Q");
    dLatch0.connect(&O1, 1, 0, "!Q");

    DCSEngine::run(20);
}
#endif