// UDP_Client.cpp
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <istream>

#define PORT 12000
#define SERVER_ADDR "127.0.0.1"
#define BUFFER_SIZE 1024

using namespace std;

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cerr << "Socket creation failed!" << std::endl;
        return -1;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    
    // Configure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    while (true){
    
    char message[BUFFER_SIZE];

    std::cout << "Enter message: ";
    std::cin.getline(message, BUFFER_SIZE);


    
    // Send message to server
    sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *) &serverAddr, sizeof(serverAddr));
    

    // Receive server response
    int n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, nullptr, nullptr);
    buffer[n] = '\0';  // Null terminate the received message

    std::cout << "Server response: " << buffer << std::endl;


    

    }

    close(sockfd);

    return 0;

}
