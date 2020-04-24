//
//  DCSOr.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 13/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSOr_hpp
#define DCSOr_hpp
#include "DCSComponent.hpp"

class DCSOr: public DCSComponent {
public:
	DCSOr(std::string name);
	
	void updateOut() override;
};
#endif /* DCSOr_hpp */
