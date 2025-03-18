#include <iostream>

const int LEN = 8; // cantidad de monedas diferentes que hay
int monedas[LEN] = { 500, 200, 100, 50, 25, 10, 5, 1 }; // valores de las monedas

void Cambio(int cantidad, int monedas[])
{ // T(n) = cantidad + len = O(n)
    // M(n) = Len = O(n)
    int i = 0;
    int res[LEN] = { 0 }; // resultado, se inicializa en 0

    while (cantidad > 0) {
        if (cantidad - monedas[i] >= 0) {
            cantidad -= monedas[i];
            res[i] += 1;
            i = 0;
        } else
            i++;
    }

    for (i = 0; i < LEN; i++)
        std::cout << res[i] << " ";
    std::cout << std::endl;
}

int main()
{
    int n;
    while (true) {
        std::cin >> n;
        if (n < 0)
            break;
        Cambio(n, monedas);
    }

    return 0;
}
