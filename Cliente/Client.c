#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 8888
#define BUFFER_SIZE 1024

void insert_player(int sock) {
    char message[BUFFER_SIZE], buffer[BUFFER_SIZE];

    printf("Enter player name: ");
    fgets(message, BUFFER_SIZE, stdin);
    send(sock, message, strlen(message), 0);

    printf("Enter player ELO rating: ");
    fgets(message, BUFFER_SIZE, stdin);
    send(sock, message, strlen(message), 0);

    recv(sock, buffer, BUFFER_SIZE, 0);
    printf("%s", buffer);
}

void delete_player(int sock) {
    char message[BUFFER_SIZE], buffer[BUFFER_SIZE];

    printf("Enter player name to delete: ");
    fgets(message, BUFFER_SIZE, stdin);
    send(sock, message, strlen(message), 0);

    recv(sock, buffer, BUFFER_SIZE, 0);
    printf("%s", buffer);
}

void list_players(int sock) {
    char buffer[BUFFER_SIZE];

    send(sock, "list", strlen("list"), 0);

    while (recv(sock, buffer, BUFFER_SIZE, 0) > 0) {
        printf("%s", buffer);
    }
}

void quit(int sock) {
    send(sock, "quit", strlen("quit"), 0);
    close(sock);
    exit(EXIT_SUCCESS);
}

int main() {
    int sock = 0, read_size;
    struct sockaddr_in server;
    char message[BUFFER_SIZE], buffer[BUFFER_SIZE];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Failed to create socket\n");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);

    if (inet_pton(AF_INET, SERVER_ADDRESS, &server.sin_addr) <= 0) {
        perror("Invalid address\n");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Failed to connect to server\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter command: ");
    fgets(message, BUFFER_SIZE, stdin);

    if (send(sock, message, strlen(message), 0) < 0) {
        perror("Failed to send data to server\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp(message, "insert\n") == 0) {
        insert_player(sock);
    } else if (strcmp(message, "delete\n") == 0) {
        delete_player(sock);
    } else if (strcmp(message, "list\n") == 0) {
        list_players(sock);
    } else if (strcmp(message, "quit\n") == 0) {
        quit(sock);
    }

    return 0;
}
