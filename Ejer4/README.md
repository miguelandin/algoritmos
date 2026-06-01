# Ejer4 — Programación Dinámica y Divide y Vencerás

Este directorio contiene dos ejemplos de técnicas algorítmicas avanzadas: el
cálculo de números combinatorios mediante **programación dinámica** (triángulo
de Pascal) y la ordenación por **mezcla (Merge Sort)**, ejemplo paradigmático de
**divide y vencerás**.

---

## 1. Combinaciones mediante programación dinámica (`combinacionesDinamica.cpp`)

### Idea principal
Calcula el número combinatorio C(n, r) precomputando el **triángulo de Pascal**.
Cada entrada del triángulo es la suma de las dos que tiene encima, lo que
corresponde a la recurrencia de Pascal:

C(n, r) = C(n−1, r−1) + C(n−1, r)

Una vez construida la tabla, cada consulta C(n, r) se responde en tiempo
constante leyendo `pascal[n][r]`.

### Técnica algorítmica
**Programación dinámica** (bottom-up / tabulación). Evita el recálculo y el
desbordamiento prematuro del factorial al no multiplicar factoriales grandes:
solo realiza sumas.

### Cómo funciona el código
```cpp
const int NIVEL = 10;

void iniciar(int pascal[NIVEL][NIVEL]) {
    for (int i = 0; i < NIVEL; i++) {
        pascal[i][0] = 1;                      // primera columna siempre 1
        for (int j = 1; j <= i; j++)
            pascal[i][j] = pascal[i-1][j-1] + pascal[i-1][j]; // recurrencia de Pascal
    }
}
```
En `main`, el array se inicializa a 0, se construye el triángulo con `iniciar` y
luego se leen pares `(n, r)` en bucle:
```cpp
std::cin >> n >> r;
if (n < 0) break;                                 // n negativo termina
assertdomjudge(n >= NIVEL || r > n);              // precondiciones: si fallan, ERROR y continúa
std::cout << pascal[n][r] << std::endl;
```
La macro `assertdomjudge` imprime `ERROR` y salta a la siguiente iteración si la
consulta queda fuera de la tabla (`n >= NIVEL`) o no es válida (`r > n`).

### Complejidad
- **Construcción de la tabla:** **O(n²)** en tiempo y **O(n²)** en espacio
  (`NIVEL × NIVEL`).
- **Cada consulta:** **O(1)** (acceso directo a la tabla).

---

## 2. Ordenación por mezcla — Merge Sort (`mergesort.cpp`)

### Idea principal
Divide el array en dos mitades, las ordena recursivamente y después las combina
(fusiona) en un único array ordenado. La fusión aprovecha que ambas mitades ya
están ordenadas para mezclarlas en tiempo lineal.

### Técnica algorítmica
**Divide y vencerás**: dividir (partir por la mitad), vencer (ordenar cada mitad
recursivamente) y combinar (mezclar las dos mitades ordenadas).

### Cómo funciona el código

**Función de mezcla** — recorre dos arrays ordenados y produce uno combinado:
```cpp
void combinar(int a[], int len_a, int b[], int len_b, int c[]) {
    int k = 0, j = 0, i = 0;
    while (k < len_a && j < len_b) {
        if (a[k] < b[j]) { c[i] = a[k]; k++; }   // toma el menor de cada array
        else             { c[i] = b[j]; j++; }
        i++;
    }
    while (k < len_a) { c[i++] = a[k++]; }        // resto de a
    while (j < len_b) { c[i++] = b[j++]; }        // resto de b
}
```

**Ordenación recursiva:**
```cpp
void ordenarMergeSort(int x[], int len) {
    if (len <= 1) return;                 // caso base

    int temp[len];
    int mid  = len / 2;
    int resto = len - mid;
    int* izq = x;                         // mitad izquierda
    int* der = &x[mid];                   // mitad derecha

    ordenarMergeSort(izq, mid);           // ordena izquierda
    ordenarMergeSort(der, resto);         // ordena derecha
    combinar(izq, mid, der, resto, temp); // mezcla en temp

    for (int k = 0; k < len; k++)         // copia el resultado de vuelta a x
        x[k] = temp[k];
}
```
Se divide en `mid = len/2` y `resto = len - mid`. Se usan punteros `izq` y `der`
hacia las dos mitades del mismo array (sin copiarlas para dividir). Tras ordenar
ambas recursivamente, `combinar` las fusiona en `temp` y se copia de vuelta a
`x`. El código imprime el array tras cada fusión para mostrar la traza.

### Complejidad
- **Temporal:** T(n) = 2·T(n/2) + n → **O(n log n)** en todos los casos.
- **Espacial:** **O(n)** por el array temporal `temp` usado en la fusión (más la
  pila de recursión O(log n)).
