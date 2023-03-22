#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct libro {
  char titulo[50];
  int precio;
  int likes;
};

int libros_con_mas_likes(struct libro* libros, int n_libros, int n_likes, char* resultado) {
  int i, j = 0;
  for (i = 0; i < n_libros; i++) {
    if (libros[i].likes > n_likes) {
      // Agregar título y precio al resultado
      int len = strlen(libros[i].titulo) + 10; // +10 para precio máximo de 999999
      char temp[len];
      sprintf(temp, "%s*%d/", libros[i].titulo, libros[i].precio);
      strcat(resultado, temp);
      j++;
    }
  }
  return j;
}

int main() {
  struct libro mis_libros[] = {
    {"La odisea", 23, 50},
    {"Un mundo feliz", 42, 30},
    {"La metamorfosis", 15, 10},
    {"El principito", 30, 15},
    {"1984", 25, 70},
    {"El gran Gatsby", 50, 20},
    {"Matar a un ruiseñor", 35, 5}
  };
  int n_libros = sizeof(mis_libros) / sizeof(struct libro);
  char resultado[500] = "";
  int n_likes = 20;

  int n = libros_con_mas_likes(mis_libros, n_libros, n_likes, resultado);

  printf("Libros con más de %d likes: %s\n", n_likes, resultado);
  printf("Total de libros: %d\n", n);

  return 0;
}
