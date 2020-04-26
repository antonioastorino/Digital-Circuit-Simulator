#ifndef DCSArbitrarySignal_hpp
#define DCSArbitrarySignal_hpp
#include <vector>
typedef std::vector<uint64_t> binary_signal;

/**
 * @class DCSArbitrarySignal
 * Generates a binary signal for use as input signal
 * @param levelDurationVector	contains a vector of values corresponding to duration of each
 * logical level.
 * @param synch					selects the units for each logic level duration
 * The units for the levels are:
 * - tau            if synch = 0
 * - clockPeriods   if synch = 1
 */
class DCSArbitrarySignal {
private:
    uint64_t leveNumber;
    size_t totalDuration;
    std::vector<uint64_t> flipBitAtSteps; // stores the time at witch the level needs to change
    void fromLevelsToFlipBitAtSteps(std::vector<uint64_t> levelDurationVector, bool synch);

protected:
    uint64_t counter;
    bool currVal;

public:
    DCSArbitrarySignal() = delete;
    DCSArbitrarySignal(std::vector<uint64_t> levelDurationVector, bool initVal = 0,
                       bool synch = false);
    DCSArbitrarySignal(std::string zerosAndOnes, bool synch = false);
    virtual bool getVal(uint32_t step);
    virtual ~DCSArbitrarySignal();
};

#endif /* DCSArbitrarySignal_hpp */
