# Suma de Elementos por Divide y Vencerás

## Idea principal

Calcula la suma de todos los elementos de un array de enteros aplicando la técnica de **divide y vencerás**: divide el array en dos mitades, suma cada mitad recursivamente y combina los resultados sumándolos.

## Técnica algorítmica

**Divide y vencerás (Divide and Conquer)**:

1. **Dividir**: parte el array en dos subarrays (`mitadO` = primera mitad, `mitadF` = segunda mitad).
2. **Vencer**: suma recursivamente cada subarray.
3. **Combinar**: devuelve la suma de ambos resultados parciales.

## Complejidad

- **Tiempo**: `T(1) = 1`, `T(n) = 2·T(n/2) + 1` → **O(n)**. Se visitan todos los elementos; el coste es lineal, igual que una suma secuencial.
- **Espacio**: `M(1) = 1`, `M(n) = M(n/2) + 1` → **O(log n)** por la profundidad de la pila de recursión.

## Cómo funciona el código

```cpp
int sumarElementos(int* array, int n)
{
    if (n == 1)                 // caso base: un solo elemento
        return array[0];

    int mitadF = n / 2;         // tamaño de la segunda mitad
    int mitadO = n - mitadF;    // tamaño de la primera mitad

    int suma1 = sumarElementos(array, mitadO);          // primera mitad
    int suma2 = sumarElementos(array + mitadO, mitadF); // segunda mitad

    return suma1 + suma2;       // combinación
}
```

- **Caso base**: con un único elemento (`n == 1`), la suma es ese elemento.
- **División**: `mitadF = n / 2` y `mitadO = n - mitadF` reparten el array; usar `mitadO` para la primera mitad asegura un reparto correcto cuando `n` es impar.
- **Aritmética de punteros**: `array + mitadO` apunta al inicio de la segunda mitad sin copiar datos.

### `main`

```cpp
int main()
{
    int n;
    cin >> n;
    n++;                        // se procesarán n+1 elementos: 0..n

    int* array = new int[n];
    for (int i = 0; i < n; i++)
        array[i] = i;           // rellena con 0, 1, 2, ..., n-1

    cout << sumarElementos(array, n);
    delete[] array;
}
```

- Lee `n` y lo incrementa en 1, de modo que el array tendrá `n+1` casillas.
- Rellena el array con los valores `0, 1, 2, ..., n` (autogenerados, no leídos de entrada).
- Imprime la suma total. Por construcción equivale a `0 + 1 + ... + n = n·(n+1)/2`.

### Entrada / salida

- **Entrada**: un entero `n`.
- **Salida**: la suma de los enteros de 0 a n (el array se genera internamente).
