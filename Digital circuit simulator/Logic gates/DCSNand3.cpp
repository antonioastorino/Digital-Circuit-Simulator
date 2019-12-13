//
//  DCSNand3.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 13/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSNand3.hpp"

DCSNand3::DCSNand3(std::string name):
DCSComponent(name) {

};

void DCSNand3::updateOut(){
	out = !((in & (in >> 1) & (in >> 2)) & 1);
//	updateParentOut();
}
