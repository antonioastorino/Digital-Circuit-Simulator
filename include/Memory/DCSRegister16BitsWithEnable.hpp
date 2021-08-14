
#ifndef DCSRegister16BitsWithEnable_hpp
#define DCSRegister16BitsWithEnable_hpp
#include "DCSCommon.hpp"
#include "DCSComponentArray.hpp"

class DCSRegister1BitWithEnable;
class DCSNode;

/**
 * @class DCSRegister16BitsWithEnable
 * 16-bit register consisting an array of 16 1-bit registers sharing the same control signals
 *
 * @pinout
 * In 0    - Data in 0
 * In 1    - Data in 1
 * ...
 * In 15   - Data in 15
 * In 16   - Clock
 * In 17   - Clear
 * In 18   - Preset
 * In 19   - Load
 * In 20   - Output Enable
 *
 * Out 0   - Data out 0
 * Out 1   - Data out 1
 * ...
 * Out 15  - Data out 15
 * @end_pinout
 */
class DCSRegister16BitsWithEnable : public DCSComponent
{
private:
    DCSComponentArray<DCSRegister1BitWithEnable> registerArray;
    DCSComponentArray<DCSNode> nodeArray;

public:
    DCSRegister16BitsWithEnable(std::string name);

    DCSComponent* getOutComponent(uint16_t outPinNum) override;
    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    void updateOut() override;
};

#if TEST == 1
void register16BitsWithEnableTest();
#endif

#endif /* DCSRegister16BitsWithEnable_hpp */
