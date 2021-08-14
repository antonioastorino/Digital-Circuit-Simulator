#include "DCSRam256x16.hpp"
#include "DCSCommon.hpp"
#include "DCSLog.hpp"
#include "DCSRegister16BitsWithEnable.hpp"
#include "DCSRegister1BitWithEnable.hpp"

DCSRam256x16::DCSRam256x16(std::string name)
    : DCSComponent(name, false),
      regArray(name + "-Reg16Arr0_", 256),
      andArray0(name + "-ENAndArr0_", 256),
      andArray1(name + "-WRAndArr1_", 256),
      ctrlNodeArray({name + "-Clock",   // 24
                     name + "-Clear",   // 25
                     name + "-Preset",  // 26
                     name + "-Write",   // 27
                     name + "-Enable"}, // 28
                    5),
      dataNodeArray(name + "-dataNodeArr0_", 16),
      outNodeArray(name + "-outNodeArr0_", 16),
      delArray(name + "-inDelArray_", 16),
      dec0(name + "-dec0")
{

    // add a unit delay to data for synchronization with clock
    delArray.connect(&dataNodeArray);

    for (uint16_t regNum = 0; regNum < 256; regNum++)
    {
        // connect to register control pins
        ctrlNodeArray.connect(regArray[regNum], 0, 16); // Clock
        ctrlNodeArray.connect(regArray[regNum], 1, 17); // Clear
        ctrlNodeArray.connect(regArray[regNum], 2, 18); // Preset

        // connect each decoder output pin to and gates at input 0
        // either for AND'ing the Enable signal or the Write signal

        /* Write */
        dec0.connect(andArray1[regNum], regNum, 0); // connect decoder outputs to each And at in 0
        ctrlNodeArray.connect(andArray1[regNum], 3, 1); // connect Write to each And at 1
        andArray1.connect(regArray[regNum], regNum,
                          19); // connect the AND'ed result to Load of each register

        /* Enable */
        dec0.connect(andArray0[regNum], regNum, 0); // connect decoder outputs to each And at in 0
        ctrlNodeArray.connect(andArray0[regNum], 4, 1); // connect Enable to each And at 1
        andArray0.connect(regArray[regNum], regNum,
                          20); // connect the AND'ed result to Enable of each register

        for (uint16_t j = 0; j < 16; j++)
        {
            // connect Data in to all registers' Data in's
            dataNodeArray.connect(regArray[regNum], j, j); // Data
        }
        // connect all Out's of individual registers to common output
        regArray[regNum]->connect(&outNodeArray);
    }

    timeDelay    = dec0.getTimeDelay() + regArray[0]->getTimeDelay();
    numOfInPins  = 29;
    numOfOutPins = 16;
}

DCSComponent* DCSRam256x16::getOutComponent(uint16_t outPinNum)
{
    if (outPinNum < 16)
    {
        return outNodeArray.getOutComponent(outPinNum);
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSRam256x16::getInComponent(uint16_t& inPinNum)
{
    if (inPinNum < 16)
    { // Data in
        return delArray.getInComponent(inPinNum);
    }
    else if (inPinNum < 24)
    { // Address
        inPinNum -= 16;
        return dec0.getInComponent(inPinNum);
    }
    else if (inPinNum < 29)
    { // Control signals
        inPinNum -= 24;
        return ctrlNodeArray.getInComponent(inPinNum);
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}

void DCSRam256x16::updateOut() { DCSLog::error(name, 0); }

void DCSRam256x16::disconnect()
{
    // clearing the state of the input components
    for (int i = 0; i < this->numOfInPins; i++)
    {
        uint16_t inPinNum = i;
        DCSComponent* c   = this->getInComponent(inPinNum);
        c->connectedIn    = 0;
        c->fromTristateIn = 0;
        c->initialized    = false;
        c->reachableIn    = 0;
        for (int j = 0; j < c->getNumOfInPins(); j++)
        {
            c->updatedByVector[j] = nullptr;
        }
    }
    // removing connections from the output components
    for (int i = 0; i < this->numOfOutPins; i++)
    {
        DCSComponent* c = this->getOutComponent(i);
        c->wireVector.clear();
    }
}

#if TEST == 1
#include "DCSComponentArray.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"

void ram256x16Test();

void ram256x16Test()
{
    DCSLog::printTestName("Ram 256 words, 16 bits");
    uint32_t hp = 12;
    DCSEngine::initialize(hp);

    DCSComponentArray<DCSInput> inData("inData", 16);
    DCSComponentArray<DCSInput> inAddress("inAddress", 8);
    DCSComponentArray<DCSInput> inCtrl("inCtrl", 5);

    DCSRam256x16 ram0("ram");
    DCSDisplayNBits dispIn("in", 16);
    DCSDisplayNBits dispAddr("addr", 8);
    DCSDisplayNBits dispOut("out", 16);

    inData.connect(&ram0, {0, 15}, {0, 15});
    inData.connect(&dispIn, {0, 15}, {0, 15});
    inAddress.connect(&ram0, {0, 7}, {16, 23});
    inAddress.connect(&dispAddr);
    inCtrl.connect(&ram0, {0, 4}, {24, 28}, {"clk", "R", "S", "LD", "OE"});

    ram0.connect(&dispOut);

    for (uint16_t i = 0; i < 16; i++)
    {
        inData[i]->makeSquareWave(hp << ((i % 4) + 1), 0);
    }
    for (uint16_t i = 0; i < 7; i++)
    {
        inAddress[i]->makeSquareWave(hp << ((i % 4) + 1), 0);
    }
    inCtrl[0]->makeSquareWave(hp);
    inCtrl[3]->makeSignal(transitions({16, 1}), true, true);
    inCtrl[4]->makeSignal(1);

    DCSEngine::run(20 * hp + 3, true);
}
#endif