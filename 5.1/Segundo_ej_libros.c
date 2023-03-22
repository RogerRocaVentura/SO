#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int libros_populares(int n, char *libros, char *resultados[]) {
    int num_resultados = 0; // Inicializamos el contador de resultados a 0
    char *token = strtok(libros, "/"); // Obtenemos el primer libro de la lista
    while (token != NULL) {
        char *titulo = strtok(token, "*"); // Separamos el título del precio
        char *precio = strtok(NULL, "*");
        int likes = atoi(precio); // Convertimos el precio a entero
        if (likes > n) { // Comprobamos si el libro tiene más de N likes
            resultados[num_resultados] = token; // Añadimos el libro al vector de resultados
            num_resultados++; // Incrementamos el contador de resultados
        }
        token = strtok(NULL, "/"); // Obtenemos el siguiente libro de la lista
    }
    return num_resultados; // Devolvemos el número de resultados obtenidos
}