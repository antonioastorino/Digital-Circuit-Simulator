#ifndef DCSTimer_hpp
#define DCSTimer_hpp
#include <chrono>
#include <vector>
#include <mutex>

#if PROFILING
#define PROFILE() DCSTimer timer##__LINE__ = DCSTimer(__FUNCTION__)
#else
#define PROFILE()
#endif

struct TimingResult {
    std::string functionName;
    int64_t duration;
    uint32_t threadID;

};

class DCSTimer {
private:
    const char* m_title;
    std::chrono::steady_clock::time_point m_startTimepoint;
    static std::ofstream profilingFile;
    static std::vector<TimingResult> results;
    static void storeResult(std::string title, int64_t elapsedTime);
    static std::mutex m;
public:
    DCSTimer(const char*);
    ~DCSTimer();

    static void printResults();
};

#endif /* DCSTimer_hpp */