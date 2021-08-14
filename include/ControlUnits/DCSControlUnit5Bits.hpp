
#ifndef DCSControlUnit5Bits_hpp
#define DCSControlUnit5Bits_hpp
#include "DCSComponent.hpp"
#include "DCSDisplayNBits.hpp"
#include "DCSInput.hpp"
#include "DCSNode.hpp"
#include "DCSNot.hpp"
#include "DCSRegister8Bits.hpp"
#include "DCSUnitDelay.hpp"
#include "DCSUpCounterWithLoadAndAsyncSR.hpp"
class DCSPLD8In16Out;
class DCSAnd3;
class DCSNot;
class DCSOr;

/**
 * @class DCSControlUnit5Bits
 * The core of this component is a combinatorial logic, represented by the internal PLD. A counter
 * drives the first 3 bits of the PLD address while the remaining 5 bits are available to the user.
 * The counter is incremented upon clock rising edge. A register is placed at the output to
 * synchronize all the output pins. The register is updated upon clock falling edge.
 *
 * @pinout
 * In 0    - Clock
 * In 1    - Reset
 * In 2    - Address 0
 * In 3    - Address 1
 * In 4    - Address 2
 * In 5    - Address 3
 * In 6    - Address 4
 *
 * Out 0   - Ctrl 0
 * Out 1   - Ctrl 1
 * ...
 * Out 15  - Ctrl 15
 * @end_pinout
 */
class DCSControlUnit5Bits : public DCSComponent
{
private:
    DCSPLD8In16Out* p_pld0;
    DCSUpCounterWithLoadAndAsyncSR count0;
    DCSRegister8Bits regMSB;
    DCSRegister8Bits regLSB;
    DCSNot notClk;
    DCSNode nodeClk;
    DCSNode nodeRst;
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
    DCSControlUnit5Bits(std::string name, DCSPLD8In16Out* pld);
    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    DCSComponent* getOutComponent(uint16_t outPinNum) override;

    void updateOut() override;
};

#endif /* DCSControlUnit5Bits_hpp */