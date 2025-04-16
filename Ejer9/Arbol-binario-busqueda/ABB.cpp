#include "ABB.h"
#include "Nodo.h"
#include "assertdomjudge.h"
#include "iostream"

using namespace std;

/* métodos públicos */
ABB::ABB() // crea un árbol vacío
{ // T(n) = M(n) = O(1)
    n = 0;
    raiz = nullptr;
}

ABB::~ABB() // destructor
{ // T(n) = O(n), M(n) = O(1)
    eliminarSubarbol(raiz);
    raiz = nullptr;
}

void ABB::insertar(int nuevo) // inserta un nuevo elemento como hoja
{ // T(n) = O(log(n)) ó O(n), M(n) = O(1)
    Nodo* nuevoNodo = new Nodo(); // se crea el nuevo nodo

    nuevoNodo->contenido = nuevo; // inserta el contenido
    nuevoNodo->hijoIzquierdo = nullptr; // establece los hijos a null
    nuevoNodo->hijoDerecho = nullptr;

    if (raiz == nullptr) { // en caso de ser el primer elemento
        nuevoNodo->padre = nullptr; // el padre no existe
        raiz = nuevoNodo; // pasa a ser el root del árbol
    } else {
        Nodo* padre = buscarHueco(raiz, nuevo); // busca el padre más adecuado
        nuevoNodo->padre = padre; // establece el padre del nuevoNodo
        if (nuevo < padre->contenido) // comprobar el lado
            padre->hijoIzquierdo = nuevoNodo; // si es menor, hijo izquierda
        else
            padre->hijoDerecho = nuevoNodo; // si es mayor, hijo derecha
    }

    n++; // aumenta el número de nodos
}

Nodo* ABB::buscar(int encontrar) // busca un elemento en el ABB que coincida
{ // T(n) = O(log(n)) ó O(n), M(n) = O(1)
    return buscarRecursivo(raiz, encontrar); // busca recursivamente
}

void ABB::eliminar(int elementoAEliminar) // eliminar el nodo que se indique
{ // T(n) = O(log(n)) ó O(n), M(n) = O(1)
    Nodo* eliminar = buscar(elementoAEliminar);

    if (eliminar != nullptr) // si existe el nodo
        eliminarNodo(eliminar); // eliminar el nodo recursivamente
}

bool ABB::esABB() // comprueba que el árbol binario de busqueda sea correcto
{ // T(n) = O(n²), M(n) = O(1)
    return esSubABB(raiz);
}

bool ABB::esAVL() // Comprueba que sea un AVL
{ // T(n) = O(n²), M(n) = O(1)
    if (!esABB()) // primero comprueba que sea ABB
        return false;

    return esSubAVL(raiz);
}

/* métodos privados */
Nodo* ABB::buscarRecursivo(Nodo* raizSubarbol, int elementoABuscar)
{ // T(n) = O(log(n)) ó O(n), M(n) = O(1)
    if (raizSubarbol == nullptr) // en caso de no encontrarlo
        return nullptr;
    if (raizSubarbol->contenido == elementoABuscar) // caso base (lo encuentra)
        return raizSubarbol;
    if (elementoABuscar < raizSubarbol->contenido) // por la derecha
        return buscarRecursivo(raizSubarbol->hijoIzquierdo, elementoABuscar);
    else
        return buscarRecursivo(raizSubarbol->hijoDerecho, elementoABuscar);
}

Nodo* ABB::buscarHueco(Nodo* raizSubarbol, int elementoAInsertar)
{ // T(n) = O(log(n)) ó O(n), M(n) = O(1)
    if (elementoAInsertar < raizSubarbol->contenido) { // por la izquierda
        if (raizSubarbol->hijoIzquierdo == nullptr) // si está libre
            return raizSubarbol; // devuelve el padre del hueco encontrado
        else
            return buscarHueco(raizSubarbol->hijoIzquierdo, elementoAInsertar);
    } else { // por la izquierda
        if (raizSubarbol->hijoDerecho == nullptr) // si está libre
            return raizSubarbol; // devuelve el padre del hueco encontrado
        else
            return buscarHueco(raizSubarbol->hijoDerecho, elementoAInsertar);
    }
}

Nodo* ABB::buscarMaximo(Nodo* raizSubarbol) // duevelve el nodo más grande
{ // T(n) = O(log(n)) ó O(n), M(n) = O(1)
    if (raizSubarbol->hijoDerecho == NULL) // caso base, llega a una hoja
        return raizSubarbol;
    else
        return buscarMaximo(raizSubarbol->hijoDerecho); // va por la derecha
}

Nodo* ABB::buscarMinimo(Nodo* raizSubarbol) // devuelve el nodo más pequeño
{ // T(n) = O(log(n)) ó O(n), M(n) = O(1)
    if (raizSubarbol->hijoIzquierdo == NULL) // caso base, llega a una hoja
        return raizSubarbol;
    else
        return buscarMinimo(raizSubarbol->hijoIzquierdo); // por la izquierda
}

int ABB::alturaNodo(Nodo* raizSubarbol) // calcula la altura del árbol
{ // T(n) = O(n), M(n) = O(1)
    if (raizSubarbol == nullptr) // si el árbol es vacío, devuelve -1
        return -1; // caso base

    /* se llama por la izquierda y derecha */
    int alturaIzquierda = alturaNodo(raizSubarbol->hijoIzquierdo);
    int alturaDerecha = alturaNodo(raizSubarbol->hijoDerecho);

    /* se obtiene el que tenga más altura y se suma un nivel mas (+1) */
    return std::max(alturaIzquierda, alturaDerecha) + 1;
}

void ABB::eliminarNodo(Nodo* eliminar) // elimina recursivamente el nodo
{ // T(n) = O(log(n)) ó O(n), M(n) = O(1)
    /* Caso base: Es nodo hoja */
    if (eliminar->hijoIzquierdo == NULL && eliminar->hijoDerecho == NULL) {
        if (eliminar->padre == nullptr) // si es el root
            raiz = nullptr;
        else if (eliminar->padre->hijoIzquierdo == eliminar) // hijo izquierdo
            eliminar->padre->hijoIzquierdo = nullptr;
        else // si es hijo derecho
            eliminar->padre->hijoDerecho = nullptr;

        delete eliminar; // libera el nodo que queremos eliminar
        n--; // disminuye el total de nodos
    }
    /* Caso 2: Tiene solo hijo izquierdo */
    else if (eliminar->hijoIzquierdo != NULL && eliminar->hijoDerecho == NULL) {
        Nodo* maximo = buscarMaximo(eliminar->hijoIzquierdo);
        eliminar->contenido = maximo->contenido; // intercambio de contenidos
        eliminarNodo(maximo); // pasa a eliminar el nodo intercambiado
    }
    /* Caso 3: Tiene solo hijo derecho */
    else if (eliminar->hijoIzquierdo == NULL && eliminar->hijoDerecho != NULL) {
        Nodo* minimo = buscarMinimo(eliminar->hijoDerecho);
        eliminar->contenido = minimo->contenido; // intercambio de contenidos
        eliminarNodo(minimo); // pasa a eliminar el nodo intercambiado
    }
    /* Caso 4: Tiene ambos hijos */
    else {
        int alturaIzq = alturaNodo(eliminar->hijoIzquierdo);
        int alturaDer = alturaNodo(eliminar->hijoDerecho);

        if (alturaIzq >= alturaDer) { // se decide el sentido según la altura
            Nodo* maximo = buscarMaximo(eliminar->hijoIzquierdo); // izquierda
            eliminar->contenido = maximo->contenido;
            eliminarNodo(maximo);
        } else {
            Nodo* minimo = buscarMinimo(eliminar->hijoDerecho); // derecha
            eliminar->contenido = minimo->contenido;
            eliminarNodo(minimo);
        }
    }
}

bool ABB::esSubABB(Nodo* raizSubarbol)
{ // T(n²), M(n) = O(n)
    if (raizSubarbol == nullptr) // caso base, llega hasta al final
        return true;

    bool respuesta = true; // se inicializa como verdadero la respuesta

    /* Comprueba que se cumpla la condición del ABB */
    if (raizSubarbol->hijoIzquierdo != nullptr) // si existe
        respuesta = respuesta && (raizSubarbol->hijoIzquierdo->contenido < raizSubarbol->contenido) && (buscarMaximo(raizSubarbol->hijoIzquierdo)->contenido < raizSubarbol->contenido);

    if (raizSubarbol->hijoDerecho != nullptr) // si existe
        respuesta = respuesta && (raizSubarbol->hijoDerecho->contenido > raizSubarbol->contenido) && (buscarMinimo(raizSubarbol->hijoDerecho)->contenido > raizSubarbol->contenido);

    /* devuelve la repusta e itera con los hijos */
    return respuesta && esSubABB(raizSubarbol->hijoIzquierdo) && esSubABB(raizSubarbol->hijoDerecho);
}

bool ABB::esSubAVL(Nodo* raizSubarbol)
{ // T(n²), M(n) = O(n)
    if (raizSubarbol == nullptr) // caso base, llega al final
        return true;

    int Fe = alturaNodo(raizSubarbol->hijoDerecho) - alturaNodo(raizSubarbol->hijoIzquierdo); // calculamos el factor de equilibrio para saber si es AVL

    return (abs(Fe) <= 1) && esSubAVL(raizSubarbol->hijoIzquierdo) && esSubAVL(raizSubarbol->hijoDerecho);
}

void ABB::eliminarSubarbol(Nodo* raizSubarbol) // elimina todos los subárboles
{ // T(n) = O(n), M(n) = O(1)
    if (raizSubarbol != NULL) {
        eliminarSubarbol(raizSubarbol->hijoIzquierdo);
        eliminarSubarbol(raizSubarbol->hijoDerecho);
        delete raizSubarbol;
        n--; // reduce el número de elementos
    }
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
