
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
 * ### Initialization for arbitrary signal
 *
 * ```
 * DCSInput(std::string name);
 * ```
 *
 * The signal can be attached afterwards using one of the following methods:
 *
 * - assign a constant value
 *
 * ```
 * void makeSignal(bool constValue);
 *
 * ```
 * - assign a signal that changes at given time intervals, defined in 'signal'
 *
 * ```
 * void makeSignal(transitions signal, bool initVal = 0, bool synch = false);
 * ```
 *
 * - assign a signal expressed as a string of bits
 * 		void makeSignal(std::string signal, bool synch = false);
 * 		To generate the same signal as in the previous example, you can use
 *
 * 		```makeSignal("001110");```
 *
 * - assign a square wave
 *
 * ```
 * void makeSquareWave(uint16_t halfPeriod = 0, bool initVal = 0);
 * ```
 *
 * For example, a signal that starts at 0 and changes after 3 clock cycles and then
 * again after 2 clock cycles can be obtained as follows:
 *
 * ```makeSignal({2, 3}, 0, true);```
 *
 * ### Initialization with constant signal
 *
 * ```
 * DCSInput(std::string name, bool initValue);
 * ```
 *
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
    void makeSquareWave(uint16_t halfPeriod, bool initVal = 0);
    void updateOut() override;
    void restart();
};

#endif /* DCSInput_hpp */
