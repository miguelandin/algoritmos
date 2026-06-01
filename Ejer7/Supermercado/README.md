# Ejer7/Supermercado — Colas (FIFO) aplicadas a las cajas de un supermercado

Simula las cajas de un supermercado donde los clientes se atienden por orden de llegada.
Cada caja es una **cola (FIFO)** y el supermercado es un array de colas.

## Estructura de datos: la cola
- `Nodo` (`Nodo.h`): un `int valor` (id de usuario) y un puntero `Nodo* siguiente`.
- `Cola` (`Cola.h` / `Cola.cpp`): cola enlazada con punteros `principio` y `final`.
  - **`encolar(num)`**: añade un nodo al final. Si la cola está vacía, `principio` y `final`
    apuntan al nuevo nodo; si no, se enlaza tras el `final` y se actualiza `final`. `O(1)`.
  - **`desencolar()`**: extrae el nodo del `principio`, lo libera y devuelve su valor; si la
    cola queda vacía, pone `final = nullptr`. `O(1)`.
  - **`estaVacia()`**: comprueba si `principio` es `nullptr`. `O(1)`.

Mantener punteros a principio y final permite que ambas operaciones (encolar al final,
desencolar del principio) sean `O(1)`, que es lo característico de una cola FIFO.

## El supermercado (`Supermercado.h` / `Supermercado.cpp`)
`Supermercado` contiene un array dinámico de `Cola` (`cajas`) y el número de cajas
(`n_cajas`). La macro `assertdomjudge` valida que el índice de caja sea correcto.

- **Constructor `Supermercado(n)`**: exige `n > 0` y reserva un array de `n` colas.
  `O(1)` en tiempo, `O(n)` en memoria.
- **`nuevoUsuario(n, id)`**: encola al usuario `id` en la caja `n`. `O(1)`.
- **`atenderUsuario(n)`**: desencola (atiende) al primer usuario de la caja `n`. `O(1)`.
- **`cajaVacia(n)`**: indica si la caja `n` no tiene clientes. `O(1)`.
- **`cerrarCaja(n)`**: vacía la caja `n` repartiendo sus clientes entre las **otras** cajas
  que no estén vacías, recorriendo el resto de cajas de forma circular (`i` da la vuelta al
  llegar a `n_cajas`). `O(n)` por número de cajas/clientes a reubicar.

## Cómo funciona el programa (`mainSupermercardo.cpp`)
Menú interactivo por entrada estándar:
- `N`: crear supermercado (pide número de cajas).
- `U`: nuevo usuario (pide caja e id).
- `C`: cerrar una caja (si está vacía imprime `VACIA`, si no reparte sus clientes).
- `A`: atender al primer usuario de una caja (imprime su id, o `VACIA` si no hay).
- `S`: salir.

## Complejidad
- Encolar, desencolar, atender y consultar: `O(1)`.
- Cerrar caja: proporcional al número de cajas y clientes a reubicar.
- Memoria: `O(n)` en cajas más un nodo por cliente en espera.
