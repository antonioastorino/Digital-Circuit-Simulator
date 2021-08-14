#include "DCSAddressDecoder4Bits.hpp"
#include "DCSAnd4.hpp"
#include "DCSCommon.hpp"
#include "DCSLog.hpp"

DCSAddressDecoder4Bits::DCSAddressDecoder4Bits(std::string name)
    : DCSComponent(name, false),
      nodeArray(name + "-In", 4),
      notArray(name + "-Not", 4),
      delArray(name + "-Del", 4),
      and4Array(name + "-And4", 16)
{
    for (uint16_t i = 0; i < 4; i++)
    {
        nodeArray.connect(&delArray, i, i);
        nodeArray.connect(&notArray, i, i);
        for (uint16_t IN = 0; IN < 16; IN++)
        {
            if ((IN >> i) & 1)
            {
                delArray.connect(and4Array[IN], i, i);
            }
            else
            {
                notArray.connect(and4Array[IN], i, i);
            }
        }
    }

    timeDelay    = 2;
    numOfInPins  = 4;
    numOfOutPins = 16;
}

DCSComponent* DCSAddressDecoder4Bits::getOutComponent(uint16_t outPinNum)
{
    if (outPinNum < 16)
    {
        return and4Array.getOutComponent(outPinNum);
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSAddressDecoder4Bits::getInComponent(uint16_t& inPinNum)
{
    if (inPinNum < 4)
    {
        return nodeArray.getInComponent(inPinNum);
    }
    DCSLog::error(name, 11);
    return nullptr;
}

void DCSAddressDecoder4Bits::updateOut() { DCSLog::error(name, 0); }

#if TEST == 1
#include "DCSAddressDecoder4Bits.hpp"
#include "DCSComponentArray.hpp"
#include "DCSDisplayNBits.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"

void addressDecoderTest4Bits()
{
    DCSLog::printTestName("4-bit address decoder");
    uint16_t hcp = 3;
    DCSEngine::initialize(hcp);
    DCSComponentArray<DCSInput> inArray0("IN", 4);
    // DCSComponentArray<DCSOutput> outArray0("OUT", 16);
    DCSDisplayNBits inDisp0("in", 4);
    DCSDisplayNBits outDisp0("out", 16);

    DCSAddressDecoder4Bits dec0("dec0");

    inArray0.connect(&dec0);
    inArray0.connect(&inDisp0);
    // dec0.connect(&outArray0);
    dec0.connect(&outDisp0);

    inArray0[0]->makeSquareWave(hcp);
    inArray0[1]->makeSquareWave(2 * hcp);
    inArray0[2]->makeSquareWave(4 * hcp);
    inArray0[3]->makeSquareWave(8 * hcp);

    DCSEngine::run(50, false);
}
#endif