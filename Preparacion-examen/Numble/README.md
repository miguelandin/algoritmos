# Numble — Combinaciones que suman un total

## Idea principal

Dado un conjunto de 4 posiciones (`TAM = 4`) parcialmente rellenas, donde algunas casillas son conocidas y otras están "huecas" (marcadas con `-1`), el programa encuentra e imprime **todas las combinaciones de dígitos (0–9)** que completan las casillas vacías de forma que la suma total coincida con un objetivo dado.

## Técnica algorítmica

**Backtracking (vuelta atrás)** con recursión:

- Se avanza posición a posición.
- Si la posición ya tiene un valor fijo (distinto de `-1`), se mantiene y se pasa a la siguiente.
- Si la posición es un hueco (`-1`), se prueban todos los dígitos del 0 al 9; tras cada intento se restaura el `-1` (deshacer el cambio) para explorar la siguiente alternativa.
- Al completar las 4 posiciones, se comprueba si la suma cumple el objetivo y, en ese caso, se imprime la combinación.

## Complejidad

- **Tiempo**: cada hueco genera hasta 10 ramas. Con `k` huecos, el número de combinaciones exploradas es **O(10^k)** (en el peor caso, los 4 huecos, O(10^4)). El comentario del código indica O(n²) de forma aproximada, pero el coste real es exponencial en el número de huecos.
- **Espacio**: **O(1)** adicional (más allá del array de tamaño fijo y la pila de recursión de profundidad TAM = 4).

## Cómo funciona el código

### `calcularTotal`

```cpp
int calcularTotal(int* valores)
{
    int total = 0;
    for (int i = 0; i < TAM; i++) {
        if (valores[i] != -1) total += valores[i];
        else                  total += 0;
    }
    return total;
}
```

Suma los valores del array, ignorando las casillas que siguen siendo `-1`. Recorre las 4 posiciones → **O(n)** con n = TAM.

### `combinaciones`

```cpp
void combinaciones(int total, int* valores, int pos)
{
    if (pos == TAM) {                         // caso base: combinación completa
        if (calcularTotal(valores) == total) {
            for (int i = 0; i < TAM; i++)
                cout << valores[i] << " ";
            cout << endl;
        }
        return;
    }

    if (valores[pos] != -1)                   // posición ya fijada
        combinaciones(total, valores, pos + 1);
    else
        for (int i = 0; i < 10; i++) {        // hueco: prueba 0..9
            valores[pos] = i;
            combinaciones(total, valores, pos + 1);
            valores[pos] = -1;                // backtracking: deshacer
        }
}
```

- **Caso base** (`pos == TAM`): la combinación está completa; se valida la suma y, si coincide, se imprime.
- **Posición fija**: avanza sin modificar.
- **Hueco**: itera los 10 dígitos posibles, llama recursivamente y restaura el `-1` para no contaminar otras ramas.

### `main`

Lee los 4 valores iniciales (con `-1` en los huecos) y el `total` objetivo, luego lanza `combinaciones(total, valores, 0)`.

### Entrada / salida

- **Entrada**: 4 enteros (usar `-1` para huecos) seguidos del total objetivo.
- **Salida**: cada combinación válida en una línea.
