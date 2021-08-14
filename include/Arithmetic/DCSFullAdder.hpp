
#ifndef DCSFullAdder_hpp
#define DCSFullAdder_hpp
#include "DCSAnd.hpp"
#include "DCSCommon.hpp"
#include "DCSNode.hpp"
#include "DCSOr.hpp"
#include "DCSXor.hpp"

/**
 * @class DCSFullAdder
 * Full adder.
 *
 * @pinout
 * In  0 - A
 * In  1 - B
 * In  2 - Carry in
 *
 * Out 0 - Sum
 * Out 1 - Carry out
 * @end_pinout
 */
class DCSFullAdder : public DCSComponent
{
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

#if TEST == 1
void fullAdderTest();
#endif

#endif /* DCSFullAdder_hpp */
