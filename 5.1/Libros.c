#include <stdio.h>

struct libro {
  char titulo[50];
  char autor[50];
  int precio;
  int likes;
};

int main() {
  struct libro libros[100];
  
  libros[0].precio = 20;
  libros[1].likes = 50;
 
  return 0;
}
