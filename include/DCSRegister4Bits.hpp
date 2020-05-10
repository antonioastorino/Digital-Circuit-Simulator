#ifndef DCSRegister4Bits_hpp
#define DCSRegister4Bits_hpp
#include "DCSComponentArray.hpp"
class DCSRegister1Bit;
class DCSNode;
/**
 * @class DCSRegister4Bits
 * 4-bit register made up of 4 1-bit registers sharing the same control signals
 * 
 * @pinout
 * In 0    - Data in 0
 * In 1    - Data in 1
 * In 2    - Data in 2
 * In 3    - Data in 3
 * In 4    - Clock
 * In 5    - Clear
 * In 6    - Preset
 * In 7    - Load
 *
 * Out 0   - Data out 0
 * Out 1   - Data out 1
 * Out 2   - Data out 2
 * Out 3   - Data out 3
 * @end_pinout
 */

class DCSRegister4Bits : public DCSComponent {
private:
    DCSComponentArray<DCSRegister1Bit> registerArray;
    DCSComponentArray<DCSNode> nodeArray;

public:
    DCSRegister4Bits(std::string name);

    DCSComponent* getOutComponent(uint16_t outPinNum) override;
    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    void updateOut() override;
};

#endif /* DCSRegister4Bits_hpp */
