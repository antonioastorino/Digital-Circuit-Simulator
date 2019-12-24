//
//  DCSNand.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 13/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSNand_hpp
#define DCSNand_hpp

class DCSNand: public DCSComponent {
public:
	DCSNand(std::string name);
	
	void updateOut() override;
};

#endif /* DCSNand_hpp */
