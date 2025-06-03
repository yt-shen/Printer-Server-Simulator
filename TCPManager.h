#pragma once
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

// TCPManager handles TCP/IP connection initialization and communication
class TCPManager {
public:
    TCPManager(int port);
    ~TCPManager();
    bool initialize();
    int acceptConnection();
    std::string receiveData(int clientSocket);
    void closeConnection(int clientSocket);
private:
    int port;
    int listenSocket;
};