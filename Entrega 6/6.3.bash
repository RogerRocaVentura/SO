echo $HOME

#!/bin/bash

for file in a*.txt; do
   dni=$(sed -n '3p' $file)
   echo $dni >> $1
done

echo "El archivo $1 ha sido creado."
