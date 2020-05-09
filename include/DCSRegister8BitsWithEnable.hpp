/**
 * @class DCSRegister8BitsWithEnable
 * 8-bit register made up of 8 1-bit registers sharing the same control signals
 * 
 * @pinout
 * In 0    - Data in 0
 * In 1    - Data in 1
 * In 2    - Data in 2
 * In 3    - Data in 3
 * In 4    - Data in 4
 * In 5    - Data in 5
 * In 6    - Data in 6
 * In 7    - Data in 7
 * In 8    - Clock
 * In 9    - Clear
 * In 10   - Preset
 * In 11   - Load
 * In 12   - Output Enable
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

#ifndef DCSRegister8BitsWithEnable_hpp
#define DCSRegister8BitsWithEnable_hpp
#include "DCSComponentArray.hpp"
class DCSRegister1BitWithEnable;
class DCSNode;

class DCSRegister8BitsWithEnable : public DCSComponent {
private:
    DCSComponentArray<DCSRegister1BitWithEnable> registerArray;
    DCSComponentArray<DCSNode> nodeArray;

public:
    DCSRegister8BitsWithEnable(std::string name);

    DCSComponent* getOutComponent(uint16_t outPinNum) override;
    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    void updateOut() override;
};

#endif /* DCSRegister8BitsWithEnable_hpp */
