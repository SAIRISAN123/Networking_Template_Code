// UDP_Server.cpp
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define PORT 12000
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen;
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cerr << "Socket creation failed!" << std::endl;
        return -1;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    
    // Configure...
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind socket 
    if (bind(sockfd, (const struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Bind failed!" << std::endl;
        return -1;
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    // Wait for client messages
    while (true) {
        clientAddrLen = sizeof(clientAddr);
        int n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *) &clientAddr, &clientAddrLen);
        buffer[n] = '\0';  // Null terminate the received message

        std::cout << "Received message: " << buffer << std::endl;
        
        // Send a response back to the client
        

        //UpperCase buffer
        for (int i = 0; i < strlen(buffer); i++) {
            buffer[i] = toupper(buffer[i]);
        }
        

        sendto(sockfd, (const char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &clientAddr, clientAddrLen);
    }

    close(sockfd);
    return 0;
}
