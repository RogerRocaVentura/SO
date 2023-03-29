#include <stdio.h>
#include <sqlite3.h> // Librería SQLite

int main() {
    sqlite3 *6.1; 
    char *zErrMsg = 0;
    int rc;
    char actividad[50];
    

    rc = sqlite3_open("6.1.sql", &6.1);
    if (rc) {
        fprintf(stderr, "No se pudo abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    

    printf("Introduce el nombre de la actividad: ");
    scanf("%s", actividad);
    
    // Realizar la consulta
    char sql[200];
    sprintf(sql, "SELECT Usuarios.Nombre FROM Usuarios INNER JOIN Participaciones ON Usuarios.IdUsuario = Participaciones.IdUsuario INNER JOIN Actividades ON Participaciones.IdActividad = Actividades.IdActividad WHERE Actividades.Nombre = '%s' AND Participaciones.Puntuacion <= 3", actividad);
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(6.1, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    
    
    printf("Usuarios que han valorado la actividad %s igual o por debajo de 3:\n", actividad);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("%s\n", sqlite3_column_text(stmt, 0));
    }
    
    
    sqlite3_finalize(stmt);
    sqlite3_close(6.1);
    
    return 0;
}
