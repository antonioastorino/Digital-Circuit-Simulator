#ifndef DCSDFlipFlopAsyncSR_hpp
#define DCSDFlipFlopAsyncSR_hpp
#include "DCSAnd.hpp"
#include "DCSDLatchAsyncSR.hpp"
#include "DCSNot.hpp"

/**
 * @class DCSDFlipFlopAsyncSR
 * D Flip-flop with asynchronous Set and Reset
 *
 * @pinout
 * In 0   - Data
 * In 1   - Clock
 * In 2   - Reset
 * In 3   - Preset
 *
 * Out 0  - Q
 * Out 1  - !Q
 * @end_pinout
 */
class DCSDFlipFlopAsyncSR : public DCSComponent
{
private:
    DCSNot not0              = DCSNot(name + "-CLK");
    DCSDLatchAsyncSR dLatSR0 = DCSDLatchAsyncSR(name + "-DLatch0");
    DCSAnd and0              = DCSAnd(name + "-And0");
    DCSNot not1              = DCSNot(name + "-Not1");
    DCSUnitDelay del0        = DCSUnitDelay(name + "-Del0");

public:
    DCSDFlipFlopAsyncSR(std::string name);

    DCSComponent* getOutComponent(uint16_t outPinNum) override;
    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    void updateOut() override;
};

#endif /* DCSDFlipFlopAsyncSR_hpp */
