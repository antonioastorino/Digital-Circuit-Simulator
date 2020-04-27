#ifndef DCSRegister1Bit_hpp
#define DCSRegister1Bit_hpp
#include "DCSDFlipFlopAsyncSR.hpp"
#include "DCSOr.hpp"
#include "DCSTriStateBuffer.hpp"

class DCSNode;

/**
 * @class DCSRegister1Bit
 * Input 4 (load) must be asserted at least 3 tau before the clock falling edge.
 * Input 0 (Data) must be stable at least 2 tau before the clock falling edge.
 * Both have to be stable for at least 1 tau after the clock falling edge.
 * Inputs 2 (clear) and 3 (preset) work the same as in the SR latch. Use them with input 4 low.
 * Here is an example:
 *       |  ____
 * LOAD: | X    XXXXXXXX
 *       |  ^ start
 *       |   ___
 * DATA: | XX   XXXXXXXX
 *       | ____  _______
 * CLK:  |     __
 *       |          ____
 * Q:    | _________
 *       | ________
 *!Q:    |         _____
 *                  ^ ready
 *
 * PINOUT
 * Input 0: Output Enable
 * Input 1: Clock
 * Input 2: Clear
 * Input 3: Preset
 * Input 4: Load
 * Input 5: Data in
 * Out   0: Data out
 */
class DCSRegister1Bit : public DCSComponent {
private:
    DCSNode node0;
    DCSNot not0;
    DCSAnd and0;
    DCSAnd and1;
    DCSOr or0;
    DCSTriStateBuffer tris0;
    DCSDFlipFlopAsyncSR dffsr0;

public:
    DCSRegister1Bit(std::string name);

    DCSComponent* getOutComponent(uint16_t outPinNum) override;
    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    void updateOut() override;
};
#endif /* DCSRegister1Bit_hpp */
