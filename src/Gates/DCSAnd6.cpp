#include "DCSAnd6.hpp"
#include "DCSLog.hpp"
#include "DCSCommon.hpp"

DCSAnd6::DCSAnd6(std::string name)
    : DCSComponent(name, false), and3array(name + "-and3array", 2), and0(name + "-and0") {
    and3array.connect(&and0);

    timeDelay    = 2; 
    numOfInPins  = 6;
    numOfOutPins = 1;
}

DCSComponent* DCSAnd6::getOutComponent(uint16_t outPinNum) {
    if (outPinNum == 0)
        return &and0;
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSAnd6::getInComponent(uint16_t& inPinNum) {
    if (inPinNum < 6)
        return and3array.getInComponent(inPinNum);
    DCSLog::error(this->name, 11);
    return nullptr;
}

void DCSAnd6::updateOut() { DCSLog::error(this->name, 0); }

#if TEST == 1
#include "DCSAnd6.hpp"
#include "DCSComponentArray.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"
void and6Test()
{
    DCSLog::printTestName("And 6");
    uint16_t hp = 2;
    DCSEngine::initialize(hp);

    DCSComponentArray<DCSInput> inArray("In", 6);
    DCSAnd6 and6_0("And6_0");
    DCSOutput out0("Out0");

    inArray.connect(&and6_0, {"I"});
    and6_0.connect(&out0, {"O"});

    for (uint16_t i = 0; i < 6; i++)
    {
        inArray[i]->makeSquareWave(hp << i, 0);
    }

    DCSEngine::run(64 * hp + 1, true);
}

#endif