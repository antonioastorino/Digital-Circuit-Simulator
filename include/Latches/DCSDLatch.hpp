#ifndef DCSDLatch_hpp
#define DCSDLatch_hpp
#include "DCSAnd.hpp"
#include "DCSCommon.hpp"
#include "DCSNode.hpp"
#include "DCSNot.hpp"
#include "DCSSRLatch.hpp"
#include "DCSUnitDelay.hpp"

/**
 * @class DCSDLatch
 * D Latch
 *
 * @pinout
 * In 0  - Data in
 * In 1  - Enable
 * Out 0 - Q
 * Out 1 - !Q
 * @end_pinout
 *
 * @diagram
 *|       |  ___
 *| DATA: | X___XXXXXXXX
 *|       |  ^ start
 *|       |   __
 *| EN:   | __  ________
 *|       |
 *|       |     ________
 *| Q:    | XXXX________
 *|       |      _______
 *| !Q:   | XXXXX_______
 *|       |      ^ ready
 * @end_diagram
 *
 * `Data in` needs to be ready at least `1 tau` before `Enable` is asserted.
 * `Data` and `Enable` must be stable for at least 2 tau.
 * The output is stable after 4 tau from the change in the input.
 */
class DCSDLatch : public DCSComponent
{
private:
    DCSSRLatch srLatch0 = DCSSRLatch(name + "-SR0");
    DCSAnd and0         = DCSAnd(name + "-And0");
    DCSAnd and1         = DCSAnd(name + "-And1");
    DCSNot not0         = DCSNot(name + "-Not0");
    DCSUnitDelay del0   = DCSUnitDelay(name + "-Del0");
    DCSNode node0       = DCSNode(name + "-Node0");
    DCSNode node1       = DCSNode(name + "-Node1");

public:
    DCSDLatch(std::string name);

    DCSComponent* getOutComponent(uint16_t outPinNum) override;
    DCSComponent* getInComponent(uint16_t& inPinNum) override;

    void updateOut() override;
};

#if TEST == 1
void dLatchTest();
#endif

#endif /* DCSDLatch_hpp */
