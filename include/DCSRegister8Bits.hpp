/**
 * @class DCSRegister8Bits
 * Implements an 8-bit register made up of 8 1-bit registers sharing the same control signals
 * 
 * @pinout
 * In 0    - Output Enable
 * In 1    - Clock
 * In 2    - Clear
 * In 3    - Preset
 * In 4    - Load
 * In 5    - Data in 0
 * In 6    - Data in 1
 * In 7    - Data in 2
 * In 8    - Data in 3
 * In 9    - Data in 4
 * In 10   - Data in 5
 * In 11   - Data in 6
 * In 12   - Data in 7
 *
 * Out 0   - Data out 0
 * Out 1   - Data out 1
 * Out 2   - Data out 2
 * Out 3   - Data out 3
 * Out 4   - Data out 4
 * Out 5   - Data out 5
 * Out 6   - Data out 6
 * Out 7   - Data out 7
 * @end_pinout
 */

#ifndef DCSRegister8Bits_hpp
#define DCSRegister8Bits_hpp
#include "DCSComponentArray.hpp"
class DCSRegister1Bit;
class DCSNode;

class DCSRegister8Bits : public DCSComponent {
private:
    DCSComponentArray<DCSRegister1Bit> registerArray;
    DCSComponentArray<DCSNode> nodeArray;

public:
    DCSRegister8Bits(std::string name);

    DCSComponent* getOutComponent(uint16_t outPinNum) override;
    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    void updateOut() override;
};

#endif /* DCSRegister8Bits_hpp */
