/*
 PINOUT:
 INPUT 0: Output enable
 INPUT 1-8: Data input
 OUTPUT 0-7: Data out
 */

#ifndef DCSTriStateBuffer8Bits_hpp
#define DCSTriStateBuffer8Bits_hpp
#include "DCSComponentArray.hpp"
#include "DCSNode.hpp"
#include "DCSTriStateBuffer.hpp"

class DCSTriStateBuffer8Bits : public DCSComponent {
private:
    DCSComponentArray<DCSTriStateBuffer> bufferArray;
    DCSNode node0;

public:
    DCSTriStateBuffer8Bits(std::string name);

    DCSComponent* getOutComponent(uint16_t outPinNum) override;
    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    void updateOut() override;

    void enable() override;
    void disable() override;
};

#endif /* DCSTriStateBuffer8Bits_hpp */
