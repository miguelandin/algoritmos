# Ejer6/Enlazada — Lista enlazada simple

Implementación de una **lista enlazada simple de enteros**: una secuencia de nodos donde cada
uno apunta al siguiente.

## Estructura de datos
- `Nodo` (`Nodo.h`): un `int elemento` y un puntero `Nodo* siguienteNodo`.
- `ListaEnlazada` (`ListaEnlazada.h`): puntero `Nodo* lista` al primer nodo, contador `int n`
  de elementos, y un método privado auxiliar `getNodo(pos)`.

## Idea principal
A diferencia de la lista contigua, los elementos no están en memoria consecutiva. Insertar y
eliminar solo requieren reenganchar punteros (no hay desplazamientos), pero el **acceso a una
posición es lineal** porque hay que recorrer la cadena desde el principio.

## Técnica
Enlace por punteros con gestión manual de memoria (`new`/`delete`). La macro `assertdomjudge`
valida los índices y aborta con `ERROR` si están fuera de rango.

## Operaciones (`ListaEnlazada.cpp`)
- **Constructor**: `n = 0`, `lista = nullptr`. `O(1)`.
- **Destructor**: recorre la lista liberando cada nodo. `O(n)`.
- **`getNodo(pos)`** (privado): recorre desde el inicio `pos` saltos y devuelve ese nodo.
  Es la base del acceso indexado. `O(n)`.
- **`getValor(pos)` / `setValor(pos, v)`**: usan `getNodo`. `O(n)`.
- **`getN()`**: devuelve `n`. `O(1)`.
- **`insertar(pos, v)`**: crea un nodo nuevo. Si `pos == 0` lo enlaza como cabeza; si no,
  obtiene el nodo anterior y reengancha los punteros. `O(n)` (por localizar la posición).
- **`eliminar(pos)`**: desengancha el nodo en `pos` (caso especial para la cabeza) y libera su
  memoria. `O(n)`.
- **`concatenar(lista)`**: enlaza el último nodo de esta lista con la cabeza de la otra (o
  toma directamente su cabeza si esta lista está vacía) y suma los contadores. `O(n)`.
- **`buscar(val)`**: recorrido lineal; devuelve la posición o `-1`. `O(n)`.

## Complejidad
- Inserción/eliminación en una posición conocida: el reenganche es `O(1)`, pero localizar la
  posición es `O(n)`.
- Acceso por índice y búsqueda: `O(n)`.
- Memoria: `O(n)`, un nodo por elemento.

## Comparación con la lista contigua
| Operación        | Contigua (array) | Enlazada |
|------------------|------------------|----------|
| Acceso por índice| `O(1)`           | `O(n)`   |
| Insertar/eliminar| `O(n)` (memmove) | `O(n)` localizar, `O(1)` reenganchar |
| Memoria extra    | huecos de capacidad | un puntero por nodo |

## Programa de prueba (`mainEnlazada.cpp`)
Menú interactivo análogo al de la lista contigua:
`N` (nueva), `I` (insertar), `E` (eliminar), `V` (ver), `T` (ver todos), `S` (modificar),
`L` (longitud), `C` (concatenar 1..N), `B` (buscar) y `F` (fin).
