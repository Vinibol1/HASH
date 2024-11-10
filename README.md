<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA HASH

## Repositorio de Tobias Portella - 112257 - tobias240405@gmail.com

- Para compilar:

```bash
gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g src/*.c tp_hash.c -o tp_hash 
```

- Para ejecutar:

```bash
./tp_hash pokedex.csv
```

- Para ejecutar con valgrind:
```bash
valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes ./tp_hash pokedex.csv
```
---
##  Funcionamiento

Explicación de cómo funcionan las estructuras desarrolladas en el TP y el funcionamiento general del mismo.

Aclarar en esta parte todas las decisiones que se tomaron al realizar el TP, cosas que no se aclaren en el enunciado, fragmentos de código que necesiten explicación extra, etc.

Incluir **EN TODOS LOS TPS** los diagramas relevantes al problema (mayormente diagramas de memoria para explicar las estructuras, pero se pueden utilizar otros diagramas si es necesario).

### Por ejemplo:

El programa funciona abriendo el archivo pasado como parámetro y leyendolo línea por línea. Por cada línea crea un registro e intenta agregarlo al vector. La función de lectura intenta leer todo el archivo o hasta encontrar el primer error. Devuelve un vector con todos los registros creados.

<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>

En el archivo `sarasa.c` la función `funcion1` utiliza `realloc` para agrandar la zona de memoria utilizada para conquistar el mundo. El resultado de `realloc` lo guardo en una variable auxiliar para no perder el puntero original en caso de error:

```c
int *vector = realloc(vector_original, (n+1)*sizeof(int));

if(vector == NULL)
    return -1;
vector_original = vector;
```


<div align="center">
<img width="70%" src="img/diagrama2.svg">
</div>

---

## Respuestas a las preguntas teóricas
---Un diccionarios es un TDA el cual se caracteriza por tener una clave asociada a los valores ingresados, por lo que se buscaría al elemento por la clave y no por el valor, no existen las claves repetidas
Incluír acá las respuestas a las preguntas del enunciado (si aplica).

<div align="center">
<img width="70%" src="img/diccionario.png">
</div>

---Una forma de implementar un diccionario es con una tabla de hash, esta implementación usa una función de hash para transformar la clave en un indice de la tabla, intentando acercar su busqueda a una complejidad de O(1). otra forma de implementar un diccionario seria con una lista y que cada elemento de la lista sea una estructura que almacene la clave y el valor, esto tendría una complejidad para buscar de O(n). un diccionario se podria implementar con infinidad de estructuras de datos, otro ejemplo de esto sería implementarlo con un abb y almacenar una estructura con clave y valor de elemento.


---Una función hash es una función que convierte un elemento pasado en otro, ya sea un numero, una cadena, etc, siendo estos elementos de salida finitos, esta función en nuestro caso necesitamos que dado una cadena de caracteres la salida seam enteros, vamos a tratar que la función de un numero diferente para distintas cadena de caracteres así cada cadenas tiene un propio numero asociado.

<div align="center">
<img width="70%" src="img/funcion_hash.png">
</div>



   - Qué es una tabla de Hash y los diferentes métodos de resolución de colisiones vistos (encadenamiento, probing, etc)
   - Explique por qué es importante el tamaño de la tabla (tanto para tablas abiertas como cerradas)
     - Dado que en una tabla abierta se pueden encadenar colisiones sin importar el tamaño de la tabla, ¿Realmente importa el tamaño?
   - Mas te vale que expliques con dibujos