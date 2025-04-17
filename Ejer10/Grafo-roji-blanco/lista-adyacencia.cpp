#include "lista-adyacencia.h"

ListaAdyacencia::ListaAdyacencia()
{ // T(n) = M(n) = O(1)
    lista = nullptr;
    n = 0; // numero de elementos
}

ListaAdyacencia::~ListaAdyacencia() // destructor
{ // T(n) = O(n), M(n) = O(1)
    Nodo* temp = lista;
    while (temp != nullptr) {
        Nodo* siguiente = temp->siguiente;
        delete temp;
        temp = siguiente;
    }
    n = 0;
}

void ListaAdyacencia::insertar(int valor) // inserta un vertice
{ // T(n) = M(n) = O(1)
    Nodo* nuevoNodo = new Nodo;
    nuevoNodo->valor = valor;
    nuevoNodo->siguiente = lista; // Insertar al principio
    lista = nuevoNodo;
    n++;
}
