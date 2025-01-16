#include <iostream>
#include <thread>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>
#include <random>

std::string generateRandomName() {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int nameLength = 8;
    std::string name;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> dist(0, sizeof(charset) - 2);

    for (int i = 0; i < nameLength; ++i) {
        name += charset[dist(generator)];
    }
    return name;
}

void receiveMessages(int serverSocket) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(serverSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            std::cout << "Disconnected from server.\n";
            break;
        }
        std::cout << buffer << "\n";
    }
    close(serverSocket);
    exit(0);
}

int main() {
    std::string serverIP;
    int serverPort = 8080;

    std::cout << "Enter server IP address: ";
    std::cin >> serverIP;

    std::string anonymousName = generateRandomName();

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Failed to create socket.\n";
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    if (inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr) <= 0) {
        std::cerr << "Invalid server IP address.\n";
        return 1;
    }

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to connect to server.\n";
        return 1;
    }

    std::cout << "Connected to server as " << anonymousName << ". You can start typing messages.\n";

    std::thread receiverThread(receiveMessages, clientSocket);

    while (true) {
        std::string message;
        std::getline(std::cin, message);
        if (message == "exit") {
            std::cout << "Disconnecting...\n";
            break;
        }
        std::string formattedMessage = "[" + anonymousName + "]: " + message;
        send(clientSocket, formattedMessage.c_str(), formattedMessage.size(), 0);
    }

    close(clientSocket);
    receiverThread.join();
    return 0;
}
