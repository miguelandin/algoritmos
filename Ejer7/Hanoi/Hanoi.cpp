#include "Pila.h"
#include "assertdomjudge.h"
#include <iostream>
using namespace std;

void Hanoi(int n, Pila* origen, Pila* destino, Pila* temporal)
{ // T(n) = O(2^n), M(n) = O(n)
    if (n == 0) // si no quedan discos, terminar
        return;

    Hanoi(n - 1, origen, temporal, destino); // mueve los n - 1 discos superiores a temp
    destino->apilar(origen->desapilar()); // se hace el movimiento
    Hanoi(n - 1, temporal, destino, origen); // mueve los n - 1 discos que están a temp a destino
}

int main()
{
    Pila* A = new Pila("A");
    Pila* B = new Pila("B");
    Pila* C = new Pila("C");

    int n;
    cin >> n;

    for (int i = n; i > 0; i--)
        A->apilar(i);

    assertdomjudge(n > 0 && A != NULL && B != NULL && C != NULL); // precon
    Hanoi(n, A, C, B);

    for (int i = 0; i < n; i++)
        C->desapilar();

    return 0;
}
