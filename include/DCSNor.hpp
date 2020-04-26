#ifndef DCSNor_hpp
#define DCSNor_hpp
#include "DCSComponent.hpp"

/**
 * @class DCSNor
 * Implements the NOR gate
 */
class DCSNor: public DCSComponent {
public:
	DCSNor(std::string name);
	
	void updateOut() override;
};
#endif /* DCSNor_hpp */