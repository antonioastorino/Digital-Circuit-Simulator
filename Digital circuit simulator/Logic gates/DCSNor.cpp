//
//  DCSNor.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 26/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSNor.hpp"


DCSNor::DCSNor(std::string name):
DCSComponent(name) {

};

void DCSNor::updateOut(){
//	std::cout << in[0] << in[1] << std::endl;
	out = !((in | (in >> 1)) & 1);
//	updateParentOut();
}
