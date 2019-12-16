//
//  DCSNor.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 26/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSNor::DCSNor(std::string name):
DCSComponent(name) {

};

void DCSNor::updateOut(){
	out = !((in | (in >> 1)) & 1);
//	updateParentOut();
}
