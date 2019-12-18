//
//  DCSAnd4.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 18/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSAnd4::DCSAnd4(std::string name):
DCSComponent(name) {

};

void DCSAnd4::updateOut(){
	out = (in & (in >> 1) & (in >> 2) & (in >> 3)) & 1;
}
