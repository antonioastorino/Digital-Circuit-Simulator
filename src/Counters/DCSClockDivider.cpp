#include "DCSClockDivider.hpp"
#include "DCSLog.hpp"

DCSClockDivider::DCSClockDivider(std::string name) : DCSComponent(name, false) {
    // D
    node0.connect(&not0, 0, 0);
    node0.connect(&and0, 0, 1);
    // Load
    node1.connect(&not1, 0, 0);
    node1.connect(&and0, 0, 0);
    node1.connect(&and1, 0, 0);
    // Count in
    node2.connect(&and2, 0, 1);
    node2.connect(&and3, 0, 1);
    // Others
    not0.connect(&and1, 0, 1);
    not1.connect(&and2, 0, 0);
    and2.connect(&or0, 0, 1);
    and2.connect(&or1, 0, 1);
    and0.connect(&or0, 0, 0);
    and1.connect(&or1, 0, 0);
    or0.connect(&jk0, 0, 0); // to master J
    or1.connect(&jk0, 0, 1); // to master K
    jk0.connect(&and3, 0, 0);

    timeDelay    = 10;
    numOfInPins  = 6;
    numOfOutPins = 3;
}

DCSComponent* DCSClockDivider::getOutComponent(uint16_t outPinNum) {
    if (outPinNum == 0 || outPinNum == 1) {
        return jk0.getOutComponent(outPinNum);
    } else if (outPinNum == 2) {
        outPinNum = 0;
        return &and3;
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}
DCSComponent* DCSClockDivider::getInComponent(uint16_t& inPinNum) {
    switch (inPinNum) {
    case 0: // Data
        return &node0;
    case 1: // Load
        inPinNum = 0;
        return &node1;
    case 2: // CLK
        return jk0.getInComponent(inPinNum);
    case 3: // Clear
        return jk0.getInComponent(inPinNum);
    case 4: // Preset
        return jk0.getInComponent(inPinNum);
    case 5: // Enable
        inPinNum = 0;
        return &node2;
    default:
        DCSLog::error(this->name, 11);
        return nullptr;
    }
}

void DCSClockDivider::updateOut() { DCSLog::error(name, 0); }
