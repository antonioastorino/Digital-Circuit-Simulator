/*
 PINOUT
 IN  0 - A
 IN  1 - B
 IN  2 - Carry in

 OUT 0 - Sum
 OUT 1 - Carry out
 */

#ifndef DCSFullAdder_hpp
#define DCSFullAdder_hpp
#include "DCSAnd.hpp"
#include "DCSNode.hpp"
#include "DCSOr.hpp"
#include "DCSXor.hpp"

class DCSFullAdder : public DCSComponent {
private:
    DCSNode node0;
    DCSNode node1;
    DCSNode node2;
    DCSXor xor0;
    DCSXor xor1;
    DCSAnd and0;
    DCSAnd and1;
    DCSOr or0;

public:
    DCSFullAdder(std::string name);
    ~DCSFullAdder();

    DCSComponent* getOutComponent(uint16_t outPinNum) override;
    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    virtual void updateOut() override;
};

#endif /* DCSFullAdder_hpp */
