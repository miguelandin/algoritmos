# Ejer2 — Algoritmos de Ordenación y Combinaciones

Este directorio contiene tres algoritmos de ordenación clásicos basados en
comparación (burbuja, inserción y selección) y un programa para calcular
números combinatorios mediante factoriales.

Todos los programas de ordenación leen por entrada estándar el tamaño `n` y
luego los `n` elementos del array, y van imprimiendo el estado del array tras
cada paso del algoritmo (útil para ver la traza de ejecución).

---

## 1. Ordenación de la burbuja (`burbuja.cpp`)

### Idea principal
Recorre repetidamente el array comparando pares de elementos adyacentes e
intercambiándolos si están en el orden incorrecto. En cada pasada, el elemento
mayor "burbujea" hacia el final.

### Técnica algorítmica
Fuerza bruta / comparación e intercambio. No utiliza memoria auxiliar: trabaja
*in place* sobre el array de entrada.

### Cómo funciona el código
```cpp
for (int i = 0; i < tam - 1; i++) {
    for (int j = 0; j < tam - 1; j++) {
        if (array[j] > array[j + 1]) {
            temp = array[j];
            array[j] = array[j + 1];
            array[j + 1] = temp;
        }
    }
}
```
El bucle externo (`i`) controla el número de pasadas. El bucle interno (`j`)
compara cada par adyacente y los intercambia usando una variable temporal
`temp`. El array se imprime durante el recorrido para mostrar la evolución.

Nota: esta implementación siempre realiza el número completo de pasadas (no se
detiene aunque el array ya esté ordenado), por lo que no aplica la optimización
del "centinela".

### Complejidad
- **Temporal:** T(n) = n(n-1)/2 → **O(n²)** en todos los casos.
- **Espacial:** **O(1)** (opera sobre el array de entrada).

---

## 2. Ordenación por inserción (`insercion.cpp`)

### Idea principal
Construye la secuencia ordenada elemento a elemento: toma cada nuevo elemento y
lo inserta en su posición correcta dentro de la parte ya ordenada situada a su
izquierda, desplazando hacia la derecha los elementos mayores.

### Técnica algorítmica
Comparación con desplazamiento, *in place*. Es eficiente cuando el array está
casi ordenado.

### Cómo funciona el código
```cpp
for (int i = 1; i < len; i++) {
    temp = x[i];      // elemento a insertar
    j = i - 1;
    while (j >= 0 && x[j] > temp) { // desplaza los mayores a la derecha
        x[j + 1] = x[j];
        j--;
    }
    x[j + 1] = temp;  // coloca el elemento en su hueco
}
```
Por cada `i`, se guarda `x[i]` en `temp` y el bucle `while` recorre hacia atrás
desplazando todos los elementos mayores que `temp` una posición a la derecha,
dejando un hueco donde finalmente se inserta `temp`.

### Complejidad
- **Temporal:** **O(n²)** en el peor caso (array inverso); **O(n)** en el mejor
  caso (array ya ordenado). La cota indicada en el código, n(n-1)/2, corresponde
  al peor caso.
- **Espacial:** **O(1)**.

---

## 3. Ordenación por selección (`seleccion.cpp`)

### Idea principal
En cada iteración busca el elemento mínimo del subarray no ordenado y lo coloca
en la posición correspondiente al inicio de dicho subarray.

### Técnica algorítmica
Comparación e intercambio, *in place*.

### Cómo funciona el código
```cpp
for (int i = 0; i < len; i++) {
    encontrado = false;
    temp = x[i];
    for (int j = i + 1; j < len; j++)
        if (temp > x[j]) {     // se encontró un valor menor
            temp = x[j];
            pos = j;
            encontrado = true;
        }
    if (encontrado) {          // intercambia el mínimo con la posición i
        x[pos] = x[i];
        x[i] = temp;
    }
}
```
El bucle interno recorre desde `i+1` hasta el final guardando el menor valor en
`temp` y su posición en `pos`. Si se encontró un valor menor (`encontrado`), se
intercambia con `x[i]`. El uso del booleano `encontrado` evita intercambios
innecesarios cuando `x[i]` ya es el mínimo.

### Complejidad
- **Temporal:** T(n) = n(n-1)/2 → **O(n²)** en todos los casos (siempre realiza
  todas las comparaciones).
- **Espacial:** **O(1)**.

---

## 4. Números combinatorios (`Combinaciones.cpp`)

### Idea principal
Calcula el número combinatorio C(n, r) = n! / (r! · (n−r)!) usando una función
factorial recursiva. Lee pares `(n, r)` en bucle hasta que alguno sea negativo.

### Técnica algorítmica
Recursión sobre el factorial (cálculo directo mediante la fórmula).

### Cómo funciona el código
```cpp
res = factorial(n) / (factorial(r) * factorial(n - r));

int factorial(int entrada) {
    if (entrada <= 1) return 1;            // caso base
    else return entrada * factorial(entrada - 1);
}
```
El bucle principal lee `n` y `r`; termina si alguno es negativo e imprime
`ERROR` si `r > n` (combinación no definida). En caso válido aplica la fórmula
del coeficiente binomial.

Limitación: al usar enteros, el factorial desborda aproximadamente a partir de
`13!`, por lo que solo es fiable para valores de `n` pequeños.

### Complejidad
- **Temporal:** cada `factorial` es **O(n)**; el cálculo total por consulta es
  **O(n)**.
- **Espacial:** **O(n)** por la pila de recursión del factorial.
