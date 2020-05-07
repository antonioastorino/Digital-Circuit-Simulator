#ifndef DCSOr_hpp
#define DCSOr_hpp
#include "DCSComponent.hpp"
/**
 * @class DCSOr
 * OR gate
 */
class DCSOr: public DCSComponent {
public:
	DCSOr(std::string name);
	
	void updateOut() override;
};
#endif /* DCSOr_hpp */
