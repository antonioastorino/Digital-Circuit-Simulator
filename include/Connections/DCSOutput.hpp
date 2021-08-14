#ifndef DCSOutput_hpp
#define DCSOutput_hpp
#include "DCSComponent.hpp"

/**
 * @class DCSOutput
 * This component has no logical functions but is used to connect any floating output.
 * Unconnected outputs generate errors!
 * Also, by naming the used instance of this class, the connected input is probed and hence it can
 * be displayed.
 */
class DCSOutput : public DCSComponent
{
public:
    DCSOutput(std::string name);
    void updateOut() override{};
};

#endif /* DCSOutput_hpp */
