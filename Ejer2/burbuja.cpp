#include <iostream>
int main()
{

    // parametros
    int tam;
    int temp;
    std::cin >> tam;
    int array[tam];
    for (int i = 0; i < tam; i++)
        std::cin >> array[i];

    // Ordenación
    for (int i = 0; i < tam - 1; i++) { // precondicion: Ninguna, T(n) = n(n-1)/2
        for (int j = 0; j < tam - 1; j++) { // el algoritmo opera sobre el array de entrada -> complejidad espacial = O(1)
            if (array[j] > array[j + 1]) {
                temp = array[j]; // valor temporal
                array[j] = array[j + 1]; // el valor menor pasa atrás
                array[j + 1] = temp; // el valor temporal pasa a ser el mayor
            }
            std::cout << array[j] << " ";
            if (j == tam - 2)
                std::cout << array[j + 1] << " " << std::endl;
        }
    }
    return 0;
}
