#ifndef DCSRam16x8_hpp
#define DCSRam16x8_hpp
#include "DCSAddressDecoder4Bits.hpp"

class DCSNode;
class DCSRegister8Bits;
class DCSAnd;
/**
 * @class DCSRam16x8
 * Implements a Ram module of 16 bytes.
 * When inputs 13 to 16 (address) change, the output changes after 3 tau, independently of the
 * clock. Since the Load signal of each individual register (here called Write - input 4) is AND'ed
 * with the address decoder, compared to a single register, the RAM needs the address to be ready 3
 * taus before the Load of each address.
 *
 * The write sequence is
 *       |  ___
 * ADDR: | X___XXXXXXXX
 *       |  ^ start
 *       |   ____
 * WRITE:| XX    XXXXXX
 *       |     ___
 * DATA: | XXXX   XXXXX
 *       | ______  ____
 * CLK:  |       __
 *
 * Input 0: Output enable
 * Input 1: Clock
 * Input 2: Clear
 * Input 3: Preset
 * Input 4: Write
 * Input 5: Data in bit 0
 * Input 6: Data in bit 1
 * ...
 * Input 12: Data in bit 7
 *
 * Input 13: Address bit 0
 * Input 14: Address bit 1
 * Input 15: Address bit 2
 * Input 16: Address bit 3
 *
 * Out   0: Data out bit 0
 * Out   1: Data out bit 1
 * ...
 */
class DCSRam16x8 : public DCSComponent {
private:
    DCSComponentArray<DCSRegister8Bits> regArray;
    DCSComponentArray<DCSAnd> andArray0;
    DCSComponentArray<DCSAnd> andArray1;
    DCSComponentArray<DCSNode> ctrlNodeArray;
    DCSComponentArray<DCSNode> dataNodeArray;
    DCSComponentArray<DCSNode> outNodeArray;
    DCSAddressDecoder4Bits dec0;

public:
    DCSRam16x8(std::string name);

    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    DCSComponent* getOutComponent(uint16_t outPinNum) override;

    void updateOut() override;
};

#endif /* DCSRam16x8_hpp */
