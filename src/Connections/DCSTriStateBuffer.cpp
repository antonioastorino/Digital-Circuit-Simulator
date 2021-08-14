#include "DCSTriStateBuffer.hpp"
#include "DCSCommon.hpp"

DCSTriStateBuffer::DCSTriStateBuffer(std::string name) : DCSComponent(name)
{
    tristate = true;
    enabled  = false; // disabled by default

    timeDelay    = 1;
    numOfInPins  = 2;
    numOfOutPins = 1;
}

void DCSTriStateBuffer::updateOut()
{
    if ((in >> 1) & 1)
    {
        enable();
        out = in & 1;
    }
    else
    {
        disable();
    }
}

void DCSTriStateBuffer::enable() { enabled = true; }
void DCSTriStateBuffer::disable() { enabled = false; }

#if TEST == 1
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSNode.hpp"
#include "DCSOutput.hpp"

void triStateBufferTest()
{
    DCSLog::printTestName("Tri-state buffer");
    DCSEngine::initialize(5);

    DCSInput inA0("A0", 0);
    DCSInput inA1("A1");
    DCSInput inB0("B0", 1);
    DCSInput inB1("B1");
    DCSTriStateBuffer tsbA("tsbA");
    DCSTriStateBuffer tsbB("tsbB");
    DCSNode node0("Del0");
    DCSOutput out0("Out0");

    inA1.makeSignal({2, 2, 2, 2, 2, 100}, 1, false);
    inB1.makeSignal(transitions{2, 2, 2, 2, 2, 2, 100});

    inA0.connect(&tsbA, 0, 0, "INA");
    inA1.connect(&tsbA, 0, 1, "ENA");
    inB0.connect(&tsbB, 0, 0, "INB");
    inB1.connect(&tsbB, 0, 1, "ENB");
    tsbA.connect(&node0, 0, 0);
    tsbB.connect(&node0, 0, 0);
    node0.connect(&out0, 0, 0, "Out");

    DCSEngine::run(20);
}
#endif
