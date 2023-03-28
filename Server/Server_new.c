#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "chess_db"

#define BUFFER_SIZE 1024
#define PORT 8888

MYSQL *conn;

int connect_to_db() {
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "Failed to initialize database connection: %s\n", mysql_error(conn));
        return 0;
    }

    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Failed to connect to database: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    return 1;
}

void close_db_connection() {
    mysql_close(conn);
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int read_size;

    while ((read_size = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[read_size] = '\0';

        char *token;
        token = strtok(buffer, " ");

        if (strcmp(token, "SELECT") == 0) {
            MYSQL_RES *result;
            MYSQL_ROW row;

            if (mysql_query(conn, buffer)) {
                fprintf(stderr, "Failed to select players: %s\n", mysql_error(conn));
                return;
            }

            result = mysql_store_result(conn);

            while ((row = mysql_fetch_row(result))) {
                sprintf(buffer, "ID: %s\nName: %s\nCountry: %s\nDate of Birth: %s\nRating: %s\n",
                    row[0], row[1], row[2], row[3], row[4]);

                if (send(client_socket, buffer, strlen(buffer), 0) < 0) {
                    fprintf(stderr, "Failed to send data to client\n");
                    return;
                }
            }

            mysql_free_result(result);
        } else if (strcmp(token, "INSERT") == 0) {
            if (mysql_query(conn, buffer)) {
                fprintf(stderr, "Failed to insert player: %s\n", mysql_error(conn));
                return;
            }

            if (send(client_socket, "Player inserted\n", strlen("Player inserted\n"), 0) < 0) {
                fprintf(stderr, "Failed to send data to client\n");
                return;
            }
        } else {
            if (send(client_socket, "Invalid command\n", strlen("Invalid command\n"), 0) < 0) {
                fprintf(stderr, "Failed to send data to client\n");
                return;
            }
        }
    }

    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int opt = 1;
    int addrlen = sizeof(server_addr);

    if (!connect_to_db()) {
        exit(EXIT_FAILURE);
    }

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Failed to create server socket\n");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Failed to set socket options\n");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Failed to bind server socket\n");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0) {
        perror("Failed to listen to server socket\n");
        exit(EXIT_FAILURE);
    }

    printf("Server is running on port %d\n", PORT);

    while (1) {
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, (socklen_t *)&addrlen)) < 0) {
            perror("Failed to accept client connection\n");
            exit(EXIT_FAILURE);
         }

        printf("New client connection accepted\n");

        handle_client(client_socket);

        printf("Client connection closed\n");
     }

close_db_connection();

return 0;
