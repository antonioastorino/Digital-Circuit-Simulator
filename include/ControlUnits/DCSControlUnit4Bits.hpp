
#ifndef DCSControlUnit4Bits_hpp
#define DCSControlUnit4Bits_hpp
#include "DCSCommon.hpp"
#include "DCSComponent.hpp"
#include "DCSDisplayNBits.hpp"
#include "DCSInput.hpp"
#include "DCSUnitDelay.hpp"
#include "DCSUpCounterWithLoadAndAsyncSR.hpp"
class DCSRam256x16;
class DCSAnd3;
class DCSNot;
class DCSOr;

/**
 * @class DCSControlUnit4Bits
 *
 * @pinout
 * In 0    - Clock
 * In 1    - Reset
 * In 2    - Address 0
 * In 3    - Address 1
 * In 4    - Address 2
 * In 5    - Address 3
 *
 * Out 0   - Ctrl 0
 * Out 1   - Ctrl 1
 * ...
 * Out 15  - Ctrl 15
 * @end_pinout
 */
class DCSControlUnit4Bits : public DCSComponent
{
private:
    DCSRam256x16* p_ram0;
    DCSUpCounterWithLoadAndAsyncSR count0;
    // Reset logic
    DCSAnd3 and3_0;
    DCSNot not0;
    DCSUnitDelay del0;
    DCSUnitDelay del1;
    DCSOr or0;
    DCSInput inGND;
    DCSInput inVcc;
    DCSDisplayNBits dispStep;

public:
    DCSControlUnit4Bits(std::string name, DCSRam256x16* ram);
    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    DCSComponent* getOutComponent(uint16_t outPinNum) override;

    void updateOut() override;
};

#if TEST == 1
void controlUnitTest();

#endif

#endif /* DCSControlUnit4Bits_hpp */