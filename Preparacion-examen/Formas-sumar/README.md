# Formas de Sumar N

Programa que genera e imprime **todas las formas de expresar un número `n` como suma de enteros positivos** (composiciones), usando sumandos en el rango `1..n-1`.

## Idea principal

Construir combinaciones de sumandos de manera incremental: en cada paso se prueba a añadir un sumando `i` mientras la suma parcial no supere `n`. Cuando la suma acumulada llega exactamente a `n`, se ha encontrado una combinación válida y se imprime. Se exploran así todas las ramas posibles mediante retroceso (backtracking).

## Técnica algorítmica

- **Backtracking / exploración recursiva** del espacio de combinaciones.
- Se reutiliza un array `valores` como **pila de la combinación actual**, donde `j` indica la profundidad / número de sumandos colocados.

## Complejidad

Indicada en el propio código:

- Tiempo: **T(n) = O(2ⁿ)** (número exponencial de composiciones).
- Memoria: **M(n) = O(n)** por la profundidad de la recursión y el array `valores`.

## Cómo funciona el código

- **`main`**: lee `n`, reserva `valores = new int[n]` y lanza `formaSumar(n, 0, valores, 0)` (suma inicial 0, profundidad 0). Libera la memoria al final.
- **`formaSumar(n, suma, valores, j)`**:
  - Si `suma == n`, imprime los `j` sumandos almacenados en `valores[0..j-1]`: es una composición encontrada.
  - Recorre los posibles sumandos `i` de `1` a `n-1`; si `suma + i <= n`, coloca `i` en `valores[j]` y llama recursivamente con `suma + i` y profundidad `j + 1`.
  - Al volver de la recursión, el bucle prueba el siguiente valor de `i`, sobrescribiendo `valores[j]` (efecto de backtracking).

Como los sumandos van de `1` a `n-1` y el orden importa, se generan **composiciones ordenadas** (por ejemplo, para `n = 3` produce `1 1 1`, `1 2`, `2 1`).

## Notas / observaciones del código

- El bucle usa sumandos hasta `n-1`, por lo que `n` solo no aparece como única forma (no se considera el sumando igual a `n`).
- Tras imprimir una solución, el flujo continúa el bucle; dado que ningún sumando adicional cabría sin superar `n`, no se generan ramas espurias a partir de una suma ya completa.
