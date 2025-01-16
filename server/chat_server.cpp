// Chat Server
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>

std::vector<int> clientSockets;
std::mutex clientSocketsMutex;

void handleClient(int clientSocket) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            std::lock_guard<std::mutex> lock(clientSocketsMutex);
            clientSockets.erase(std::remove(clientSockets.begin(), clientSockets.end(), clientSocket), clientSockets.end());
            close(clientSocket);
            std::cout << "Client disconnected.\n";
            break;
        }

        std::string message(buffer);
        std::cout << "Received: " << message << "\n";

        std::lock_guard<std::mutex> lock(clientSocketsMutex);
        for (int socket : clientSockets) {
            if (socket != clientSocket) {
                send(socket, buffer, bytesReceived, 0);
            }
        }
    }
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket.\n";
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to bind socket.\n";
        return 1;
    }

    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Failed to listen on socket.\n";
        return 1;
    }

    std::cout << "Server started on port 8080. Waiting for clients...\n";

    while (true) {
        sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientLen);
        if (clientSocket < 0) {
            std::cerr << "Failed to accept client connection.\n";
            continue;
        }

        {
            std::lock_guard<std::mutex> lock(clientSocketsMutex);
            clientSockets.push_back(clientSocket);
        }

        std::cout << "New client connected.\n";
        std::thread(handleClient, clientSocket).detach();
    }

    close(serverSocket);
    return 0;
}
