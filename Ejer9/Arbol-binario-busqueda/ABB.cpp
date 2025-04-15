#include "ABB.h"
#include "assertdomjudge.h"
#include "iostream"

using namespace std;

/* métodos públicos */
ABB::ABB() // crea un árbol vacío
{ // T(n) = M(n) = O(n)
    n = 0;
    raiz = nullptr;
}

ABB::~ABB() // destructor
{
    delete raiz; // libera la memoria ocupada por el struct
    n = 0; // el número de nodos pasa a 0
    raiz = nullptr; // el puntero pasa a apuntar a NULL
}

void ABB::insertar(int nuevo) // inserta un nuevo elemento como hoja
{ // T(n) = O(log(n)) ó O(n), M(n) = O(1)
    Nodo* elemento = new Nodo; // se crea el nuevo nodo

    elemento->contenido = nuevo; // se inserta su contenido
    elemento->padre = buscarHueco(raiz, nuevo); // se inserta su padre

    if(elemento->padre->contenido >= nuevo) // se inserta a su padre el hijo
        elemento->padre->hijoIzquierdo = elemento;
    else
        elemento->padre->hijoDerecho = elemento;
}

Nodo* ABB::buscar(int encontrar) // busca un elemento en el ABB que coincida
{ // T(n) = O(log(n)) ó O(n), M(n) = O(1)
    return buscarRecursivo(raiz, encontrar); // busca recursivamente
}

/* métodos privados */
Nodo* ABB::buscarRecursivo(Nodo* raizSubarbol, int elementoABuscar)
{ // T(n) = O(log(n)) ó O(n), M(n) = O(1)
    if (raizSubarbol->contenido == elementoABuscar) // caso base
        return raizSubarbol;

    if (raizSubarbol->contenido > elementoABuscar) // por la derecha
        return buscarRecursivo(raizSubarbol->hijoDerecho, elementoABuscar);

    else if (raizSubarbol->contenido < elementoABuscar) // por la izquierda
        return buscarRecursivo(raizSubarbol->hijoIzquierdo, elementoABuscar);

    return nullptr; // si falla la búsqueda, devuelve null
}

Nodo* ABB::buscarHueco(Nodo* raizSubarbol, int ins) // busca para insertar
{ // T(n) = O(log(n)) ó O(n), M(n) = O(1)
    /* Caso base, se encunetra el hueco para insertar "ins" como una hoja */
    if (raizSubarbol->hijoIzquierdo == NULL && raizSubarbol->contenido >= ins)
        return raizSubarbol;
    if (raizSubarbol->hijoDerecho == NULL && raizSubarbol->contenido < ins)
        return raizSubarbol;

    /* Si no, se calcula la diferencia entre los nodos y el elemento ins */
    int valorIzq = raizSubarbol->hijoIzquierdo->contenido - ins;
    if (valorIzq < 0) // valor absoluto
        valorIzq *= -1;

    int valorDer = raizSubarbol->hijoDerecho->contenido - ins;
    if (valorDer < 0) // valor absoluto
        valorDer *= -1;

    /* Se comprueba que diferencia es menor para saber cual más se acerca */
    if (valorIzq < valorDer)
        buscarHueco(raizSubarbol->hijoIzquierdo, ins); // busca por izquierda
    else if (valorDer < valorIzq)
        buscarHueco(raizSubarbol->hijoDerecho, ins); // busca por derecha

    return nullptr; // en caso de que falle el algoritmo, devuelve NULL
}
/* plantilla */
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
