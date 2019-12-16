//
//  DCSComponentArray.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 12/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

template<class T>
DCSComponentArray<T>::DCSComponentArray(std::string name, ushort numOfElements):
DCSComponent(name, false),
numOfElements(numOfElements),
name{name} {
	componentArray.reserve(numOfElements);
	for (int i =0; i < numOfElements; i++) {
		std::stringstream cName;
				cName << name << i;
		// Indentation bug here: Xcode thinks that '<' is a bracket and expects '>>>>' to fix the indentation. Help!
		T* component = new T(cName.str());
//		component->setParent(this);
		componentArray.push_back(component);
		
	}
}

template<class T>
DCSComponentArray<T>::~DCSComponentArray() {
	for (int i =0; i < numOfElements; i++) {
		delete componentArray[i];
	}
}

template<class T>
DCSComponent* DCSComponentArray<T>::getOutComponent(ushort &outPinNum) {
	ushort oldPin = outPinNum;
	ushort numOfOutPins = componentArray[0]->getNumOfOutPins();
	outPinNum %= numOfOutPins;
	return componentArray[oldPin / numOfOutPins];
}
		
		
template<class T>
DCSComponent* DCSComponentArray<T>::getInComponent(ushort &inPinNum) {
	ushort oldPin = inPinNum;
	ushort numOfInPins = componentArray[0]->getNumOfInPins();
	inPinNum %= numOfInPins;
	return componentArray[oldPin / numOfInPins];
}
		
template<class T>
void DCSComponentArray<T>::updateOut() {
	out = 0;
	for (uint64_t i = 0; i < numOfElements; i++) {
		out |= componentArray[i]->getOutVec() << (i * getNumOfOutPins());
	}
//	updateParentOut();
}

template<class T>
T* DCSComponentArray<T>::operator [] (ushort  elemNum) {
	return componentArray[elemNum];
}

template class DCSComponentArray<DCSInput>;
template class DCSComponentArray<DCSOutput>;
template class DCSComponentArray<DCSAnd>;
template class DCSComponentArray<DCSNand>;
template class DCSComponentArray<DCSOr>;
template class DCSComponentArray<DCSNot>;
template class DCSComponentArray<DCSNor>;
template class DCSComponentArray<DCSNor3>;
template class DCSComponentArray<DCSNand3>;
template class DCSComponentArray<DCSUnitDelay>;
template class DCSComponentArray<DCSNode>;
template class DCSComponentArray<DCSSRLatch>;
template class DCSComponentArray<DCSDLatch>;
template class DCSComponentArray<DCSDFlipFlop>;
template class DCSComponentArray<DCSDLatchAsyncSR>;
template class DCSComponentArray<DCSDFlipFlopAsyncSR>;
template class DCSComponentArray<DCSRegister1Bit>;
template class DCSComponentArray<DCSJKLatchMasterSlaveAsyncSR>;
template class DCSComponentArray<DCSClockDiv2WithEnableAndLoad>;

