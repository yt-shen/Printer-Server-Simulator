#include "Producer.h"
#include "PrintJob.h"
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

Producer::Producer(QueueManager& qMgr, Logger& logger, TCPManager& tcpMgr)
    : qMgr(qMgr), logger(logger), tcpMgr(tcpMgr) {}

void Producer::run() {
    while (true) {
        // Accept a connection from a client
        int clientSocket = tcpMgr.acceptConnection();
        if (clientSocket == -1) {
            continue;
        }

        // Receive data from the client
        string data = tcpMgr.receiveData(clientSocket);
        data.erase(remove(data.begin(), data.end(), '\r'), data.end());
        data.erase(remove(data.begin(), data.end(), '\n'), data.end());

        // Parse the job_id, pages, and priority from the received data
        istringstream ss(data);
        string temp;
        PrintJob job{0,0,0};
        if (getline(ss, temp, ',')) {
            job.id = stoi(temp);
        }
        if (getline(ss, temp, ',')) {
            job.pages = stoi(temp);
        }
        if (getline(ss, temp, ',')) {
            job.priority = stoi(temp);
        }

        // Record the reception of the job and add it to the queue
        logger.log("Received job ID=" + to_string(job.id) + ", pages=" + to_string(job.pages) + ", priority=" + to_string(job.priority));
        qMgr.push(job);
        logger.log("Job " + to_string(job.id) + " enqueued");

        // Close the connection with the client
        tcpMgr.closeConnection(clientSocket);
    }
}