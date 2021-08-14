#include "DCSDFlipFlop.hpp"
#include "DCSCommon.hpp"
#include "DCSLog.hpp"

DCSDFlipFlop::DCSDFlipFlop(std::string name)
    : DCSComponent(name, false),
      node0(name + "CLK0"),
      dLat0(name + "-DLatch0"),
      and0(name + "-And0"),
      not0(name + "-Not0"),
      del0(name + "-Del0")
{
    node0.connect(&not0, 0, 0);
    node0.connect(&and0, 0, 0);
    not0.connect(&del0, 0, 0);
    del0.connect(&and0, 0, 1);
    and0.connect(&dLat0, 0, 1);

    timeDelay    = 4;
    numOfInPins  = 2;
    numOfOutPins = 2;
}

DCSComponent* DCSDFlipFlop::getOutComponent(uint16_t outPinNum)
{
    return dLat0.getOutComponent(outPinNum);
}

DCSComponent* DCSDFlipFlop::getInComponent(uint16_t& inPinNum)
{
    if (inPinNum == 0)
        return dLat0.getInComponent(inPinNum);
    else if (inPinNum == 1)
    {
        // input pin 1 is the clock, connected to the node pin 0
        inPinNum = 0;
        return &node0;
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

void DCSDFlipFlop::updateOut() { DCSLog::error(this->name, 0); }

#if TEST == 1
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"

void dFlipFlopTest()
{
    DCSLog::printTestName("D-FlipFlop");
    DCSEngine::initialize(1);
    transitions d   = {4, 7, 3, 10};
    transitions clk = {4, 2, 5, 2, 4};

    DCSDFlipFlop dff0("DFF0");
    DCSInput I0("In0");
    DCSInput I1("In1");

    I0.makeSignal(d);
    I1.makeSignal(clk);

    DCSOutput O0("Out0");
    DCSOutput O1("Out1");

    I0.connect(&dff0, 0, 0, "DATA");
    I1.connect(&dff0, 0, 1, "CLK");
    dff0.connect(&O0, 0, 0, " Q");
    dff0.connect(&O1, 1, 0, "!Q");

    DCSEngine::run(20);
}
#endif