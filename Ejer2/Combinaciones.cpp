#include <iostream>

int factorial(int entrada);

int main()
{
    int n, r, res;

    while (true) { // se repetirá hasta que el input sea negativo
        std::cin >> n;
        std::cin >> r;

        if (n < 0 || r < 0) // si es negativo termine el bucle
            break;

        if (r > n) { // si r > n no se pdría calcular la combinación
            std::cout << "ERROR"<<std::endl;
            continue;
        }

        res = factorial(n) / (factorial(r) * factorial(n - r));
        std::cout << res << std::endl;
    }

    return 0;
}

int factorial(int entrada) // calcula el factorial de entrada (limite ~ 12!)
{
    if (entrada <= 1) // caso base, devuelve 1
        return 1;
    else
        return entrada * factorial(entrada - 1); // devuelve π(x-1)
}
