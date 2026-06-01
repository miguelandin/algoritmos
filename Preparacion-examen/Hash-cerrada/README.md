# Agenda con Tabla Hash de Dispersión Cerrada

Implementación de una **agenda de contactos** (teléfono → nombre) mediante una **tabla hash de direccionamiento abierto (dispersión cerrada)** con resolución de colisiones por **sondeo lineal**.

## Idea principal

Cada contacto se almacena en un array de tamaño `capacidad`. La posición inicial se obtiene aplicando una función hash al teléfono. Si esa casilla está ocupada (colisión), se prueba la siguiente posición de forma lineal hasta encontrar hueco. Para distinguir casillas nunca usadas de casillas liberadas, se mantienen marcas auxiliares de "vacía" y "borrada".

## Técnica algorítmica

- **Tabla hash con dispersión cerrada / direccionamiento abierto**: todos los datos viven dentro del propio array, sin listas enlazadas externas.
- **Sondeo lineal (linear probing)** para resolver colisiones: ante una colisión se avanza posición a posición.
- **Función hash por módulo**: `obtenerPosicion(telefono) = telefono % capacidad`.
- Marcado de **borrado lógico** (lápidas / tombstones) con el array `borradas`, necesario para que la búsqueda no se detenga prematuramente en huecos dejados por elementos eliminados.

## Estructura de datos (`Agenda.h`)

Arrays paralelos de tamaño `capacidad`:
- `telefonos[]` (clave, `long`), `nombres[]` (valor, `string`).
- `vacias[]`: indica si la casilla está libre.
- `borradas[]`: marca si la casilla fue ocupada y luego borrada (lápida).
- Contadores `capacidad` y `n` (número de contactos).

## Complejidad

- Caso medio (factor de carga bajo): inserción, búsqueda y borrado en **O(1)**.
- Peor caso (tabla muy llena o muchas colisiones / lápidas): **O(capacidad)** por el sondeo lineal.
- Memoria: O(capacidad).

## Cómo funciona el código

- **Constructor `Agenda(capacidad)`**: reserva los cuatro arrays e inicializa todas las casillas como `vacias = true` y `borradas = false`.
- **`obtenerPosicion(telefono)`**: posición hash inicial = `telefono % capacidad`.
- **`buscarContacto(telefono)`**: parte de la posición hash y avanza linealmente. Devuelve la posición si encuentra una casilla ocupada con ese teléfono; se detiene al llegar a una casilla vacía no borrada (no puede haber pasado por ahí en la inserción) o al final de la tabla. Devuelve `-1` si no existe.
- **`buscarHueco(telefono)`**: desde la posición hash, avanza hasta encontrar la primera casilla `vacia`, devolviendo su índice (o `-1` si la tabla está llena).
- **`introducirContacto(telefono, contacto)`**: busca hueco con `buscarHueco`; si hay sitio, guarda teléfono y nombre, marca la casilla como no vacía e incrementa `n`.
- **`eliminarContacto(telefono)`**: localiza el contacto con `buscarContacto`; si existe, marca la casilla como `borrada` y `vacia`, y decrementa `n` (borrado lógico mediante lápida).
- **`existeContacto` / `getContacto`**: se apoyan en `buscarContacto`.
- **`isLlena()`**: devuelve `capacidad == n`.
- **`imprimir()`**: vuelca todas las casillas con sus marcas `vacias`/`borradas` (útil para depurar el estado de la tabla).
- **Destructor**: libera los cuatro arrays.

## Programa de prueba (`Main.cpp`)

Crea una agenda de capacidad 25, inserta varios contactos, los imprime, elimina uno, comprueba su existencia y vuelve a insertar otro, mostrando el estado de la tabla tras cada operación.

## Notas / observaciones del código

- En `buscarContacto`, el sondeo incrementa `pos` y compara `pos == capacidad`, pero no envuelve el índice de forma circular ni acota el acceso al array dentro del bucle; con la tabla parcialmente llena funciona, pero conviene tener presente este límite frente a tablas muy ocupadas.
- Una casilla borrada queda marcada a la vez como `vacia = true` y `borrada = true`; la marca `borradas` está pensada como lápida para que las búsquedas/inserciones puedan reutilizar o atravesar correctamente esos huecos.
