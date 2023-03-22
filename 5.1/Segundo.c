#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITULO 100


struct libro {
  char titulo[MAX_TITULO];
  char autor[100];
  int precio;
  int likes;
};

char* libros_mas_populares(int N, struct Libro* libros, int num_libros) {
  char* result = malloc(sizeof(char) * MAX_TITULO * num_libros);
  int result_idx = 0;
  
  for (int i = 0; i < num_libros; i++) {
    if (libros[i].likes > N) {
      sprintf(result + result_idx, "%s*%d/", libros[i].titulo, libros[i].precio);
      result_idx += strlen(libros[i].titulo) + 1 + snprintf(NULL, 0, "%d", libros[i].precio);
    }
  }
  
  if (result_idx > 0) {
    result[result_idx - 1] = '\0';  // eliminamos el último '/'
  } else {
    result[0] = '\0';  // en caso de que no haya libros populares
  }
  
  return result;
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#char* libros_populares(int likes[], char* titulos[], int precios[], int n, int N) {
    #char** libros = (char**) malloc(n * sizeof(char*));
    #int num_libros = 0;

    #for (int i = 0; i < n; i++) {
        #if (likes[i] > N) {
         #   char* titulo_precio = (char*) malloc(100 * sizeof(char));
          #  sprintf(titulo_precio, "%s*%d", titulos[i], precios[i]);
           # libros[num_libros++] = titulo_precio;
        }
    }

    # char* resultado = (char*) malloc(1000 * sizeof(char));
   # strcpy(resultado, libros[0]);
   # for (int i = 1; i < num_libros; i++) {
    #    strcat(resultado, "/");
     #   strcat(resultado, libros[i]);
    }

   # return resultado;
}

