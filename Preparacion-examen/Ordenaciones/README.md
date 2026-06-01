# Algoritmos de Ordenación

Este directorio contiene tres algoritmos clásicos de ordenación por comparación, todos sobre un array de enteros leído desde la entrada estándar. Cada programa imprime el array tras cada pasada para visualizar el progreso de la ordenación.

Los tres comparten la misma estructura de `main`: leen el tamaño `tam`, reservan el array dinámicamente, lo rellenan y lo ordenan. Todos son algoritmos **in situ** (espacio adicional **O(1)**) y de coste temporal **O(n²)**.

---

## Bubble Sort (Ordenación por Burbuja) — `BubbleShort.cpp`

### Idea principal

Recorre repetidamente el array comparando pares de elementos adyacentes e intercambiándolos si están en el orden incorrecto. En cada pasada, el elemento mayor "burbujea" hacia el final.

### Técnica e implementación

```cpp
void ordenarBurbuja(int* numeros, int tam)
{
    int temp1, temp2;
    for (int i = 0; i < tam - 1; i++) {
        for (int j = 0; j < tam - i; j++) {
            temp1 = numeros[j];
            temp2 = numeros[j + 1];
            if (temp1 > temp2) {       // intercambio si están desordenados
                numeros[j]     = temp2;
                numeros[j + 1] = temp1;
            }
        }
        imprimir(numeros, tam);
    }
}
```

- El bucle externo (`i`) cuenta las pasadas; el interno (`j`) compara pares adyacentes.
- Tras cada pasada se imprime el estado del array.

> **Aviso de implementación**: el bucle interno usa `j < tam - i` y accede a `numeros[j + 1]`. En la primera pasada (`i = 0`), `j` llega hasta `tam - 1` y `numeros[j + 1]` accede a `numeros[tam]`, **fuera de los límites del array**. La cota correcta sería `j < tam - 1 - i`.

### Complejidad

- **Tiempo**: O(n²) en todos los casos (esta versión no detecta si el array ya está ordenado).
- **Espacio**: O(1).

---

## Insertion Sort (Ordenación por Inserción) — `InsertionShort.cpp`

### Idea principal

Construye la parte ordenada del array elemento a elemento: toma cada elemento y lo "inserta" en su posición correcta dentro de la sublista ya ordenada a su izquierda, desplazando los mayores hacia la derecha.

### Técnica e implementación

```cpp
void ordenarInserccion(int* numeros, int tam)
{
    int temp;
    for (int i = 0; i < tam; i++) {
        temp = numeros[i];
        int j = i;
        while (temp < numeros[j - 1] && j > 0) {   // desplaza mayores a la derecha
            numeros[j] = numeros[j - 1];
            j--;
        }
        numeros[j] = temp;        // inserta en su hueco
        imprimir(numeros, tam);
    }
}
```

- `temp` guarda el elemento a insertar.
- El `while` desplaza hacia la derecha los elementos mayores que `temp` hasta encontrar su posición.

> **Aviso de implementación**: la condición es `temp < numeros[j - 1] && j > 0`. Al evaluarse de izquierda a derecha, cuando `j == 0` se accede primero a `numeros[-1]` antes de comprobar `j > 0`. Lo seguro sería invertir el orden: `j > 0 && temp < numeros[j - 1]`.

### Complejidad

- **Tiempo**: O(n²) en el peor caso; O(n) si el array ya está casi ordenado (pocos desplazamientos).
- **Espacio**: O(1).
- Es un algoritmo **estable**.

---

## Selection Sort (Ordenación por Selección) — `SelectionShort.cpp`

### Idea principal

En cada iteración busca el elemento mínimo del subarray no ordenado y lo coloca en su posición definitiva al principio de dicho subarray.

### Técnica e implementación

```cpp
void ordenarSeleccion(int* numeros, int tam)
{
    int temp, pos;
    for (int i = 0; i < tam; i++) {
        temp = numeros[i];
        pos = i;
        for (int j = i; j < tam; j++) {   // busca el mínimo desde i
            if (temp > numeros[j]) {
                temp = numeros[j];
                pos = j;
            }
        }
        numeros[pos] = numeros[i];        // intercambia mínimo con la posición i
        numeros[i]   = temp;
        imprimir(numeros, tam);
    }
}
```

- El bucle interno encuentra el mínimo del rango `[i, tam)` y guarda su valor (`temp`) y posición (`pos`).
- Luego intercambia ese mínimo con `numeros[i]`.

### Complejidad

- **Tiempo**: O(n²) en todos los casos (siempre recorre el subarray completo para hallar el mínimo).
- **Espacio**: O(1).
- Realiza un número mínimo de intercambios (a lo sumo n).

---

## Resumen comparativo

| Algoritmo  | Mejor caso | Peor caso | Espacio | Estable |
|------------|------------|-----------|---------|---------|
| Burbuja    | O(n²)\*    | O(n²)     | O(1)    | Sí      |
| Inserción  | O(n)       | O(n²)     | O(1)    | Sí      |
| Selección  | O(n²)      | O(n²)     | O(1)    | No      |

\* Esta implementación de burbuja no incorpora la optimización de parada anticipada, por lo que su mejor caso también es O(n²).

### Entrada / salida (los tres)

- **Entrada**: el tamaño `tam` seguido de `tam` enteros.
- **Salida**: el array tras cada pasada del algoritmo.
