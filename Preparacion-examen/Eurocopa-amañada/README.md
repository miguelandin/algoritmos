# Eurocopa Amañada

Programa que simula un **torneo de eliminación directa** (estilo cuadro de la Eurocopa) en el que el resultado de cada ronda está "amañado": el ganador no se decide por mérito, sino por una regla fija basada en la **paridad del número de ronda**.

## Idea principal

Dado un cuadro con `n` equipos (etiquetados `A`, `B`, `C`, ...), el torneo se resuelve recursivamente dividiendo el cuadro en dos mitades. Cada mitad produce un ganador y, según si la ronda es par o impar, avanza el ganador de la izquierda o el de la derecha. Así se conoce de antemano (de forma amañada) quién gana cada enfrentamiento.

## Técnica algorítmica

- **Divide y vencerás (divide and conquer)**: el problema sobre `n` equipos se parte en dos subproblemas de tamaño `n/2`, resolviendo cada mitad recursivamente y combinando sus ganadores.
- La estructura de llamadas reproduce el **árbol del cuadro de eliminatorias**.

## Complejidad

- Tiempo: cada equipo participa en la recursión y se realizan O(n) llamadas en total, dando **O(n)** (asumiendo `n` potencia de 2 para que las divisiones sean exactas).
- Memoria: O(log n) por la pila de recursión (profundidad igual al número de rondas) más O(n) por el array de equipos.

## Cómo funciona el código

- **`main`**: lee `n`, reserva `char[n+1]` y rellena los equipos con letras consecutivas a partir de `'A'` (`equipos[i] = 'A' + i`), terminando la cadena con `'\0'`. Llama a `calcular_ganador(equipos, n, 0)` empezando en la ronda 0 y libera la memoria.
- **`calcular_ganador(equipos, n, ronda)`**:
  - **Caso base**: si `n == 1`, ese único equipo es el ganador y se devuelve.
  - **División**: parte el array en dos mitades (`mitad = n/2`). La primera mitad es `equipos`, la segunda es `equipos + mitad` (aritmética de punteros).
  - Resuelve recursivamente ambas mitades en la ronda siguiente (`ronda + 1`), obteniendo `ganador1` y `ganador2`.
  - **Regla amañada**: si `ronda` es par gana `ganador1` (mitad izquierda); si es impar gana `ganador2` (mitad derecha).
  - Imprime `"Ronda <ronda> Ganador <ganador>"` y devuelve el ganador.

Como la recursión imprime tras resolver las mitades, los mensajes aparecen **de las rondas más profundas (mayor número) hacia la final (ronda 0)**.

## Notas / observaciones del código

- El cuadro funciona limpiamente cuando `n` es potencia de 2; con otros valores las divisiones `n/2` no reparten exactamente todos los equipos.
