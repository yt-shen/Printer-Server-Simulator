#pragma once
#include <string>
#include <mutex>
#include <fstream>

// Logger handles logging of messages
class Logger {
public:
    Logger();
    ~Logger();
    void log(const std::string& message);
private:
    std::ofstream logFile;
    std::mutex mtx;
};