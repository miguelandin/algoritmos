# Ejer3/Determinante — Clase Matriz y Determinante Recursivo

Implementa una clase `Matriz` con gestión dinámica de memoria, operaciones
algebraicas básicas y, como pieza central, el **cálculo del determinante por
expansión de cofactores (desarrollo de Laplace)** de forma recursiva.

## Archivos
- `Matriz.h` — declaración de la clase (atributos y firmas de métodos).
- `Matriz.cpp` — implementación de todos los métodos.
- `main.cpp` — programa interactivo controlado por menú de operaciones.

---

## Estructura de la clase `Matriz`

```cpp
class Matriz {
private:
    double** matriz;   // matriz bidimensional dinámica
    int n_filas;
    int n_columnas;
public:
    // constructores, destructor, operador =, operaciones...
};
```
La matriz se almacena como un puntero a punteros (`double**`) reservado
dinámicamente. La clase implementa la **regla de los tres**: constructor de
copia, operador de asignación (`operator=`) y destructor, todos liberando y
reservando memoria para evitar fugas y copias superficiales.

### Operaciones implementadas
| Operación | Método / operador | Complejidad temporal |
|-----------|--------------------|----------------------|
| Suma | `operator+` | O(n·m) |
| Resta | `operator-` | O(n·m) |
| Producto por escalar | `operator*(double)` | O(n·m) |
| Producto de matrices | `operator*(Matriz)` | ~O(n·m·k) |
| Traspuesta | `calcularTraspuesta` | O(n·m) |
| ¿Es simétrica? | `esSimetrica` | O(n·m) |
| Máximo / mínimo | `obtenerMaximo` / `obtenerMinimo` | O(n·m) |
| Rellenar manual / aleatorio | `rellenarManual` / `rellenarAleatorio` | O(n·m) |
| Mostrar | `mostrarMatriz` | O(n·m) |
| Determinante | `calcularDeterminante` | O(n!) |

> Nota sobre el producto de matrices: el bucle interno itera con
> `k < m.n_columnas` en lugar de sobre la dimensión común; esto es correcto
> solo cuando la matriz es cuadrada (`n_columnas == m.n_filas == m.n_columnas`).

---

## Algoritmo central: cálculo del determinante

### Idea principal
El determinante se calcula desarrollando por la **primera fila**: para cada
columna se construye la submatriz menor (eliminando la fila 0 y esa columna), se
calcula recursivamente su determinante y se suman/restan los términos según el
signo del cofactor (alternancia +/−).

### Técnica algorítmica
**Divide y vencerás recursivo** (expansión de Laplace / cofactores). Reduce una
matriz n×n a n subproblemas de (n−1)×(n−1).

### Cómo funciona el código
```cpp
double Matriz::calcularDeterminante() const {
    if (n_filas != n_columnas) { std::cout << "ERROR"; return 0; } // debe ser cuadrada
    if (n_filas == 1) return matriz[0][0];                          // caso base 1x1
    if (n_filas == 2)                                               // caso base 2x2
        return matriz[0][0]*matriz[1][1] - matriz[0][1]*matriz[1][0];

    double det = 0;
    for (int col = 0; col < n_columnas; ++col) {
        Matriz submatriz(n_filas - 1, n_columnas - 1);  // menor sin fila 0 y col
        for (int i = 1; i < n_filas; ++i) {             // se salta la fila 0
            int subcol = 0;
            for (int j = 0; j < n_columnas; ++j) {
                if (j == col) continue;                 // se salta la columna actual
                submatriz.matriz[i-1][subcol] = matriz[i][j];
                ++subcol;
            }
        }
        double subdet = submatriz.calcularDeterminante();          // recursión
        det += (col % 2 == 0 ? 1 : -1) * matriz[0][col] * subdet;  // signo alterno
    }
    return det;
}
```
Pasos:
1. **Precondición:** la matriz debe ser cuadrada; si no, imprime `ERROR`.
2. **Casos base:** 1×1 devuelve el único elemento; 2×2 aplica la fórmula directa
   `ad − bc`.
3. **Caso general:** por cada columna `col` de la primera fila, construye la
   submatriz menor copiando todas las filas salvo la 0 y todas las columnas
   salvo `col`. Calcula su determinante recursivamente y acumula
   `signo · matriz[0][col] · subdet`, donde el signo alterna +, −, +, ...

### Complejidad
- **Temporal:** T(n) = n·T(n−1) + O(n²) → **O(n!)**. Es el método clásico de
  cofactores, exponencial/factorial; práctico solo para matrices pequeñas.
- **Espacial:** **O(n³)** por las submatrices creadas a lo largo de la cadena de
  recursión.

---

## Programa principal (`main.cpp`)

Ejecuta un bucle con menú controlado por un carácter de operación:

| Tecla | Acción |
|-------|--------|
| `N` | Crear matriz nueva y rellenarla manualmente (`temp`) |
| `R` | Crear matriz nueva aleatoria con una semilla |
| `A` / `B` | Asignar `temp` a las matrices `a` o `b` |
| `+` `-` | `c = a + b` / `c = a - b` |
| `*` | `c = a * escalar` |
| `X` | `c = a * b` (producto de matrices) |
| `I` | Imprimir `c` |
| `>` / `<` | Máximo / mínimo de `a` |
| `S` | ¿Es `a` simétrica? |
| `T` | `c = traspuesta(a)` |
| `D` | Determinante de `a` |
| `F` | Fin del programa |

El flujo típico es crear matrices con `N`/`R`, asignarlas a `a`/`b` con `A`/`B`,
operar y consultar resultados.
