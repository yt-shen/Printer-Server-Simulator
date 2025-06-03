#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include "PrintJob.h"

// QueueManager handles the management of the PrintJob queue
class QueueManager {
public:
    void push(const PrintJob& job);
    PrintJob pop();
private:
    std::priority_queue<PrintJob> pq;
    std::mutex mtx;
    std::condition_variable cv;
};