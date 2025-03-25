#include "Cola.h"

Cola::Cola() // T(n) = M(n) = O(1)
{
    principio = final = nullptr; // se inicializa a null
}

void Cola::encolar(int num) // T(n) = M(n) = O(1)
{
    Nodo* nuevo = new Nodo(num); // crea un nuevo cliente
    if (estaVacia()) {
        principio = nuevo; // lo pone al principio de la cola
        final = principio; // el princpio apunta al final porque solo hay 1
    } else
        final->siguiente = nuevo; // lo pone como el nuevo último elemento

    final = nuevo; // el final pasa a ser el nuevo elemento
}

int Cola::desencolar() // T(n) = M(n) = O(1)
{
    int res = principio->valor; // se obtiene su número
    Nodo* eliminar = principio; // se apunta al primero de la cola
    principio = principio->siguiente; // el siguiente pasa a ser el primero

    if (estaVacia())
        final = nullptr; // si está vacía el final pasa a apuntar a null

    delete eliminar;
    return res;
}

bool Cola::estaVacia() // T(n) = M(n) = O(1)
{
    return (principio == nullptr); // si principio apunta a null -> está vacía
}
