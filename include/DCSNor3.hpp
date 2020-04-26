#ifndef DCSNor3_hpp
#define DCSNor3_hpp
#include "DCSComponent.hpp"

/**
 * @class DCSNor3
 * Implements the NOR gate with 3 inputs
 */
class DCSNor3: public DCSComponent {
public:
	DCSNor3(std::string name);
	
	void updateOut() override;
};

#endif /* DCSNor3_hpp */
