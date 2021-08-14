#include "DCSControlUnit4Bits.hpp"
#include "DCSAnd3.hpp"
#include "DCSCommon.hpp"
#include "DCSLog.hpp"
#include "DCSRam256x16.hpp"

DCSControlUnit4Bits::DCSControlUnit4Bits(std::string name, DCSRam256x16* ram)
    : DCSComponent(name, false),
      p_ram0(ram),
      count0(name + "_count0", 3),
      and3_0(name + "_resetLogicAnd3_0"),
      not0(name + "resetLogicNot0"),
      del0(name + "_resetLogicDel0"),
      del1(name + "_resetLogicDel1"),
      or0(name + "_resetLogicOr0"),
      inGND(name + "_inGND"),
      inVcc(name + "_inVcc"),
      dispStep(name + "_step", 3)
{
    // connect counter output to reset logic to reset when 0b110 is output
    count0.connect(&not0, 0, 0);
    count0.connect(&del0, 1, 0);
    count0.connect(&del1, 2, 0);
    not0.connect(&and3_0, 0, 0);
    del0.connect(&and3_0, 0, 1);
    del1.connect(&and3_0, 0, 2);
    // connect reset logic to OR gate @ in 1. In 0 will be available externally for manually
    // resetting the counter
    and3_0.connect(&or0, 0, 1);
    // connect OR output to counter reset pin
    or0.connect(&count0, 0, 3);
    // connect Count Enable to Vcc
    inVcc.connect(&count0, 0, 0);
    // connect Load, Clear, and Preset to ground
    inGND.connect(&count0, 0, 1);
    inGND.connect(&count0, 0, 4);

    // connect counter data in to ground
    for (uint16_t i = 5; i < 8; i++)
        inGND.connect(&count0, 0, i);

    // connect counter output to ram address 0, 1, and 2
    count0.connect(p_ram0, {0, 2}, {16, 18});
    // connect ram data in to ground
    for (uint16_t i = 0; i < 16; i++)
        inGND.connect(p_ram0, 0, i);
    // connect ram address 7 to ground (we use only 7 bits out of 8)
    inGND.connect(p_ram0, 0, 23);
    // connect ram Clock, Clear, Preset and Write to ground
    for (uint16_t i = 24; i < 28; i++)
        inGND.connect(p_ram0, 0, i);
    // connect ram output enable to Vcc
    inVcc.connect(p_ram0, 0, 28);

    inVcc.makeSignal(1);

    // connect counter to display
    count0.connect(&dispStep, {0, 2}, {0, 2});

    timeDelay    = count0.getTimeDelay() + p_ram0->getTimeDelay();
    numOfInPins  = 6;
    numOfOutPins = 16;
}

DCSComponent* DCSControlUnit4Bits::getInComponent(uint16_t& inPinNum)
{
    if (inPinNum == 0)
    {
        inPinNum = 2;
        return count0.getInComponent(inPinNum); // counter clock
    }
    else if (inPinNum == 1)
    {
        inPinNum = 0;
        return &or0; // counter reset (OR'ed with automatic reset)
    }
    else if (inPinNum < 6)
    {
        inPinNum += 17;
        return p_ram0->getInComponent(inPinNum); // ram addresses from 3 to 6 (pins 19 to 22)
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}

DCSComponent* DCSControlUnit4Bits::getOutComponent(uint16_t outPinNum)
{
    if (outPinNum < 16)
    {
        return p_ram0->getOutComponent(outPinNum);
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

void DCSControlUnit4Bits::updateOut() { DCSLog::error(name, 0); }

#if TEST == 1
#include "DCSComponentArray.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"

void controlUnitTest()
{
    DCSLog::printTestName("Control Unit");
    uint32_t hcp = 12;
    DCSEngine::initialize(hcp);

    DCSRam256x16 cuRam("cuRam");

    DCSEngine::programControlUnit(&cuRam, false);
    DCSEngine::useRamElements();

    DCSControlUnit4Bits cu0("CU", &cuRam);
    DCSComponentArray<DCSInput> inAddress("inAddress", 4);
    DCSInput inClock("inClock");
    DCSInput inReset("inReset");

    DCSDisplayNBits dispOut("out", 16);
    DCSDisplayNBits dispAddr("addr", 4);

    inClock.connect(&cu0, 0, 0, "CLK");
    inReset.connect(&cu0, 0, 1);
    inAddress.connect(&dispAddr);
    cu0.connect(&dispOut);

    inAddress.connect(&cu0, {0, 3}, {2, 5});
    inAddress[0]->makeSquareWave(6 * (hcp << 1));
    inAddress[1]->makeSquareWave(6 * (hcp << 2));
    inAddress[2]->makeSquareWave(6 * (hcp << 3));
    inAddress[3]->makeSquareWave(6 * (hcp << 4));

    inClock.makeSquareWave(hcp);

    DCSEngine::run(6 * (hcp << 4) + 3, true);
}
#endif