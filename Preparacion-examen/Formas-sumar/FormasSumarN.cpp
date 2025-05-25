#include <iostream>
using namespace std;

void formaSumar(int n, int suma, int* valores, int j) // T(n) = O(2^n), M(n) = O(n)
{
    if (suma == n) { // en caso de exito imprimir la combinación
        for (int i = 0; i < j; i++)
            cout << valores[i] << " ";
        cout << endl;
    }

    for (int i = 1; i < n; i++)
        if (suma + i <= n) {
            valores[j] = i;
            formaSumar(n, suma + i, valores, j + 1);
        }
}

int main()
{
    int n;
    cin >> n;
    int* valores = new int[n];

    formaSumar(n, 0, valores, 0);
    delete[] valores;
    return 0;
}
