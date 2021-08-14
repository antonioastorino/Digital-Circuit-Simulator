#include "DCSRegister16BitsWithEnable.hpp"
#include "DCSCommon.hpp"
#include "DCSLog.hpp"
#include "DCSRegister1BitWithEnable.hpp"

DCSRegister16BitsWithEnable::DCSRegister16BitsWithEnable(std::string name)
    : DCSComponent(name, false),
      registerArray(name + "-reg1Arr_", 16),
      nodeArray({name + "-Clock", name + "-Clear", name + "-Preset", name + "-Load", name + "-OE"},
                5)
{
    // connect control signals
    for (uint16_t i = 0; i < 16; i++)
    {
        nodeArray.connect(registerArray[i], 0, 1);
        nodeArray.connect(registerArray[i], 1, 2);
        nodeArray.connect(registerArray[i], 2, 3);
        nodeArray.connect(registerArray[i], 3, 4);
        nodeArray.connect(registerArray[i], 4, 5);
    }

    timeDelay    = registerArray[0]->getTimeDelay();
    numOfInPins  = 21;
    numOfOutPins = 16;
}

DCSComponent* DCSRegister16BitsWithEnable::getOutComponent(uint16_t outPinNum)
{
    if (outPinNum < 16)
    {
        return registerArray.getOutComponent(outPinNum);
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSRegister16BitsWithEnable::getInComponent(uint16_t& inPinNum)
{
    if (inPinNum < 16)
    { // Data 0 to 15
        uint16_t elementNumber = inPinNum;
        inPinNum               = 0;
        return registerArray[elementNumber]->getInComponent(inPinNum);
    }
    else if (inPinNum < 21)
    { // control signals
        inPinNum -= 16;
        return nodeArray.getInComponent(inPinNum);
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}

void DCSRegister16BitsWithEnable::updateOut() { DCSLog::error(this->name, 0); }

#if TEST == 1
#include "DCSDisplayNBits.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"

void register16BitsWithEnableTest()
{
    DCSLog::printTestName("16-bit register with enable");
    DCSEngine::initialize(1);

    DCSRegister16BitsWithEnable reg0("reg0");
    DCSComponentArray<DCSInput> inArray("In", reg0.getNumOfInPins());
    DCSDisplayNBits disp0("In", 16);
    DCSDisplayNBits disp1("Out", 16);

    inArray.connect(&reg0, {0, 15}, {0, 15});
    inArray.connect(&disp0, {0, 15}, {0, 15});
    inArray.connect(&reg0, {16, 20}, {16, 20}, {"CLK", "R", "S", "LD", "OE"});

    reg0.connect(&disp1);

    //
    //
    uint16_t hcp = reg0.getTimeDelay() / 2 + 2;
    DCSEngine::setHalfClockPeriod(hcp);

    inArray[0]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[1]->makeSignal(transitions{1, 1, 2}, 0, true);
    inArray[2]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[3]->makeSignal(transitions{2, 1, 1}, 0, true);
    inArray[4]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[5]->makeSignal(transitions{1, 1, 1, 1}, 1, true);
    inArray[6]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[7]->makeSignal(transitions{1, 1, 1, 1}, 1, true);
    inArray[8]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[9]->makeSignal(transitions{1, 1, 1, 1}, 1, true);
    inArray[10]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[11]->makeSignal(transitions{1, 1, 1, 1}, 1, true);
    inArray[12]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[13]->makeSignal(transitions{1, 1, 1, 1}, 1, true);
    inArray[14]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[15]->makeSignal(transitions{1, 1, 1, 1}, 1, true);
    inArray[16]->makeSquareWave(hcp, true);
    inArray[17]->makeSignal(0);
    inArray[18]->makeSignal(transitions{6, 1}, 0, true);
    inArray[19]->makeSignal(transitions{1, 3, 1}, 0, true); // LD
    inArray[20]->makeSignal(1);                             // OE

    DCSEngine::run(hcp * 15, false);
}
#endif