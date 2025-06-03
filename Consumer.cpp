#include "Consumer.h"
#include "PrintJob.h"
#include <thread>
#include <chrono>
#include <string>

using namespace std;

Consumer::Consumer(QueueManager& qMgr, Logger& logger)
    : qMgr(qMgr), logger(logger) {}

void Consumer::run() {
    while (1) {
        PrintJob job = qMgr.pop(); // Retrieve the next print job from the QueueManager
        logger.log("Printing job ID=" + to_string(job.id)); // Record the start of the print job
        this_thread::sleep_for(chrono::seconds(job.pages)); // Simulate the time taken to print (assuming 1 second per page)
        logger.log("Completed job ID=" + to_string(job.id)); // Record the completion of the print job
    }
}