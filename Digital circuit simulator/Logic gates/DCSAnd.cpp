//
//  DCSAnd.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 15/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSAnd.hpp"

DCSAnd::DCSAnd(): DCSComponent(2, 1) {
	
};

void DCSAnd::updateOut(){
	out = (in & (in >> 1)) & 1;
	updateParentOut();
}
