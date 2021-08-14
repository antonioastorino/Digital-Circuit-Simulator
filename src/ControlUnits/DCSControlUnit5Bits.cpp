#include "DCSControlUnit5Bits.hpp"
#include "DCSAnd3.hpp"
#include "DCSLog.hpp"
#include "DCSPLD8In16Out.hpp"
#include "DCSRam256x16.hpp"

DCSControlUnit5Bits::DCSControlUnit5Bits(std::string name, DCSPLD8In16Out* pld)
    : DCSComponent(name, false),
      p_pld0(pld),
      count0(name + "_count0_", 3),
      regMSB(name + "_regMSB_"),
      regLSB(name + "_regLSB_"),
      notClk(name + "_notClk_"),
      nodeClk(name + "_nodeClk_"),
      nodeRst(name + "_nodeRst_"),
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
    nodeRst.connect(&or0, 0, 0); // Manual reset
    // connect OR output to counter reset pin
    or0.connect(&count0, 0, 3);
    // connect Count Enable to Vcc
    inVcc.connect(&count0, 0, 0);
    // connect Load, Clear, and Preset to ground
    inGND.connect(&count0, 0, 1);
    inGND.connect(&count0, 0, 4);

    p_pld0->connect(&regLSB, {0, 7}, {0, 7});
    p_pld0->connect(&regMSB, {8, 15}, {0, 7});

    // connect counter data in to ground
    for (uint16_t i = 5; i < 8; i++)
        inGND.connect(&count0, 0, i);

    // connect counter output to PLD address 0, 1, and 2
    count0.connect(p_pld0, {0, 2}, {0, 2});

    inVcc.makeSignal(1);

    // connect counter to display
    count0.connect(&dispStep, {0, 2}, {0, 2});

    nodeClk.connect(&count0, 0, 2); // counter clock

    nodeClk.connect(&notClk); // invert clock

    notClk.connect(&regMSB, 0, 8);  // clock
    notClk.connect(&regLSB, 0, 8);  // clock
    nodeRst.connect(&regMSB, 0, 9); // Reset
    nodeRst.connect(&regLSB, 0, 9); // Reset
    inGND.connect(&regMSB, 0, 10);  // Preset to GND
    inGND.connect(&regLSB, 0, 10);  // Preset to GND
    inVcc.connect(&regMSB, 0, 11);  // Load always enabled
    inVcc.connect(&regLSB, 0, 11);  // Load always enabled

    timeDelay    = count0.getTimeDelay() + p_pld0->getTimeDelay();
    numOfInPins  = 7;
    numOfOutPins = 16;
}

DCSComponent* DCSControlUnit5Bits::getInComponent(uint16_t& inPinNum)
{
    if (inPinNum == 0)
    {
        return &nodeClk;
    }
    else if (inPinNum == 1)
    {
        inPinNum = 0;
        return &nodeRst; // counter reset (OR'ed with automatic reset)
    }
    else if (inPinNum < 7)
    {
        inPinNum += 1;
        return p_pld0->getInComponent(inPinNum); // PLD addresses from 3 to 7
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}

DCSComponent* DCSControlUnit5Bits::getOutComponent(uint16_t outPinNum)
{
    if (outPinNum < 8)
    {
        return regLSB.getOutComponent(outPinNum);
    }
    if (outPinNum < 16)
    {
        outPinNum -= 8;
        return regMSB.getOutComponent(outPinNum);
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

void DCSControlUnit5Bits::updateOut() { DCSLog::error(name, 0); }