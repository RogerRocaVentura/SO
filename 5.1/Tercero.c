#include <stdio.h>
#include <stdlib.h>

struct libro {
  char titulo[50];
  int precio;
  int likes;
};

int obtener_libros_populares(struct libro libros[], int n, char resultado[]);

int main() {
  int i, n, num_likes, num_libros_populares;
  char resultado[500] = "";
  struct libro libros[10] = {
    {"La odisea", 20, 50},
    {"Un mundo feliz", 15, 30},
    {"La metamorfosis", 10, 25},
    {"El gran Gatsby", 18, 40},
    {"Cien años de soledad", 25, 60},
    {"1984", 12, 35},
    {"La Divina Comedia", 30, 70},
    {"El viejo y el mar", 16, 45},
    {"Matar a un ruiseñor", 22, 55},
    {"Orgullo y prejuicio", 14, 20}
  };

  printf("Ingrese el número mínimo de likes para los libros: ");
  scanf("%d", &num_likes);

  num_libros_populares = obtener_libros_populares(libros, 10, resultado);

  printf("\nLibros con más de %d likes:\n", num_likes);
  for (i = 0; i < num_libros_populares; i++) {
    printf("%s\n", resultado);
    resultado += strlen(resultado) + 1; // Avanzar el puntero al siguiente libro
  }

  return 0;
}
