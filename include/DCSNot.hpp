//
//  DCSNot.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 16/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSNot_hpp
#define DCSNot_hpp

class DCSNot: public DCSComponent {
public:
	DCSNot(std::string name);
	
	void updateOut() override;
};

#endif /* DCSNot_hpp */
