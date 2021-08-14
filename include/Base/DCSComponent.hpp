#ifndef DCSComponent_hpp
#define DCSComponent_hpp

#include <sstream>
#include <vector>

class DCSWire;

struct DCSPinNumRange
{
    uint16_t startPinNum;
    uint16_t endPinNum;
    DCSPinNumRange(uint16_t startPinNum, uint16_t endPinNum)
        : startPinNum(startPinNum), endPinNum(endPinNum)
    {
    }
};

/**
 * @class DCSComponent
 * Base virtual class for every logic component which provides components with the necessary
 * functionalities, e.g:
 *
 * - connect with other components using `DCSWire` objects
 * - update the output based on the current state (values read at the input)
 * - keep track of which pins are not connected
 * - keep track of which pins are not reached during the initialization process
 *
 * #### How to connect two components
 * Supposing we have two components, `compA` and `compB`, and we want to connect the output of the
 * first to the second. If `compA.getNumOfOutPins()` returns the same value as
 * `compB.getNumOfInPins()`, say `N`, the easiest way to perform the connection is by using the
 * method
 *
 * ```
 * void connect(DCSComponent* const to, const std::vector<std::string>& probeNames = {});
 * ```
 * as follows
 *
 * ```
 * compA.connect(&compB);
 * ```
 * or
 *
 * ```
 * compA.connect(&compB, {"<probe_name1>", "<probe_name2>", ..., "<probe_nameN>"});
 * ```
 * NOTE: Specifying the lables entails the probes to be prompted at run time.
 *
 * This will connect the output pins of `compA` to the corresponding (same pin number) input pins of
 * `compB`. If this is not the desired order or the pin numbers do not match it is possible to
 * connect one pin at a time using
 *
 * ```
 * void connect(DCSComponent* const to, uint16_t outPinNum, uint16_t inPinNum, const std::string&
 * probeName = "");
 * ```
 *
 * In addition, one can select a range of output pins to connect to a range of input pins using
 *
 * ```
 *  void connect(DCSComponent* const to, DCSPinNumRange outPinNumRange, DCSPinNumRange
 * inPinNumRange, const std::vector<std::string>& probeNames = {});
 * ```
 */
class DCSComponent
{
private:
    std::vector<DCSComponent*> rightComponentVector; // components connected to the output

protected:
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
    bool node;     // true for DCSNode child only
    bool tristate; // true for DCSTristate child only
    bool initialized;
    bool outChanged;

    std::vector<DCSWire*> wireVector = {};

public:
    std::vector<DCSComponent*>
        updatedByVector; // stores the component who updated a given pin each clock cycle

private:
    DCSComponent();

protected:
    virtual ~DCSComponent();
    DCSComponent(const std::string& name, bool shouldUpdate = true, bool isNode = false);
    void checkOutputChanged(bool newOutValue);

public:
    void resetUpdatedByVector();
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

    std::string getName() const;
    uint16_t getTimeDelay(); // Return the latency between input and output
    bool getOutput();        // single-bit output value
    bool isInConnected(uint16_t inPinNum);
    bool isFromTristateIn(uint16_t inPinNum) const;
    bool isInitialized() const;
    bool isNode() const;
    bool isTristate() const;
    bool needsPropagation() const;

    void setConnectedIn(uint16_t inPinNum);
    void setFromTristateIn(uint16_t inPinNum);

    bool isFullyConnected() const;
    bool isReachableAtIn(uint16_t inPinNum) const;

    bool propagateValues();

    uint16_t getNumOfInPins() const;
    uint16_t getNumOfOutPins() const;
    uint64_t getAllReachedQWord() const;

    virtual void enable();
    virtual void disable();
    bool isEnabled() const;

    friend class DCSRam16x8;
    friend class DCSRam256x16;
    friend class DCSEngine;
};

#endif /* DCSComponent_hpp */
