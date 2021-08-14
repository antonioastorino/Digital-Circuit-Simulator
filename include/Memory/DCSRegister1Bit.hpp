#ifndef DCSRegister1Bit_hpp
#define DCSRegister1Bit_hpp
#include "DCSCommon.hpp"
#include "DCSDFlipFlopAsyncSR.hpp"
#include "DCSOr.hpp"
#include "DCSTriStateBuffer.hpp"

class DCSNode;

/**
 * @class DCSRegister1Bit
 *
 * @pinout
 * In 0 - Data in
 * In 1 - Clock
 * In 2 - Clear
 * In 3 - Preset
 * In 4 - Load
 *
 * Out 0 - Data out
 * @end_pinout
 *
 * @diagram
 *|       |  ____
 *| LOAD: | X    XXXXXXXX
 *|       |  ^ start
 *|       |   ___
 *| DATA: | XX   XXXXXXXX
 *|       | ____  _______
 *| CLK:  |     __
 *|       |          ____
 *| Q:    | _________
 *|       | ________
 *|!Q:    |         _____
 *|                  ^ ready
 * @end_diagram
 *
 * `Load` must be asserted at least `3 tau` before `Clock`'s falling edge.
 * `Data` must be stable at least `2 tau` before `Clock`'s falling edge.
 * `Data` and `Load` have to both be stable for at least `1 tau` after `Clock`'s falling edge.
 * `Clear` and `Preset` work the same as in the SR latch.
 */
class DCSRegister1Bit : public DCSComponent
{
private:
    DCSNode node0;
    DCSNot not0;
    DCSAnd and0;
    DCSAnd and1;
    DCSOr or0;
    DCSDFlipFlopAsyncSR dffsr0;

public:
    DCSRegister1Bit(std::string name);

    DCSComponent* getOutComponent(uint16_t outPinNum) override;
    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    void updateOut() override;
};

#if TEST == 1
void register1BitTest();
#endif

#endif /* DCSRegister1Bit_hpp */
