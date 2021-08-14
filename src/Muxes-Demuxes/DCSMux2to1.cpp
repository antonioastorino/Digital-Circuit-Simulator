#include "DCSMux2To1.hpp"
#include "DCSCommon.hpp"
#include "DCSLog.hpp"
#include "DCSTriStateBuffer8Bits.hpp"

DCSMux2To1::DCSMux2To1(std::string name)
    : DCSComponent(name, false),
      and0(name + "-And0"),
      and1(name + "-And1"),
      not0(name + "-Not0"),
      del0(name + "-Del0"),
      or0(name + "-Or0"),
      node0(name + "-Sel0")
{
    // Selector
    node0.connect(&not0, 0, 0);
    node0.connect(&del0, 0, 0);
    not0.connect(&and0, 0, 1);
    del0.connect(&and1, 0, 1);
    and0.connect(&or0, 0, 0);
    and1.connect(&or0, 0, 1);

    timeDelay    = 2;
    numOfInPins  = 3;
    numOfOutPins = 1;
}

DCSComponent* DCSMux2To1::getOutComponent(uint16_t outPinNum)
{
    if (outPinNum == 0)
        return &or0;
    DCSLog::error(name, 10);
    return nullptr;
}

DCSComponent* DCSMux2To1::getInComponent(uint16_t& inPinNum)
{
    if (inPinNum == 0)
        return &and0;
    else if (inPinNum == 1)
    {
        inPinNum = 0;
        return &and1;
    }
    else if (inPinNum == 2)
    {
        inPinNum = 0;
        return &node0;
    }
    DCSLog::error(name, 11);
    return nullptr;
}

void DCSMux2To1::updateOut() { DCSLog::error(name, 0); }

#if TEST == 1
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"

void mux2To1Test()
{
    DCSLog::printTestName("Mux 2 to 1");
    uint16_t hp = 3;
    DCSEngine::initialize(hp);

    DCSMux2To1 mux0("Mux0");

    DCSInput in0("In0");
    DCSInput in1("In1");
    DCSInput in2("Sel0");

    DCSOutput out0("Out0");

    in0.connect(&mux0, 0, 0, "I0");
    in1.connect(&mux0, 0, 1, "I1");
    in2.connect(&mux0, 0, 2, "SEL");

    mux0.connect(&out0, 0, 0, "OUT");

    /*
     Expected result:
    I0 I1 SEL OUT    0
     1  1   1   0    0
     1  1   0   1    3
     0  1   1   1    6
     0  1   0   1    9
     1  0   1   0    12
     1  0   0   0    15
     0  0   1   1    18
     0  0   0   0    21
     1  1   1   0    24
     */
    in0.makeSquareWave(hp * 2);
    in1.makeSquareWave(hp * 4);
    in2.makeSquareWave(1);

    DCSEngine::run(hp * 9, true);
}
#endif