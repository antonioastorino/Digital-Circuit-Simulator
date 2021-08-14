#ifndef DCSComponentArray_hpp
#define DCSComponentArray_hpp
#include "DCSCommon.hpp"
#include "DCSComponent.hpp"

/**
 * @class DCSComponentArray
 * Generates an array of identical components.
 */
template <class T> class DCSComponentArray : public DCSComponent
{
private:
    uint16_t numOfElements;
    std::string name;
    std::vector<T*> componentArray;

    void initialize();

public:
    DCSComponentArray(std::string name, uint16_t numOfElements);
    DCSComponentArray(std::vector<std::string> nameVector, uint16_t numOfElements);
    ~DCSComponentArray();

    DCSComponent* getOutComponent(uint16_t outPinNum) override;
    DCSComponent* getInComponent(uint16_t& inPinNum) override;

    void updateOut() override;
    T* operator[](uint16_t elemNum);
    uint16_t getNumOfElements();
};

#if TEST == 1

void andArrayTest();
#endif

#endif /* DCSComponentArray_hpp */
