#ifndef DCSUnitDelay_hpp
#define DCSUnitDelay_hpp
#include "DCSCommon.hpp"
#include "DCSComponent.hpp"

class DCSUnitDelay : public DCSComponent
{
public:
    DCSUnitDelay(std::string name);

    void updateOut() override;
};

#if TEST == 1
void unitDelayTest();
#endif

#endif /* DCSUnitDelay_hpp */
