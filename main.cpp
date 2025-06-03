#include <iostream>
#include <string>
#include <thread>
#include <locale>
#include "Logger.h"
#include "QueueManager.h"
#include "Producer.h"
#include "Consumer.h"
#include "TCPManager.h"

using namespace std;

int main(int argc, char* argv[]) {
    locale::global(locale("C"));

    // Set the listening port (default to 55555)
    int port = 55555;
    if (argc > 1) {
        port = stoi(argv[1]);
    }

    // Initialize the TCP server with the specified port
    TCPManager tcpManager(port);
    if (!tcpManager.initialize()) {
        cerr << "Failed to initialize TCP server\n";
        return 1;
    }
    cout << "Print server is running on port " << port << endl;

    // Initialize logger and queue manager, create producer and consumer
    Logger logger;
    QueueManager qMgr;
    Producer producer(qMgr, logger, tcpManager);
    Consumer consumer(qMgr, logger);

    // Start producer and consumer threads
    thread producerThread(&Producer::run, &producer);
    thread consumerThread(&Consumer::run, &consumer);

    // Wait for threads to finish
    producerThread.join();
    consumerThread.join();

    return 0;
}