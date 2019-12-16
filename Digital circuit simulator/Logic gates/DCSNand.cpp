//
//  DCSNand.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 13/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSNand::DCSNand(std::string name):
DCSComponent(name) {};

void DCSNand::updateOut(){ out = !((in & (in >> 1)) & 1); }
