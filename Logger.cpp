#include "Logger.h"
#include <chrono>
#include <iomanip>
#include <ctime>
#include <filesystem>

using namespace std;

Logger::Logger() {
    filesystem::create_directories("logs");
    logFile.open("logs/server.log", ios::out);
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(const string& message) {
    lock_guard<mutex> lock(mtx); // Use unique_lock to ensure that only one thread accesses the log file at a time

    // Get the current time and log it with the corresponding message
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    auto time_ptr = localtime(&now_time);
    if (time_ptr) {
        logFile << put_time(time_ptr, "%Y-%m-%d %H:%M:%S") << " " << message << endl;
    } else {
        logFile << "Unknown time " << message << endl;
    }
}