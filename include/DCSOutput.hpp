//
//  DCSOutput.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 01/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSOutput_hpp
#define DCSOutput_hpp

class DCSOutput: public DCSComponent {
public:
	DCSOutput(std::string name);
	void updateOut() override {};
};

#endif /* DCSOutput_hpp */
