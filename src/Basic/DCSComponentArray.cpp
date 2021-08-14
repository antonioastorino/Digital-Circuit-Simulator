#include "DCSComponentArray.hpp"
#include "DCSAnd.hpp"
#include "DCSAnd3.hpp"
#include "DCSAnd4.hpp"
#include "DCSAnd6.hpp"
#include "DCSAnd8.hpp"
#include "DCSClockDivider.hpp"
#include "DCSDFlipFlop.hpp"
#include "DCSDFlipFlopAsyncSR.hpp"
#include "DCSDLatch.hpp"
#include "DCSDLatchAsyncSR.hpp"
#include "DCSFullAdder.hpp"
#include "DCSInput.hpp"
#include "DCSJKLatchMasterSlaveAsyncSR.hpp"
#include "DCSLog.hpp"
#include "DCSNand.hpp"
#include "DCSNand3.hpp"
#include "DCSNode.hpp"
#include "DCSNor.hpp"
#include "DCSNor3.hpp"
#include "DCSNot.hpp"
#include "DCSOr.hpp"
#include "DCSOutput.hpp"
#include "DCSRegister16BitsWithEnable.hpp"
#include "DCSRegister1Bit.hpp"
#include "DCSRegister1BitWithEnable.hpp"
#include "DCSRegister8Bits.hpp"
#include "DCSRegister8BitsWithEnable.hpp"
#include "DCSSRLatch.hpp"
#include "DCSTriStateBuffer.hpp"
#include "DCSTriStateBuffer8Bits.hpp"
#include "DCSUnitDelay.hpp"
#include "DCSXor.hpp"
#include "DCSCommon.hpp"

class DCSNode;

template <class T>
DCSComponentArray<T>::DCSComponentArray(std::string name, uint16_t numOfElements)
    : DCSComponent(name, false), numOfElements(numOfElements), name({name}) {
    componentArray.reserve(numOfElements);
    for (int i = 0; i < numOfElements; i++) {
        std::stringstream cName;
        cName << name << i;
        T* component = new T(cName.str());
        componentArray.push_back(component);
    }

    initialize();
}

template <class T>
DCSComponentArray<T>::DCSComponentArray(std::vector<std::string> nameArray, uint16_t numOfElements)
    : DCSComponent("Array", false), numOfElements(numOfElements), name{"Array"} {
    componentArray.reserve(numOfElements);
    for (int i = 0; i < numOfElements; i++) {
        T* component = new T(nameArray[i]);
        componentArray.push_back(component);
    }
    initialize();
}

template <class T> void DCSComponentArray<T>::initialize() {
    timeDelay    = componentArray[0]->getTimeDelay();
    numOfInPins  = componentArray[0]->getNumOfInPins() * numOfElements;
    numOfOutPins = componentArray[0]->getNumOfOutPins() * numOfElements;
}

template <class T> DCSComponentArray<T>::~DCSComponentArray() {
    for (int i = 0; i < numOfElements; i++) {
        delete componentArray[i];
        componentArray[i] = nullptr;
    }
}

template <class T> DCSComponent* DCSComponentArray<T>::getOutComponent(uint16_t outPinNum) {
    uint16_t oldPin       = outPinNum;
    uint16_t numOfOutPins = componentArray[0]->getNumOfOutPins();
    outPinNum %= numOfOutPins;
    return componentArray[oldPin / numOfOutPins]->getOutComponent(outPinNum);
}

template <class T> DCSComponent* DCSComponentArray<T>::getInComponent(uint16_t& inPinNum) {
    uint16_t oldPin      = inPinNum;
    uint16_t numOfInPins = componentArray[0]->getNumOfInPins();
    inPinNum %= numOfInPins;
    return componentArray[oldPin / numOfInPins]->getInComponent(inPinNum);
}

template <class T> void DCSComponentArray<T>::updateOut() { DCSLog::error(name, 0); }

template <class T> T* DCSComponentArray<T>::operator[](uint16_t elemNum) {
    return componentArray[elemNum];
}

template <class T> uint16_t DCSComponentArray<T>::getNumOfElements() {
    return this->numOfElements;
};

template class DCSComponentArray<DCSInput>;
template class DCSComponentArray<DCSOutput>;
template class DCSComponentArray<DCSTriStateBuffer>;
template class DCSComponentArray<DCSTriStateBuffer8Bits>;
template class DCSComponentArray<DCSAnd>;
template class DCSComponentArray<DCSAnd3>;
template class DCSComponentArray<DCSAnd4>;
template class DCSComponentArray<DCSAnd6>;
template class DCSComponentArray<DCSAnd8>;
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
template class DCSComponentArray<DCSRegister1BitWithEnable>;
template class DCSComponentArray<DCSRegister8Bits>;
template class DCSComponentArray<DCSRegister8BitsWithEnable>;
template class DCSComponentArray<DCSRegister16BitsWithEnable>;
template class DCSComponentArray<DCSJKLatchMasterSlaveAsyncSR>;
template class DCSComponentArray<DCSClockDivider>;
template class DCSComponentArray<DCSFullAdder>;


#if TEST == 1
#include "DCSAnd.hpp"
#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
void andArrayTest()
{
    DCSLog::printTestName("And array");
    uint16_t hcp = 2;
    DCSEngine::initialize(hcp);

    DCSComponentArray<DCSInput> inArray("In", 4);
    DCSComponentArray<DCSAnd> andArray("And", 2);
    DCSDisplayNBits inDisp0("InAnd", 4);
    DCSDisplayNBits outDisp0("OutAnd", 2);

    inArray[0]->makeSquareWave(hcp);
    inArray[1]->makeSquareWave(hcp * 2);
    inArray[2]->makeSquareWave(hcp * 4);
    inArray[3]->makeSquareWave(hcp * 8);
    inArray.connect(&inDisp0);

    inArray.connect(&andArray);
    andArray.connect(&outDisp0);

    DCSEngine::run(2 * hcp * 10);
}
#endif