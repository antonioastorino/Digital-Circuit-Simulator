
#include "DCSClockSignal.hpp"
#include "DCSArbitrarySignal.hpp"
#include "DCSEngine.hpp"

DCSClockSignal::DCSClockSignal(uint16_t halfPeriod, bool initVal)
    : DCSArbitrarySignal(transitions{0})
{
    currVal = initVal;
    if (halfPeriod)
        this->halfPeriod = halfPeriod;
    else
        this->halfPeriod = DCSEngine::getClockPeriod() / 2;
}

bool DCSClockSignal::getVal(uint32_t step)
{
    if (step != m_counter)
    {
        DCSLog::error("Clock signal", 12);
    }
    m_counter++;
    // Shift the commutation by 1 tau because the first one is used to initialize the system
    if (step > 1)
    { // don't change at first step
        if (step % (halfPeriod) == 1 || halfPeriod == 1)
        {
            currVal = !currVal;
        }
    }
    return currVal;
}
