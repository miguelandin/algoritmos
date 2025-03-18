#include <iostream>
using namespace std;

void combinar(int a[], int len_a, int b[], int len_b, int c[]) // ordena y combina dos arrays en un nuevo array
{ // T(n) = len_a + len_b = O(a+b)
    // M(n) = len_a + len_b = O(a+b)
    int k = 0, j = 0, i = 0;
    while (k < len_a && j < len_b) { // cuando se llega al final del array de alguno de los dos termina
        if (a[k] < b[j]) { // si el numero de a es menor que el de b
            c[i] = a[k];
            k++; // se pasa al siguiente numero de a, b se queda en la misma posición
        } else { // lo opuesto
            c[i] = b[j];
            j++; // se pasa al siguiente número de b y a se queda igual
        }

        i++; // se pasa a la siguiente posición del array que estamos creando
    }
    while (k < len_a) { // los valores restantes se ponen sin comprobar

        c[i] = a[k];
        i++;
        k++;
    }
    while (j < len_b) { // los valores restantes se ponen sin comprobar
        c[i] = b[j];
        i++;
        j++;
    }
}

void ordenarMergeSort(int x[], int len) // ordena un array dividiendolo en arrays mas pequeños recursivamente
{ // T(1) = 1, T(n) = 2T(n/2) + n + 1 -> T(n) = 2n + nlogn/log(2) - 1 = O(nlogn)
    // M(1) = 0, M(n) = M(n/2) + n + 1 -> M(n) = 2n + logn/log2 - 1 = O(n)
    if (len <= 1) // caso base
        return;

    int temp[len]; // array temporal
    int mid = len / 2; // posicion media del array
    int resto = len - mid; // la mitad izquierda redondeado hacia abjo
    int* izq = x; // apunta a la posición 0 del array temp
    int* der = &x[mid]; // apunta a la posicion "mid" del array temp

    /* Ordenar dos mitades */
    ordenarMergeSort(izq, mid);
    ordenarMergeSort(der, resto);
    /*Combinar ambas mitades y guardarlo en temp */
    combinar(izq, mid, der, resto, temp); // O(n)
    /* Copiar del array temporal al array resultado */

    for (int k = 0; k < len; k++) { // O(n)
        x[k] = temp[k];
        cout << x[k] << " ";
    }
    cout << endl;
}

int main()
{
    int n;
    cin >> n;
    int* x = new int[n];
    for (int i = 0; i < n; i++)
        cin >> x[i];
    ordenarMergeSort(x, n);
}
