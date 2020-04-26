#include "DCSMux2to1.hpp"
#include "DCSLog.hpp"
#include "DCSTriStateBuffer8Bits.hpp"

/**
 * @class DCSMux2to1
 * Implements a 2 to 1 multiplexer
 * PINOUT:
 * Input 0 - Data in 0
 * Input 1 - Data in 1
 * Input 2 - Selector
 *
 * Out 0 - Data out 0
 */
DCSMux2to1::DCSMux2to1(std::string name)
    : DCSComponent(name, false),
      and0(name + "-And0"),
      and1(name + "-And1"),
      not0(name + "-Not0"),
      del0(name + "-Del0"),
      or0(name + "-Or0"),
      node0(name + "-Sel0") {
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

DCSComponent* DCSMux2to1::getOutComponent(uint16_t& outPinNum) {
    if (outPinNum == 0)
        return &or0;
    DCSLog::error(name, 10);
	return nullptr;
}

DCSComponent* DCSMux2to1::getInComponent(uint16_t& inPinNum) {
    if (inPinNum == 0)
        return &and0;
    else if (inPinNum == 1) {
        inPinNum = 0;
        return &and1;
    } else if (inPinNum == 2) {
        inPinNum = 0;
        return &node0;
    }
    DCSLog::error(name, 11);
	return nullptr;
}

void DCSMux2to1::updateOut() { DCSLog::error(name, 0); }
