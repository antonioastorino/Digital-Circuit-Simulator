//
//  DCSUnitDelay.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 08/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSUnitDelay_hpp
#define DCSUnitDelay_hpp

#include "DCSComponent.hpp"

class DCSUnitDelay: public DCSComponent {
public:
	DCSUnitDelay();
	void updateOut() override;
	int getTimeDelay() override { return 1; };
};


#endif /* DCSUnitDelay_hpp */
