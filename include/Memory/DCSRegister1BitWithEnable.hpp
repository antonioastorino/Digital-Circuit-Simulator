#ifndef DCSRegister1BitWithEnable_hpp
#define DCSRegister1BitWithEnable_hpp
#include "DCSCommon.hpp"
#include "DCSRegister1Bit.hpp"
#include "DCSTriStateBuffer.hpp"

class DCSNode;

/**
 * @class DCSRegister1BitWithEnable
 *
 * @pinout
 * In 0 - Data in
 * In 1 - Clock
 * In 2 - Clear
 * In 3 - Preset
 * In 4 - Load
 * In 5 - Enable
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
 * `Load` must be asserted at least `3 tau` before `Clock`'s falling edge. Data` must be stable at
 *least `2 tau` before `Clock`'s falling edge. `Data` and `Load` have to both be stable for at least
 *`1 tau` after `Clock`'s falling edge. `Clear` and `Preset` work the same as in the SR latch. Use
 *them with `Enable` low.
 */
class DCSRegister1BitWithEnable : public DCSComponent
{
private:
    DCSRegister1Bit reg0;
    DCSTriStateBuffer tris0;

public:
    DCSRegister1BitWithEnable(std::string name);

    DCSComponent* getOutComponent(uint16_t outPinNum) override;
    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    void updateOut() override;
};

#if TEST == 1
void register1BitWithEnableTest();
#endif
#endif /* DCSRegister1BitWithEnable_hpp */
