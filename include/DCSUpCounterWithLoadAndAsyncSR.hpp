#ifndef DCSUpCounterWithLoadAndAsyncSR_hpp
#define DCSUpCounterWithLoadAndAsyncSR_hpp
#include "DCSClockDivider.hpp"
#include "DCSComponentArray.hpp"

/**
 * @class DCSUpCounterWithLoadAndAsyncSR
 * N-bit up-counter (N defined upon instantiation) with synchronous load and asynchronous clear and reset.
 * Internally, there are N clock dividers in cascade.
 * 
 * @pinout
 * In 0         - Count enable
 * In 1         - Load  - node arrray with index 0
 * In 2         - Clock - node arrray with index 1
 * In 3         - Clear - node arrray with index 2
 * In 4         - Preset - node arrray with index 3
 * In 5         - Bit 0
 * In 6         - Bit 1
 * ...
 * In 5 + N-1   - Bit N-1;
 * 
 * Out 0         - Bit 0
 * Out 1         - Bit 1
 * ...
 * Out N-1       - Bit N-1
 * Out N         - Count out
 * @end_pinout
 * 
 * @table
 *| LD | CE | CLK | Function
 *|----|:-----|:----|:--------
 *|  0 |   0  | X   |  Pause
 *|  0 |   1  | _/  |  Count
 *|  1 |   X  | _/  |  Load
 * @end_table
 * 
 * `Cout in` follows the rule of input 5 of the first divider. Therefore, it hast to be set
 * from `3` to `1 tau` before the clock rising edge. However, every `Count in` in the subsequent dividers
 * is delayed by `1 tau`. In addition, the output byte of the counter is ready `5 tau` after the clock
 * rising edge. As a consequence, supposing that the expected output is all 1's, the last `Count in`
 * will be ready `5+N-1 tau` after the clock rising edge and has to be ready `3 tau` before
 * the next clock rising edge. Therefore, the clock period has to be at least `5+N-1+3 = 7+N tau`.
 */
class DCSUpCounterWithLoadAndAsyncSR : public DCSComponent {
private:
    DCSComponentArray<DCSClockDivider> dividerArray;
    DCSComponentArray<DCSNode> nodeArray; // inputs shared among dividers
    uint16_t numOfBits;

public:
    DCSUpCounterWithLoadAndAsyncSR(std::string name, uint16_t numBits);

    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    DCSComponent* getOutComponent(uint16_t outPinNum) override;

    void updateOut() override;
};

#endif /* DCSUpCounterWithLoadAndAsyncSR_hpp */


