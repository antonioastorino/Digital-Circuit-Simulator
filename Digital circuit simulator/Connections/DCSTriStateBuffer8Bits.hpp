//
//  DCSTriStateBuffer8Bits.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 18/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
/*
 PINOUT:
 INPUT 0: Output enable
 INPUT 1-8: Data input
 OUTPUT 0-7: Data out
 */

#ifndef DCSTriStateBuffer8Bits_hpp
#define DCSTriStateBuffer8Bits_hpp

class DCSTriStateBuffer8Bits: public DCSComponent {
private:
	DCSComponentArray<DCSTriStateBuffer> bufferArray;
	DCSNode node0;
public:
	DCSTriStateBuffer8Bits(std::string name);
	
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	DCSComponent* getInComponent(ushort &inPinNum) override;
	void updateOut() override;
	
	void enable() override;
	void disable() override;
};

#endif /* DCSTriStateBuffer8Bits_hpp */
