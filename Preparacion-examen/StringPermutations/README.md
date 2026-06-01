# Permutaciones de una Cadena por Backtracking

## Idea principal

Genera e imprime **todas las permutaciones** de los caracteres de una cadena introducida por el usuario, usando intercambios de caracteres y recursión.

## Técnica algorítmica

**Backtracking (vuelta atrás) con intercambios in situ**:

- Se fija una posición `n` y se prueba colocar en ella, por turnos, cada uno de los caracteres restantes (posiciones de `n` hasta el final).
- Para cada elección se intercambia el carácter elegido a la posición `n` y se permuta recursivamente el resto de la cadena (`n + 1`).
- Tras cada rama se **restaura** la cadena a su estado previo, de modo que la siguiente iteración parta del orden original.

## Complejidad

- **Tiempo**: `T(n) = n·T(n-1) + 1` → **O(n!)**, ya que existen n! permutaciones distintas y cada una se construye e imprime.
- **Espacio**: **O(n²)** según el comentario del código. El factor extra proviene de que en cada nivel de recursión se crea una `copia` completa de la cadena (`string copia = palabra;`), y la profundidad de la recursión es n.

## Cómo funciona el código

```cpp
void permutaciones(string& palabra, int n)
{
    if (palabra.length() - 1 == n) {   // caso base: última posición fijada
        cout << palabra << " ";
        return;
    }

    string copia = palabra;
    for (int i = n; i < palabra.length(); i++) {
        char temp   = palabra[i];      // intercambia palabra[i] <-> palabra[n]
        palabra[i]  = palabra[n];
        palabra[n]  = temp;
        permutaciones(palabra, n + 1); // permuta el resto
        palabra = copia;               // backtracking: restaura
    }
}
```

- **Caso base** (`palabra.length() - 1 == n`): cuando solo queda la última posición por fijar, la cadena ya representa una permutación completa y se imprime.
- **Bucle de intercambios**: para cada posición `i` desde `n`, se lleva el carácter de `i` al frente (`n`), se resuelve recursivamente el resto y se deshace el cambio restaurando desde `copia`.
- El uso de `palabra = copia` garantiza que cada iteración del bucle parta del mismo estado, evitando que intercambios anteriores contaminen las siguientes ramas.

### `main`

```cpp
int main()
{
    string palabra;
    cin >> palabra;
    permutaciones(palabra, 0);
}
```

Lee una palabra y lanza la generación de permutaciones desde la posición 0.

### Entrada / salida

- **Entrada**: una cadena (sin espacios, pues `cin >>` se detiene en el espacio).
- **Salida**: todas las permutaciones separadas por espacios.

> Nota: si la cadena tiene caracteres repetidos, las permutaciones duplicadas también se imprimen (el algoritmo no las filtra).
