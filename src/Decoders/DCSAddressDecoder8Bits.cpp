#include "DCSAddressDecoder8Bits.hpp"
#include "DCSAnd8.hpp"
#include "DCSLog.hpp"
#include "DCSCommon.hpp"

DCSAddressDecoder8Bits::DCSAddressDecoder8Bits(std::string name)
    : DCSComponent(name, false),
      m_nodeArray(name + "-In_", 8),
      m_notArray(name + "-Not_", 8),
      m_delArray(name + "-Del_", 8),
      m_and8Array(name + "-And8_", 256) {
    for (uint16_t i = 0; i < 8; i++) {
        m_nodeArray.connect(&m_delArray, i, i);
        m_nodeArray.connect(&m_notArray, i, i);
        for (uint16_t IN = 0; IN < 256; IN++) {
            if ((IN >> i) & 1) {
                m_delArray.connect(m_and8Array[IN], i, i);
            } else {
                m_notArray.connect(m_and8Array[IN], i, i);
            }
        }
    }

    timeDelay    = 3;
    numOfInPins  = 8;
    numOfOutPins = 256;
}

DCSComponent* DCSAddressDecoder8Bits::getOutComponent(uint16_t outPinNum) {
    if (outPinNum < 256) {
        return m_and8Array.getOutComponent(outPinNum);
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSAddressDecoder8Bits::getInComponent(uint16_t& inPinNum) {
    if (inPinNum < 8) {
        return m_nodeArray.getInComponent(inPinNum);
    }
    DCSLog::error(name, 11);
    return nullptr;
}

void DCSAddressDecoder8Bits::updateOut() { DCSLog::error(name, 0); }

#if TEST == 1
#include "DCSAddressDecoder8Bits.hpp"
#include "DCSComponentArray.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"
void addressDecoder8BitsTest()
{
    DCSLog::printTestName("8-bit address decoder");
    uint16_t hp = 1;
    DCSEngine::initialize(hp);

    DCSComponentArray<DCSInput> inArray("In", 8);
    DCSAddressDecoder8Bits dec8("dec8");
    DCSDisplayNBits dispIn("in", 8);
    DCSDisplayNBits dispOutA("outA", 32);
    DCSDisplayNBits dispOutB("outB", 32);
    DCSDisplayNBits dispOutC("outC", 32);
    DCSDisplayNBits dispOutD("outD", 32);
    DCSDisplayNBits dispOutE("outE", 32);
    DCSDisplayNBits dispOutF("outF", 32);
    DCSDisplayNBits dispOutG("outG", 32);
    DCSDisplayNBits dispOutH("outH", 32);

    inArray.connect(&dec8);
    inArray.connect(&dispIn);
    uint16_t startPin = 0;
    dec8.connect(&dispOutA, {0, 31}, {0, 31});
    dec8.connect(&dispOutB, {32, 63}, {0, 31});
    dec8.connect(&dispOutC, {64, 95}, {0, 31});
    dec8.connect(&dispOutD, {96, 127}, {0, 31});
    dec8.connect(&dispOutE, {128, 159}, {0, 31});
    dec8.connect(&dispOutF, {160, 191}, {0, 31});
    dec8.connect(&dispOutG, {192, 223}, {0, 31});
    dec8.connect(&dispOutH, {224, 255}, {0, 31});

    for (uint16_t i = 0; i < 8; i++)
    {
        inArray[i]->makeSquareWave(hp << i, 0);
    }

    DCSEngine::run(256 * hp + 3, false);
}

#endif