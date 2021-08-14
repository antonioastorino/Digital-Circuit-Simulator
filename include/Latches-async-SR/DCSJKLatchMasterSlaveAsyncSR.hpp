#ifndef DCSJKLatchMasterSlaveAsyncSR_hpp
#define DCSJKLatchMasterSlaveAsyncSR_hpp
#include "DCSAnd.hpp"
#include "DCSAnd3.hpp"
#include "DCSCommon.hpp"
#include "DCSNode.hpp"
#include "DCSNor3.hpp"
#include "DCSNot.hpp"

/**
 * @class DCSJKLatchMasterSlaveAsyncSR
 * J-K Latch Master-Slave with asynchronous reset.
 * IMPORTANT: the input value is read when the clock is low.
 * Inputs 0 (J) and 1 (K) must be stable for at least 1 tau before and 1 tau after the clock rising
 * edge.
 * The output is read 4 tau after the rising edge of the clock. Inputs 3 (Clear) and 4 (Preset) must
 * be stable at least 3 tau for the reset to have effect (after 3 tau)
 *
 * @diagram
 *|      |   __
 *| J:   | XX  XXXXXXXX
 *|      |   ^ start
 *|      |   __
 *| K:   | XX  XXXXXXXX
 *|      |    __
 *| CLK: | X__  \\\\\\  go down any time 2 tau after rising edge
 *|      |    ^ stored
 *|      |        _____
 *| Q:   | _______
 *|      | ______
 *|!Q:   |       ______
 *|      |        ^ ready
 * @end_diagram
 */
class DCSJKLatchMasterSlaveAsyncSR : public DCSComponent
{
private:
    DCSNot not0    = DCSNot(name + "-CLK");
    DCSNode node0  = DCSNode(name + "-Node1");
    DCSNode node1  = DCSNode(name + "-Node2");
    DCSAnd3 and3_0 = DCSAnd3(name + "-And3_0");
    DCSAnd3 and3_1 = DCSAnd3(name + "-And3_1");
    DCSNot not1    = DCSNot(name + "-Not1");
    DCSAnd and0    = DCSAnd(name + "-And0");
    DCSAnd and1    = DCSAnd(name + "-And1");
    DCSNor3 nor3_0 = DCSNor3(name + "-Master !Q");
    DCSNor3 nor3_1 = DCSNor3(name + "-Master Q");
    DCSNor3 nor3_2 = DCSNor3(name + "-Q");
    DCSNor3 nor3_3 = DCSNor3(name + "-!Q");

public:
    DCSJKLatchMasterSlaveAsyncSR(std::string name);

    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    DCSComponent* getOutComponent(uint16_t outPinNum) override;

    void updateOut() override;
};

#if TEST == 1
void jkLatchMasterSlaveAsyncSRTest();
#endif

#endif /* DCSJKLatchMasterSlaveAsyncSR_hpp */
