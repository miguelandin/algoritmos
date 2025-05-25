#include <iostream>
using namespace std;
void permutaciones(string& palabra, int n) // T(0) = 1, T(n) = n*T(n-1) + 1 = O(n!)
{ // M(n) = O(n²)
    if (palabra.length() - 1 == n) {
        cout << palabra << " ";
        return;
    }

    string copia = palabra;
    for (int i = n; i < palabra.length(); i++) {
        char temp = palabra[i];
        palabra[i] = palabra[n];
        palabra[n] = temp;
        permutaciones(palabra, n + 1);
        palabra = copia;
    }
}

int main()
{
    string palabra;
    cin >> palabra;
    permutaciones(palabra, 0);
}
