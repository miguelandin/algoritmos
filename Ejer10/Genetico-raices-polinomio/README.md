# Algoritmo Genético para Raíces de un Polinomio

## Idea principal

Aproxima una **raíz de un polinomio** (un valor `x` tal que `p(x) ≈ 0`) mediante un
**algoritmo genético / de búsqueda por mutación**. Se parte de una solución `x = 0`
y, en cada generación, se generan varias variantes ("hijos") mutando la `x` actual;
se conserva el hijo cuyo valor del polinomio esté **más cerca de 0**. El proceso se
repite hasta que ninguna mutación mejora a la solución actual.

## Técnica: optimización genética / hill-climbing estocástico

- Cada solución parcial es un par `(x, y)` donde `y = p(x)` (`SolucionParcial.h`).
- **Mutación**: a partir del padre se generan `ITERACIONES = 10` hijos sumando a la
  `x` del padre un número aleatorio.
- **Selección**: se evalúa la "aptitud" como cercanía de `|y|` a 0; cualquier hijo
  con `|y|` menor que la del padre lo reemplaza.
- **Criterio de parada**: si en una generación ningún hijo mejora al padre, se
  devuelve la `x` del padre como aproximación de la raíz.
- El proceso es **recursivo**: cada nueva generación llama de nuevo a la búsqueda con
  el mejor candidato encontrado.

## Función de mutación / generador aleatorio

```cpp
float Polinomio::obtenerAleatorioNormalEstandar() {
    float suma = 0;
    for (int i = 0; i < 12; i++)
        suma += rand() / (float)RAND_MAX; // 12 uniformes en [0,1]
    return (suma - 6); // resultado aproximadamente N(0,1) en [-6,+6]
}
```

Genera un número que sigue aproximadamente una **distribución normal estándar**
(media 0, desviación 1) sumando 12 variables uniformes en `[0,1]` y restando 6
(aplicación del Teorema Central del Límite). Esto provoca mutaciones pequeñas cerca
de la media y, ocasionalmente, saltos mayores.

## Estructuras de datos

- **`SolucionParcial`** (`SolucionParcial.h`): clase con `float x`, `float y` y un
  método `imprimir()`.
- **`Polinomio`** (`Polinomio.h/.cpp`): guarda el grado `n` y un array de
  `coeficientes` de tamaño `n+1` (índice = grado del sumando).

## Cómo funciona el código

- `Polinomio(n, coeficientes)`: copia los coeficientes a memoria propia.
- `evaluar(x)`: calcula `p(x) = Σ coeficientes[i] · x^i`.
- `obtenerRaiz()`: crea la solución inicial `x = 0`, `y = p(0)` y lanza la búsqueda
  recursiva.
- `obtenerRaizRecursivo(padre)`:
  1. Imprime el padre seleccionado.
  2. Genera 10 hijos mutando `padre.x` y evalúa cada uno (los imprime).
  3. Elige cualquier hijo con `|y|` menor que el del padre como nuevo padre.
  4. Si hubo mejora, recursión con el nuevo padre; si no, devuelve `padre.x`.
- `main.cpp`: lee semilla aleatoria (`srand`), grado y coeficientes, crea el
  polinomio y ejecuta **5 búsquedas** independientes de raíz, mostrando cada una.

## Complejidad

- `evaluar`: O(n) en el grado del polinomio (usa `pow` por término).
- `obtenerAleatorioNormalEstandar`: O(1) (12 iteraciones fijas).
- `obtenerRaizRecursivo`: en cada generación hace un trabajo O(ITERACIONES · grado).
  El número total de generaciones depende del polinomio y del azar; el código lo
  documenta como ~O(n²) en tiempo y espacio (el espacio crece por la pila de
  recursión, ya que cada llamada reserva un array de 10 hijos).

## Notas

- Es un método **heurístico y estocástico**: no garantiza encontrar la raíz exacta
  ni todas las raíces; el resultado depende de la semilla aleatoria. Por eso `main`
  repite la búsqueda 5 veces.
