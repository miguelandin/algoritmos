#include "ListaEnlazada.h"
#include "assertdomjudge.h"

ListaEnlazada::ListaEnlazada() // T(n) = M(n) = O(1)
{
    n = 0;
    lista = nullptr;
    punteroUltimoNodoAccedido = nullptr;
}

Nodo* ListaEnlazada::getNodo(int pos) // T(n) = O(n), M(n) = O(1)
{
    assertdomjudge(pos >= 0);

    Nodo* res = lista; // se incializa en la pos inicial

    if (pos > n / 2) // decide por donde buscar
        for (int i = 0; i < pos; i++) // derecha
            res = res->siguienteNodo;
    else
        for (int i = n; i > pos; i--) // izquierda
            res = res->anteriorNodo;

    posicionUltimoNodoAccedido = pos; // pos del último nodo accedido
    punteroUltimoNodoAccedido = res; // puntero del último nodo accedido
    return res;
}

Contacto ListaEnlazada::getValor(int pos) // T(n) = O(n), M(n) = O(1)
{
    assertdomjudge(n > 0 && pos >= 0 && pos < n);

    return getNodo(pos)->elemento; // devuelve el contacto del nodo en pos
}

void ListaEnlazada::setValor(int pos, Contacto nuevo) // T(n) = O(n), M(n) = O(1)
{
    assertdomjudge(n > 0 && pos >= 0 && pos < n);

    getNodo(pos)->elemento = nuevo; // pasa a apuntar al nuevo contacto
}

int ListaEnlazada::getN() // T(n) = M(n) = O(1)
{
    return n;
}

void ListaEnlazada::insertar(int pos, Contacto nuevo) // T(n) = O(n), M(n) = O(1)
{
    assertdomjudge(pos >= 0 && pos <= n);

    Nodo* nuevoNodo = new Nodo(); // se crea un nuevo nodo
    nuevoNodo->elemento = nuevo; // se establece su contacto

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
        
        if(pos == 0) // en caso de que queramos que sea el primero
            lista = nuevoNodo;
    }

    n++;
}

void ListaEnlazada::eliminar(int pos) // T(n) = O(n), M(n) = O(1)
{
    assertdomjudge(pos >= 0 && pos < n);

    Nodo* anterior = getNodo(pos == 0 ? n - 1 : pos - 1); // coge el anterior
    Nodo* eliminar = anterior->siguienteNodo; // nodo a eliminar
    Nodo* siguiente = eliminar->siguienteNodo; // el siguiente a pos

    anterior->siguienteNodo = siguiente;
    siguiente->anteriorNodo = anterior;

    delete eliminar;
    n--;
}

void ListaEnlazada::concatenar(ListaEnlazada* listaC) // T(n) = M(n) = O(n)
{
    assertdomjudge(listaC != NULL);

    Nodo* temp = listaC->lista; // puntero temporal que apunta al principio

    for (int i = 0; i < listaC->n; i++) // recorre los elementos de listaC
    {
        insertar(n, temp->elemento); // se inserta el elemento del nodo actual
        temp = temp->siguienteNodo; // pasa al siguiente nodo de lista a concat
    }
}

int ListaEnlazada::buscar(Contacto encontrar) // T(n) = O(n); M(n) = O(1)
{
    int res = -1, i = 0;
    Nodo* temp = lista;
    bool encontrado = false;

    while (!encontrado && i < n) { // hasta que se encuentre o llegue al final
        if (temp->elemento.telefono == encontrar.telefono) { // si misma clave
            res = i;
            encontrado = true; // termina la búsqueda
        } else {
            temp = temp->siguienteNodo; // itera al siguiente nodo
            i++;
        }
    }

    return res;
}

ListaEnlazada::~ListaEnlazada() // T(n) = O(n), M(n) = O(1)
{
    for (int i = 0; i < n; i++)
        eliminar(0);
}
