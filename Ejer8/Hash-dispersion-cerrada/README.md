# Tabla Hash con Dispersión Cerrada (Direccionamiento Abierto)

## Idea principal

Implementa una **agenda de contactos** sobre una **tabla hash con dispersión
cerrada** (también llamada *direccionamiento abierto*). Todos los elementos se
almacenan **dentro del propio vector** de la tabla, sin listas auxiliares. Cuando
hay una colisión, se busca otra posición libre dentro de la misma tabla.

La clave es el teléfono (`long`) y el valor el nombre (`string`).

## Técnica

- **Direccionamiento abierto con exploración lineal** (*linear probing*): si la
  posición calculada está ocupada, se avanza posición a posición (`pos++`) hasta
  encontrar un hueco libre.
- Se mantienen **vectores paralelos**: `nombres`, `telefonos`, `vacias`
  (indica si la posición está libre) y `borradas` (marca de borrado).
- **Borrado perezoso (lazy deletion)**: al eliminar, la posición se marca como
  `vacia = true` y `borrada = true`. La marca de borrado permite que la búsqueda
  siga atravesando esa posición sin detenerse prematuramente, conservando la cadena
  de exploración.

## Función de dispersión (hash)

```cpp
int Agenda::obtenerPosicion(long clave) {
    return clave % capacidad; // método de división
}
```

Método de la división (resto de la clave entre la capacidad). O(1).

## Estructuras de datos

- **`Agenda`** (`Agenda.h`, `Agenda.cpp`, `AgendaDispersionCerrada.cpp`):
  - `capacidad`, `n` (número de elementos).
  - `string* nombres`, `long* telefonos`: datos de cada contacto.
  - `bool* vacias`: `true` = posición libre.
  - `bool* borradas`: `true` = posición que tuvo un elemento eliminado.

## Cómo funciona el código

- `Agenda(capacidad)`: reserva los vectores; `vacias` se inicializa a `true`,
  `borradas` a `false`.
- `buscarContacto(telefono)`: parte de `obtenerPosicion` y avanza linealmente.
  Devuelve la posición si encuentra el teléfono; se detiene (devolviendo -1) al
  llegar a una posición vacía nunca borrada o al final de la tabla.
- `buscarHueco(telefono)`: parte de la posición hash y avanza hasta la primera
  posición marcada como `vacia`, devolviendo su índice (o -1 si no hay sitio).
- `introducirContacto(telefono, nombre)`: busca un hueco con `buscarHueco`, guarda
  teléfono y nombre, marca la posición como ocupada e incrementa `n`.
- `existeContacto` / `getContacto`: usan `buscarContacto`.
- `eliminarContacto(telefono)`: localiza el contacto y lo marca como
  `vacia = true` y `borrada = true` (borrado perezoso), decrementando `n`.
- `isLlena()`: devuelve `n == capacidad`.
- `imprimir()`: muestra para cada posición su estado (vacía/borrada), teléfono y
  nombre.
- `mainAgenda.cpp`: menú interactivo (I, C, V, A, E, S).

## Complejidad

| Operación            | Tiempo | Espacio |
|----------------------|--------|---------|
| `obtenerPosicion`    | O(1)   | O(1)    |
| `buscarContacto`     | O(n)   | O(1)    |
| `buscarHueco`        | O(n)   | O(1)    |
| `introducirContacto` | O(n)   | O(1)    |
| `existeContacto`     | O(n)   | O(1)    |
| `getContacto`        | O(n)   | O(1)    |
| `eliminarContacto`   | O(n)   | O(1)    |

En el peor caso (muchas colisiones / tabla casi llena) la exploración lineal recorre
O(n) posiciones. Con factor de carga bajo, las operaciones son ~O(1) en promedio.

## Notas

- La tabla **no se redimensiona**: la capacidad es fija. Si se llena, no caben más
  contactos.
- El borrado perezoso provoca que las posiciones borradas no se reutilicen con
  `buscarHueco` (que solo mira `vacias`), pero sí mantienen la integridad de las
  cadenas de búsqueda gracias al vector `borradas`.
