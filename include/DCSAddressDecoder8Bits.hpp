#ifndef DCSAddressDecoder8Bits_hpp
#define DCSAddressDecoder8Bits_hpp
#include "DCSComponentArray.hpp"
class DCSNode;
class DCSUnitDelay;
class DCSNot;
class DCSAnd8;

class DCSAddressDecoder8Bits : public DCSComponent {
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

#endif /* DCSAddressDecoder8Bits_hpp */
