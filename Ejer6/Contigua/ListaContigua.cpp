#include "ListaContigua.h"
#include <cstdlib>
#include <cstring>
#include<iostream>
#include<stdlib.h>
#define assertdomjudge(x) if(!(x)){std::cout<<"ERROR"<<std::endl;exit(0);}

ListaContigua::ListaContigua(int incremento)
{ // T(n) = 1
    // M(n) = 1
    this->n = 0;
    this->incremento = incremento;
    this->capacidad = this->incremento;
    this->vector = new int[this->capacidad];
}

ListaContigua::~ListaContigua() // T(n) = 1, M(n) = 1
{
    delete[] this->vector; // libera la memoria del vector
}

int ListaContigua::getValor(int pos) // T(n) = 1, M(n) = 1
{
    assertdomjudge(pos >= 0 && pos < this->n);
    return this->vector[pos];
}

void ListaContigua::setValor(int pos, int nuevo) // T(n) = 1, M(n) = 1
{
    assertdomjudge(pos >= 0 && pos < this->n)
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
{ // T(n) = n + n + 1 = O(n)
    // M(n) = n + n + n + 1 = O(n)
    assertdomjudge(pos >= 0 && pos <= this->n);
    if (this->n == this->capacidad) // si no hay un hueco de más
    {
        this->vector = (int*)realloc(this->vector, sizeof(int) * (this->capacidad + this->incremento)); // se aumenta la memoria
        this->capacidad += this->incremento; // aumenta la capacidad
    }
    memmove(&vector[pos + 1], &vector[pos], sizeof(int) * (n - pos)); // se mueve a la derecha desde pos + 1
    this->vector[pos] = nuevo; // se introduce el nuevo valor en el hueco creado
    this->n++; // se añade una posición
}

void ListaContigua::eliminar(int pos)
{ // T(n) = n + 1 = O(n)
    // M(n) = n + 1 = O(n)
    assertdomjudge(pos >= 0 && pos < this->n);
    if (this->n < this->capacidad - this->incremento) { // si hay demasiada memoria sin usar se libera
        this->vector = (int*)realloc(this->vector, sizeof(int) * (this->capacidad - this->incremento)); // se libera memoria
        this->capacidad -= this->incremento; // se reduce la capcidad
    }
    memmove(&vector[pos], &vector[pos + 1], sizeof(int) * (n - pos)); // se superpone los valores desde pos por el siguiente
    this->n--; // se pierde un posición
}

void ListaContigua::concatenar(ListaContigua* lista)
{ // T(n) = n + 1
    // M(n) = 1
    assertdomjudge(lista != nullptr);
    for (int i = 0; i < lista->n; i++) {
        insertar(this->n, lista->vector[i]); // inserta los valores de lista al final del vector
    }
}

int ListaContigua::buscar(int elemento)
{ // T(n) = n
    // M(n) = 1
    int res = -1, i = 0;

    while (res == -1 && i < n) {
        if (this->vector[i] == elemento)
            res = i;
        else
            i++;
    }
    return res;
}
