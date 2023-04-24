#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define DB_HOST "localhost"
#define DB_NAME "ChessDB"

#define BUFFER_SIZE 1024
#define PORT 8888

#define MAX_PLAYERS 100

struct sockaddr_in players[MAX_PLAYERS];
int num_players = 0;

MYSQL *conn;

typedef struct {
    int socket;
    char *name;
} player_t;

player_t players[100];
int num_players = 0;

int connect_to_db() {
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "Error al inicializar la base de datos: %s\n", mysql_error(conn));
        return 0;
    }

    if (mysql_real_connect(conn, DB_HOST, "root", "", DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Error al conectar a la base de datos: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    printf("Conectado a la base de datos: %s\n", DB_NAME);

    return 1;
}

void close_db_connection() {
    mysql_close(conn);
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int read_size;

    // Add new client to the connected players list
	// Note that we are using a mutex to protect the shared connected_players array,
	// so that multiple threads cannot access it simultaneously and cause a race condition.

    pthread_mutex_lock(&connected_players_mutex);
    connected_players[num_connected_players++] = client_socket;
    pthread_mutex_unlock(&connected_players_mutex);

    while ((read_size = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[read_size] = '\0';

        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        if (strncmp(buffer, "INSERT", 6) == 0) {
            if (mysql_query(conn, buffer)) {
                fprintf(stderr, "Error en la consulta: %s\n", mysql_error(conn));
                return;
            }
            else {
                if (send(client_socket, "Query ejecutada correctamente", strlen("Query ejecutada correctamente"), 0) < 0) {
                    fprintf(stderr, "Error al enviar los datos al cliente\n");
                    return;
                }
            }
        }

        else {
            if (mysql_query(conn, buffer)) {
                fprintf(stderr, "Error en la consulta: %s\n", mysql_error(conn));
                return;
            }

            MYSQL_RES *result;
            MYSQL_ROW row;

            result = mysql_store_result(conn);

            if (result == NULL) {
                if (send(client_socket, mysql_error(conn), strlen(mysql_error(conn)), 0) < 0) {
                    fprintf(stderr, "Error al enviar los datos al cliente\n");
                    return;
                }
            } else {
                while ((row = mysql_fetch_row(result))) {
                    sprintf(buffer, "%s, %s, %s, %s, %s\n", row[0], row[1], row[2], row[3], row[4]);

                    if (send(client_socket, buffer, strlen(buffer), 0) < 0) {
                        fprintf(stderr, "Error al enviar los datos al cliente\n");
                        return;
                    }
                }

                mysql_free_result(result);
            }
        }
    }

    // Remove client from the connected players list
    pthread_mutex_lock(&connected_players_mutex);
    for (int i = 0; i < num_connected_players; i++) {
        if (connected_players[i] == client_socket) {
            connected_players[i] = connected_players[--num_connected_players];
            break;
        }
    }
    pthread_mutex_unlock(&connected_players_mutex);

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
        perror("Error creando el socket\n");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Error inicializando el socket\n");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);
	if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Error en el bind\n");
    exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0) {
        perror("Error escuchando\n");
        exit(EXIT_FAILURE);
    }

    printf("El servidor esta funcionando en el puerto: %d\n", PORT);

    while (1) {
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, (socklen_t *)&addrlen)) < 0) {
            perror("Error al aceptar la conexión\n");
            exit(EXIT_FAILURE);
        }

        printf("Nuevo cliente aceptado\n");

        handle_client(client_socket);

        printf("Conexion cerrada\n");

        // Query to get the list of connected players
        char *connected_players_query = "SELECT * FROM players WHERE connected=1";
        sqlite3_stmt *stmt;
        if (sqlite3_prepare_v2(db, connected_players_query, -1, &stmt, NULL) == SQLITE_OK) {
            printf("\nLista de jugadores conectados:\n");
            printf("---------------------------------\n");
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                int id = sqlite3_column_int(stmt, 0);
                char *name = (char *) sqlite3_column_text(stmt, 1);
                printf("ID: %d, Nombre: %s\n", id, name);
            }
            printf("---------------------------------\n");
            sqlite3_finalize(stmt);
        } else {
            fprintf(stderr, "Error ejecutando la consulta: %s\n", sqlite3_errmsg(db));
        }
    }

    close_db_connection();

    return 0;
}

//Mutual exclusion should be used in the list of players whenever multiple threads might access or modify the list simultaneously. 
//In the current implementation of the server, each connection is handled by a separate thread. 
//Therefore, it is possible for multiple threads to try to access or modify the list of players simultaneously. 
//To ensure that the list is not corrupted by concurrent access, mutual exclusion should be used to prevent
//multiple threads from accessing or modifying the list at the same time. 
//One way to achieve mutual exclusion in this scenario is to use a lock or mutex around any code that modifies the list of players.