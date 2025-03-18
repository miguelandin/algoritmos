#include <iostream>
using namespace std;

void ordenarSeleccion(int x[], int len) // Precondición Ninguna (solo que haya array y tamaño)
{ // T(n) = n(n-1)/2 Comp Temp = O(n²) Comp Esp = O(1)
    int temp; //valor temporal
    int pos; //la posicion en la que se encontro el valor más pequeño
    bool encontrado; // Crear boleano para saber si se ha encontrado un número menor

    for (int i = 0; i < len; i++) {
        encontrado = false; //se inicializa como no encontrado
        temp = x[i]; // valor temporal en la iteración que se encuentre el bucle
        for (int j = i + 1; j < len; j++) //el bulce empieza desde donde se encuentre la i del anterior
            if (temp > x[j]) { //si se encuentra un num menor, se guarda como valor temporal y su posicion
                temp = x[j];
                pos = j;
                encontrado = true; // se establece como encontrado para hacer el cambio de lugares entre el numero mayor y el menor
            }
        if (encontrado) { // se hace el cambio
            x[pos] = x[i];
            x[i] = temp;
        }

        for (int k = 0; k < len; k++)
            cout << x[k] << " ";
        cout << endl;
    }
}

int main()
{
    int n;
    cin >> n;
    int* x = new int[n];
    for (int i = 0; i < n; i++)
        cin >> x[i];
    ordenarSeleccion(x, n);
}
