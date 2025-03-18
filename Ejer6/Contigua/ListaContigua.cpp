#include "ListaContigua.h"
#include "assertdomjudge.h"
#include <cstdlib>
#include <cstring>

ListaContigua::ListaContigua(int incremento)
{ // T(n) = 1
    // M(n) = 1
    this->n = 0;
    this->capacidad = 0;
    this->vector = nullptr;
    this->incremento = incremento;
}

ListaContigua::~ListaContigua() // T(n) = 1 = O(1), M(n) = 1 = O(1)
{
    delete[] this->vector; // libera la memoria del vector
}

int ListaContigua::getValor(int pos) // T(n) = 1, M(n) = 1
{
    return this->vector[pos];
}

void ListaContigua::setValor(int pos, int nuevo) // T(n) = 1, M(n) = 1
{
    this->vector[pos] = nuevo;
}

int ListaContigua::getN() // T(n) = 1, M(n) = 1
{
    return this->n;
}

int ListaContigua::getCapacidad() // T(n) = 1, M(n) = 1
{
    return this->capacidad;
}

void ListaContigua::insertar(int pos, int nuevo)
{
    if (this->n == this->capacidad) // si no hay un hueco de más
    {
        this->vector = (int*)realloc(this->vector, sizeof(int) * (this->capacidad + this->incremento)); // se aumenta la memoria
        this->capacidad += this->incremento; // aumenta la capacidad
    }
    memmove(&vector[pos + 1], &vector[pos], sizeof(int) * (n - pos)); // se mueve a la derecha desde pos + 1
    setValor(pos, nuevo); // se introduce el nuevo valor en el hueco creado
    this->n++; // se añade una posición
}

void ListaContigua::eliminar(int pos)
{
    if (this->n < this->capacidad - this->incremento) { // si hay demasiada memoria sin usar se libera
        this->vector = (int*)realloc(this->vector, sizeof(int) * (this->capacidad - this->incremento)); // se libera memoria
        this->capacidad -= this->incremento; // se reduce la capcidad
    }
    memmove(&vector[pos], &vector[pos + 1], sizeof(int) * (n - pos)); // se superpone los valores desde pos por el siguiente
    this->n--; // se pierde un posición
}

void ListaContigua::concatenar(ListaContigua* lista)
{
    for (int i = 0; i < lista->n; i++) {
        insertar(this->n, lista->vector[i]); // inserta los valores de lista al final del vector
    }
}

int ListaContigua::buscar(int elemento)
{
    int res = -1, i = 0;

    while (res == -1 && i < n) {
        if (this->vector[i] == elemento)
            res = i;
        else
            i++;
    }
    return res;
}
