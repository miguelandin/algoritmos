#include <iostream>
using namespace std;

void ordenarInsercion(int x[], int len) // Ninguna precondición (solo que haya array y tamaño)
{ // T(n) = n(n-1)/2, Orden de comp Temp = O(n²) Oden de comp Esp = O(1)
    int temp;
    int j;

    for (int i = 1; i < len; i++) {
        temp = x[i]; // coge el valor que se comparará
        j = i - 1; // j va hacia atrás desde i

        while (j >= 0 && x[j] > temp) // mientras que los valores sean mayorer al temporal, se
        {
            x[j + 1] = x[j];
            j--;
        }

        x[j + 1] = temp;

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
    ordenarInsercion(x, n);
}
