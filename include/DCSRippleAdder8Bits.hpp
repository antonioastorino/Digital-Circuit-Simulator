#ifndef DCSRippleAdder8Bits_hpp
#define DCSRippleAdder8Bits_hpp
#include "DCSComponentArray.hpp"
class DCSFullAdder;

class DCSRippleAdder8Bits : public DCSComponent {
private:
    DCSComponentArray<DCSFullAdder> faArray;

public:
    DCSRippleAdder8Bits(std::string name);

    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    DCSComponent* getOutComponent(uint16_t outPinNum) override;

    void updateOut() override;
};

#endif /* DCSRippleAdder8Bits_hpp */
