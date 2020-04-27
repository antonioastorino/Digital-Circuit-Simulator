#ifndef DCSComponent_hpp
#define DCSComponent_hpp

#include <sstream>
#include <vector>

class DCSWire;

struct DCSPinNumRange {
    uint16_t startPinNum;
    uint16_t endPinNum;
    DCSPinNumRange(uint16_t startPinNum, uint16_t endPinNum)
        : startPinNum(startPinNum), endPinNum(endPinNum) {}
};

/**
 * @class DCSComponent
 * Base virtual class for every logic component.
 */
class DCSComponent {
private:
    DCSComponent();

protected:
    virtual ~DCSComponent();
    DCSComponent(const std::string& name, bool shouldUpdate = true);
    uint64_t in;
    bool out;
    std::string name;
    uint64_t reachableIn;    // Keep track of which input is updated at least once
    uint64_t connectedIn;    // Detect if the component input is fully connected
    uint64_t fromTristateIn; // Detect which input is connected to a tristate output
    bool enabled;
    uint16_t timeDelay;
    uint16_t numOfInPins;
    uint16_t numOfOutPins;

    std::vector<DCSWire*> wireVector = {};

public:
    bool isNode;     // true for DCSNode child only
    bool isTristate; // true for DCSTristate child only

    std::vector<DCSComponent*> rightComponentVector = {}; // components connected to the output
    bool initialized;

    virtual void setIn(bool inVal, uint16_t inPinNum);
    virtual void updateOut() = 0;
    virtual DCSComponent* getOutComponent(uint16_t outPinNum);
    virtual DCSComponent* getInComponent(uint16_t& inPinNum);

    // Connect a single output to a single output of another component
    void connect(DCSComponent* const to, uint16_t outPinNum, uint16_t inPinNum,
                 const std::string& probeName = "");
    // Connect a set of consecutive outputs to a set of consecutive inputs of another component
    void connect(DCSComponent* const to, DCSPinNumRange outPinNumRange,
                 DCSPinNumRange inPinNumRange, const std::vector<std::string>& probeNames = {});
    // Connect all the outputs to all the inputs of another component
    void connect(DCSComponent* const to, const std::vector<std::string>& probeNames = {});

    std::string getName();
    uint16_t getTimeDelay(); // Return the latency between input and output
    bool getOutput();        // single-bit output value
    bool isInConnected(uint16_t inPinNum);
    bool getFromTristateIn(uint16_t inPinNum);

    void setConnectedIn(uint16_t inPinNum);
    void setFromTristateIn(uint16_t inPinNum);

    bool isFullyConnected();
    bool isReachableAtIn(uint16_t inPinNum);

    bool propagateValues();

    uint16_t getNumOfInPins();
    uint16_t getNumOfOutPins();
    virtual uint64_t getAllReachedQWord();

    virtual void enable();
    virtual void disable();
    bool isEnabled();
};

#endif /* DCSComponent_hpp */
