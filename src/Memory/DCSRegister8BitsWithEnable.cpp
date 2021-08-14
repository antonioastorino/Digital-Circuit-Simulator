#include "DCSRegister8BitsWithEnable.hpp"
#include "DCSLog.hpp"
#include "DCSRegister1BitWithEnable.hpp"
#include "DCSCommon.hpp"

DCSRegister8BitsWithEnable::DCSRegister8BitsWithEnable(std::string name)
    : DCSComponent(name, false),
      registerArray(name + "-reg1Arr_", 8),
      nodeArray({name + "-Clock", name + "-Clear", name + "-Preset", name + "-Load", name + "-OE"},
                5) {
    // connect control signals
    for (uint16_t i = 0; i < 8; i++) {
        nodeArray.connect(registerArray[i], 0, 1);
        nodeArray.connect(registerArray[i], 1, 2);
        nodeArray.connect(registerArray[i], 2, 3);
        nodeArray.connect(registerArray[i], 3, 4);
        nodeArray.connect(registerArray[i], 4, 5);
    }

    timeDelay    = registerArray[0]->getTimeDelay();
    numOfInPins  = 13;
    numOfOutPins = 8;
}

DCSComponent* DCSRegister8BitsWithEnable::getOutComponent(uint16_t outPinNum) {
    if (outPinNum < 8) {
        return registerArray.getOutComponent(outPinNum);
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSRegister8BitsWithEnable::getInComponent(uint16_t& inPinNum) {
    if (inPinNum < 8) { // Data 0 to 7
        uint16_t elementNumber = inPinNum;
        inPinNum = 0;
        return registerArray[elementNumber]->getInComponent(inPinNum);
    } else if (inPinNum < 13) { // control signals
        inPinNum -= 8;
        return nodeArray.getInComponent(inPinNum);
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}

void DCSRegister8BitsWithEnable::updateOut() { DCSLog::error(this->name, 0); }

#if TEST == 1
#include "DCSDisplayNBits.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"

void register8BitsWithEnableTest()
{
    DCSLog::printTestName("8-bit register with enable");
    DCSEngine::initialize(1);

    DCSRegister8BitsWithEnable reg0("reg0");
    DCSComponentArray<DCSInput> inArray("In", reg0.getNumOfInPins());
    DCSDisplayNBits disp0("In", 8);
    DCSDisplayNBits disp1("Out", 8);

    inArray.connect(&reg0, {0, 7}, {0, 7});
    inArray.connect(&disp0, {0, 7}, {0, 7});
    inArray.connect(&reg0, {8, 12}, {8, 12}, {"CLK", "R", "S", "LD", "OE"});

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
    inArray[5]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[6]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[7]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[8]->makeSquareWave(hcp, true);
    inArray[9]->makeSignal(0);
    inArray[10]->makeSignal(transitions{6, 1}, 0, true);
    inArray[11]->makeSignal(transitions{1, 3, 1}, 0, true); // LD
    inArray[12]->makeSignal(1);                             // OE
    // inArray[12]->makeSignal(transitions{3, 1}, 0, true); // OE

    DCSEngine::run(hcp * 15, false);
}
#endif
