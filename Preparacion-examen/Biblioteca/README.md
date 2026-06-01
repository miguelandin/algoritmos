# Lista Contigua (Biblioteca)

Implementación de una **lista de enteros sobre un array contiguo dinámico** con crecimiento y decrecimiento por bloques de tamaño fijo (`incremento`).

## Idea principal

Mantener los elementos en memoria contigua (`int* vector`) y redimensionar el bloque solo cuando es necesario: al llenarse se amplía en `incremento` posiciones, y cuando sobra más de un bloque se reduce. Las inserciones y borrados en una posición arbitraria se hacen desplazando el resto de elementos.

## Técnica algorítmica

- **Array dinámico amortizado** con redimensionado por bloques mediante `realloc`.
- Desplazamiento de elementos con `memmove` para mantener la contigüidad al insertar/eliminar en posiciones intermedias.

## Complejidad

| Operación | Complejidad |
|-----------|-------------|
| `elemento(pos)`, `modificar(pos)` | O(1) |
| `insertar(pos, val)` | O(n) (desplazamiento + posible `realloc`) |
| `eliminar(pos)` | O(n) |
| `imprimir()` | O(n) |

Memoria O(capacidad), donde `capacidad` es múltiplo de `incremento`.

## Cómo funciona el código

Atributos (ver `ListaContigua.h`): `vector` (datos), `n` (número de elementos), `capacidad` (espacio reservado) e `incremento` (tamaño del bloque de crecimiento).

- **Constructor `ListaContigua(incremento)`**: guarda el incremento, pone `capacidad = n = 0` y `vector = nullptr`.
- **`insertar(pos, val)`**: si está llena (`n == capacidad`), amplía el array con `realloc` sumando `incremento` a la capacidad. Luego usa `memmove` para desplazar a la derecha los elementos desde `pos`, e inserta `val` en `pos`. Incrementa `n`.
- **`eliminar(pos)`**: si sobra un bloque entero (`capacidad - incremento > n`), reduce la capacidad con `realloc`. Con `memmove` desplaza a la izquierda los elementos posteriores a `pos` y decrementa `n`.
- **`modificar(pos, val)`**: asigna directamente `vector[pos] = val`.
- **`elemento(pos)`**: devuelve `vector[pos]`.
- **`estaLlena()`**: devuelve `n == capacidad`.
- **`imprimir()`**: imprime los `n` elementos separados por espacios.
- **Destructor**: libera la memoria y resetea los contadores.

## Programa de prueba (`Main.cpp`)

Crea una lista con `incremento = 2`, inserta 10 valores, realiza varios `eliminar` e `insertar` en distintas posiciones, imprime el estado tras cada operación y comprueba `estaLlena()`.

## Notas / observaciones del código

- El destructor usa `delete[]` sobre memoria reservada con `realloc`; lo coherente con `realloc` sería `free`. Además, `insertar`/`eliminar` no validan que `pos` esté dentro de rango, por lo que el programa de prueba asume índices válidos.
