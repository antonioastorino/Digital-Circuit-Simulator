//
//  DCSUnitDelay.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 08/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSUnitDelay.hpp"

DCSUnitDelay::DCSUnitDelay() : DCSComponent(1, 1) {

}
void DCSUnitDelay::updateOut() {
	out = in;
	updateParentOut();
}
