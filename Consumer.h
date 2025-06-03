#pragma once
#include "QueueManager.h"
#include "Logger.h"

// Consumer handles fetching print jobs from the queue and simulating the printing process
class Consumer {
public:
    Consumer(QueueManager& qMgr, Logger& logger);
    void run();
private:
    QueueManager& qMgr;
    Logger& logger;
};