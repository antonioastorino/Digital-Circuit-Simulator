//
//  DCSNand3.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 13/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSNand3_hpp
#define DCSNand3_hpp
#include "DCSComponent.hpp"

class DCSNand3: public DCSComponent {
public:
	DCSNand3(std::string name);
	
	void updateOut() override;
};

#endif /* DCSNand3_hpp */
