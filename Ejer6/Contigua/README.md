# Ejer6/Contigua — Lista contigua (basada en array dinámico)

Implementación de una **lista de enteros con representación contigua**, es decir, almacenada
en un array dinámico en memoria que crece y decrece por bloques.

## Estructura de datos
`ListaContigua` (ver `ListaContigua.h`) guarda:
- `int* vector` — array dinámico de enteros.
- `int n` — número de elementos almacenados.
- `int capacidad` — número máximo de elementos que caben sin redimensionar.
- `int incremento` — tamaño del bloque en que crece o se reduce la capacidad.

## Idea principal
Los elementos se guardan de forma consecutiva en memoria, lo que da **acceso por índice en
O(1)**. La capacidad se gestiona dinámicamente con `realloc`: cuando se llena, se amplía en
`incremento` posiciones; cuando sobra demasiado, se reduce en `incremento`.

## Técnica
Array dinámico con redimensionado por bloques y desplazamiento de elementos mediante
`memmove`. La macro `assertdomjudge` comprueba precondiciones (índices válidos, punteros no
nulos) y aborta imprimiendo `ERROR` si fallan.

## Operaciones (`ListaContigua.cpp`)
- **Constructor `ListaContigua(incremento)`**: inicializa `n = 0`, fija la capacidad inicial
  al `incremento` y reserva el array. `O(1)`.
- **Destructor**: libera el `vector`. `O(1)`.
- **`getValor(pos)` / `setValor(pos, v)`**: acceso directo por índice con comprobación de
  rango. `O(1)`.
- **`getN()` / `getCapacidad()`**: devuelven número de elementos y capacidad. `O(1)`.
- **`insertar(pos, v)`**: si el array está lleno, amplía la capacidad con `realloc`; desplaza
  con `memmove` los elementos desde `pos` una posición a la derecha e inserta el nuevo valor.
  `O(n)`.
- **`eliminar(pos)`**: si sobra más de un bloque de capacidad, reduce con `realloc`; superpone
  con `memmove` los elementos desde `pos+1` hacia la izquierda. `O(n)`.
- **`concatenar(lista)`**: inserta al final todos los elementos de otra lista llamando a
  `insertar(this->n, ...)`. `O(n)` (más el coste de cada inserción).
- **`buscar(elemento)`**: búsqueda lineal; devuelve la posición o `-1` si no está. `O(n)`.

## Complejidad
- Acceso/modificación por índice: `O(1)`.
- Inserción/eliminación: `O(n)` por el desplazamiento de elementos.
- Memoria: `O(n)`.

## Programa de prueba (`mainContigua.cpp`)
Menú interactivo por entrada estándar. Cada letra ejecuta una operación:
`N` (nueva lista, pide incremento), `I` (insertar), `E` (eliminar), `V` (ver elemento),
`T` (ver todos), `S` (modificar/set), `L` (longitud), `M` (capacidad máxima),
`C` (concatenar N números 1..N), `B` (buscar) y `F` (fin).
