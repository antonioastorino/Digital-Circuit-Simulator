#ifndef DCSArbitrarySignal_hpp
#define DCSArbitrarySignal_hpp
#include <vector>
#include <string>
typedef std::vector<uint64_t> transitions;

/**
 * @class DCSArbitrarySignal
 * Generates a binary signal for use as input signal. Instances of this class are created by
 * DCSClockSignal and DCSInput classes. The user should not use this class directly.
 */
class DCSArbitrarySignal {
private:
    uint64_t leveNumber;
    size_t totalDuration;
    std::vector<uint64_t> flipBitAtSteps; // stores the time at witch the level needs to change
protected:
    uint64_t m_counter;

private:
    void fromLevelsToFlipBitAtSteps(std::vector<uint64_t> levelDurationVector, bool synch);

protected:
    DCSArbitrarySignal(std::vector<uint64_t> levelDurationVector, bool initVal = 0,
                       bool synch = false);
    DCSArbitrarySignal(std::string zerosAndOnes, bool synch = false);

    bool currVal;

public:
    DCSArbitrarySignal() = delete;

    virtual bool getVal(uint32_t step);
    void resetCounter();
    virtual ~DCSArbitrarySignal();

    friend class DCSInput;
};

#endif /* DCSArbitrarySignal_hpp */
