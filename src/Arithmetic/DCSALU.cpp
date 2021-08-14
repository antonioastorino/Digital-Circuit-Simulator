#include "DCSALU.hpp"
#include "DCSCommon.hpp"
#include "DCSLog.hpp"

DCSALU::DCSALU(std::string name)
    : DCSComponent(name, false),
      adder0(name + "-adder0"),           // adder
      xorArr0(name + "-xorArr0_", 8),     // controller inverter for 1's complement
      nor3Array0(name + "-nor3Arr0_", 3), // zero detector input
      and3_0(name + "and3_0"),            // zero detector output
      not0(name + "not0"),                // used to invert SU
      nodeSU(name + "-SU")                // subtract control input
{

    for (uint16_t i = 0; i < 8; i++)
    {
        xorArr0.connect(&adder0, i, i + 8); // connect controlled inverters to input B of full adder
        nodeSU.connect(xorArr0[i], 0, 1);   // connect SU to second input of all XOR's in the array
    }
    nodeSU.connect(&adder0, 0, 16); // connect to Carry in of ripple adder for 2-complement
    adder0.connect(&nor3Array0, {0, 7}, {0, 7}); // connect sum and
    nodeSU.connect(&not0);                       // invert SU
    not0.connect(&nor3Array0, 0, 8);             //+subract bit (zero checked on subtraction only)
    nor3Array0.connect(&and3_0); // zero signal - is 1 if result of subtraction is zero bit are zero

    timeDelay    = 15;
    numOfInPins  = 17;
    numOfOutPins = 10;
}

DCSComponent* DCSALU::getInComponent(uint16_t& inPinNum)
{
    if (inPinNum < 8)
    { // return input A of full adder
        return adder0.getInComponent(inPinNum);
    }
    else if (inPinNum < 16)
    { // return the input 0 of the corresponding XOR in the array
        inPinNum = 2 * (inPinNum - 8);
        return xorArr0.getInComponent(inPinNum);
    }
    else if (inPinNum == 16)
    {
        inPinNum = 0;
        return &nodeSU;
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}

DCSComponent* DCSALU::getOutComponent(uint16_t outPinNum)
{
    if (outPinNum < 9)
    {
        return adder0.getOutComponent(outPinNum);
    }
    else if (outPinNum == 9)
    {
        return &and3_0;
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

void DCSALU::updateOut() { DCSLog::error(this->name, 0); }

#if TEST == 1

#include "DCSALU.hpp"
#include "DCSDisplayNBits.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"
void aluTest()
{
    DCSLog::printTestName("ALU");
    {
        uint16_t masterClockHP = 1;
        DCSEngine::initialize(masterClockHP);

        DCSDisplayNBits dispA("dispA", 8);
        DCSDisplayNBits dispB("dispB", 8);
        DCSDisplayNBits dispE("dispE", 8);

        DCSALU alu("alu");
        DCSComponentArray<DCSInput> inA("A", 8);
        DCSComponentArray<DCSInput> inB("B", 8);
        DCSInput su("SU");
        DCSOutput outZero("OZ");

        inA.connect(&alu, {0, 7}, {0, 7});
        inA.connect(&dispA, {0, 7}, {0, 7});

        inB.connect(&alu, {0, 7}, {8, 15});
        inB.connect(&dispB, {0, 7}, {0, 7});

        su.connect(&alu, 0, 16, "SU");
        alu.connect(&dispE, {0, 7}, {0, 7});
        alu.connect(&outZero, 9, 0, "OZ");

        inA[0]->makeSignal(1);
        // inA[4]->makeSignal(1);
        inA[5]->makeSignal(1);
        // inA[6]->makeSignal(1);
        inB[0]->makeSignal(1);
        inB[5]->makeSignal(1);

        su.makeSignal(1);

        DCSEngine::run(30 * masterClockHP, false);
    }
}
#endif