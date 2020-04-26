#ifndef DCSUnitDelay_hpp
#define DCSUnitDelay_hpp
#include "DCSComponent.hpp"

class DCSUnitDelay: public DCSComponent {
public:
	DCSUnitDelay(std::string name);
	
	void updateOut() override;
};


#endif /* DCSUnitDelay_hpp */
