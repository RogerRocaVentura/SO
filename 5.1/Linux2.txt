#!/bin/bash

# Verificar que se proporciona un parámetro
if [ $# -eq 0 ]; then
  echo "Error: debe proporcionar una palabra como parámetro."
  exit 1
fi

# Pedir al usuario que introduzca una frase
echo "Introduzca una frase para añadir al final de los ficheros:"
read frase

# Recorrer los archivos de texto que contienen la palabra del parámetro
for archivo in *"$1"*.txt; do
  # Añadir la frase al final de cada archivo
  echo "$frase" >> "$archivo"
  echo "Frase añadida al archivo $archivo"
done

echo "Proceso completado."
