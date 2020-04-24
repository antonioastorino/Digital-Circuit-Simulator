//
//  DCSAnd3.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 14/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSAnd3_hpp
#define DCSAnd3_hpp
#include "DCSComponent.hpp"

class DCSAnd3: public DCSComponent {
public:
	DCSAnd3(std::string name);
	
	void updateOut() override;
};

#endif /* DCSAnd3_hpp */
