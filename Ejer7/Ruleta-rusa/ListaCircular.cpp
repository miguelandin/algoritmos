#include "ListaCircular.h"
#define assertdomjudge(x)                  \
    if (!(x)) {                            \
        std::cout << "ERROR" << std::endl; \
        exit(0);                           \
    }

ListaCircular::ListaCircular()
{
    n = 0;
    lista = nullptr;
}

Nodo* ListaCircular::getNodo(int pos)
{
    assertdomjudge(pos >= 0 && pos < n);

    Nodo* res = lista;

    for (int i = 0; i < pos; i++)
        res = res->siguienteNodo;

    return res;
}

void ListaCircular::insertar(int pos, string nuevo)
{
    assertdomjudge(pos >= 0 && pos <= n);

    if (n == 0) { // en caso de que sea el mismo elemento se apunta a si mismo
        lista->siguienteNodo = lista;
        lista->anteriorNodo = lista;
        lista->elemento = nuevo;

    } else {
        Nodo* nuevoNodo = new Nodo(); // se crea un nuevo nodo
        nuevoNodo->elemento = nuevo; // se establece su valor

        if (pos == 0) {
            nuevoNodo->siguienteNodo = lista; // apunta al principio
            nuevoNodo->anteriorNodo = lista->anteriorNodo; // apunta al final
            lista->anteriorNodo = nuevoNodo; // lista añade el nuevo nodo detrás
            lista = nuevoNodo; // se establece el nuevo nodo

        } else if (pos == n) {
            Nodo* ultimo = lista->anteriorNodo; // se obtiene el último
            nuevoNodo->siguienteNodo = lista; // apunta al principio
            nuevoNodo->anteriorNodo = ultimo; // apunta al final
            ultimo->siguienteNodo = nuevoNodo; // se establece el nuevo Nodo

        } else {
            Nodo* anterior = getNodo(pos - 1); // se obtiene el anterior
            nuevoNodo->anteriorNodo = anterior; // apunta al anterior
            nuevoNodo->siguienteNodo = anterior->siguienteNodo; // al siguiente
            anterior->siguienteNodo = nuevoNodo; // se establece el nuevo Nodo
        }
    }
    n++;
}
void ListaCircular::eliminar(int pos)
{
    assertdomjudge(pos >= 0 && pos < n);

    Nodo* eliminar; // puntero que indicará que nodo eliminar

    if (pos == 0) {
        Nodo* ultimo = getNodo(n - 1); // se obtiene el último
        eliminar = lista; // el nodo a eliminar apunta al principio
        lista = lista->siguienteNodo; // el principio pasa a ser el siguiente
        lista->anteriorNodo = ultimo; // el anterior es el último
        ultimo->siguienteNodo = lista; // el ultimo se actualiza

    } else if (pos == n - 1) {
        Nodo* anterior = getNodo(pos - 1); // se obtiene el anterior
        eliminar = anterior->siguienteNodo; // eliminar apunta al nodo pos
        anterior->siguienteNodo = lista; // el siguiente es el principio
        lista->anteriorNodo = anterior; // se actualiza el primero

    } else {
        Nodo* anterior = getNodo(pos - 1); // obtenemos el anterior
        eliminar = anterior->siguienteNodo; // eliminar apunta al nodo pos
        anterior->siguienteNodo = eliminar->siguienteNodo; // actualiza los-
        eliminar->siguienteNodo->anteriorNodo = anterior; // nodos adyacentes
    }

    delete eliminar;
    n--;
}

string ListaCircular::getValor(int pos)
{
    return getNodo(pos)->elemento;
}

void ListaCircular::setValor(int pos, string nuevo)
{
    getNodo(pos)->elemento = nuevo;
}

int ListaCircular::getN()
{
    return n;
}

void ListaCircular::girar(int p)
{
    Nodo* principio = lista; // para que gira la lista se cambia el principio

    for (int i = 0; i < p; i++) // hacia la derecha
        principio = principio->siguienteNodo;

    for (int i = p; i < 0; i++) // hacia la izquierda
        principio = principio->anteriorNodo;

    lista = principio; // se actualiza el primer Nodo
}

ListaCircular::~ListaCircular()
{
    Nodo* actual = lista;
    Nodo* siguiente;

    for (int i = 0; i < n; i++) {
        siguiente = actual->siguienteNodo;
        delete actual;
        actual = siguiente;
    }
}
