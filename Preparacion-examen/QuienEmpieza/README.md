# ¿Quién Empieza? — Problema de Josephus con Lista Circular Doblemente Enlazada

## Idea principal

Resuelve una variante del **problema de Josephus**: se colocan `niños` numerados de 1 a N en círculo y, dando un número fijo de `saltos` cada vez, se va eliminando un niño en cada ronda. El proceso continúa hasta que queda un único superviviente, cuyo número se imprime.

La estructura de soporte es una **lista circular doblemente enlazada** implementada con las clases `Nodo` y `Circulo`.

## Técnica algorítmica

- **Estructura de datos**: lista circular doblemente enlazada (cada nodo conoce su `anterior` y `siguiente`, y el último apunta de vuelta al primero). Esto permite avanzar en círculo indefinidamente y eliminar nodos en O(1).
- **Simulación directa**: se recorre el círculo dando los saltos indicados y se elimina el nodo correspondiente en cada vuelta.

## Complejidad

- **Tiempo**: hay N − 1 eliminaciones; antes de cada una se avanzan `saltos` posiciones. Total **O(N · saltos)**.
- **Espacio**: **O(N)** por los N nodos de la lista.

## Estructura del código

### `Nodo.h`

```cpp
class Nodo {
public:
    int num;
    Nodo* siguiente;
    Nodo* anterior;
    Nodo(int num) { this->num = num; siguiente = nullptr; anterior = nullptr; }
};
```

Nodo de lista doblemente enlazada que almacena un número y punteros a vecinos.

### `Circulo.h` / `Circulo.cpp`

Clase que gestiona la lista circular. Atributos: `n` (número de elementos) y `principio` (puntero al primer nodo).

- **`encolar(int num)`**: inserta un nuevo nodo al final del círculo (justo antes de `principio`, manteniendo la circularidad).
  - Si la lista está vacía, el nodo se enlaza consigo mismo (`siguiente` y `anterior` apuntan a sí mismo).
  - Si no, se inserta entre el último (`principio->anterior`) y `principio`. O(1).
- **`eliminar(Nodo* eliminar)`**: desengancha un nodo reconectando su anterior con su siguiente. Si el nodo eliminado es `principio`, este avanza al siguiente. Libera memoria y decrementa `n`. O(1).
- **`getPrincipio()` / `getN()`**: acceso al primer nodo y al tamaño.
- **Destructor `~Circulo()`**: elimina repetidamente `principio` hasta vaciar la lista.

### `Main.cpp`

```cpp
int main()
{
    int niños, saltos;
    cin >> niños >> saltos;
    Circulo circulo;

    for (int i = 1; i <= niños; i++)
        circulo.encolar(i);                 // llena el círculo 1..niños

    Nodo* apunta = circulo.getPrincipio();
    Nodo* eliminar;

    while (circulo.getN() > 1) {
        for (int i = 0; i < saltos; i++)    // avanza 'saltos' posiciones
            apunta = apunta->siguiente;
        eliminar = apunta;
        apunta = apunta->siguiente;         // mueve el puntero antes de borrar
        circulo.eliminar(eliminar);
    }
    cout << apunta->num;                    // superviviente
}
```

1. Se construye el círculo con los niños numerados de 1 a N.
2. Mientras quede más de un niño:
   - Se avanza `saltos` nodos desde la posición actual.
   - Se marca ese nodo para eliminar y se mueve el puntero `apunta` al siguiente **antes** de borrarlo (para no quedar con un puntero colgante).
   - Se elimina el nodo.
3. Cuando queda uno solo, se imprime su número (el superviviente).

### Entrada / salida

- **Entrada**: dos enteros, `niños` (cantidad) y `saltos` (paso de conteo).
- **Salida**: el número del niño que sobrevive.
