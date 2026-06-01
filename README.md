# Algoritmos y Estructuras de Datos

Repositorio de ejercicios de la asignatura de Algoritmos y Estructuras de Datos, implementados en C++. Cada subdirectorio contiene su propio `README.md` con la explicación detallada del algoritmo, su técnica y su complejidad.

## Estructura

El material está dividido en dos bloques: los ejercicios de prácticas (`Ejer2`–`Ejer10`) y el conjunto de problemas de `Preparacion-examen`.

### Ejercicios de prácticas

| Ejercicio | Tema | Contenido |
|-----------|------|-----------|
| [Ejer2](Ejer2/) | Ordenación y combinatoria | Burbuja, inserción, selección y combinaciones |
| [Ejer3](Ejer3/) | Recursión | Combinaciones, palíndromo, raíz cuadrada por bisección y [determinante](Ejer3/Determinante/) por cofactores |
| [Ejer4](Ejer4/) | Divide y vencerás / Prog. dinámica | Merge Sort y combinaciones con triángulo de Pascal |
| [Ejer5](Ejer5/) | Voraz y backtracking | Cambio de monedas y laberinto |
| [Ejer6](Ejer6/) | Listas | Lista [contigua](Ejer6/Contigua/) y [enlazada](Ejer6/Enlazada/) |
| [Ejer7](Ejer7/) | Pilas, colas y listas circulares | [Torres de Hanói](Ejer7/Hanoi/), [ruleta rusa](Ejer7/Ruleta-rusa/) y [supermercado](Ejer7/Supermercado/) |
| [Ejer8](Ejer8/) | Tablas hash | Dispersión [abierta](Ejer8/Hash-dispersion-abierta/), [cerrada](Ejer8/Hash-dispersion-cerrada/) y [sin colisión](Ejer8/Hash-sin-colision/) |
| [Ejer9](Ejer9/) | Árboles y colas de prioridad | [ABB](Ejer9/Arbol-binario-busqueda/) y [cola de prioridad](Ejer9/Supermercado-Cola-Prioridad/) (min-heap) |
| [Ejer10](Ejer10/) | Metaheurística y grafos | [Algoritmo genético](Ejer10/Genetico-raices-polinomio/) y [grafo bipartito](Ejer10/Grafo-roji-blanco/) |

### Preparación de examen

| Problema | Técnica |
|----------|---------|
| [ABB](Preparacion-examen/ABB/) | Árbol binario de búsqueda |
| [BateriaCoches](Preparacion-examen/BateriaCoches/) | Emparejado voraz / fuerza bruta |
| [Biblioteca](Preparacion-examen/Biblioteca/) | Lista contigua |
| [Eurocopa-amañada](Preparacion-examen/Eurocopa-amañada/) | Divide y vencerás |
| [Formas-sumar](Preparacion-examen/Formas-sumar/) | Backtracking |
| [Hash-cerrada](Preparacion-examen/Hash-cerrada/) | Tabla hash dispersión cerrada |
| [Maximo](Preparacion-examen/Maximo/) | Divide y vencerás |
| [Numble](Preparacion-examen/Numble/) | Backtracking |
| [Ordenaciones](Preparacion-examen/Ordenaciones/) | Burbuja, inserción, selección |
| [QuienEmpieza](Preparacion-examen/QuienEmpieza/) | Problema de Josephus (lista circular) |
| [StringPermutations](Preparacion-examen/StringPermutations/) | Permutaciones por backtracking |
| [Sumar-elementos](Preparacion-examen/Sumar-elementos/) | Divide y vencerás |

## Compilación

Cada ejercicio se compila con `g++`. Ejemplo:

```sh
g++ -o out *.cpp
./out < 1.in
```

Muchos ejercicios incluyen ficheros de prueba `*.in` (entrada) y la macro `assertdomjudge.h`, propia del juez online DOMjudge, para validar precondiciones.

> Los binarios compilados (`out`, `a.out`) están ignorados por Git.
