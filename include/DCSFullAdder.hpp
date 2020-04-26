/*
 PINOUT
 IN  0 - A
 IN  1 - B
 IN  2 - Carry in
 
 OUT 0 - Sum
 OUT 1 - Carry out
 */

#ifndef DCSFullAdder_hpp
#define DCSFullAdder_hpp
#include "DCSNode.hpp"
#include "DCSXor.hpp"
#include "DCSOr.hpp"
#include "DCSAnd.hpp"

class DCSFullAdder: public DCSComponent {
private:
	DCSNode node0;
	DCSNode node1;
	DCSNode node2;
	DCSXor xor0;
	DCSXor xor1;
	DCSAnd and0;
	DCSAnd and1;
	DCSOr or0;
public:
	DCSFullAdder(std::string name);
	~DCSFullAdder();
	
	DCSComponent* getOutComponent(unsigned short &outPinNum) override;
	DCSComponent* getInComponent(unsigned short &inPinNum) override;
	virtual void updateOut() override;
};

#endif /* DCSFullAdder_hpp */
