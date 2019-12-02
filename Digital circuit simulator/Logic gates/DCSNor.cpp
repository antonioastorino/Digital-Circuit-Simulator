//
//  DCSNor.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 26/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSNor.hpp"


DCSNor::DCSNor(): DCSComponent(2, 1) {
	
};

void DCSNor::updateOut(){
//	std::cout << in[0] << in[1] << std::endl;
	out = !((in | (in >> 1)) & 1);
}
