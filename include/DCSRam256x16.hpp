#ifndef DCSRam256x16_hpp
#define DCSRam256x16_hpp
#include "DCSAddressDecoder8Bits.hpp"
#include "DCSCommon.hpp"

class DCSNode;
class DCSRegister16BitsWithEnable;
class DCSAnd;
/**
 * @class DCSRam256x16
 * Ram module of 16 bytes.
 *
 * @pinout
 * In 0    - Data in 0
 * In 1    - Data in 1
 * ...
 * In 15   - Data in 15
 * In 16   - Address 0
 * In 17   - Address 1
 * ...
 * In 23   - Address 8
 * In 24   - Clock
 * In 25   - Clear
 * In 26   - Preset
 * In 27   - Write
 * In 28   - Output enable
 *
 * Out 0   - Data out 0
 * Out 1   - Data out 1
 * ...
 * Out 15  - Data out 15
 * @end_pinout
 *
 * @diagram
 *|       |  ____
 *| ADDR: | X____XXXXXXXX
 *|       |  ^ start
 *|       |    ____
 *| WRITE:| XXX    XXXXXX
 *|       |     ___
 *| DATA: | XXXX   XXXXX
 *|       | _______  ____
 *| CLK:  |        __
 *|       |          ^ ready
 * @end_diagram
 *
 * The time diagram is similar to that of Ram16x8. The only difference is in the that `Address`
 *needs to be prepared `1 tau` earlier because the internal address decoder introduces an extra
 *`1-tau` delay due to the presence of 8-bit AND gates. The smaller ram's address decoder was using
 *4-bit AND gates, instead.
 */
class DCSRam256x16 : public DCSComponent {
private:
    DCSComponentArray<DCSRegister16BitsWithEnable> regArray;
    DCSComponentArray<DCSAnd> andArray0;
    DCSComponentArray<DCSAnd> andArray1;
    DCSComponentArray<DCSNode> ctrlNodeArray;
    DCSComponentArray<DCSNode> dataNodeArray;
    DCSComponentArray<DCSNode> outNodeArray;
    DCSComponentArray<DCSUnitDelay> delArray;
    DCSAddressDecoder8Bits dec0;

public:
    DCSRam256x16(std::string name);

    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    DCSComponent* getOutComponent(uint16_t outPinNum) override;

    void updateOut() override;
    void disconnect();
};

#if TEST == 1
void ram256x16Test();
#endif

#endif /* DCSRam256x16_hpp */
