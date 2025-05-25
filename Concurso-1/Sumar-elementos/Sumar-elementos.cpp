#include <iostream>
using namespace std;

int sumarElementos(int* array, int n) // T(0) = 1, T(n) = 2*T(n/2) + 1 -> T(n) = O(n)
{ // M(0) = 1, M(n) = M(n/2) + 1 -> M(n) = O(log(n))
    if (n == 1) // caso base, se ha dividido por completo
        return array[0];

    int mitadF = n / 2; // segunda mitad
    int mitadO = n - mitadF; // primera mitad

    int suma1 = sumarElementos(array, mitadO);
    int suma2 = sumarElementos(array + mitadO, mitadF);

    return suma1 + suma2; // resultado final
}

int main()
{
    int n;
    cin >> n;
    n++;

    int* array = new int[n];

    for (int i = 0; i < n; i++)
        array[i] = i;
    
    cout<<sumarElementos(array, n);
    delete[] array;
}
