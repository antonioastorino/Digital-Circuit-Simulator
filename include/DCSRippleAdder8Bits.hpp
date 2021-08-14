#ifndef DCSRippleAdder8Bits_hpp
#define DCSRippleAdder8Bits_hpp
#include "DCSCommon.hpp"
#include "DCSComponentArray.hpp"

class DCSFullAdder;

/**
 * @class DCSRippleAdder8Bits
 *
 * 8-bit ripple adder
 *
 * @pinout
 * In 0   - A 0
 * In 1   - A 1
 * In 2   - A 2
 * In 3   - A 3
 * In 4   - A 4
 * In 5   - A 5
 * In 6   - A 6
 * In 7   - A 7
 * In 8   - B 0
 * In 9   - B 1
 * In 10  - B 2
 * In 11  - B 3
 * In 12  - B 4
 * In 13  - B 5
 * In 14  - B 6
 * In 15  - B 7
 * In 16  - Carry in
 *
 * Out 0  - Sum 0
 * Out 1  - Sum 1
 * Out 2  - Sum 2
 * Out 3  - Sum 3
 * Out 4  - Sum 4
 * Out 5  - Sum 5
 * Out 6  - Sum 6
 * Out 7  - Sum 7
 * @end_pinout
 */

class DCSRippleAdder8Bits : public DCSComponent
{
private:
    DCSComponentArray<DCSFullAdder> faArray;

public:
    DCSRippleAdder8Bits(std::string name);

    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    DCSComponent* getOutComponent(uint16_t outPinNum) override;

    void updateOut() override;
};

#if TEST == 1
void rippleAdderTest();
#endif

#endif /* DCSRippleAdder8Bits_hpp */
