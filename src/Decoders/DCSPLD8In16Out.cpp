#include "DCSPLD8In16Out.hpp"
#include "DCSLog.hpp"

DCSPLD8In16Out::DCSPLD8In16Out(std::string name, const uint16_t data[32][8])
    : DCSComponent(name, false), dec0(this->name + "dec0"), inGND(this->name + "_inGND")
{
    for (int i = 0; i < 16; i++)
    {
        // instantiation
        orArr0[i] = new DCSComponentArray<DCSOr>("orArr0", 128);
        orArr1[i] = new DCSComponentArray<DCSOr>("orArr1", 64);
        orArr2[i] = new DCSComponentArray<DCSOr>("orArr1", 32);
        orArr3[i] = new DCSComponentArray<DCSOr>("orArr1", 16);
        orArr4[i] = new DCSComponentArray<DCSOr>("orArr1", 8);
        orArr5[i] = new DCSComponentArray<DCSOr>("orArr1", 4);
        orArr6[i] = new DCSComponentArray<DCSOr>("orArr1", 2);
        or7[i]    = new DCSOr("or7");
        // connection
        orArr0[i]->connect(orArr1[i]);
        orArr1[i]->connect(orArr2[i]);
        orArr2[i]->connect(orArr3[i]);
        orArr3[i]->connect(orArr4[i]);
        orArr4[i]->connect(orArr5[i]);
        orArr5[i]->connect(orArr6[i]);
        orArr6[i]->connect(or7[i]);
    }

    size_t decPinNum = 0;
    for (size_t instr = 0; instr < 32; instr++)
    {
        for (size_t uCode = 0; uCode < 8; uCode++)
        {
            for (uint16_t bit = 0; bit < 16; bit++)
            {
                bool val = (data[instr][uCode] >> bit) & 1;
                if (val)
                {
                    dec0.connect(orArr0[bit], decPinNum, decPinNum);
                }
                else
                {
                    inGND.connect(orArr0[bit], 0, decPinNum);
                }
            }
            decPinNum++;
        }
    }

    this->timeDelay    = dec0.getTimeDelay() + 7;
    this->numOfInPins  = 8;
    this->numOfOutPins = 16;
}

DCSPLD8In16Out::~DCSPLD8In16Out()
{
    for (int i = 0; i < 16; i++)
    {
        // instantiation
        delete orArr0[i];
        orArr0[i] = nullptr;
        delete orArr1[i];
        orArr1[i] = nullptr;
        delete orArr2[i];
        orArr2[i] = nullptr;
        delete orArr3[i];
        orArr3[i] = nullptr;
        delete orArr4[i];
        orArr4[i] = nullptr;
        delete orArr5[i];
        orArr5[i] = nullptr;
        delete orArr6[i];
        orArr6[i] = nullptr;
        delete or7[i];
        or7[i] = nullptr;
    }
}

DCSComponent* DCSPLD8In16Out::getInComponent(uint16_t& inPinNum)
{
    if (inPinNum < 8)
    { // return decoder input
        return dec0.getInComponent(inPinNum);
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}
DCSComponent* DCSPLD8In16Out::getOutComponent(uint16_t outPinNum)
{
    if (outPinNum < 16)
    {
        return or7[outPinNum];
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

void DCSPLD8In16Out::updateOut() { DCSLog::error(this->name, 0); }