#include "DCSTimer.hpp"
#include "DCSLog.hpp"
#include <fstream>
#include <sstream>
#include <thread>

std::vector<TimingResult> DCSTimer::results = {};
std::mutex DCSTimer::m;
int64_t DCSTimer::timeZero;
std::string DCSTimer::fileName;
std::string DCSTimer::title;
uint16_t DCSTimer::fileId;
int DCSTimer::optLev;
bool DCSTimer::initialized = false;

DCSTimer::DCSTimer(const char* title)
    : m_title(title), m_startTimepoint(std::chrono::steady_clock::now())
{
}

DCSTimer::~DCSTimer()
{
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

void DCSTimer::printResults()
{
    if (DCSTimer::results.size())
    {
        std::ofstream profilingFile;
        std::stringstream file;
        file << "gui/performance-analyzer/data/profile-" << DCSTimer::fileName << "-n"
             << DCSTimer::fileId << "-o" << DCSTimer::optLev << ".log";
        profilingFile.open(file.str());
        profilingFile << "Title: " << DCSTimer::title << "\n";
        for (auto it = DCSTimer::results.begin(); it != DCSTimer::results.end(); ++it)
        {
            profilingFile << it->threadID << ":" << it->functionName << ":" << it->startTimepoint
                          << ":" << it->duration << "\n";
        }
        profilingFile.close();
    }
}

void DCSTimer::initialize(const std::string& fileName, uint16_t fileId, int optLev)
{
    if (initialized)
        DCSLog::error("DCSTimer", 20);
    DCSTimer::fileName    = fileName;
    DCSTimer::fileId      = fileId;
    DCSTimer::optLev      = optLev;
    DCSTimer::initialized = true;
    DCSTimer::timeZero
        = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now())
              .time_since_epoch()
              .count();
}