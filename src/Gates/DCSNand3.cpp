#include "DCSNand3.hpp"
#include "DCSCommon.hpp"

DCSNand3::DCSNand3(std::string name) : DCSComponent(name)
{
    timeDelay    = 1;
    numOfInPins  = 3;
    numOfOutPins = 1;
}

void DCSNand3::updateOut()
{
    uint64_t newOutValue = !((in & (in >> 1) & (in >> 2)) & 1);
    DCSComponent::checkOutputChanged(newOutValue);
    out = newOutValue;
}
#if TEST == 1
#include "DCSComponentArray.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"

void nand3Test()
{
    DCSLog::printTestName("Nand 3");
    DCSEngine::initialize(1);

    DCSComponentArray<DCSInput> inArray("In", 3);
    DCSNand3 nand3_0("Nand3_0");
    DCSOutput out0("Out0");

    inArray[0]->makeSquareWave(1, 0);
    inArray[1]->makeSquareWave(2, 0);
    inArray[2]->makeSquareWave(4, 0);

    inArray.connect(&nand3_0, 0, 0, "In0");
    inArray.connect(&nand3_0, 1, 1, "In1");
    inArray.connect(&nand3_0, 2, 2, "In2");
    nand3_0.connect(&out0, 0, 0, "Out");

    DCSEngine::run(9);
}
#endif