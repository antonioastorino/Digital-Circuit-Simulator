#ifndef DCSAddressDecoder8Bits_hpp
#define DCSAddressDecoder8Bits_hpp
#include "DCSCommon.hpp"
#include "DCSComponentArray.hpp"
class DCSNode;
class DCSUnitDelay;
class DCSNot;
class DCSAnd8;

/**
 * @class DCSAddressDecoder8Bits
 * Address decoder with an 8-bit input and 256-bit output.
 *
 * @pinout
 * In 0    - Address 0
 * In 1    - Address 1
 * ...
 * In 7    - Address 7
 *
 * Out 0   - Decoded in 0 (asserted only when the input is 00000000)
 * Out 1   - Decoded in 1 (asserted only when the input is 00000001)
 * ...
 * Out 255 - Decoded in 255 (asserted only when the input is 11111111)
 * @end_pinout
 */
class DCSAddressDecoder8Bits : public DCSComponent
{
private:
    DCSComponentArray<DCSNode> m_nodeArray;
    DCSComponentArray<DCSNot> m_notArray;
    DCSComponentArray<DCSUnitDelay> m_delArray;
    DCSComponentArray<DCSAnd8> m_and8Array;

public:
    DCSAddressDecoder8Bits(std::string name);

    DCSComponent* getOutComponent(uint16_t outPinNum) override;
    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    void updateOut() override;
};

#if TEST == 1
void addressDecoder8BitsTest();
#endif

#endif /* DCSAddressDecoder8Bits_hpp */
