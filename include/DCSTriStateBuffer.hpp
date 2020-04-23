//
//  DCSTriStateBuffer.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 12/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSTriStateBuffer_hpp
#define DCSTriStateBuffer_hpp

/*
 When input 1 is low, the output does not change and does not propagate (the wire ignores it).
 When input 1 is high, the output matches the value of input 0 but delayed by tau.
 */

class DCSTriStateBuffer: public DCSComponent {

public:
	DCSTriStateBuffer(std::string name);
	
	void updateOut() override;
	
	void enable() override;
	void disable() override;
};

#endif /* DCSTriStateBuffer_hpp */
