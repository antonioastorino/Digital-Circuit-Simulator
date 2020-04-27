#ifndef DCSClockDivider_hpp
#define DCSClockDivider_hpp
#include "DCSComponent.hpp"
#include "DCSJKLatchMasterSlaveAsyncSR.hpp"
#include "DCSNode.hpp"
#include "DCSOr.hpp"
/**
 * @class DCSClockDivider
 * This clock divider (by 2) is mainly meant to be used as a building block for counters.
 * The minimum clock period is 10 (5 high + 5 low) taus.
 *
 * Inputs 0 (Data) and 1 (Load) must be stable for at least 4 taus before and 1 tau after the clock
 * rising edge. The resulting output is displayed 5 taus after the rising edge.
 * Inputs 3 (Clear) and 4 (Preset) are directly connected to the internal JK master-slave. They must
 * be stable for at least 3 taus and their effect is visible 3 taus after they are set.
 * Input 5 (Count in) asserts both J and K in the internal latch with a delay of 2 taus. Therefore,
 * it has to remain stable from 3 taus to 1 taus before the clock rising edge while Load is low.
 * 
 * Output 2 (Count out) is high when input 5 and out 0 are high, with a delay of 1 tau. When
 * connecting several dividers in cascade, this delay is multiplied by the number of dividers. This
 * has to be taken into account when choosing the clock speed.
 */
class DCSClockDivider : public DCSComponent {
private:
    DCSNode node0                    = DCSNode(name + "-Data");
    DCSNode node1                    = DCSNode(name + "-Load");
    DCSNode node2                    = DCSNode(name + "-C_in");
    DCSNot not0                      = DCSNot(name + "-Not0");
    DCSNot not1                      = DCSNot(name + "-Not1");
    DCSAnd and0                      = DCSAnd(name + "-And0");
    DCSAnd and1                      = DCSAnd(name + "-And1");
    DCSAnd and2                      = DCSAnd(name + "-And2");
    DCSAnd and3                      = DCSAnd(name + "-C_out");
    DCSOr or0                        = DCSOr(name + "-Or0");
    DCSOr or1                        = DCSOr(name + "-Or1");
    DCSJKLatchMasterSlaveAsyncSR jk0 = DCSJKLatchMasterSlaveAsyncSR(name + "-JK0");

public:
    DCSClockDivider(std::string name);

    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    DCSComponent* getOutComponent(uint16_t outPinNum) override;

    void updateOut() override;
};

#endif /* DCSClockDivider_hpp */
