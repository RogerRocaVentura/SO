#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "ChessDB"

MYSQL* conn;

int ConexiónDB() {
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "Error inicializando: %s\n", mysql_error(conn));
        return 0;
    }

    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Error de conexión: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    return 1;
}

void close_db_connection() {
    mysql_close(conn);
}

int insert_player(char* name, char* country, char* date_of_birth, int rating) {
    char query[256];
    sprintf(query, "Insertar en (name, country, date_of_birth, rating) VALUES ('%s', '%s', '%s', %d)", name, country, date_of_birth, rating);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error al insertar jugador: %s\n", mysql_error(conn));
        return 0;
    }

    return 1;
}

void print_player_info(MYSQL_ROW row) {
    printf("ID: %s\n", row[0]);
    printf("Nombre: %s\n", row[1]);
    printf("País: %s\n", row[2]);
    printf("Fecha de nacimiento: %s\n", row[3]);
    printf("Elo: %s\n", row[4]);
}

void select_players() {
    if (mysql_query(conn, "Seleccione jugador")) {
        fprintf(stderr, "Error al seleccionar jugador: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "Error al guardar el resultado: %s\n", mysql_error(conn));
        return;
    }

    printf("Jugadores:\n");
    while (MYSQL_ROW row = mysql_fetch_row(result)) {
        print_player_info(row);
        printf("\n");
    }

    mysql_free_result(result);
}

int main() {
    if (!connect_to_db()) {
        exit(EXIT_FAILURE);
    }

    insert_player("Viswanathan Anand", "India", "1969-12-11", 2770);
    insert_player("Vladimir Kramnik", "Russia", "1975-06-25", 2782);

    select_players();

    close_db_connection();

    return 0;
}

