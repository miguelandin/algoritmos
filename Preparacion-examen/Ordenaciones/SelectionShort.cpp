#include <iostream>
using namespace std;

void imprimir(int* numeros, int tam)
{
    for (int i = 0; i < tam; i++)
        cout << numeros[i] << " ";
    cout << endl;
}

void ordenarSeleccion(int* numeros, int tam)
{
    int temp, pos;
    for (int i = 0; i < tam; i++) {
        temp = numeros[i];
        pos = i;

        for (int j = i; j < tam; j++) {
            if (temp > numeros[j]) {
                temp = numeros[j];
                pos = j;
            }
        }
        numeros[pos] = numeros[i];
        numeros[i] = temp;
        imprimir(numeros, tam);
    }
}

int main()
{
    int num, tam;
    cin >> tam;
    int* numeros = new int[tam];
    for (int i = 0; i < tam; i++) {
        cin >> num;
        numeros[i] = num;
    }
    imprimir(numeros, tam);
    ordenarSeleccion(numeros, tam);
}
