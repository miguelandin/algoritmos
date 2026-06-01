# Batería de Coches

Programa que, dado un conjunto de pilas con cierto voltaje y un voltaje mínimo, calcula el **número máximo de coches** que se pueden cargar emparejando pilas.

## Enunciado (reconstruido del código)

Cada coche necesita un voltaje mínimo `v_min` para arrancar. Se dispone de `n_pilas` pilas, cada una con un voltaje. Un coche se carga usando **dos pilas distintas** cuya suma de voltajes alcance o supere `v_min`; esas dos pilas se consumen (se eliminan). Se quiere saber cuántos coches se pueden cargar.

### Entrada
- Número de casos de prueba.
- Por cada caso: `n_pilas`, `v_min` y a continuación los `n_pilas` voltajes.

### Salida
- Por cada caso, el número de coches cargables.

## Idea principal

Estrategia **voraz (greedy)** por fuerza bruta: recorre las pilas y, para cada una, busca otra pila con la que la suma de voltajes alcance `v_min`. Si la encuentra, incrementa el contador de coches y elimina ambas pilas del array; continúa hasta agotar las posibilidades.

## Técnica algorítmica

- **Voraz / fuerza bruta** con doble bucle anidado sobre las pilas.
- Array dinámico (`new int[n_pilas]`) que se va **compactando** al eliminar pilas usadas, ajustando `n_pilas` por referencia.

## Complejidad

- `calculaMax`: doble bucle O(n²) y cada `eliminar` es O(n) por el desplazamiento, dando un peor caso de **O(n³)** por caso de prueba.
- Memoria: O(n) para el array de voltajes.

## Cómo funciona el código

- **`main`**: lee el número de casos. Por cada caso lee `n_pilas`, `v_min` y rellena el array `pilas`. Llama a `calculaMax` e imprime el resultado, liberando luego el array con `delete[]`.
- **`calculaMax(pilas, n_pilas, v_min)`**:
  - Itera con `i` sobre cada pila y, en un bucle interno `j`, busca una pila distinta (`i != j`).
  - Calcula `v_acumulado = pilas[i] + pilas[j]`. Si alcanza `v_min`, suma un coche, **elimina** ambas pilas y rompe el bucle interno.
  - Al eliminar primero la posición `i` y luego `j`, ajusta el índice de `j` (`j > i ? j-1 : j`) porque tras borrar `i` los elementos posteriores se han desplazado una posición a la izquierda.
- **`eliminar(pilas, n_pilas, pos)`**: desplaza a la izquierda todos los elementos a partir de `pos` y decrementa `n_pilas` (pasado por referencia).

## Notas / observaciones del código

- `calculaMax` recibe `n_pilas` **por valor**, pero `eliminar` lo recibe **por referencia**; por tanto las eliminaciones no reducen el `n_pilas` que controla los bucles `for` de `calculaMax`. Esto puede hacer que se recorran posiciones más allá del número real de pilas vivas. La intención algorítmica es la descrita (emparejar y consumir pilas).
