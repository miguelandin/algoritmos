#include "ListaEnlazada.h"
#include <iostream>
#include <stdlib.h>
#define assertdomjudge(x)                  \
    if (!(x)) {                            \
        std::cout << "ERROR" << std::endl; \
        exit(0);                           \
    }

ListaEnlazada::ListaEnlazada()
{
    n = 0;
    lista = nullptr;
}

ListaEnlazada::~ListaEnlazada()
{
    Nodo* actual = lista;
    Nodo* siguiente;
    for (int i = 0; i < this->n; i++) {
        siguiente = actual->siguienteNodo; // se guarda el siguiente nodo
        delete actual; // se libera el nodo actual
        actual = siguiente; // el actual pasa a ser el siguiente
    }
}

Nodo* ListaEnlazada::getNodo(int pos)
{
    Nodo* res = lista;
    int i = 0;

    while (i != pos) {
        res = res->siguienteNodo;
        i++;
    }
    return res;
}

int ListaEnlazada::getValor(int pos)
{
    return getNodo(pos)->elemento;
}

void ListaEnlazada::setValor(int pos, int nuevo)
{
    getNodo(pos)->elemento = nuevo;
}

int ListaEnlazada::getN()
{
    return this->n;
}

void ListaEnlazada::insertar(int pos, int nuevo)
{
    Nodo* nuevoNodo = new Nodo;
    nuevoNodo->elemento = nuevo; // se inserta el valor
    nuevoNodo->siguienteNodo = getNodo(pos)->siguienteNodo; // se inserta la posición de su siguiente nodo
    getNodo(pos)->siguienteNodo = nuevoNodo; // se cambia el siguiente nodo del anterior por el nuevo nodo
    n++;
}

void ListaEnlazada::eliminar(int pos)
{
    if (pos == 0) {
        delete getNodo(pos);
    } else {
        getNodo(pos - 1)->siguienteNodo = getNodo(pos)->siguienteNodo; // se desenlaza
        delete getNodo(pos); // se libera memoria}
        n--;
    }
}

void ListaEnlazada::concatenar(ListaEnlazada* conectar)
{
    Nodo* temp = lista; // puntero temporal

    // itera hasta encontrar el ultimo elemento de la lista
    while (temp->siguienteNodo != NULL)
        temp = temp->siguienteNodo;

    // unimos el último nodo de nuestra lista con el primero de la otra lista
    temp->siguienteNodo = conectar->lista;
    n += conectar->n; // se añaden los n de la otra lista a la nuestra
}

int ListaEnlazada::buscar(int val)
{
    int res = -1, i = 0;
    Nodo* temp = lista;
    bool encontrado = false;

    while (!encontrado && temp != NULL) {
        if (temp->elemento == val) {
            res = i;
            encontrado = true;
        } else {
            temp = temp->siguienteNodo;
            i++;
        }
    }

    return res;
}
