# Cola de Prioridad (Montículo) — Simulación de Supermercado

## Idea principal

Implementa una **cola de prioridad** mediante un **montículo binario de mínimos**
(*min-heap*) y la aplica a la simulación de las **cajas de un supermercado**. En la
cola, el elemento de **menor valor** (mayor prioridad) es siempre el primero en ser
atendido.

Cada caja del supermercado es una cola de prioridad; los usuarios se identifican por
un `id` (entero) que actúa a la vez como clave de prioridad.

## Técnica

- **Montículo binario (min-heap)** representado sobre un **array (lista contigua)**,
  sin punteros. Para el nodo en la posición `i`:
  - padre: `(i - 1) / 2`
  - hijo izquierdo: `2*i + 1`
  - hijo derecho: `2*i + 2`
- Propiedad del montículo de mínimos: cada nodo es **menor que sus descendientes**,
  por lo que el mínimo está siempre en la raíz (posición 0).
- Se mantiene mediante dos operaciones de reubicación:
  - **flotar / sift-up** (en `encolar`): el nuevo elemento sube mientras sea menor
    que su padre.
  - **hundir / sift-down** (`reestructurar`, en `desencolar`): la nueva raíz baja
    intercambiándose con el menor de sus hijos hasta restaurar la propiedad.

## Estructuras de datos

- **`ListaContigua`** (`ListaContigua.h/.cpp`): vector dinámico de enteros con
  redimensionado automático. Crece/decrece en bloques de `INCREMENTO` (2) usando
  `realloc`. Ofrece `insertarAlFinal`, `eliminarAlFinal`, `getValor`, `setValor`,
  `getN`, `insertar`, `eliminar`, `buscar` y `concatenar`.
- **`ColaPrioridad`** (`ColaPrioridad.h/.cpp`): el min-heap, construido **sobre** una
  `ListaContigua` interna.
- **`Supermercado`** (`Supermercado.h/.cpp`): vector de `ColaPrioridad` (una por
  caja) con `n_cajas`.

## Cómo funciona el código

### ColaPrioridad
- `encolar(num)`: inserta al final del array y **flota** el elemento: mientras no sea
  la raíz y sea menor que su padre, los intercambia.
- `desencolar()`: guarda la raíz (el mínimo), coloca el último elemento en la raíz,
  elimina el último y **reestructura** (hunde la raíz). Devuelve el valor mínimo
  original.
- `estaVacia()`: `getN() == 0`.
- `reestructurar()`: desde la raíz, intercambia repetidamente con el menor de los
  hijos hasta que el padre sea el menor.

### Supermercado
- `Supermercado(n)`: crea `n` cajas (colas de prioridad).
- `nuevoUsuario(caja, id)`: encola `id` en la caja indicada.
- `atenderUsuario(caja)`: desencola (atiende al usuario de mayor prioridad / menor
  id) de la caja.
- `cerrarCaja(n)`: vacía la caja `n` repartiendo sus usuarios entre las demás cajas
  que no estén vacías (recorriendo las cajas de forma circular con índice `i`).
- `cajaVacia(n)`: indica si la caja está vacía.

`mainSupermercado.cpp`: menú interactivo con N (nuevo supermercado), U (nuevo
usuario), C (cerrar caja), A (atender) y S (salir).

## Complejidad

| Operación      | Tiempo    | Espacio |
|----------------|-----------|---------|
| `encolar`      | O(log n)  | O(1)*   |
| `desencolar`   | O(log n)  | O(1)    |
| `estaVacia`    | O(1)      | O(1)    |
| `reestructurar`| O(log n)  | O(1)    |
| `cerrarCaja`   | O(k·log n)| O(1)    |

`n` = número de elementos en la cola; `k` = usuarios a reubicar al cerrar una caja.
(*) La inserción amortizada es O(log n); puntualmente la `ListaContigua` puede
hacer un `realloc` O(n) al crecer.
