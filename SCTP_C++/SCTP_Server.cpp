#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create an SCTP socket
    server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
    if (server_fd < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // Bind the socket to an address and port
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(server_fd);
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) < 0) {
        std::cerr << "Failed to listen on socket" << std::endl;
        close(server_fd);
        return 1;
    }

    std::cout << "SCTP Server is listening on port " << PORT << std::endl;

    while (true) {
        std::cout << "Waiting for a connection..." << std::endl;

        // Accept a connection
        client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) {
            std::cerr << "Failed to accept connection" << std::endl;
            continue;
        }

        std::cout << "Client connected" << std::endl;

        while (true) {
            // Receive data from the client
            ssize_t bytes_received = sctp_recvmsg(client_fd, buffer, BUFFER_SIZE, nullptr, nullptr, nullptr, nullptr);
            if (bytes_received <= 0) {
                std::cerr << "Connection closed by client" << std::endl;
                break;
            }

            buffer[bytes_received] = '\0';
            std::cout << "Received from client: " << buffer << std::endl;

            // Send a response back to the client
            // std::string response = "Hello from SCTP Server!";
            
            // capitalize uppercase received message
            std::string response = buffer;
            for (int i = 0; i < response.size(); i++) {
                if (response[i] >= 'a' && response[i] <= 'z') {
                    response[i] = response[i] - 32;
                }
            }

            sctp_sendmsg(client_fd, response.c_str(), response.size(), nullptr, 0, 0, 0, 0, 0, 0);
        }

        // Close the client connection
        close(client_fd);
        std::cout << "Client disconnected" << std::endl;
    }

    // Close the server socket
    close(server_fd);
    return 0;
}