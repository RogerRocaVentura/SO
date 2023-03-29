#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "ChessDB"

MYSQL* conn;

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

int insert_player(char* name, char* country, char* date_of_birth, int rating) {
    char query[256];
    sprintf(query, "INSERT INTO players (name, country, date_of_birth, rating) VALUES ('%s', '%s', '%s', %d)", name, country, date_of_birth, rating);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Failed to insert player: %s\n", mysql_error(conn));
        return 0;
    }

    return 1;
}

void print_player_info(MYSQL_ROW row) {
    printf("ID: %s\n", row[0]);
    printf("Name: %s\n", row[1]);
    printf("Country: %s\n", row[2]);
    printf("Date of Birth: %s\n", row[3]);
    printf("Rating: %s\n", row[4]);
}

void select_players() {
    if (mysql_query(conn, "SELECT * FROM players")) {
        fprintf(stderr, "Failed to select players: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "Failed to store result: %s\n", mysql_error(conn));
        return;
    }

    printf("Players:\n");
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

// This code uses the MySQL C Connector library to connect to the chess_db database and perform some basic database operations.
// The connect_to_db() function initializes the database connection and returns 1 if successful, 0 otherwise.
// The close_db_connection() function closes the database connection.The insert_player() function inserts a new player into the players table.
// The print_player_info() function prints the information of a single player.
// The select_players() function selects all players from the players table and prints their information using the print_player_info() function.
