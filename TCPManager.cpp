#include "TCPManager.h"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>

using namespace std;

TCPManager::TCPManager(int port) : port(port), listenSocket(-1) {}

TCPManager::~TCPManager() {
    if (listenSocket != -1) {
        close(listenSocket);
    }
}

// Initialize the listening socket, bind it, and start listening for incoming connections
bool TCPManager::initialize() {
    // Create the listening socket
    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket < 0) {
        cerr << "Failed to create socket\n";
        return false;
    }

    // Bind the socket with the address information
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);
    if (bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "Bind failed\n";
        close(listenSocket);
        listenSocket = -1;
        return false;
    }

    // Start listening for incoming connections on the socket
    if (listen(listenSocket, SOMAXCONN) < 0) {
        cerr << "Listen failed\n";
        close(listenSocket);
        listenSocket = -1;
        return false;
    }

    return true;
}

// Accept client connection
int TCPManager::acceptConnection() {
    // Accept the incoming connection request and get the client socket
    int clientSocket = accept(listenSocket, nullptr, nullptr);
    if (clientSocket < 0) {
        cerr << "Accept failed\n";
    }
    
    return clientSocket;
}

// Receive all data from the client
string TCPManager::receiveData(int clientSocket) {
    string data;
    char buffer[1024];
    int bytesReceived = 0;

    // Receive data in a loop until the connection is closed
    while ((bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesReceived] = '\0';
        data += buffer;
    }

    return data;
}

// Close the client connection
void TCPManager::closeConnection(int clientSocket) {
    close(clientSocket);
}