#include <stdio.h>

struct libro {
  char titulo[50];
  char autor[50];
  int precio;
  int likes;
};

int main() {
  struct libro libros[100];
  // Ahora se puede acceder a cada campo de cada libro en el arreglo 'libros'
  libros[0].precio = 20;
  libros[1].likes = 50;
  // ... y así sucesivamente
  return 0;
}