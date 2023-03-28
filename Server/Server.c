#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080

// Function to handle incoming client connections
void handle_client(int client_socket) {
    char buffer[1024];
    int n;
    
    // Send initial game state to client
    char *initial_state = "RNBQKBNRPPPPPPPP................................pppppppprnbqkbnr\n";
    write(client_socket, initial_state, strlen(initial_state));

    // Main loop to handle client requests
    while (true) {
        // Read client request
        memset(buffer, 0, sizeof(buffer));
        n = read(client_socket, buffer, sizeof(buffer));
        if (n < 0) {
            perror("Error reading from socket");
            break;
        } else if (n == 0) {
            // Client disconnected
            break;
        }
        
        // Process client request
        printf("Received message: %s\n", buffer);
        char *response = "OK\n";
        write(client_socket, response, strlen(response));
    }
    
    // Close client socket
    close(client_socket);
}

int main(int argc, char const *argv[]) {
    int server_fd, client_socket, opt = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    // Create server socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }
    
    // Bind socket to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    
    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    
    // Main loop to handle incoming connections
    while (true) {
        // Accept incoming connection
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
        
        // Handle client in new thread/process
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            close(server_fd);
            handle_client(client_socket);
            exit(0);
        } else if (pid > 0) {
            // Parent process
            close(client_socket);
        } else {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
    }
    
    // Close server socket
    close(server_fd);
    
    return 0;
}
