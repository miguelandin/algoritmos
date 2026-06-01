# Tabla Hash con Dispersión Abierta (Encadenamiento)

## Idea principal

Esta práctica implementa una **agenda de contactos** sobre una **tabla hash con
dispersión abierta** (también llamada *encadenamiento* o *hashing abierto*). Cada
posición de la tabla no guarda directamente un contacto, sino una **lista enlazada**
con todos los contactos cuya clave colisiona en esa misma posición.

La clave es el número de teléfono (`long`) y el valor asociado es el nombre del
contacto (`string`), agrupados en la estructura `Contacto`.

## Técnica

- **Dispersión abierta / encadenamiento**: las colisiones se resuelven manteniendo
  una lista de elementos por cada cubeta (*bucket*). La tabla es un vector de
  `ListaEnlazada` de tamaño fijo `capacidad`.
- Al insertar, se calcula la posición de la cubeta y se añade el contacto **al
  principio** de su lista (`insertar(0, ...)`), lo que hace la inserción muy rápida
  dentro de la lista.

## Función de dispersión (hash)

```cpp
int Agenda::obtenerPosicion(long clave) {
    return clave % capacidad; // método de división (módulo)
}
```

Se usa el **método de la división**: el resto de dividir el teléfono entre la
capacidad de la tabla. Es O(1).

## Estructuras de datos

- **`Contacto`** (`Contacto.h`): `struct` con `long telefono` y `string nombre`.
- **`Nodo`** (`Nodo.h`): nodo con un `Contacto`, puntero `anteriorNodo` y
  puntero `siguienteNodo`.
- **`ListaEnlazada`** (`ListaEnlazada.h/.cpp`): lista enlazada **doblemente enlazada
  y circular**. El método `getNodo` aprovecha la circularidad para recorrer por la
  izquierda o por la derecha según la posición pedida (como mucho n/2 saltos).
  Soporta `insertar`, `eliminar`, `buscar` (por teléfono), `getValor`, `setValor`,
  `concatenar` y `getN`.
- **`Agenda`** (`Agenda.h`, `Agenda.cpp`, `AgendaDispersionAbierta.cpp`): la tabla
  hash. Guarda `capacidad`, número de elementos `n` y el vector `tabla`.

## Cómo funciona el código

- `Agenda(capacidad)`: reserva `capacidad` listas enlazadas vacías.
- `introducirContacto(telefono, nombre)`: calcula la cubeta con `obtenerPosicion`
  e inserta el `Contacto` al inicio de la lista de esa cubeta.
- `existeContacto(telefono)`: calcula la cubeta y usa `buscar` sobre su lista;
  devuelve `true` si la posición encontrada no es -1.
- `getContacto(telefono)`: localiza la cubeta y la posición dentro de la lista,
  comprueba con `assert` que exista y devuelve el `nombre`.
- `eliminarContacto(telefono)`: localiza el elemento en su lista y lo borra.
- `imprimir()` (en `AgendaDispersionAbierta.cpp`): recorre todas las cubetas y
  delega en `imprimirListaEnlazada` (`impresionListasEnlazadas.cpp`), que muestra
  el tamaño y los pares `(telefono,nombre)`.
- `mainAgenda.cpp`: menú interactivo con opciones I (imprimir), C (comprobar),
  V (ver), A (añadir), E (eliminar) y S (salir).

## Complejidad

| Operación            | Tiempo  | Espacio |
|----------------------|---------|---------|
| `obtenerPosicion`    | O(1)    | O(1)    |
| `introducirContacto` | O(n)*   | O(1)    |
| `existeContacto`     | O(n)    | O(1)    |
| `getContacto`        | O(n)    | O(1)    |
| `eliminarContacto`   | O(n)    | O(1)    |

El peor caso O(n) se da si todos los contactos caen en la misma cubeta. Con una
buena distribución y factor de carga bajo, las operaciones son ~O(1) en promedio.
(*) La inserción en la lista es al principio, pero los métodos internos de la lista
están acotados por O(n).
