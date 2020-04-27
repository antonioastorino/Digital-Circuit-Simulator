
#ifndef DCSInput_hpp
#define DCSInput_hpp

#include "DCSArbitrarySignal.hpp"
#include "DCSComponent.hpp"
typedef std::vector<uint64_t> transitions;

/**
 * @class DCSInput
 * This class is needed to provide controlled inputs to the circuit from the external world.
 * In the initialization procedure, the Engine will start by propagating the values
 * coming from this component first.
 * Initialization 1
 * DCSInput I0("I0");
 * The signal can be attached afterwards using one of the following methods:
 * - assign a constant value
 * 		void makeSignal(bool constValue);
 * - assign a signal that changes at given time intervals, defined in 'transitions'
 * 		void makeSignal(transitions signal, bool initVal = 0, bool synch = false);
 * 		For example, a signal that starts at 0 and changes after 3 clock cycles and then
 * again after 2 clock cycles can be obtained as follows:
 * 		@example makeSignal({2, 3}, 0, true);
 * - assign a signal expressed as a string of bits
 * 		void makeSignal(std::string signal, bool synch = false);
 * 		To generate the same signal as in the previous example, you can use
 * 		@example makeSignal("001110");
 * - assign a square wave
 *      void makeSquareWave(uint16_t halfPeriod = 0, bool initVal = 0);
 * Initialization 2
 * DCSInput I0("I0", 1); // initialized with constant value 1
 * @example Initialization 3
 * DCSInput I0("I0", {2,2,3}, true); // initialized with a signal that will evolve with
 * synchronously with the clock (synch = true) as follows: Start with value 0 and stay at 0 for 2
 * clock cycles Switch to 1 and stay at 1 for 2 clock cycles Switch to 0 and stay at 0 for 3 clock
 * cycles Switch to 1 and stay at 1 indefinitely. NOTE: if you want the signal to start with a 1,
 * initialize with {0, ..., ...}
 */
class DCSInput : public DCSComponent {
private:
    bool hasSignal  = false;
    bool constValue = 0;
    DCSArbitrarySignal* signal;
    void initialize();

public:
    DCSInput(std::string name);
    DCSInput(std::string name, bool initValue);
    ~DCSInput();

    void makeSignal(bool constValue);
    void makeSignal(transitions signal, bool initVal = 0, bool synch = false);
    void makeSignal(std::string signal, bool synch = false);
    void makeSquareWave(uint16_t halfPeriod = 0, bool initVal = 0);
    void updateOut() override;
};

#endif /* DCSInput_hpp */
