# Ejer7/Ruleta-rusa — Lista circular doblemente enlazada

Simula una **ruleta rusa** sobre el tambor de un revólver modelado con una **lista circular
doblemente enlazada**. Es una variante del esquema tipo Josephus: el tambor gira y se
"dispara" la recámara que queda en la posición inicial.

## Estructura de datos
- `Nodo` (`Nodo.h`): un `string elemento` (`"BANG"` o `"CLACK"`) y dos punteros,
  `anteriorNodo` y `siguienteNodo`.
- `ListaCircular` (`ListaCircular.h`): puntero `lista` al nodo de inicio y contador `n`. Es
  **circular** (el último nodo apunta al primero y viceversa) y **doblemente enlazada** (cada
  nodo conoce a su anterior y a su siguiente), lo que permite recorrer en ambos sentidos.

## Idea principal
Cada recámara del tambor es un nodo. Una de ellas contiene la bala (`"BANG"`), el resto están
vacías (`"CLACK"`). Girar el tambor equivale a mover el nodo de inicio de la lista; disparar
es leer el valor de la recámara en la posición 0.

## Técnica
Lista circular doblemente enlazada con gestión manual de memoria. La macro `assertdomjudge`
valida precondiciones.

## Operaciones (`ListaCircular.cpp`)
- **Constructor**: `n = 0`, `lista = nullptr`. `O(1)`.
- **`getNodo(pos)`** (privado): localiza un nodo eligiendo la **dirección más corta** (avanza
  por `siguienteNodo` o retrocede por `anteriorNodo` según `pos` esté en la mitad superior o
  inferior). `O(n)` en el peor caso, optimizado a ~`n/2`.
- **`insertar(pos, valor)`**: si la lista está vacía, el nodo se apunta a sí mismo (anterior y
  siguiente); en caso contrario reengancha los cuatro punteros entre el nodo anterior y el
  siguiente. `O(n)`.
- **`eliminar(pos)`**: desengancha el nodo enlazando su anterior con su siguiente y lo libera.
  `O(n)`.
- **`getValor(pos)` / `setValor(pos, v)`**: usan `getNodo`. `O(n)`.
- **`getN()`**: devuelve `n`.
- **`girar(p)`**: desplaza el puntero de inicio `lista` `p` posiciones (hacia la derecha si
  `p >= 0`, hacia la izquierda si `p < 0`). Es la operación que "gira el tambor". `O(n)`.
- **Destructor**: elimina repetidamente la posición 0 hasta vaciar la lista. `O(n)`.

## Cómo funciona el programa (`RuletaRusa.cpp`)
1. Lee el número de recámaras y la posición inicial de la bala.
2. Construye el tambor insertando `"BANG"` en la posición de la bala y `"CLACK"` en el resto.
3. En bucle: lee cuánto se gira el tambor (`girar`), lee la recámara en la posición 0
   (`getValor(0)`) y la imprime. Repite hasta que salga `"BANG"`.
4. Vacía la lista al terminar.

## Complejidad
- La mayoría de operaciones son `O(n)` (acceso/giro requieren recorrer nodos), optimizadas con
  la elección de dirección más corta.
- Memoria: `O(n)`, un nodo por recámara.
