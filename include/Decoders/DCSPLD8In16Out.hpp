#ifndef DCSPLD8In16Out_hpp
#define DCSPLD8In16Out_hpp

#include "DCSAddressDecoder8Bits.hpp"
#include "DCSComponent.hpp"
#include "DCSComponentArray.hpp"
#include "DCSInput.hpp"
#include "DCSOr.hpp"

/**
 * @class DCSPLD8In16Out
 * This class implements a Programmable Logic Device (PLD) equivalent to `DCSRam256x16` but, once
 * programmed, it becomes read-only. Programming a `DCSPLD8In16Out` is done by its initializer,
 * which requires the configuration data to be passed as an argument. The advantage of using this
 * class in place of a RAM is that it much faster (the number of logic gates in a RAM is about 75
 * times that of this PLD). Therefore, the computation time is substantially reduced when using this
 * PLD. Also, there is no control logic involved, which makes its use much simpler than a RAM.
 *
 * @pinout
 * In 0  - Address 0
 * In 1  - Address 1
 * ...
 * In 7  - Address 7
 *
 * Out 0 - Data out 0
 * Out 1 - Data out 1
 * ...
 * Out 15 - Data out 15
 * @end_pinout
 */

class DCSPLD8In16Out : public DCSComponent
{
private:
    // PLD
    DCSAddressDecoder8Bits dec0;
    DCSComponentArray<DCSOr>* orArr0[16];
    DCSComponentArray<DCSOr>* orArr1[16];
    DCSComponentArray<DCSOr>* orArr2[16];
    DCSComponentArray<DCSOr>* orArr3[16];
    DCSComponentArray<DCSOr>* orArr4[16];
    DCSComponentArray<DCSOr>* orArr5[16];
    DCSComponentArray<DCSOr>* orArr6[16];
    DCSOr* or7[16];
    DCSInput inGND;

public:
    DCSPLD8In16Out(std::string name, const uint16_t data[32][8]);
    ~DCSPLD8In16Out();

    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    DCSComponent* getOutComponent(uint16_t outPinNum) override;

    void updateOut() override;
};

#endif /* DCSPLD8In16Out_hpp */
