#include "ABB.h"
#include <iostream>
using namespace std;

ABB::ABB()
{
    raiz = nullptr;
    n = 0;
}

void ABB::insertar(int nuevoElemento)
{
    Nodo* nodo = new Nodo;
    nodo->contenido = nuevoElemento;

    if (raiz == nullptr) { // en caso de ser el primer nodo del árbol
        nodo->padre = nullptr;
        nodo->hijoIzquierdo = nullptr;
        nodo->hijoDerecho = nullptr;
        raiz = nodo;
    } else {
        Nodo* padre = buscarHueco(raiz, nuevoElemento); // devuelve el padre del hueco
        if (padre->contenido > nuevoElemento) // establece donde se situa
            padre->hijoIzquierdo = nodo;
        else
            padre->hijoDerecho = nodo;
        nodo->padre = padre; // establece su padre
    }
    n++;
}

void ABB::eliminar(int elementoAEliminar)
{
    Nodo* eliminar = buscar(elementoAEliminar);
    if (eliminar != nullptr)
        eliminarNodo(eliminar);
}

Nodo* ABB::buscar(int elementoABuscar)
{
    return buscarRecursivo(raiz, elementoABuscar);
}

Nodo* ABB::buscarHueco(Nodo* raizSubarbol, int elementoAInsertar)
{
    if (raizSubarbol->contenido > elementoAInsertar) {
        if (raizSubarbol->hijoIzquierdo == nullptr)
            return raizSubarbol;
        else
            return buscarHueco(raizSubarbol->hijoIzquierdo, elementoAInsertar);
    } else {
        if (raizSubarbol->hijoDerecho == nullptr)
            return raizSubarbol;
        else
            return buscarHueco(raizSubarbol->hijoDerecho, elementoAInsertar);
    }
}

Nodo* ABB::buscarRecursivo(Nodo* raizSubarbol, int elementoABuscar)
{
    if (raizSubarbol == nullptr) // caso base, no se encontró
        return nullptr;
    if (raizSubarbol->contenido == elementoABuscar) // caso base lo encuentra
        return raizSubarbol;

    if (raizSubarbol->contenido > elementoABuscar) // por la izquierda si es menor
        return buscarRecursivo(raizSubarbol->hijoIzquierdo, elementoABuscar);
    else // por la derecha si es mayor
        return buscarRecursivo(raizSubarbol->hijoDerecho, elementoABuscar);
}

Nodo* ABB::buscarMaximo(Nodo* raizSubarbol)
{
    if (raizSubarbol == nullptr)
        return raizSubarbol->padre;
    return buscarMaximo(raizSubarbol->hijoDerecho);
}

Nodo* ABB::buscarMinimo(Nodo* raizSubarbol)
{
    if (raizSubarbol == nullptr)
        return raizSubarbol->padre;
    return buscarMinimo(raizSubarbol->hijoIzquierdo);
}

int ABB::alturaNodo(Nodo* raizSubarbol)
{
    if (raizSubarbol == nullptr)
        return -1;

    int izq = alturaNodo(raizSubarbol->hijoIzquierdo);
    int der = alturaNodo(raizSubarbol->hijoDerecho);
    return std::max(izq, der) + 1;
}

void ABB::eliminarNodo(Nodo* raizSubarbol)
{
    if (raizSubarbol->hijoDerecho == nullptr && raizSubarbol->hijoIzquierdo == nullptr) // si es una hoja
    {
        if (raizSubarbol->padre == nullptr) // si es el root
            raiz = nullptr;
        else if (raizSubarbol->padre->hijoIzquierdo == raizSubarbol) // comprueba que hijo es para pasarlo a null
            raizSubarbol->padre->hijoIzquierdo = nullptr;
        else
            raizSubarbol->padre->hijoDerecho = nullptr;
        delete raizSubarbol;
        n--;
    } else if (raizSubarbol->hijoIzquierdo != nullptr && raizSubarbol->hijoDerecho == nullptr) {
        Nodo* max = buscarMaximo(raizSubarbol->hijoIzquierdo); // obtiene el mas grande
        raizSubarbol->contenido = max->contenido; // se cambian los contenidos para "moverlos"
        eliminarNodo(max); // ahora elimina el max
    } else if (raizSubarbol->hijoIzquierdo == nullptr && raizSubarbol->hijoDerecho != nullptr) {
        Nodo* min = buscarMinimo(raizSubarbol->hijoDerecho);
        raizSubarbol->contenido = min->contenido;
        eliminarNodo(min);
    } else if (raizSubarbol->hijoIzquierdo != nullptr && raizSubarbol->hijoDerecho != nullptr) {
        int altruraIzq = alturaNodo(raizSubarbol->hijoIzquierdo);
        int altruraDer = alturaNodo(raizSubarbol->hijoDerecho);

        if (altruraIzq > altruraDer) {
            Nodo* max = buscarMaximo(raizSubarbol->hijoIzquierdo);
            raizSubarbol->contenido = max->contenido;
            eliminarNodo(max);
        } else {
            Nodo* min = buscarMinimo(raizSubarbol->hijoDerecho);
            raizSubarbol->contenido = min->contenido;
            eliminarNodo(min);
        }
    }
}

bool ABB::esABB()
{
    return esSubABB(raiz);
}

bool ABB::esAVL()
{
    return esABB() && esSubAVL(raiz);
}

bool ABB::esSubABB(Nodo* raizSubarbol)
{
    bool cumple = true;
    if (raizSubarbol == nullptr) // caso base, llega al final
        return true;
    if (raizSubarbol->contenido > raizSubarbol->hijoDerecho->contenido && raizSubarbol->hijoDerecho != nullptr)
        cumple = false;
    if (raizSubarbol->contenido < raizSubarbol->hijoIzquierdo->contenido && raizSubarbol->hijoIzquierdo != nullptr)
        cumple = false;

    return esSubABB(raizSubarbol->hijoIzquierdo) && esSubABB(raizSubarbol->hijoDerecho) && cumple;
}

bool ABB::esSubAVL(Nodo* raizSubarbol)
{
    if (raizSubarbol == nullptr)
        return true;
    int Fe = (alturaNodo(raizSubarbol->hijoDerecho) - alturaNodo(raizSubarbol->hijoIzquierdo));
    if (abs(Fe) <= 1)
        return esSubAVL(raizSubarbol->hijoIzquierdo) && esSubAVL(raizSubarbol->hijoDerecho);
    else
        return false;
}

void ABB::imprimir()
{
    if (raiz == NULL)
        cout << "VACIO" << endl;
    else
        imprimirRecorrido(raiz);
}

void ABB::imprimirRecorrido(Nodo* raizSubarbol)
{
    cout << raizSubarbol->contenido << endl;
    if (raizSubarbol->hijoIzquierdo != NULL) {
        cout << "I";
        imprimirRecorrido(raizSubarbol->hijoIzquierdo);
        cout << endl;
    }
    if (raizSubarbol->hijoDerecho != NULL) {
        cout << "D";
        imprimirRecorrido(raizSubarbol->hijoDerecho);
        cout << endl;
    }
}

void ABB::leerArbol()
{
    raiz = leerSubarbol(NULL);
}

Nodo* ABB::leerSubarbol(Nodo* padre)
{
    int contenido;
    cin >> contenido;
    if (contenido >= 0) {
        Nodo* arbol = new Nodo;
        arbol->contenido = contenido;
        arbol->hijoIzquierdo = leerSubarbol(arbol);
        arbol->hijoDerecho = leerSubarbol(arbol);
        arbol->padre = padre;
        return arbol;
    } else {
        return NULL;
    }
}

ABB::~ABB()
{
    eliminarSubarbol(raiz);
    raiz = nullptr;
}

void ABB::eliminarSubarbol(Nodo*raizSubarbol){
    if(raizSubarbol!=nullptr){
        eliminarSubarbol(raizSubarbol->hijoIzquierdo);
        eliminarSubarbol(raizSubarbol->hijoDerecho);
        delete raizSubarbol;
        n--;
    }
}
