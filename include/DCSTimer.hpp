#include <chrono>
#include <string>
#include <vector>

#define PROFILE() DCSTimer timer##__LINE__ = DCSTimer(__FUNCTION__)

struct TimingResult {
    std::string functionName;
    int64_t duration;
    uint32_t threadID;

};

class DCSTimer {
private:
    const char* m_title;
    std::chrono::steady_clock::time_point m_startTimepoint;

    static std::vector<TimingResult> results;
    static void storeResult(std::string title, int64_t elapsedTime);

public:
    DCSTimer(const char*);
    ~DCSTimer();

    static void printResults();
};