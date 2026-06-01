# Tabla Hash sin Colisión (Direccionamiento Directo)

## Idea principal

Implementa una **agenda de contactos** sobre una **tabla hash sin gestión de
colisiones**. Cada clave se asigna a una única posición calculada por la función
hash y se asume que **no habrá colisiones**: si dos claves caen en la misma
posición, la segunda inserción se rechaza (mediante `assert`).

Es la versión más simple de las tres prácticas de hash (abierta, cerrada y sin
colisión) y sirve como punto de partida para entender el problema de las colisiones.

## Técnica

- **Direccionamiento directo**: la posición hash determina de forma única dónde
  vive el contacto. No hay listas ni exploración alternativa.
- Vectores paralelos `nombres`, `telefonos` y un flag `ocupada` por posición.
- Las colisiones **no se resuelven**: se detectan con `assert` y se consideran un
  error de uso (la tabla debe dimensionarse para que no ocurran).

## Función de dispersión (hash)

```cpp
int Agenda::obtenerPosicion(long clave) {
    return clave % capacidad; // método de división
}
```

Método de la división. O(1).

## Estructuras de datos

- **`Agenda`** (`Agenda.h`, `Agenda.cpp`, `AgendaSinColision.cpp`):
  - `capacidad`.
  - `string* nombres`, `long* telefonos`: datos.
  - `bool* ocupada`: `true` si la posición contiene un contacto (`false` = libre,
    inicializado con `new bool[capacidad]()`).

## Cómo funciona el código

- `Agenda(capacidad)`: reserva los vectores; `ocupada` se inicializa a `false`.
- `obtenerPosicion(telefono)`: devuelve la posición única de la clave.
- `existeContacto(telefono)`: devuelve `ocupada[pos] && telefonos[pos] == telefono`,
  es decir, comprueba que la posición esté ocupada **y** que la clave coincida.
- `getContacto(telefono)`: comprueba que exista y devuelve `nombres[pos]`.
- `introducirContacto(telefono, nombre)`: calcula la posición y comprueba con
  `assert` que esté libre; si lo está, guarda los datos y marca `ocupada = true`.
  Si ya estaba ocupada (colisión), el `assert` falla.
- `eliminarContacto(telefono)`: comprueba que exista y marca `ocupada = false`.
- `imprimir()`: muestra para cada posición si está ocupada, su teléfono y nombre.
- `mainAgenda.cpp`: menú interactivo (I, C, V, A, E, S).

## Complejidad

Todas las operaciones principales son **O(1)** en tiempo y espacio, porque cada
clave tiene una posición fija y no hay exploración:

| Operación            | Tiempo | Espacio |
|----------------------|--------|---------|
| `obtenerPosicion`    | O(1)   | O(1)    |
| `existeContacto`     | O(1)   | O(1)    |
| `getContacto`        | O(1)   | O(1)    |
| `introducirContacto` | O(1)   | O(1)    |
| `eliminarContacto`   | O(1)   | O(1)    |

## Limitaciones

- No tolera colisiones: dos teléfonos con el mismo resto módulo `capacidad` no
  pueden coexistir; la segunda inserción aborta.
- La capacidad es fija y no se redimensiona.
