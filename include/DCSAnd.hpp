#ifndef DCSAnd_hpp
#define DCSAnd_hpp
#include "DCSCommon.hpp"
#include "DCSComponent.hpp"

/**
 * @class DCSAnd
 * AND gate
 */
class DCSAnd : public DCSComponent
{
public:
    DCSAnd(std::string name);

    void updateOut() override;
};

#endif /* DCSAnd_hpp */
