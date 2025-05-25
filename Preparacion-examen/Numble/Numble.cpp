#include <iostream>
using namespace std;
const int TAM = 4;

int calcularTotal(int* valores) // T(n) = O(n), M(n) = O(1)
{
    int total = 0;

    for (int i = 0; i < TAM; i++) {
        if (valores[i] != -1)
            total += valores[i];
        else
            total += 0;
    }

    return total;
}

void combinaciones(int total, int* valores, int pos) // T(n) = O(n^2), M(n) = O(1)
{
    if (pos == TAM) { // caso base, se completa la combinación
        if (calcularTotal(valores) == total) { // en caso de llegar al objetivo
            for (int i = 0; i < TAM; i++) // lo imprime
                cout << valores[i] << " ";
            cout << endl;
        }
        return; // termina iteración
    }

    if (valores[pos] != -1) // si no es -1 se pasa al siguiente número de la combinación
        combinaciones(total, valores, pos + 1);
    else
        for (int i = 0; i < 10; i++) { // se es -1 se prueba todas las posibilidades del 0 al 9
            valores[pos] = i;
            combinaciones(total, valores, pos + 1);
            valores[pos] = -1;
        }
}
int main()
{
    int num;
    int* valores = new int[TAM];
    int total;

    for (int i = 0; i < TAM; i++) {
        cin >> num;
        valores[i] = num;
    }
    cin >> total;

    combinaciones(total, valores, 0);
    delete[] valores;
    return 0;
}
