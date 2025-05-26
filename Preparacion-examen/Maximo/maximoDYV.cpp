#include <iostream>
using namespace std;

int maximo(int* array, int tam) // T(0) = 1, T(n) = T(n/2) + 1 = O(n)
{ //M(n) = O(log(n))
    if (tam == 1) // caso base, se separa hasta un único número
        return array[0];

    int mid = tam / 2;
    int a = maximo(array, mid);
    int b = maximo(array + mid, tam - mid);

    if(a > b) // se devuelve el mayor
        return a;
    else
        return b;
}

int main()
{
    int tam, num;
    cin >> tam;
    int* array = new int[tam];
    for (int i = 0; i < tam; i++) {
        cin >> num;
        array[i] = num;
    }

    cout<<maximo(array, tam);
    delete[] array;
    return 0;
}
