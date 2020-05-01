#include "DCSTimer.hpp"
#include "DCSLog.hpp"
#include <fstream>
#include <thread>

std::vector<TimingResult> DCSTimer::results = {};
std::mutex DCSTimer::m;
int64_t DCSTimer::timeZero;

DCSTimer::DCSTimer(const char* title)
    : m_title(title), m_startTimepoint(std::chrono::steady_clock::now()) {}

DCSTimer::~DCSTimer() {
    auto endTimepoint = std::chrono::steady_clock::now();

    int64_t start = std::chrono::time_point_cast<std::chrono::nanoseconds>(m_startTimepoint)
                        .time_since_epoch()
                        .count();
    int64_t stop = std::chrono::time_point_cast<std::chrono::nanoseconds>(endTimepoint)
                       .time_since_epoch()
                       .count();
    int64_t elapsedTime = stop - start;
    uint32_t threadID   = std::hash<std::thread::id>{}(std::this_thread::get_id());

    m.lock();
    DCSTimer::results.push_back({threadID, m_title, start - DCSTimer::timeZero, elapsedTime});
    m.unlock();
}

void DCSTimer::printResults() {
    if (DCSTimer::results.size()) {
        std::ofstream profilingFile;
        profilingFile.open("gui/performance-analyzer/assets/profileFile");

        for (auto it = DCSTimer::results.begin(); it != DCSTimer::results.end(); ++it) {
            profilingFile << it->threadID << ":" << it->functionName << ":" << it->startTimepoint
                          << ":" << it->duration << "\n";
        }
        profilingFile.close();
    }
}

void DCSTimer::initialize() {
    DCSTimer::timeZero =
        std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now())
            .time_since_epoch()
            .count();
}