//
//  DCSUnitDelay.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 08/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSUnitDelay::DCSUnitDelay(std::string name) :
DCSComponent(name) { }

void DCSUnitDelay::updateOut() { out = in; }
