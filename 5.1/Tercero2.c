#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct libro {
  char titulo[50];
  int precio;
  int likes;
};

int obtener_libros_populares(struct libro libros[], int n, char resultado[]);

int main() {
  struct libro libros[100];
  char resultado[500] = "";
  int i, n, num_populares;

  // Pedir al usuario el número de libros y los datos de cada libro
  printf("Ingrese el número de libros: ");
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    printf("Ingrese el título del libro %d: ", i + 1);
    scanf("%s", libros[i].titulo);
    printf("Ingrese el precio del libro %d: ", i + 1);
    scanf("%d", &libros[i].precio);
    printf("Ingrese el número de likes del libro %d: ", i + 1);
    scanf("%d", &libros[i].likes);
  }

  // Pedir al usuario el número mínimo de likes para los libros populares
  printf("Ingrese el número mínimo de likes para los libros populares: ");
  scanf("%d", &num_populares);

  // Obtener los datos de los libros populares
  obtener_libros_populares(libros, n, resultado);

  // Imprimir los datos de los libros populares
  printf("\nLos libros populares con más de %d likes son:\n%s\n", num_populares, resultado);

  return 0;
}
