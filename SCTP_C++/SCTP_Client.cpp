// This project uses the SCTP protocol. Chat application

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create an SCTP socket
    client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
    if (client_fd < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // Define the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    // Connect to the server
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to connect to server" << std::endl;
        close(client_fd);
        return 1;
    }

    std::cout << "Connected to SCTP Server at " << SERVER_IP << ":" << PORT << std::endl;

    while (true) {
        // Send a message to the server
        std::string message;
        std::cout << "Enter a message (or 'exit' to quit): ";
        std::getline(std::cin, message);

        if (message == "exit") {
            break;
        }

        sctp_sendmsg(client_fd, message.c_str(), message.size(), nullptr, 0, 0, 0, 0, 0, 0);

        // Receive a response from the server
        ssize_t bytes_received = sctp_recvmsg(client_fd, buffer, BUFFER_SIZE, nullptr, nullptr, nullptr, nullptr);
        if (bytes_received <= 0) {
            std::cerr << "Connection closed by server" << std::endl;
            break;
        }

        buffer[bytes_received] = '\0';
        std::cout << "Received from server: " << buffer << std::endl;
    }

    // Close the client socket
    close(client_fd);
    std::cout << "Connection closed" << std::endl;
    return 0;
}