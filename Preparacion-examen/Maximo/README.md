# Máximo por Divide y Vencerás

## Idea principal

Calcula el valor máximo de un array de enteros usando la técnica de **divide y vencerás**: en lugar de recorrer el array secuencialmente, lo divide recursivamente en dos mitades, obtiene el máximo de cada mitad y devuelve el mayor de los dos.

## Técnica algorítmica

**Divide y vencerás (Divide and Conquer)**:

1. **Dividir**: parte el array en dos subarrays de tamaño aproximadamente igual (`mid = tam / 2`).
2. **Vencer**: resuelve recursivamente el máximo de cada mitad.
3. **Combinar**: compara los dos máximos parciales y devuelve el mayor.

## Complejidad

- **Tiempo**: `T(1) = 1`, `T(n) = 2·T(n/2) + 1` → **O(n)**. Aunque se divide el problema, hay que visitar todos los elementos al menos una vez, por lo que no se mejora respecto a un recorrido lineal.
- **Espacio**: **O(log n)** por la profundidad de la pila de recursión.

> Nota: el comentario en el código indica `T(n) = T(n/2) + 1`, pero realmente hay **dos** llamadas recursivas, por lo que la recurrencia correcta es `T(n) = 2·T(n/2) + 1`, que también resuelve a O(n).

## Cómo funciona el código

```cpp
int maximo(int* array, int tam)
{
    if (tam == 1)          // caso base: un solo elemento
        return array[0];

    int mid = tam / 2;
    int a = maximo(array, mid);            // máximo de la primera mitad
    int b = maximo(array + mid, tam - mid); // máximo de la segunda mitad

    if (a > b) return a;
    else       return b;
}
```

- **Caso base**: cuando el subarray tiene un único elemento (`tam == 1`), ese elemento es el máximo.
- **Aritmética de punteros**: `array + mid` desplaza el puntero al inicio de la segunda mitad, y `tam - mid` es su tamaño. Esto evita copiar el array.
- El `main` lee el tamaño `tam`, reserva el array dinámicamente, lo rellena desde la entrada estándar, imprime el resultado de `maximo` y libera la memoria con `delete[]`.

### Entrada / salida

- **Entrada**: primero el tamaño `tam`, luego `tam` enteros.
- **Salida**: el valor máximo del array.
