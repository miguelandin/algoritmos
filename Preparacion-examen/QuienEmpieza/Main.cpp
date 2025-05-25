#include "Circulo.h"
#include <iostream>
using namespace std;

int main()
{
    int niños, saltos;
    cin >> niños >> saltos;
    Circulo circulo;

    for (int i = 1; i <= niños; i++)
        circulo.encolar(i);

    Nodo* apunta = circulo.getPrincipio();
    Nodo* eliminar;

    while (circulo.getN() > 1) {
        for (int i = 0; i < saltos; i++)
            apunta = apunta->siguiente;
        eliminar = apunta;
        apunta = apunta->siguiente;
        circulo.eliminar(eliminar);
    }
    cout << apunta->num;
}
