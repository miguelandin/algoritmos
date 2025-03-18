#include <cmath>
#include <iostream>
double raiz(double objeto, double error, double alto, double bajo);

int main()
{
    double num, error;

    std::cin >> num;
    std::cin >> error;
    if (num >= 0 && error > 0) // precondición
        std::cout << raiz(num, error, num, 0); // siempre poner alto = num, bajo = 0
    else
        std::cout << "ERROR";
    return 0;
}

double raiz(double objeto, double error, double alto, double bajo) // t(n) = t(n/2) + 1 -> t(n) = c + log(n)/log(2) = O(log(n))
{
    double media = (alto + bajo) / 2; // coge la media entre alto y bajo
    double sqr = media * media; // se calcula el cuadrado
    double diff = fabs(sqr - objeto); // calcula la diferencia en valor absoluto

    if (diff <= error) // caso base, comprueba que se aproxime al error
        return media; // devuelve el resultado

    if (sqr > objeto) // se comprueba por donde se hace la busqueda:
    {
        std::cout << media << std::endl; // muestra el estado del resultado
        return raiz(objeto, error, media, bajo); // por debajo de media
    } else {

        std::cout << media << std::endl; // muestra el estado del resultado
        return raiz(objeto, error, alto, media); // por encima de media
    }
}
