//
//  DCSXor.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 17/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSXor_hpp
#define DCSXor_hpp

class DCSXor: public DCSComponent {
public:
	DCSXor(std::string name);
	
	void updateOut() override;
};

#endif /* DCSXor_hpp */
