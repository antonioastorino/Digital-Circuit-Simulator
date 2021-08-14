#include "DCSRam16x8.hpp"
#include "DCSCommon.hpp"
#include "DCSLog.hpp"
#include "DCSRegister1BitWithEnable.hpp"
#include "DCSRegister8BitsWithEnable.hpp"

DCSRam16x8::DCSRam16x8(std::string name)
    : DCSComponent(name, false),
      regArray(name + "-Reg8Arr0_", 16),
      andArray0(name + "-ENAndArr0_", 16),
      andArray1(name + "-WRAndArr1_", 16),
      ctrlNodeArray({name + "-Clock",   // 13
                     name + "-Clear",   // 14
                     name + "-Preset",  // 15
                     name + "-Write",   // 16
                     name + "-Enable"}, // 12
                    5),
      dataNodeArray(name + "-dataNodeArr0_", 8),
      outNodeArray(name + "-outNodeArr0_", 8),
      delArray(name + "-inDelArray_", 8),
      dec0(name + "-dec0")
{

    // add a unit delay to data for synchronization with clock
    delArray.connect(&dataNodeArray);

    for (uint16_t regNum = 0; regNum < 16; regNum++)
    {
        // connect to register control pins
        ctrlNodeArray.connect(regArray[regNum], 0, 8);  // Clock
        ctrlNodeArray.connect(regArray[regNum], 1, 9);  // Clear
        ctrlNodeArray.connect(regArray[regNum], 2, 10); // Preset

        // connect each decoder output pin to and gates at input 0
        // either for AND'ing the Enable signal or the Write signal

        /* Write */
        dec0.connect(andArray1[regNum], regNum, 0); // connect decoder outputs to each And at in 0
        ctrlNodeArray.connect(andArray1[regNum], 3, 1); // connect Write to each And at 1
        andArray1.connect(regArray[regNum], regNum,
                          11); // connect the AND'ed result to Load of each register

        /* Enable */
        dec0.connect(andArray0[regNum], regNum, 0); // connect decoder outputs to each And at in 0
        ctrlNodeArray.connect(andArray0[regNum], 4, 1); // connect Enable to each And at 1
        andArray0.connect(regArray[regNum], regNum,
                          12); // connect the AND'ed result to Enable of each register

        for (uint16_t j = 0; j < 8; j++)
        {
            // connect Data in to all registers' Data in's
            dataNodeArray.connect(regArray[regNum], j, j); // Data
        }
        // connect all Out's of individual registers to common output
        regArray[regNum]->connect(&outNodeArray);
    }

    timeDelay    = dec0.getTimeDelay() + regArray[0]->getTimeDelay();
    numOfInPins  = 17;
    numOfOutPins = 8;
}

DCSComponent* DCSRam16x8::getOutComponent(uint16_t outPinNum)
{
    if (outPinNum < 8)
    {
        return outNodeArray.getOutComponent(outPinNum);
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSRam16x8::getInComponent(uint16_t& inPinNum)
{
    if (inPinNum < 8)
    { // Data in
        return delArray.getInComponent(inPinNum);
    }
    else if (inPinNum < 12)
    { // Address
        inPinNum -= 8;
        return dec0.getInComponent(inPinNum);
    }
    else if (inPinNum < 17)
    { // Control signals
        inPinNum -= 12;
        return ctrlNodeArray.getInComponent(inPinNum);
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}

void DCSRam16x8::updateOut() { DCSLog::error(name, 0); }

void DCSRam16x8::disconnect()
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
#include "DCSLog.hpp"
#include "DCSOutput.hpp"
#include "DCSRam16x8.hpp"
void ramTest()
{
    DCSLog::printTestName("RAM");

    uint16_t hcp = 10; // half clock period
    DCSEngine::initialize(hcp);
    DCSRam16x8 ram0("Ram0");

    DCSComponentArray<DCSInput> inArray0("In", ram0.getNumOfInPins());
    DCSComponentArray<DCSOutput> outArray0("Out", 5);

    DCSDisplayNBits dispAddr("ADDR", 4);
    DCSDisplayNBits dispData("DATA", 8);
    // DCSDisplayNBits dispCtrl("CTRL", 5);
    DCSDisplayNBits dispOut("OUT", 8);

    inArray0.connect(&ram0);
    inArray0.connect(&dispAddr, {8, 11}, {0, 3});
    inArray0.connect(&dispData, {0, 7}, {0, 7});
    inArray0.connect(&outArray0, {12, 16}, {0, 4}, {"CLK", "R", "S", "WR", "OE"});
    ram0.connect(&dispOut);

    inArray0[0]->makeSignal(std::string("0000011100"));   // Data in 0
    inArray0[7]->makeSignal(std::string("0000011100"));   // Data in 1
    inArray0[8]->makeSignal({2, 1, 1}, 0, true);          // Address 0
    inArray0[16]->makeSignal(1);                          // Enable
    inArray0[12]->makeSignal(std::string("11111111001")); // Clock
    inArray0[13]->makeSignal(std::string("1111000000"));  // Clear
    inArray0[14]->makeSignal({5, 1, 1}, 0, true);         // Preset
    inArray0[15]->makeSignal(1);                          // Write

    DCSEngine::run(15 * hcp, false);
}
#endif