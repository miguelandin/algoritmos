#include <iostream>
using namespace std;

void imprimir(int* numeros, int tam)
{
    for (int i = 0; i < tam; i++)
        cout << numeros[i] << " ";
    cout << endl;
}

void ordenarBurbuja(int* numeros, int tam)
{
    int temp1, temp2;
    for (int i = 0; i < tam - 1; i++) {
        for (int j = 0; j < tam - i; j++) {
            temp1 = numeros[j];
            temp2 = numeros[j + 1];

            if (temp1 > temp2) {
                numeros[j] = temp2;
                numeros[j + 1] = temp1;
            }
        }
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
    ordenarBurbuja(numeros, tam);
}
