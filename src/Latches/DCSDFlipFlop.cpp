#include "DCSDFlipFlop.hpp"
#include "DCSLog.hpp"

DCSDFlipFlop::DCSDFlipFlop(std::string name)
    : DCSComponent(name, false),
      node0(name + "CLK0"),
      dLat0(name + "-DLatch0"),
      and0(name + "-And0"),
      not0(name + "-Not0"),
      del0(name + "-Del0") {
    node0.connect(&not0, 0, 0);
    node0.connect(&and0, 0, 0);
    not0.connect(&del0, 0, 0);
    del0.connect(&and0, 0, 1);
    and0.connect(&dLat0, 0, 1);

    timeDelay    = 4;
    numOfInPins  = 2;
    numOfOutPins = 2;
}

DCSComponent* DCSDFlipFlop::getOutComponent(uint16_t& outPinNum) {
    return dLat0.getOutComponent(outPinNum);
}

DCSComponent* DCSDFlipFlop::getInComponent(uint16_t& inPinNum) {
    if (inPinNum == 0)
        return dLat0.getInComponent(inPinNum);
    else if (inPinNum == 1) {
        // input pin 1 is the clock, connected to the node pin 0
        inPinNum = 0;
        return &node0;
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

void DCSDFlipFlop::updateOut() { DCSLog::error(this->name, 0); }
