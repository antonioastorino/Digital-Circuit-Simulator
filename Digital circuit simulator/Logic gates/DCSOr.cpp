//
//  DCSOr.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 13/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSOr.hpp"

DCSOr::DCSOr(std::string name):
DCSComponent(name) {

};

void DCSOr::updateOut(){
	out = (in | (in >> 1)) & 1;
//	updateParentOut();
}