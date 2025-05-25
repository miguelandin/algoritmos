#include "Circulo.h"

Circulo::Circulo()
{
    n = 0;
    principio = nullptr;
}
Nodo* Circulo::getPrincipio()
{
    return principio;
}

int Circulo::getN()
{
    return n;
}

void Circulo::encolar(int num)
{
    Nodo* nuevo = new Nodo(num);
    if (principio == nullptr) {
        principio = nuevo;
        nuevo->anterior = nuevo;
        nuevo->siguiente = nuevo;
    } else {
        Nodo* ultimo = principio->anterior;
        nuevo->anterior = ultimo;
        nuevo->siguiente = principio;
        ultimo->siguiente = nuevo;
        principio->anterior = nuevo;
    }
    n++;
}

void Circulo::eliminar(Nodo* eliminar)
{
    Nodo* anteriorEliminar = eliminar->anterior;
    Nodo* siguienteEliminar = eliminar->siguiente;

    if (eliminar == principio)
        principio = principio->siguiente;
    anteriorEliminar->siguiente = siguienteEliminar;
    siguienteEliminar->anterior = anteriorEliminar;
    delete eliminar;
    n--;
}

Circulo::~Circulo()
{
    for (int i = 0; i < n; i++) {
        eliminar(principio);
    }
    principio = nullptr;
}
