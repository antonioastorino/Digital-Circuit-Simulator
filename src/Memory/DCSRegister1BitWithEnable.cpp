#include "DCSRegister1BitWithEnable.hpp"
#include "DCSCommon.hpp"
#include "DCSLog.hpp"

DCSRegister1BitWithEnable::DCSRegister1BitWithEnable(std::string name)
    : DCSComponent(name, false), reg0(name + "-Reg0"), tris0(name + "-OutTris")
{
    reg0.connect(&tris0, 0, 0); // tri-state buffer

    timeDelay    = 7;
    numOfInPins  = 6;
    numOfOutPins = 1;
}

DCSComponent* DCSRegister1BitWithEnable::getOutComponent(uint16_t outPinNum)
{
    if (outPinNum == 0)
        return &tris0;
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSRegister1BitWithEnable::getInComponent(uint16_t& inPinNum)
{
    if (inPinNum < 5)
    { // same connections as for the register without enable
        return reg0.getInComponent(inPinNum);
    }
    else if (inPinNum == 5)
    {
        inPinNum = 1;
        return &tris0;
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}
void DCSRegister1BitWithEnable::updateOut() { DCSLog::error(name, 0); }

#if TEST == 1
#include "DCSComponentArray.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"

void register1BitWithEnableTest()
{
    DCSLog::printTestName("1-bit register with enable");
    DCSEngine::initialize(4);

    DCSRegister1BitWithEnable reg0("Reg0");
    DCSComponentArray<DCSInput> inArray("In", reg0.getNumOfInPins());
    DCSOutput O0("Out0");

    inArray.connect(&reg0, 0, 0, "D");
    inArray.connect(&reg0, 1, 1, "CLK");
    inArray.connect(&reg0, 2, 2, "R");
    inArray.connect(&reg0, 3, 3, "S");
    inArray.connect(&reg0, 4, 4, "LD");
    inArray.connect(&reg0, 5, 5, "OE");
    reg0.connect(&O0, 0, 0, " Q");

    inArray[0]->makeSignal(transitions{13, 3, 1});
    inArray[1]->makeSquareWave(3, true);
    inArray[2]->makeSignal(transitions{3, 40, 3, 1}, true);
    inArray[3]->makeSignal(transitions{37, 3, 1}, 0);
    inArray[4]->makeSignal(transitions{12, 4, 8, 4, 1});
    inArray[5]->makeSignal(1);

    DCSEngine::run(55, false);
}
#endif