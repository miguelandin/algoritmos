#include "ListaCircular.h"
#define assertdomjudge(x)                  \
    if (!(x)) {                            \
        std::cout << "ERROR" << std::endl; \
        exit(0);                           \
    }

ListaCircular::ListaCircular() // T(n) = M(n) = O(1)
{
    n = 0;
    lista = nullptr;
}

Nodo* ListaCircular::getNodo(int pos) // T(n) = O(n), M(n) = O(1)
{
    assertdomjudge(pos >= 0);

    Nodo* res = lista; // se inicializa en la pos inicial

    if (pos > n / 2) // se decide por que dirección ir
        for (int i = 0; i < pos; i++) // derecha
            res = res->siguienteNodo;
    else
        for (int i = n; i > pos; i--) // izquierda
            res = res->anteriorNodo;

    return res;
}

void ListaCircular::insertar(int pos, string nuevo) // T(n) = O(n), M(n) = O(1)
{
    Nodo* nuevoNodo = new Nodo(); // se crea un nuevo nodo
    nuevoNodo->elemento = nuevo; // se establece su valor

    if (n == 0) { // en caso de que sea el unico elemento, se apunta a si mismo
        lista = nuevoNodo;
        lista->siguienteNodo = nuevoNodo;
        lista->anteriorNodo = nuevoNodo;

    } else {
        Nodo* anterior = getNodo(pos == 0 ? n - 1 : pos - 1); // coge el anterior
        Nodo* siguiente = anterior->siguienteNodo; // el siguiente a pos

        nuevoNodo->anteriorNodo = anterior;
        nuevoNodo->siguienteNodo = siguiente;
        anterior->siguienteNodo = nuevoNodo;
        siguiente->anteriorNodo = nuevoNodo;
    }

    n++;
}

void ListaCircular::eliminar(int pos) // T(n) = O(n), M(n) = O(1)
{
    Nodo* anterior = getNodo(pos == 0 ? n - 1 : pos - 1); // coge el anterior
    Nodo* eliminar = anterior->siguienteNodo; // nodo a eliminar
    Nodo* siguiente = eliminar->siguienteNodo; // el siguiente a pos

    anterior->siguienteNodo = siguiente;
    siguiente->anteriorNodo = anterior;

    delete eliminar;
    n--;
}

string ListaCircular::getValor(int pos) // T(n) = O(n), M(n) = O(1)
{
    return getNodo(pos)->elemento;
}

void ListaCircular::setValor(int pos, string nuevo) // T(n) = O(n), M(n) = O(1)
{
    getNodo(pos)->elemento = nuevo;
}

int ListaCircular::getN()
{
    return n;
}

void ListaCircular::girar(int p) // T(n) = O(n), M(n) = O(1)
{
    Nodo* principio = lista; // para que gira la lista se cambia el principio
    if (p >= 0)
        for (int i = 0; i < p; i++) // hacia la derecha
            principio = principio->siguienteNodo;
    else
        for (int i = p; i < 0; i++) // hacia la izquierda
            principio = principio->anteriorNodo;

    lista = principio; // se actualiza el primer Nodo
}

ListaCircular::~ListaCircular() // T(n) = O(n), M(n) = O(1)
{
    for (int i = 0; i < n; i++)
        eliminar(0);
}
