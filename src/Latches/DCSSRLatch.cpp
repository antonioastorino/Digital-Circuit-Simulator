#include "DCSSRLatch.hpp"
#include "DCSCommon.hpp"
#include "DCSLog.hpp"

DCSSRLatch::DCSSRLatch(std::string name)
    : DCSComponent(name, false), nor0(name + "-Nor0"), nor1(name + "-Nor1")
{
    nor0.connect(&nor1, /*out*/ 0, /*in*/ 0);
    nor1.connect(&nor0, /*out*/ 0, /*in*/ 1);

    timeDelay    = 2;
    numOfInPins  = 2;
    numOfOutPins = 2;
}

DCSComponent* DCSSRLatch::getOutComponent(uint16_t outPinNum)
{
    if (outPinNum == 0)
        return &nor0;
    if (outPinNum == 1)
    {
        outPinNum = 0;
        return &nor1;
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSSRLatch::getInComponent(uint16_t& inPinNum)
{
    if (inPinNum == 0)
        return &nor0;
    if (inPinNum == 1)
        return &nor1;
    DCSLog::error(this->name, 11);
    return nullptr;
}

void DCSSRLatch::updateOut() { DCSLog::error(this->name, 11); }

#if TEST == 1
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"

void srLatchTest()
{
    DCSLog::printTestName("SR-Latch");
    DCSEngine::initialize(5);
    transitions s = {2, 2, 1};
    transitions r = {6, 2, 1};

    DCSSRLatch SR("Latch1");
    DCSInput I0("In0");
    DCSInput I1("In1");
    DCSOutput O0("Out0");
    DCSOutput O1("Out1");

    I0.makeSignal(s);
    I1.makeSignal(r);

    I0.connect(&SR, 0, 0, "R");
    I1.connect(&SR, 0, 1, "S");
    SR.connect(&O0, 0, 0, " Q");
    SR.connect(&O1, 1, 0, "!Q");

    DCSEngine::run(11);
}
#endif