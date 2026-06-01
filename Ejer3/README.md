# Ejer3 — Algoritmos Recursivos

Este directorio reúne ejercicios centrados en la **recursión**: cálculo de
combinaciones mediante factorial recursivo, comprobación de palíndromos por
reducción del problema y cálculo de raíz cuadrada por búsqueda binaria
(bisección). El subdirectorio [`Determinante/`](Determinante/) contiene una
clase `Matriz` con el cálculo recursivo del determinante (ver su propio README).

---

## 1. Números combinatorios (`Combinaciones.cpp`)

### Idea principal
Calcula C(n, r) = n! / (r! · (n−r)!) con una función factorial recursiva,
leyendo pares `(n, r)` hasta que alguno sea negativo.

### Técnica algorítmica
Recursión (cálculo directo por fórmula).

### Cómo funciona el código
```cpp
res = factorial(n) / (factorial(r) * factorial(n - r));

int factorial(int entrada) {
    if (entrada <= 1) return 1;            // caso base
    else return entrada * factorial(entrada - 1);
}
```
Si `r > n` imprime `ERROR`; si `n` o `r` son negativos, el bucle termina. Por
usar enteros, desborda aproximadamente a partir de `13!`.

### Complejidad
- **Temporal:** `factorial` → T(n) = n + 1 = **O(n)**.
- **Espacial:** **O(n)** por la pila de recursión.

---

## 2. Comprobación de palíndromo (`Palindromo.cpp`)

### Idea principal
Una palabra es palíndromo si se lee igual de izquierda a derecha que al revés.
Se comprueba comparando el primer y el último carácter y reduciendo el problema
a la subpalabra interior.

### Técnica algorítmica
Recursión por reducción ("decrease and conquer"): cada llamada elimina dos
caracteres (los extremos).

### Cómo funciona el código
```cpp
bool esPalindromo(std::string palabra) {
    int n = palabra.length();
    if (n <= 1) return true;                       // caso base
    else {
        if (palabra[0] != palabra[n - 1])          // extremos distintos
            return false;
        else {
            std::string subPalabra = palabra.substr(1, n - 2);
            return esPalindromo(subPalabra);       // recurre sobre el interior
        }
    }
}
```
Casos base: una palabra de 0 o 1 carácter siempre es palíndromo. Si los
extremos difieren devuelve `false`; si coinciden, crea la subpalabra sin esos
dos extremos (`substr(1, n-2)`) y vuelve a llamarse.

### Complejidad
- **Temporal:** T(n) = T(n−2) + 1 → **O(n)**.
- **Espacial:** **O(n²)** debido a que en cada nivel de recursión se crea una
  nueva cadena con `substr` (copia), acumulando memoria proporcional a n + (n−2)
  + (n−4) + ... ≈ n²/4.

---

## 3. Raíz cuadrada por bisección (`RaizCuadrada.cpp`)

### Idea principal
Aproxima la raíz cuadrada de un número buscando el valor `media` cuyo cuadrado
está dentro de un margen de `error` respecto al objetivo, usando búsqueda
binaria sobre el intervalo `[bajo, alto]`.

### Técnica algorítmica
Divide y vencerás / búsqueda binaria (bisección): en cada paso se descarta la
mitad del intervalo de búsqueda.

### Cómo funciona el código
```cpp
double raiz(double objeto, double error, double alto, double bajo) {
    double media = (alto + bajo) / 2;
    double sqr = media * media;
    double diff = fabs(sqr - objeto);

    if (diff <= error) return media;          // aproximación aceptable

    if (sqr > objeto)
        return raiz(objeto, error, media, bajo); // buscar en la mitad inferior
    else
        return raiz(objeto, error, alto, media); // buscar en la mitad superior
}
```
Se invoca inicialmente con `alto = num` y `bajo = 0`. Se calcula la media del
intervalo y su cuadrado: si la diferencia con el objetivo es menor o igual que
el error, se acepta; si el cuadrado se pasa, se busca por debajo de la media; en
caso contrario, por encima. Imprime el valor de `media` en cada paso para
mostrar la convergencia. El `main` valida la precondición `num >= 0 && error > 0`
e imprime `ERROR` si no se cumple.

### Complejidad
- **Temporal:** T(n) = T(n/2) + 1 → **O(log n)** respecto al tamaño del
  intervalo / precisión buscada.
- **Espacial:** **O(log n)** por la pila de recursión (recursión de cola).
