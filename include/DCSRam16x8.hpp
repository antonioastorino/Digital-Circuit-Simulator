#ifndef DCSRam16x8_hpp
#define DCSRam16x8_hpp
#include "DCSAddressDecoder4Bits.hpp"

class DCSNode;
class DCSRegister8BitsWithEnable;
class DCSAnd;
/**
 * @class DCSRam16x8
 * Ram module of 16 bytes.
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
 * In 8    - Address 0
 * In 9    - Address 1
 * In 10   - Address 2
 * In 11   - Address 3
 * In 12   - Clock
 * In 13   - Clear
 * In 14   - Preset
 * In 15   - Write
 * In 16   - Output enable
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
 *
 * @diagram
 *|       |  ___
 *| ADDR: | X___XXXXXXXX
 *|       |  ^ start
 *|       |   ____
 *| WRITE:| XX    XXXXXX
 *|       |    ___
 *| DATA: | XXX   XXXXX
 *|       | ______  ____
 *| CLK:  |       __
 *|       |         ^ ready
 * @end_diagram
 *
 * `Address` changes, the output changes after `3 tau`, independently of the `Clock`. Since `Load`
 *of each individual register (here called `Write`) is AND'ed with the address decoder, compared to
 *a single register, the RAM needs `Address` to be ready `3 tau` before `Load` is asserted.
 */
class DCSRam16x8 : public DCSComponent {
private:
    DCSComponentArray<DCSRegister8BitsWithEnable> regArray;
    DCSComponentArray<DCSAnd> andArray0;
    DCSComponentArray<DCSAnd> andArray1;
    DCSComponentArray<DCSNode> ctrlNodeArray;
    DCSComponentArray<DCSNode> dataNodeArray;
    DCSComponentArray<DCSNode> outNodeArray;
    DCSComponentArray<DCSUnitDelay> delArray;
    DCSAddressDecoder4Bits dec0;

public:
    DCSRam16x8(std::string name);

    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    DCSComponent* getOutComponent(uint16_t outPinNum) override;

    void updateOut() override;
    void disconnect();
};

#endif /* DCSRam16x8_hpp */
