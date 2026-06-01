# Ejer5 — Algoritmos voraces y backtracking

Este directorio contiene dos programas independientes en C++ que ilustran dos técnicas
clásicas de diseño de algoritmos: un **algoritmo voraz (greedy)** y un **algoritmo de
vuelta atrás (backtracking)**.

---

## 1. `devolverCambio.cpp` — Cambio de monedas (algoritmo voraz)

### Idea principal
Dada una cantidad de dinero, calcular cómo devolverla usando el **menor número de monedas**
posible, eligiendo en cada paso la moneda de mayor valor que aún quepa en la cantidad
restante. Es la estrategia voraz del problema del cambio.

El conjunto de monedas es fijo y está definido como una variable global:

```cpp
int monedas[LEN] = { 500, 200, 100, 50, 25, 10, 5, 1 };
```

### Técnica
**Voraz (greedy)**. En cada iteración se intenta usar la moneda actual (empezando por la de
mayor valor). Para este sistema de monedas concreto, la estrategia voraz es óptima.

### Cómo funciona el código
- `Cambio(int cantidad, int monedas[])`:
  - Mantiene un array `res[LEN]` con el contador de cada tipo de moneda (inicializado a 0).
  - Recorre el array de monedas con el índice `i`. Mientras quede cantidad por devolver:
    - Si restar la moneda actual (`monedas[i]`) no deja la cantidad negativa, la resta,
      incrementa su contador y **reinicia `i = 0`** para volver a probar desde la moneda
      más grande.
    - En caso contrario pasa a la siguiente moneda (`i++`), de menor valor.
  - Al terminar imprime el número de monedas de cada tipo en una línea.
- `main()` lee números por entrada estándar en bucle y procesa cada uno; se detiene al leer
  un valor negativo.

### Complejidad
Según las anotaciones del código:
- Tiempo: `T(n) = cantidad + LEN = O(n)`
- Memoria: `M(n) = LEN = O(n)` (el array `res`).

---

## 2. `laberinto.cpp` — Búsqueda del tesoro en un laberinto (backtracking)

### Idea principal
Sobre una matriz de caracteres de `TAM x TAM` (10x10) se busca un camino desde la esquina
superior izquierda `(0,0)` hasta una casilla objetivo marcada con `'T'` (tesoro). Si existe
camino se imprime el laberinto con el recorrido y la posición del tesoro; si no, se imprime
`INALCANZABLE`.

Simbología de las casillas:
- `'.'` hueco transitable
- `'*'` pared (no se puede pasar)
- `'X'` casilla ya recorrida / marcada
- `'T'` tesoro (meta)

### Técnica
**Backtracking (vuelta atrás) recursivo**. Desde cada casilla se prueban los 4 movimientos
posibles; si un camino no conduce a la solución, se deshace la marca y se prueba otra
dirección.

Los movimientos se codifican con dos arrays paralelos:

```cpp
int movX[LEN] = { -1, 0, 1, 0 };
int movY[LEN] = {  0, 1, 0, -1 };
```

### Cómo funciona el código
- `buscarTesoro(laberinto, x, y, sol_x, sol_y)`:
  - Para cada una de las 4 direcciones `f`, calcula la nueva posición `(i, j)`.
  - Comprueba que esté dentro de los límites y que no sea pared (`'*'`) ni casilla ya
    recorrida (`'X'`).
  - Si la casilla es un hueco (`'.'`), la marca como recorrida (`'X'`) y llama
    recursivamente. Si la llamada **falla**, restaura la casilla a `'.'` (esto es la vuelta
    atrás); si tiene éxito, devuelve `true`.
  - Si la casilla es el tesoro (`'T'`), guarda su posición en `sol_x`/`sol_y` y devuelve
    `true`.
  - Si ninguna dirección conduce a la solución, devuelve `false`.
- `main()`:
  - Reserva dinámicamente la matriz `char**`, lee los datos por entrada estándar.
  - Marca la posición inicial `(0,0)` como `'X'` y lanza la búsqueda.
  - Imprime el resultado (`imprimirLaberinto` + `ENCONTRADO x y`, o `INALCANZABLE`).
  - Libera la memoria reservada.

### Complejidad
Según las anotaciones del código:
- Tiempo: `T(n) = 4·T(n-1) + 1 → O(4^n)` (en el peor caso se exploran las 4 direcciones por
  nivel de recursión).
- Memoria: `M(n) = n + 1 = O(n)` por la profundidad de la pila de recursión.
