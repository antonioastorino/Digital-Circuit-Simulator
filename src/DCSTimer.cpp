#include "DCSTimer.hpp"
#include "DCSLog.hpp"

DCSTimer::DCSTimer(const char* title)
    : m_title(title), m_startTimepoint(std::chrono::steady_clock::now()) {}

DCSTimer::~DCSTimer() {
    auto endTimepoint = std::chrono::steady_clock::now();

    int16_t start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimepoint)
                        .time_since_epoch()
                        .count();
    int16_t stop = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint)
                       .time_since_epoch()
                       .count();
    uint64_t elapsedTime = stop - start;

    DCSTimer::storeResult(m_title, elapsedTime);
}

std::vector<TimingResult> DCSTimer::results = {};

void DCSTimer::storeResult(std::string title, int64_t elapsedTime) {
    DCSTimer::results.push_back({title, elapsedTime});
    DCSLog::profile(title, elapsedTime);
}