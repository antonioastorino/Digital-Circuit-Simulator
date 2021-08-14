
#include "DCSOr.hpp"
#include "DCSCommon.hpp"

DCSOr::DCSOr(std::string name) : DCSComponent(name) {
    timeDelay    = 1;
    numOfInPins  = 2;
    numOfOutPins = 1;
}

void DCSOr::updateOut() {
    uint64_t newOutValue = (in | (in >> 1)) & 1;
    DCSComponent::checkOutputChanged(newOutValue);
    out = newOutValue;
}

#if TEST == 1
#include "DCSComponentArray.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"

void orTest()
{
    DCSLog::printTestName("Or");
    DCSEngine::initialize(1);

    DCSComponentArray<DCSInput> inArray("In", 2);
    DCSOr or0("Or0");
    DCSOutput out0("Out0");

    inArray[0]->makeSquareWave(1);
    inArray[1]->makeSquareWave(2);

    inArray.connect(&or0, 0, 0, "A");
    inArray.connect(&or0, 1, 1, "B");
    or0.connect(&out0, 0, 0, "AorB");

    DCSEngine::run(5);
}
#endif