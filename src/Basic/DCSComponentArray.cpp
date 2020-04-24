//
//  DCSComponentArray.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 12/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"
#include "DCSInput.hpp"
#include "DCSOutput.hpp"
#include "DCSTriStateBuffer.hpp"
#include "DCSTriStateBuffer8Bits.hpp"
#include "DCSAnd.hpp"
#include "DCSAnd3.hpp"
#include "DCSAnd4.hpp"
#include "DCSAnd6.hpp"
#include "DCSNand.hpp"
#include "DCSOr.hpp"
#include "DCSXor.hpp"
#include "DCSNot.hpp"
#include "DCSNor.hpp"
#include "DCSNor3.hpp"
#include "DCSNand3.hpp"
#include "DCSUnitDelay.hpp"
#include "DCSNode.hpp"
#include "DCSSRLatch.hpp"
#include "DCSDLatch.hpp"
#include "DCSDFlipFlop.hpp"
#include "DCSDLatchAsyncSR.hpp"
#include "DCSDFlipFlopAsyncSR.hpp"
#include "DCSRegister1Bit.hpp"
#include "DCSRegister8Bits.hpp"
#include "DCSJKLatchMasterSlaveAsyncSR.hpp"
#include "DCSClockDiv2WithEnableAndLoad.hpp"
#include "DCSFullAdder.hpp"
#include "DCSComponentArray.hpp"
#include "DCSLog.hpp"


class DCSNode;

template<class T>
DCSComponentArray<T>::DCSComponentArray(std::string name, ushort numOfElements):
DCSComponent(name, false),
numOfElements(numOfElements),
name({name}) {
	componentArray.reserve(numOfElements);
	for (int i =0; i < numOfElements; i++) {
		std::stringstream cName;
		cName << name << i;
		T* component = new T(cName.str());
		componentArray.push_back(component);
	}
	
	initialize();
}

template<class T>
DCSComponentArray<T>::DCSComponentArray(std::vector<std::string> nameArray,
										ushort numOfElements):
DCSComponent("Array", false),
numOfElements(numOfElements),
name{"Array"} {
	componentArray.reserve(numOfElements);
	for (int i =0; i < numOfElements; i++) {
		T* component = new T(nameArray[i]);
		componentArray.push_back(component);
	}
	initialize();
}

template<class T>
void DCSComponentArray<T>::initialize() {
	timeDelay = componentArray[0]->getTimeDelay();
	numOfInPins = componentArray[0]->getNumOfInPins() * numOfElements;
	numOfOutPins = componentArray[0]->getNumOfOutPins() * numOfElements;
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
	return componentArray[oldPin / numOfOutPins]->getOutComponent(outPinNum);
}


template<class T>
DCSComponent* DCSComponentArray<T>::getInComponent(ushort &inPinNum) {
	ushort oldPin = inPinNum;
	ushort numOfInPins = componentArray[0]->getNumOfInPins();
	inPinNum %= numOfInPins;
	return componentArray[oldPin / numOfInPins]->getInComponent(inPinNum);
}

template<class T>
void DCSComponentArray<T>::updateOut() {
	DCSLog::error(name, "This function should never be called");
}

template<class T>
T* DCSComponentArray<T>::operator [] (ushort  elemNum) {
	return componentArray[elemNum];
}

template class DCSComponentArray<DCSInput>;
template class DCSComponentArray<DCSOutput>;
template class DCSComponentArray<DCSTriStateBuffer>;
template class DCSComponentArray<DCSTriStateBuffer8Bits>;
template class DCSComponentArray<DCSAnd>;
template class DCSComponentArray<DCSAnd3>;
template class DCSComponentArray<DCSAnd4>;
template class DCSComponentArray<DCSAnd6>;
template class DCSComponentArray<DCSNand>;
template class DCSComponentArray<DCSOr>;
template class DCSComponentArray<DCSXor>;
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
template class DCSComponentArray<DCSRegister8Bits>;
template class DCSComponentArray<DCSJKLatchMasterSlaveAsyncSR>;
template class DCSComponentArray<DCSClockDiv2WithEnableAndLoad>;
template class DCSComponentArray<DCSFullAdder>;

