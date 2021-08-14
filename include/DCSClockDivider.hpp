#ifndef DCSClockDivider_hpp
#define DCSClockDivider_hpp
#include "DCSCommon.hpp"
#include "DCSComponent.hpp"
#include "DCSJKLatchMasterSlaveAsyncSR.hpp"
#include "DCSNode.hpp"
#include "DCSOr.hpp"
/**
 * @class DCSClockDivider
 * This clock divider (by 2) is mainly meant to be used as a building block for counters.
 * The minimum clock period is 10 (5 high + 5 low) taus.
 *
 * `Data in` and `Load` must be stable for at least `4 tau` before and `1 tau` after `Clock`'s
 * rising edge. The resulting output is displayed `5 tau` after that rising edge.
 * `Clear` and `Preset` are directly connected to the internal JK master-slave. They must
 * be stable for at least `3 tau` and their effect is visible `3 tau` after they are set.
 * `Count in` asserts both `J` and `K` in the internal latch with a delay of `2 tau`. Therefore,
 * it has to remain stable from `3 tau` to `1 tau` before `Clock`'s rising edge while `Load` is low.
 *
 * `Count out` is high when `Count in` and `Data out` are high, with a delay of `1 tau`. When
 * connecting several dividers in cascade, this delay is multiplied by the number of dividers. This
 * has to be taken into account when choosing the clock speed.
 *
 * @pinout
 * In 0  - Data in
 * In 1  - Load
 * In 2  - Clock
 * In 3  - Clear
 * In 4  - Preset
 * In 5  - Count in
 *
 * Out 0 - Data out
 * Out 1 - !Data out
 * Out 2 - Count out
 * @end_pinout
 */

class DCSClockDivider : public DCSComponent
{
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

#if TEST == 1
void dividerTest();
#endif

#endif /* DCSClockDivider_hpp */
