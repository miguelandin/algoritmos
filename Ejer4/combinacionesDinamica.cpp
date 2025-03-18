#include <iostream>
#define assertdomjudge(x)                  \
    if ((x)) {                             \
        std::cout << "ERROR" << std::endl; \
        continue;                          \
    }

const int NIVEL = 10; // tamaño de los arrays

void iniciar(int pascal[NIVEL][NIVEL]) // crea la piramide de pascal
{ // T(n) = ∑(N-1), i=( N-1) -> T(n) = N²/2 = O(n²)
    // M(n) = Nivel*Nivel = O(n²);
    for (int i = 0; i < NIVEL; i++) {
        pascal[i][0] = 1; // los primeros valores se ponen en 1
        for (int j = 1; j <= i; j++)
            pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j]; // el valor de arriba izquierda + el valor arriba derecha
    }
}

int main()
{
    int pascal[NIVEL][NIVEL] = { 0 }; // crea el "triangulo" de pascal y inicializa sus valores en 0

    iniciar(pascal); // se crea el triangulo de pascal
    int n, r;

    while (true) {
        std::cin >> n >> r; // se introduce los valores
        if (n < 0) // si n < 0 termina el programa
            break;
        assertdomjudge(n >= NIVEL || r > n); // precondiciones, si no se cumplen, se repite el bucle
        std::cout << pascal[n][r] << std::endl; // mostrar resultado
    }

    return 0;
}
