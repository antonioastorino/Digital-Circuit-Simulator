#include "DCSUpCounterWithLoadAndAsyncSR.hpp"
#include "DCSLog.hpp"
#include "DCSCommon.hpp"

DCSUpCounterWithLoadAndAsyncSR::DCSUpCounterWithLoadAndAsyncSR(std::string name, uint16_t numOfBits)
    : DCSComponent(name, false),
      dividerArray(name + "-divArray", numOfBits),
      nodeArray({name + "-Load", name + "-Clock", name + "-Clear", name + "-Preset"}, 4),
      numOfBits(numOfBits) {
    for (uint16_t i = 0; i < numOfBits; i++) {
        for (uint16_t j = 0; j < 4; j++) {
            /*
             connect nodes to internal inputs of dividers:
             1 = Load
             2 = Clock
             3 = Clear
             4 = Preset
             Node that inputs 0 and 5 of dividers are not shared
             */
            nodeArray[j]->connect(dividerArray[i], 0, j + 1);
        }
    }
    for (uint16_t i = 0; i < numOfBits - 1; i++) {
        // cascade dividers
        dividerArray[i]->connect(dividerArray[i + 1],
                                 2, // Count out
                                 5  // Count in
        );
    }
    // NOTE: The Count in of dividerArray[0] is an array input.
    //       The Count out of dividerArray[numOfElements-1] is an array output.

    timeDelay    = 7 + numOfBits;
    numOfInPins  = 5 + numOfBits;
    numOfOutPins = 1 + numOfBits;
}
DCSComponent* DCSUpCounterWithLoadAndAsyncSR::getOutComponent(uint16_t outPinNum) {
    if (outPinNum < numOfBits) {
        uint16_t arrayElement = outPinNum;
        outPinNum             = 0;
        return dividerArray[arrayElement]->getOutComponent(outPinNum);
    } else if (outPinNum == numOfBits) {
        outPinNum = 2;
        return dividerArray[numOfBits - 1]->getOutComponent(outPinNum);
    } else
        DCSLog::error(this->name, 10);
    return nullptr;
}
DCSComponent* DCSUpCounterWithLoadAndAsyncSR::getInComponent(uint16_t& inPinNum) {
    if (inPinNum == 0) {
        inPinNum = 5;
        return dividerArray[0]->getInComponent(inPinNum); // Count in
    } else if (inPinNum < 5) {
        uint16_t arrayElement = inPinNum - 1;
        inPinNum              = 0;
        return nodeArray[arrayElement];
    } else if (inPinNum < 5 + numOfBits) {
        uint16_t arrayElement = inPinNum - 5;
        inPinNum              = 0; // Data
        return dividerArray[arrayElement]->getInComponent(inPinNum);
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}

void DCSUpCounterWithLoadAndAsyncSR::updateOut() { DCSLog::error(name, 0); }

#if TEST == 1
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"


void upCounter4BitsTest()
{
    DCSLog::printTestName("Up counter");
    DCSEngine::initialize(5);

    DCSUpCounterWithLoadAndAsyncSR count0("count", 4);
    DCSComponentArray<DCSInput> inArray("In", count0.getNumOfInPins());
    DCSComponentArray<DCSOutput> outArray("Out", count0.getNumOfOutPins());
    DCSDisplayNBits disp0("In", 4);
    DCSDisplayNBits disp1("Count", 4);

    // connect control signals
    inArray.connect(&count0, {0, 4}, {0, 4}, {"C_in", "LD", "CLK", "", ""});

    // connect data-in signals
    inArray.connect(&count0, {5, 8}, {5, 8});

    // connect data-in to display (for enhanced visualization purposes)
    inArray.connect(&disp0, {5, 8}, {0, 3});

    // connect counter output to output object
    count0.connect(&outArray, {0, 3}, {0, 3});
    count0.connect(&outArray, 4, 4, {"Cout"});

    count0.connect(&disp1, {0, 3}, {0, 3});

    uint16_t hp = count0.getTimeDelay() / 2 + 1;

    DCSEngine::setHalfClockPeriod(hp);

    inArray[0]->makeSignal(transitions{4, 1}, 0, true);    // Carry in
    inArray[1]->makeSignal(transitions{1, 1, 1}, 0, true); // Load
    inArray[2]->makeSquareWave(hp);                        // Clock

    inArray[7]->makeSignal(transitions{1, 1, 1}, 0, true);
    inArray[8]->makeSignal(transitions{1, 1, 1}, 0, true);

    DCSEngine::run(50 * hp * 2, true);
}

void upCounter8BitsTest()
{
    DCSLog::printTestName("Up counter");
    DCSEngine::initialize(5);

    DCSUpCounterWithLoadAndAsyncSR count0("count", 8);
    DCSComponentArray<DCSInput> inArray("In", count0.getNumOfInPins());
    DCSComponentArray<DCSOutput> outArray("Out", count0.getNumOfOutPins());
    DCSDisplayNBits disp0("In", 8);
    DCSDisplayNBits disp1("Count", 8);

    inArray.connect(&count0, {"C_in", "LD", "CLK", "", "", "", "", "", "", "", "", "", ""});

    count0.connect(&outArray, {"", "", "", "", "", "", "", "", "Cout"});

    inArray.connect(&disp0, {5, 12}, {0, 7});
    count0.connect(&disp1, {0, 7}, {0, 7});

    uint16_t hp = count0.getTimeDelay() / 2 + 1;
    DCSEngine::setHalfClockPeriod(hp);
    inArray[0]->makeSignal(transitions{4, 1}, 0, true);
    inArray[1]->makeSignal(transitions{1, 1, 1}, 0, true);
    inArray[2]->makeSquareWave(hp);

    inArray[7]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[8]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[9]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[10]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[11]->makeSignal(transitions{1, 1, 1, 1}, 0, true);
    inArray[12]->makeSignal(transitions{1, 1, 1}, 0, true);

    DCSEngine::run(100 * hp * 2, true);
}

#endif
