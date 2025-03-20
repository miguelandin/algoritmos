#include "ListaEnlazada.h"
#include <iostream>
#include <stdlib.h>
#define assertdomjudge(x)                  \
    if (!(x)) {                            \
        std::cout << "ERROR" << std::endl; \
        exit(0);                           \
    }

ListaEnlazada::ListaEnlazada() // T(n) = 1, M(n) = 1
{
    n = 0;
    lista = nullptr;
}

ListaEnlazada::~ListaEnlazada() // T(n) = n + 1, M(n) = 1
{
    Nodo* actual = lista;
    Nodo* siguiente;
    while (actual != NULL) {
        siguiente = actual->siguienteNodo; // se guarda el siguiente nodo
        delete actual; // se libera el nodo actual
        actual = siguiente; // el actual pasa a ser el siguiente
    }
}

Nodo* ListaEnlazada::getNodo(int pos) // T(n) = n + 1, M(n) = 1
{
    assertdomjudge(pos >= 0 && pos < n);

    Nodo* res = lista;

    for (int i = 0; i < pos; i++) {
        res = res->siguienteNodo;
    }

    return res;
}

int ListaEnlazada::getValor(int pos) // T(n) = n + 1, M(n) = 1
{
    return getNodo(pos)->elemento;
}

void ListaEnlazada::setValor(int pos, int nuevo) // T(n) = n + 1, M(n) = 1
{
    getNodo(pos)->elemento = nuevo;
}

int ListaEnlazada::getN() // T(n) = 1, M(n) = 1
{
    return this->n;
}

void ListaEnlazada::insertar(int pos, int nuevo) // T(n) = n + 1, M(n) = 1
{
    assertdomjudge(pos >= 0 && pos <= n);

    Nodo* nuevoNodo = new Nodo(); // se crea un nuevo nodo
    nuevoNodo->elemento = nuevo; // se inserta el valor

    if (pos == 0) { // si es al inicio de la lista
        nuevoNodo->siguienteNodo = lista; // el siguiente elemento del nuevo nodo es el primero de la lista antigua
        lista = nuevoNodo; // el primer elemento pasa a ser el nuevoNodo
    } else {
        Nodo* anterior = getNodo(pos - 1);
        nuevoNodo->siguienteNodo = anterior->siguienteNodo; // apunta al siguiente del antiguo nodo en pos
        anterior->siguienteNodo = nuevoNodo; // el siguiente Nodo pasa a ser el nuevo Nodo
    }

    n++; // incrementa el número de elementos
}

void ListaEnlazada::eliminar(int pos) // T(n) = n + 1, M(n) = 1
{
    assertdomjudge(pos >= 0 && pos < n);

    Nodo* eliminar;

    if (pos == 0) {
        eliminar = lista; // eliminar apunta al primer Nodo
        lista = lista->siguienteNodo; // lista pasa a empezar por el siguienteNodo
    } else {
        Nodo* anterior = getNodo(pos - 1); // se obtiene el nodo anterior al que queremos eliminar
        eliminar = anterior->siguienteNodo; // eliminar apunta al nodo que queremo borrar
        anterior->siguienteNodo = eliminar->siguienteNodo; // se desenlaza el nodo que queremos eliminar
    }
    delete eliminar; // se libera la memoria del puntero eliminar
    n--; // se decrementa el número de elementos
}

void ListaEnlazada::concatenar(ListaEnlazada* conectar) // T(n) = n + 1, M(n) = 1
{
    if (conectar->n == 0) // si la lista está vacia, no se hace nada
        return;

    if (n == 0) // si nuestra lista está vacía se enlaza desde el principio
        lista = conectar->lista;
    else
        getNodo(n - 1)->siguienteNodo = conectar->lista; // el siguienteNodo del ultimo pasa a ser el primero de la otra lista

    this->n += conectar->n; // actualiza el número de elementos
}

int ListaEnlazada::buscar(int val) // T(n) = n + 1, M(n) = 1
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
