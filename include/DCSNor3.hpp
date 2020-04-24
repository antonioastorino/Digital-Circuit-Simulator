//
//  DCSNor3.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 13/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSNor3_hpp
#define DCSNor3_hpp
#include "DCSComponent.hpp"

class DCSNor3: public DCSComponent {
public:
	DCSNor3(std::string name);
	
	void updateOut() override;
};

#endif /* DCSNor3_hpp */
