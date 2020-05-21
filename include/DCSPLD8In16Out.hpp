#ifndef DCSPLD8In16Out_hpp
#define DCSPLD8In16Out_hpp

#include "DCSAddressDecoder8Bits.hpp"
#include "DCSComponent.hpp"
#include "DCSComponentArray.hpp"
#include "DCSOr.hpp"
#include "DCSInput.hpp"

class DCSPLD8In16Out : public DCSComponent {
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
