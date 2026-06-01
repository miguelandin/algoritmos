# Ejer7/Hanoi — Torres de Hanói con pilas

Resuelve el clásico problema de las **Torres de Hanói** modelando cada poste como una
**pila (LIFO)** enlazada y moviendo los discos mediante recursión.

## Estructura de datos: la pila
- `Nodo` (`Nodo.h`): un `int valor` (número de disco) y un puntero `Nodo* siguiente`.
- `Pila` (`Pila.h` / `Pila.cpp`): pila enlazada con puntero `cima` y un nombre (`name`,
  identifica el poste: "A", "B", "C").
  - **`apilar(num)`**: crea un nuevo nodo cuyo `siguiente` es la antigua cima y lo convierte
    en la nueva cima. `O(1)`.
  - **`desapilar()`**: guarda el valor de la cima, mueve la cima al nodo de abajo, libera el
    nodo y devuelve el valor. `O(1)`.
  - **`estaVacia()`**: comprueba si la cima es `nullptr`. `O(1)`.
  - **`nombrePila()`**: devuelve el nombre del poste.
  - Tanto `apilar` como `desapilar` imprimen el movimiento por consola.

La pila es la estructura natural porque en Hanói siempre se manipula el disco superior de un
poste, exactamente como un LIFO.

## Idea principal y técnica del algoritmo
**Divide y vencerás / recursión.** Para mover `n` discos del poste origen al destino usando
uno temporal:
1. Mover los `n-1` discos superiores de origen a temporal.
2. Mover el disco `n` (el más grande) de origen a destino.
3. Mover los `n-1` discos de temporal a destino.

Esto respeta la regla de no colocar nunca un disco mayor sobre uno menor.

## Cómo funciona el código (`Hanoi.cpp`)
- `Hanoi(n, origen, destino, temporal)`:
  - Caso base: si `n == 0`, no hace nada.
  - Recursión: `Hanoi(n-1, origen, temporal, destino)`, luego
    `destino->apilar(origen->desapilar())` (el movimiento real), y por último
    `Hanoi(n-1, temporal, destino, origen)`.
- `main()`:
  - Crea los tres postes `A`, `B`, `C`.
  - Lee `n` y apila los discos `n, n-1, ..., 1` en `A` (el mayor abajo, el menor arriba).
  - Comprueba la precondición con `assertdomjudge` y llama a `Hanoi(n, A, C, B)`.
  - Finalmente desapila los `n` discos de `C`.

## Complejidad
Según las anotaciones del código:
- Tiempo: `T(n) = O(2^n)` (el número de movimientos es `2^n - 1`).
- Memoria: `M(n) = O(n)` por la profundidad de la recursión.
