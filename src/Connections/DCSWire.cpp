#include "DCSWire.hpp"
#include "DCSLog.hpp"

DCSWire::DCSWire(DCSComponent* from, DCSComponent* to, uint16_t inPinNum, std::string probeName)
    : from(from), to(to), inPinNum(inPinNum), probeName(probeName)
{
#if LOG_LEVEL > 1
    std::stringstream s;
    s << from->getName() << " --> " << to->getName() << " in " << inPinNum;
    DCSLog::info("", s.str());
#endif
}

std::string DCSWire::getProbeName() { return probeName; };

bool DCSWire::fromNode() { return from->isNode(); }

bool DCSWire::propagateValue()
{
    bool propagated = true;
    if (from->isEnabled())
    { // Check if a component is in high-Z state
        bool outVal = from->getOutput();
        if (to->updatedByVector[inPinNum] != nullptr)
        { // If already reached
            if (to->updatedByVector[inPinNum] != from)
            {
                DCSLog::error(to->getName(), 14); // Conflict on the bus among tristate buffers
            }
            propagated = false;
        }
        to->setIn(outVal, inPinNum);
        to->updatedByVector[inPinNum] = from;
#if LOG_LEVEL > 2
        std::stringstream message;
        message << "Sending " << outVal << " to " << to->getName() << " in " << inPinNum;
        DCSLog::debug(from->getName(), message.str());
#endif
    }
    return propagated;
}

bool DCSWire::getOutVal() { return from->getOutput(); }
