#ifndef DCSTimer_hpp
#define DCSTimer_hpp
#include <chrono>
#include <mutex>
#include <vector>

#if PROFILING
#define PROFILE() DCSTimer timer = DCSTimer(__FUNCTION__)
#define PROFILE_WITH_CUSTOM_NAME(name) DCSTimer timer = DCSTimer(name)
#else
#define PROFILE()
#define PROFILE_WITH_CUSTOM_NAME(name)
#endif

struct TimingResult {
    uint32_t threadID;
    std::string functionName;
    int64_t startTimepoint;
    int64_t duration;
};

class DCSTimer {
private:
    const char* m_title;
    std::chrono::steady_clock::time_point m_startTimepoint;
    static std::ofstream profilingFile;
    static std::vector<TimingResult> results;
    static void storeResult(std::string title, int64_t elapsedTime);
    static std::mutex m;
    static int64_t timeZero;

public:
    DCSTimer(const char*);
    ~DCSTimer();

    static void printResults();
    static void initialize();
};

#endif /* DCSTimer_hpp */