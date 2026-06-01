# Grafo "Roji-Blanco" — Comprobación de Bipartición (Lista de Adyacencia + BFS)

## Idea principal

Determina si un **grafo no dirigido** puede colorearse con **dos colores** (rojo y
blanco) de forma que **ningún par de vértices adyacentes comparta color**. Es decir,
comprueba si el grafo es **bipartito**. La respuesta es `SI` o `NO` por cada caso de
prueba.

## Técnica: BFS + coloreado a 2 colores

- El grafo se representa con **listas de adyacencia** (una lista enlazada de vecinos
  por vértice).
- Se recorre el grafo con un **BFS (búsqueda en anchura)** implementado con una cola
  basada en un array y dos índices (`frente`, `final`).
- Cada vértice recibe un **color** (`0` o `1`); al visitar un vecino no coloreado se
  le asigna el **color opuesto** (`1 - color[u]`). Si un vecino ya coloreado tiene
  el **mismo color** que el vértice actual, hay un **conflicto** y el grafo **no es
  bipartito** (`NO`).
- Se itera sobre todos los vértices para cubrir grafos **no conexos** (varias
  componentes).

## Estructuras de datos

- **`Nodo`** (`Nodo.h`): `struct` con `int valor` (vértice vecino) y `Nodo*
  siguiente`.
- **`ListaAdyacencia`** (`lista-adyacencia.h/.cpp`): lista enlazada simple de
  vecinos. `insertar(valor)` añade al **principio** (O(1)); `getLista()` devuelve el
  primer nodo; `getN()` el número de aristas. El destructor libera todos los nodos.
- En `main`, el grafo es un `ListaAdyacencia*` (un array indexado por vértice).

## Cómo funciona el código

### Construcción del grafo (`main`)
- Lee casos hasta que `vertices == 0`.
- Lee `aristas` pares `(from, to)` y, al ser **no dirigido**, inserta la relación en
  **ambos** sentidos: `vector[from].insertar(to)` y `vector[to].insertar(from)`.

### Comprobación (`esRojiBlanco`)
- Inicializa `color[i] = -1` (no coloreado) para todos los vértices.
- Para cada vértice no coloreado, lo colorea con `0`, lo mete en la cola y ejecuta
  un BFS:
  - Saca un vértice `u`, recorre sus vecinos `v`.
  - Si `v` no está coloreado: `color[v] = 1 - color[u]` y se encola.
  - Si `v` ya tiene `color[v] == color[u]`: **conflicto**, devuelve `false`.
- Si termina sin conflictos, devuelve `true`.

## Complejidad

| Aspecto                 | Coste                       |
|-------------------------|-----------------------------|
| Tiempo (`esRojiBlanco`) | O(V + E)                    |
| Espacio                 | O(V) (vectores `color` y `cola`) |
| `insertar` (arista)     | O(1)                        |

donde `V` = número de vértices y `E` = número de aristas. El BFS visita cada vértice
y cada arista una vez.

## Notas

- "Roji-blanco" es simplemente el nombre del problema: equivale a comprobar la
  **bipartición** del grafo (no contiene ciclos de longitud impar).
- El programa procesa **múltiples casos** en una misma ejecución y libera la memoria
  del grafo tras cada uno.
