#ifndef DCSComponent_hpp
#define DCSComponent_hpp

#include <sstream>
#include <vector>

class DCSWire;

struct DCSPinNumRange {
    unsigned short startPinNum;
    unsigned short endPinNum;
    DCSPinNumRange(unsigned short startPinNum, unsigned short endPinNum)
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
    DCSComponent(std::string name, bool shouldUpdate = true);
    uint64_t in;
    bool out;
    std::string name;
    uint64_t reachableIn;    // Keep track of which input is updated at least once
    uint64_t connectedIn;    // Detect if the component input is fully connected
    uint64_t fromTristateIn; // Detect which input is connected to a tristate output
    bool enabled;
    unsigned short timeDelay;
    unsigned short numOfInPins;
    unsigned short numOfOutPins;

    std::vector<DCSWire*> wireVector = {};

public:
    bool isNode;     // true for DCSNode child only
    bool isTristate; // true for DCSTristate child only

    std::vector<DCSComponent*> rightComponentVector = {}; // components connected to the output
    bool initialized;

    virtual void setIn(bool inVal, unsigned short inPinNum);
    virtual void setIn(uint64_t inVec);
    virtual void updateOut() = 0;
    virtual DCSComponent* getOutComponent(unsigned short& outPinNum);
    virtual DCSComponent* getInComponent(unsigned short& inPinNum);

    // Connect a single output to a single output of another component
    void connect(DCSComponent* to, unsigned short outPinNum, unsigned short inPinNum, std::string probeName = "");
    // Connect a set of consecutive outputs to a set of consecutive inputs of another component
    void connect(DCSComponent* to, DCSPinNumRange outPinNumRange, DCSPinNumRange inPinNumRange,
                 std::vector<std::string> probeNames = {});
    // Connect all the outputs to all the inputs of another component
    void connect(DCSComponent* to, std::vector<std::string> probeNames = {});

    std::string getName();
    unsigned short getTimeDelay(); // Return the latency between input and output
    bool getOutput();      // single-bit output value
    bool isInConnected(unsigned short inPinNum);
    bool getFromTristateIn(unsigned short inPinNum);

    void setConnectedIn(unsigned short inPinNum);
    void setFromTristateIn(unsigned short inPinNum);

    bool isFullyConnected();

    bool propagateValues();

    unsigned short getNumOfInPins();
    unsigned short getNumOfOutPins();
    virtual uint64_t getAllReachedQWord();

    bool getReachableIn(unsigned short inPinNum);

    virtual void enable();
    virtual void disable();
    bool getEnabled();
};

#endif /* DCSComponent_hpp */
