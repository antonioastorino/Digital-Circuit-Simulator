#include "DCSSRLatch.hpp"
#include "DCSLog.hpp"

DCSSRLatch::DCSSRLatch(std::string name)
    : DCSComponent(name, false), nor0(name + "-Nor0"), nor1(name + "-Nor1") {
    nor0.connect(&nor1, /*out*/ 0, /*in*/ 0);
    nor1.connect(&nor0, /*out*/ 0, /*in*/ 1);

    timeDelay    = 2;
    numOfInPins  = 2;
    numOfOutPins = 2;
}

DCSComponent* DCSSRLatch::getOutComponent(uint16_t& outPinNum) {
    if (outPinNum == 0)
        return &nor0;
    if (outPinNum == 1) {
        outPinNum = 0;
        return &nor1;
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSSRLatch::getInComponent(uint16_t& inPinNum) {
    if (inPinNum == 0)
        return &nor0;
    if (inPinNum == 1)
        return &nor1;
    DCSLog::error(this->name, 11);
    return nullptr;
}

void DCSSRLatch::updateOut() { DCSLog::error(this->name, 11); }
