#include <iostream>
using namespace std;

void imprimir(int* numeros, int tam)
{
    for (int i = 0; i < tam; i++)
        cout << numeros[i] << " ";
    cout << endl;
}

void ordenarInserccion(int* numeros, int tam)
{
    int temp;
    for (int i = 0; i < tam; i++) {
        temp = numeros[i];
        int j = i;
        while (temp < numeros[j - 1] && j > 0) {
            numeros[j] = numeros[j - 1];
            j--;
        }
        numeros[j] = temp;
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
    ordenarInserccion(numeros, tam);
}
