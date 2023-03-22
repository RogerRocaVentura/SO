#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX_CLIENTS 10

int clients[MAX_CLIENTS];
int num_clients = 0;

// Function to handle incoming client connections
void handle_client(int client_socket) {
    char buffer[1024];
    int n;

    // Send initial game state to client
    char* initial_state = "RNBQKBNRPPPPPPPP................................pppppppprnbqkbnr\n";
    write(client_socket, initial_state, strlen(initial_state));

    // Main loop to handle client requests
    while (true) {
        // Read client request
        memset(buffer, 0, sizeof(buffer));
        n = read(client_socket, buffer, sizeof(buffer));
        if (n < 0) {
            perror("Error reading from socket");
            break;
        }
        else if (n == 0) {
            // Client disconnected
            break;
        }

        // Process client request
        printf("Received message: %s\n", buffer);

        if (strcmp(buffer, "GET_CONNECTED_USERS\n") == 0) {
            // Send list of connected users to client
            char response[1024] = "";
            for (int i = 0; i < num_clients; i++) {
                char user_str[16];
                snprintf(user_str, sizeof(user_str), "%d", clients[i]);
                strcat(response, user_str);
                if (i < num_clients - 1) {
                    strcat(response, ",");
                }
            }
            write(client_socket, response, strlen(response));
        }
        else {
            // Send OK response
            char* response = "OK\n";
            write(client_socket, response, strlen(response));
        }
    }

    // Remove client from list of connected clients
    for (int i = 0; i < num_clients; i++) {
        if (clients[i] == client_socket) {
            for (int j = i; j < num_clients - 1; j++) {
                clients[j] = clients[j + 1];
            }
            num_clients--;
            break;
        }
    }

    // Close client socket
    close(client_socket);
}

int main(int argc, char const* argv[]) {
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

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
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
    