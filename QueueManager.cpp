#include "QueueManager.h"

using namespace std;

void QueueManager::push(const PrintJob& job) {
    {
        lock_guard<mutex> lock(mtx); // Use lock_guard to ensure only one thread accesses the queue at a time
        pq.push(job);
    }
    cv.notify_one(); // Notify one waiting consumer that a new job is available in the queue
}

PrintJob QueueManager::pop() {
    unique_lock<mutex> lock(mtx); // Use unique_lock to ensure only one thread accesses the queue at a time
    cv.wait(lock, [this](){ return !pq.empty(); }); // Wait if the queue is empty, and proceed when a job is available
    PrintJob job = pq.top();
    pq.pop();
    return job;
}