#ifndef DCSComponent_hpp
#define DCSComponent_hpp

#include <sstream>
#include <vector>

class DCSWire;

struct DCSPinNumRange {
    ushort startPinNum;
    ushort endPinNum;
    DCSPinNumRange(ushort startPinNum, ushort endPinNum) : startPinNum(startPinNum), endPinNum(endPinNum) {}
};

/** DCSComponent class
 * Base class for every logic component.
 * It must be subclassed
 *
 **/
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
    ushort timeDelay;
    ushort numOfInPins;
    ushort numOfOutPins;

    std::vector<DCSWire*> wireVector = {};

public:
    bool isNode;     // true for DCSNode child only
    bool isTristate; // true for DCSTristate child only

    std::vector<DCSComponent*> rightComponentVector = {}; // components connected to the output
    bool initialized;

    virtual void setIn(bool inVal, ushort inPinNum);
    virtual void setIn(uint64_t inVec);
    virtual void updateOut() = 0;
    virtual DCSComponent* getOutComponent(ushort& outPinNum);
    virtual DCSComponent* getInComponent(ushort& inPinNum);

// Connect a single output to a single output of another component
    void connect(DCSComponent* to, ushort outPinNum, ushort inPinNum, std::string probeName = "");
// Connect a set of consecutive outputs to a set of consecutive inputs of another component
    void connect(DCSComponent* to, DCSPinNumRange outPinNumRange, DCSPinNumRange inPinNumRange,
                 std::vector<std::string> probeNames = {});
// Connect all the outputs to all the inputs of another component
    void connect(DCSComponent* to, std::vector<std::string> probeNames = {});

    std::string getName();
    ushort getTimeDelay(); // Return the latency between input and output
    bool getOutput();      // single-bit output value
    bool isInConnected(ushort inPinNum);
    bool getFromTristateIn(ushort inPinNum);
    
	void setConnectedIn(ushort inPinNum);
    void setFromTristateIn(ushort inPinNum);

    bool isFullyConnected();

    bool propagateValues();

    ushort getNumOfInPins();
    ushort getNumOfOutPins();
    virtual uint64_t getAllReachedQWord();

    bool getReachableIn(ushort inPinNum);

    virtual void enable();
    virtual void disable();
    bool getEnabled();
};

#endif /* DCSComponent_hpp */
