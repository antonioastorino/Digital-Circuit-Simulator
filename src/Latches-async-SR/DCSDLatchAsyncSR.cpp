#include "DCSDLatchAsyncSR.hpp"
#include "DCSCommon.hpp"
#include "DCSLog.hpp"

DCSDLatchAsyncSR::DCSDLatchAsyncSR(std::string name) : DCSComponent(name, false)
{
    node0.connect(&del0, 0, 0);
    node0.connect(&not0, 0, 0);
    node1.connect(&and0, 0, 1);
    node1.connect(&and1, 0, 0);
    not0.connect(&and0, 0, 0);
    del0.connect(&and1, 0, 1);
    and0.connect(&nor3_0, 0, 0);
    and1.connect(&nor3_1, 0, 1);
    nor3_0.connect(&nor3_1, 0, 0);
    nor3_1.connect(&nor3_0, 0, 1);

    timeDelay    = 4;
    numOfInPins  = 4;
    numOfOutPins = 2;
}

DCSComponent* DCSDLatchAsyncSR::getOutComponent(uint16_t outPinNum)
{
    if (outPinNum == 0)
        return &nor3_0;
    else if (outPinNum == 1)
    {
        outPinNum = 0;
        return &nor3_1;
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSDLatchAsyncSR::getInComponent(uint16_t& inPinNum)
{
    switch (inPinNum)
    {
    case 0:
        return &node0;
    case 1:
        inPinNum = 0;
        return &node1;
    case 2:
        return &nor3_0;
    case 3:
        inPinNum = 2;
        return &nor3_1;
    default:
        DCSLog::error(this->name, 11);
    }
    return nullptr;
}

void DCSDLatchAsyncSR::updateOut() { DCSLog::error(this->name, 0); }

#if TEST == 1
#include "DCSComponentArray.hpp"
#include "DCSDLatchAsyncSR.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"

void dLatchAsyncSRTest()
{
    DCSLog::printTestName("D-Latch with asynchronous SR");
    DCSEngine::initialize(5);
    transitions d     = {10, 3, 3, 4};
    transitions en    = {2, 2, 7, 2, 4};
    transitions reset = {18, 2, 5};

    DCSDLatchAsyncSR dLatch0("DLatch0");
    DCSComponentArray<DCSInput> inArray("In", 4);
    DCSOutput O0("Out0");
    DCSOutput O1("Out1");

    inArray.connect(&dLatch0, 0, 0, "DATA");
    inArray.connect(&dLatch0, 1, 1, "EN");
    inArray.connect(&dLatch0, 2, 2, "R");
    inArray.connect(&dLatch0, 3, 3, "S");
    dLatch0.connect(&O0, 0, 0, " Q");
    dLatch0.connect(&O1, 1, 0, "!Q");

    inArray[0]->makeSignal(d);
    inArray[1]->makeSignal(en);
    inArray[2]->makeSignal(reset);
    inArray[3]->makeSignal(0);

    DCSEngine::run(25);
}

#endif