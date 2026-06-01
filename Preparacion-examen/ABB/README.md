# Árbol Binario de Búsqueda (ABB)

Implementación de un **Árbol Binario de Búsqueda** con punteros enlazados, incluyendo operaciones de inserción, búsqueda, borrado y comprobación de las propiedades ABB y AVL.

## Idea principal

Un ABB es un árbol binario en el que, para cada nodo, todos los elementos de su subárbol izquierdo son menores y todos los del subárbol derecho son mayores (o iguales) que su contenido. Esta invariante permite buscar, insertar y borrar siguiendo un único camino raíz-hoja, descartando la mitad del árbol en cada comparación.

## Técnica algorítmica

- **Estructura de datos enlazada**: cada `Nodo` (ver `Nodo.h`) guarda su `contenido`, un puntero al `padre` y dos punteros a `hijoIzquierdo` e `hijoDerecho`. El puntero al padre simplifica el borrado.
- **Recursión** sobre subárboles: casi todas las operaciones (`buscarRecursivo`, `buscarHueco`, `alturaNodo`, `esSubABB`, `esSubAVL`, `eliminarSubarbol`, `leerSubarbol`) descienden recursivamente por la rama adecuada.
- **Divide y vencerás** implícito al elegir entre subárbol izquierdo o derecho en cada paso.

## Complejidad

Siendo `h` la altura del árbol:

| Operación | Caso medio (equilibrado) | Peor caso (degenerado en lista) |
|-----------|--------------------------|---------------------------------|
| Buscar / Insertar / Eliminar | O(log n) | O(n) |
| `alturaNodo`, `esABB`, `esAVL`, destructor | O(n) | O(n) |

El ABB no se autoequilibra, por lo que con inserciones ordenadas degenera en una lista de altura `n`.

## Cómo funciona el código

- **`ABB()` / `~ABB()`**: constructor pone `raiz = nullptr` y `n = 0`. El destructor llama a `eliminarSubarbol`, que recorre el árbol en **postorden** liberando cada nodo con `delete`.
- **`insertar(int)`**: si el árbol está vacío crea la raíz. Si no, `buscarHueco` localiza recursivamente el futuro padre (el nodo cuyo hijo correspondiente es `nullptr`) y se cuelga el nuevo nodo a izquierda o derecha según la comparación.
- **`buscar(int)` / `buscarRecursivo`**: desciende comparando; devuelve el `Nodo*` encontrado o `nullptr`.
- **`eliminar(int)` / `eliminarNodo`**: distingue tres casos clásicos de borrado en ABB:
  1. **Hoja**: se desconecta del padre y se libera.
  2. **Un solo hijo**: se sustituye el contenido por el máximo del subárbol izquierdo (o el mínimo del derecho) y se borra recursivamente ese nodo predecesor/sucesor.
  3. **Dos hijos**: elige el subárbol más alto (con `alturaNodo`) para tomar el predecesor (máximo de la izquierda) o el sucesor (mínimo de la derecha), copia su contenido y lo elimina recursivamente. Esta elección por altura ayuda a mantener el árbol más equilibrado tras el borrado.
- **`esABB()` / `esSubABB`**: comprueba recursivamente la propiedad de orden comparando cada nodo con sus hijos.
- **`esAVL()` / `esSubAVL`**: además de ser ABB, exige que el **factor de equilibrio** (diferencia de alturas entre subárbol derecho e izquierdo) sea como mucho 1 en valor absoluto en todos los nodos.
- **`leerArbol()` / `leerSubarbol`**: construye el árbol leyendo de la entrada en **preorden**; un valor negativo (`< 0`) representa un subárbol vacío (`nullptr`).
- **`imprimir()` / `imprimirRecorrido`**: recorre en preorden, marcando con `I`/`D` las ramas izquierda/derecha.

## Programa de prueba (`mainABB.cpp`)

Ofrece un menú por consola con opciones: `N` (nuevo árbol), `I` (imprimir), `C` (buscar/contiene), `L` (leer árbol), `B` (¿es ABB?), `V` (¿es AVL?), `A` (añadir), `E` (eliminar), `F` (liberar memoria) y `S` (salir).

## Notas / observaciones del código

- En `buscarMaximo`/`buscarMinimo` y en `esSubABB`, las comprobaciones de `nullptr` se realizan después de desreferenciar el puntero, lo que puede provocar accesos inválidos en ciertos casos límite. La lógica algorítmica pretendida (máximo = bajar siempre a la derecha; mínimo = bajar siempre a la izquierda) es la estándar.
