#include "DCSFullAdder.hpp"
#include "DCSLog.hpp"
#include "DCSCommon.hpp"

DCSFullAdder::~DCSFullAdder() {}

DCSFullAdder::DCSFullAdder(std::string name)
    : DCSComponent(name, false),
      node0(name + "-ANode"),
      node1(name + "-BNode"),
      node2(name + "-CinNode"),
      xor0(name + "-Xor0"),
      xor1(name + "-SumXor1"),
      and0(name + "-And0"),
      and1(name + "-And1"),
      or0(name + "-CoutOr0") {
    node0.connect(&xor0, 0, 0);
    node0.connect(&and1, 0, 0);
    node1.connect(&xor0, 0, 1);
    node1.connect(&and1, 0, 1);
    node2.connect(&xor1, 0, 1);
    node2.connect(&and0, 0, 0);
    xor0.connect(&xor1, 0, 0);
    xor0.connect(&and0, 0, 1);
    and0.connect(&or0, 0, 0);
    and1.connect(&or0, 0, 1);

    timeDelay    = 3;
    numOfInPins  = 3;
    numOfOutPins = 2;
}

DCSComponent* DCSFullAdder::getInComponent(uint16_t& inPinNum) {
    if (inPinNum == 0) {
        return &node0;
    }
    if (inPinNum == 1) {
        inPinNum = 0;
        return &node1;
    }
    if (inPinNum == 2) {
        inPinNum = 0;
        return &node2;
    }
    DCSLog::error(name, 11);
    return nullptr;
}

DCSComponent* DCSFullAdder::getOutComponent(uint16_t outPinNum) {
    if (outPinNum == 0) {
        return &xor1;
    }
    if (outPinNum == 1) {
        outPinNum = 0;
        return &or0;
    }
    DCSLog::error(name, 10);
    return nullptr;
}

void DCSFullAdder::updateOut() { DCSLog::error(name, 0); }

#if TEST == 1
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"

void fullAdderTest()
{
    DCSLog::printTestName("Full adder");
    uint16_t hp = 10;
    DCSEngine::initialize(hp);

    DCSFullAdder fa0("FA0");

    DCSInput in0("A");
    DCSInput in1("B");
    DCSInput in2("Cin");

    DCSOutput out0("Sum");
    DCSOutput out1("Cout");

    in0.connect(&fa0, 0, 0, "A");
    in1.connect(&fa0, 0, 1, "B");
    in2.connect(&fa0, 0, 2, "Cin");

    fa0.connect(&out0, 0, 0, "Sum");
    fa0.connect(&out1, 1, 0, "Cout");

    in0.makeSquareWave(hp * 2);
    in1.makeSquareWave(hp * 4);
    in2.makeSquareWave(hp);

    DCSEngine::run(hp * 9, false);
}
#endif