#ifndef DCSAddressDecoder4Bits_hpp
#define DCSAddressDecoder4Bits_hpp
#include "DCSCommon.hpp"
#include "DCSComponentArray.hpp"
class DCSNode;
class DCSUnitDelay;
class DCSNot;
class DCSAnd4;

/**
 * @class DCSAddressDecoder4Bits
 * Address decoder with a 4-bit input and 256-bit output.
 *
 * @pinout
 * In 0    - Address 0
 * In 1    - Address 1
 * In 2    - Address 2
 * In 3    - Address 3
 *
 * Out 0   - Decoded in 0 (asserted only when the input is 0000)
 * Out 1   - Decoded in 1 (asserted only when the input is 0001)
 * ...
 * Out 16  - Decoded in 16 (asserted only when the input is 1111)
 * @end_pinout
 */
class DCSAddressDecoder4Bits : public DCSComponent
{
private:
    DCSComponentArray<DCSNode> nodeArray;
    DCSComponentArray<DCSNot> notArray;
    DCSComponentArray<DCSUnitDelay> delArray;
    DCSComponentArray<DCSAnd4> and4Array;

public:
    DCSAddressDecoder4Bits(std::string name);

    DCSComponent* getOutComponent(uint16_t outPinNum) override;
    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    void updateOut() override;
};

#if TEST == 1
void addressDecoderTest4Bits();
#endif

#endif /* DCSAddressDecoder4Bits_hpp */
