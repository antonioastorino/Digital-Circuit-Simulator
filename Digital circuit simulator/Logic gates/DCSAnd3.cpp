//
//  DCSAnd3.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 14/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSAnd3::DCSAnd3(std::string name):
DCSComponent(name) {

};

void DCSAnd3::updateOut(){
	out = (in & (in >> 1) & (in >> 2)) & 1;
}
