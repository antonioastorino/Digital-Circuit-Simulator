#include <chrono>
#include <string>
#include <vector>

#define PROFILE() DCSTimer timer##__LINE__ = DCSTimer(__PRETTY_FUNCTION__)

struct TimingResult {
    std::string functionName;
    int64_t duration;
};

class DCSTimer {
private:
    const char* m_title;
    std::chrono::steady_clock::time_point m_startTimepoint;
    static void storeResult(std::string title, int64_t elapsedTime);
    static std::vector<TimingResult> results;

public:
    DCSTimer(const char*);
    ~DCSTimer();
};