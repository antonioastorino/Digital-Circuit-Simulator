#ifndef DCSAnd4_hpp
#define DCSAnd4_hpp
#include "DCSComponent.hpp"

/**
 * @class DCSAnd4
 * AND gate with 4 inputs
 */
class DCSAnd4: public DCSComponent {
public:
	DCSAnd4(std::string name);
	
	void updateOut() override;
};

#endif /* DCSAnd4_hpp */
