#pragma once
#include "QueueManager.h"
#include "Logger.h"
#include "TCPManager.h"

// Producer receives print jobs from the network, wraps them in PrintJob, and enqueues them
class Producer {
public:
    Producer(QueueManager& qMgr, Logger& logger, TCPManager& tcpMgr);
    void run();
private:
    QueueManager& qMgr;
    Logger& logger;
    TCPManager& tcpMgr;
};