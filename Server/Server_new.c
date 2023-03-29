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
        fprintf(stderr, "Error al inicializar la base de datos: %s\n", mysql_error(conn));
        return 0;
    }

    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Error al conectarse a la base de datos: %s\n", mysql_error(conn));
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

        if (strcmp(buffer, "exit") == 0) {
            break;
        }

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

        printf("El servidor está funcionando en el puerto: %d\n", PORT);

    while (1) {
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, (socklen_t *)&addrlen)) < 0) {
            perror("Error al aceptar la conexión\n");
            exit(EXIT_FAILURE);
         }

        printf("Nuevo cliente aceptado\n");

        handle_client(client_socket);

        printf("Conexión cerrada\n");
     }

close_db_connection();

return 0;

}