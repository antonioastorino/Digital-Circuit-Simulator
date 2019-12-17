//
//  DCSXor.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 17/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSXor::DCSXor(std::string name):
DCSComponent(name) {

};

void DCSXor::updateOut(){
	out = (in ^ (in >> 1)) & 1;
//	updateParentOut();
}
