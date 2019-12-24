//
//  DCSNor.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 26/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSNor_hpp
#define DCSNor_hpp

class DCSNor: public DCSComponent {
public:
	DCSNor(std::string name);
	
	void updateOut() override;
};
#endif /* DCSNor_hpp */
