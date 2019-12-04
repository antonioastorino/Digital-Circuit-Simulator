//
//  DCSNot.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 16/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSNot.hpp"

DCSNot::DCSNot() : DCSComponent(1, 1) {
	out = 0;
}
void DCSNot::updateOut() {
	out = !in;
	updateParentOut();
}
