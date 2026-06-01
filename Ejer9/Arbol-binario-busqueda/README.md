# Árbol Binario de Búsqueda (ABB)

## Idea principal

Implementa un **Árbol Binario de Búsqueda** de enteros. En un ABB, para todo nodo
se cumple que **todos los elementos de su subárbol izquierdo son menores** que él y
**todos los del subárbol derecho son mayores**. Esta propiedad permite buscar,
insertar y eliminar siguiendo un único camino desde la raíz hacia abajo.

Además de las operaciones clásicas, incluye comprobaciones de si el árbol es un ABB
válido (`esABB`) y si está equilibrado como un **AVL** (`esAVL`).

## Técnica

- **Recursión** sobre subárboles para casi todas las operaciones (búsqueda,
  inserción, borrado, altura, validaciones).
- Cada nodo guarda puntero a su **padre**, hijo izquierdo e hijo derecho, lo que
  facilita el borrado y la reconexión.

## Estructuras de datos

- **`Nodo`** (`Nodo.h`): `struct` con `int contenido`, `Nodo* padre`,
  `Nodo* hijoIzquierdo`, `Nodo* hijoDerecho`.
- **`ABB`** (`ABB.h`, `ABB.cpp`): guarda `raiz` y el número de nodos `n`. Expone
  métodos públicos y un conjunto de métodos protegidos recursivos.

## Cómo funciona el código

### Operaciones públicas
- `insertar(nuevo)`: si el árbol está vacío crea la raíz; si no, usa `buscarHueco`
  para localizar el padre adecuado y cuelga el nodo a izquierda o derecha según
  compare con el contenido del padre.
- `buscar(elemento)`: delega en `buscarRecursivo`, que desciende a izquierda o
  derecha según la comparación hasta encontrar el elemento o llegar a `nullptr`.
- `eliminar(elemento)`: busca el nodo y, si existe, llama a `eliminarNodo`.
- `esABB()`: comprueba la propiedad de orden con `esSubABB`.
- `esAVL()`: primero verifica que sea ABB y luego comprueba el equilibrio con
  `esSubAVL`.
- `leerArbol()` / `imprimir()`: leen/escriben el árbol mediante recorrido en
  preorden (un valor negativo en la entrada representa un subárbol vacío).

### Borrado (`eliminarNodo`)
Distingue cuatro casos:
1. **Hoja**: se desconecta del padre y se libera.
2. **Solo hijo izquierdo**: se sustituye el contenido por el **máximo** del subárbol
   izquierdo y se elimina recursivamente ese máximo.
3. **Solo hijo derecho**: se sustituye por el **mínimo** del subárbol derecho y se
   elimina recursivamente.
4. **Dos hijos**: se elige el lado de **mayor altura** (para tender al equilibrio) y
   se sustituye por el máximo del izquierdo o el mínimo del derecho según corresponda.

### Validaciones
- `esSubABB`: para cada nodo verifica que el hijo izquierdo y el **máximo** de su
  subárbol sean menores, y que el hijo derecho y el **mínimo** de su subárbol sean
  mayores; recursivamente en ambos lados.
- `esSubAVL`: calcula el **factor de equilibrio** `Fe = altura(derecho) -
  altura(izquierdo)` en cada nodo y exige `|Fe| <= 1`.
- `alturaNodo`: altura recursiva (un árbol vacío tiene altura -1).

`mainABB.cpp`: menú interactivo con opciones N (nuevo), I (imprimir), C (buscar),
L (leer árbol), B (¿es ABB?), V (¿es AVL?), A (añadir), E (eliminar), F (liberar) y
S (salir).

## Complejidad

| Operación   | Tiempo (equilibrado) | Tiempo (peor caso) | Espacio |
|-------------|----------------------|--------------------|---------|
| `insertar`  | O(log n)             | O(n)               | O(1)    |
| `buscar`    | O(log n)             | O(n)               | O(1)    |
| `eliminar`  | O(log n)             | O(n)               | O(1)    |
| `alturaNodo`| O(n)                 | O(n)               | O(1)    |
| `esABB`     | O(n²)                | O(n²)              | O(n)*   |
| `esAVL`     | O(n²)                | O(n²)              | O(n)*   |

El peor caso O(n) por operación ocurre cuando el árbol degenera en una "lista"
(insertando datos ya ordenados). `esABB`/`esAVL` son O(n²) porque en cada nodo
recalculan máximos/mínimos o alturas recorriendo subárboles completos.
(*) El coste espacial proviene de la pila de recursión.

## Nota

El destructor (`eliminarSubarbol`) libera todos los nodos en postorden.
