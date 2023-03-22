#include <stdio.h>

struct libro {
  char titulo[50];
  char autor[50];
  int precio;
  int likes;
};

int main() {
  struct libro libros[100];
  return 0;
}
