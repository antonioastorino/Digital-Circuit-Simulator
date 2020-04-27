#include "DCSFullAdder.hpp"
#include "DCSLog.hpp"

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
