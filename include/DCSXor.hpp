#ifndef DCSXor_hpp
#define DCSXor_hpp
#include "DCSComponent.hpp"

class DCSXor: public DCSComponent {
public:
	DCSXor(std::string name);
	
	void updateOut() override;
};

#endif /* DCSXor_hpp */
