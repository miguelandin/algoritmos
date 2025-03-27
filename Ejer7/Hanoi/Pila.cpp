#include "Pila.h"

Pila::Pila(string name) // T(n) = M(n) = O(1)
{
    this->name = name;
    this->cima = nullptr;
}

std::string Pila::nombrePila() // T(n) = M(n) = O(1)
{
    return this->name;
}

void Pila::apilar(int num) // T(n) = M(n) = O(1)
{
    if (estaVacia()) // se crea la cima actual, su siguiente es el de abajo
        cima = new Nodo(num, nullptr); // -> el siguiente apunta a null
    else
        cima = new Nodo(num, cima); // su siguiente es la antigua cima

    cout << "Apilando disco " << num << " en poste " << name << endl;
}

int Pila::desapilar() // T(n) = M(n) = O(1)
{
    Nodo* eliminar = cima; // apunta al nodo a eliminar
    cima = cima->siguiente; // la cima pasa a ser el de abajo
    int num = eliminar->valor; // se obtiene el valor de la cima
    delete eliminar; // elimina el Nodo de la cima

    cout << "Desapilando disco " << num << " del poste " << name << endl;
    return num;
}

bool Pila::estaVacia() // T(n) = M(n) = O(1)
{
    return cima == nullptr; // si la cima es null, está vacía
}
