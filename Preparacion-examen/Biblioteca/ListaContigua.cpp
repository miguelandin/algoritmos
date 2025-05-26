#include "ListaContigua.h"
#include <cstdlib>
#include <cstring>

ListaContigua::ListaContigua(int incremento)
{
    this->incremento = incremento;
    capacidad = n = 0;
    vector = nullptr;
}

void ListaContigua::insertar(int pos, int val)
{
    if (n == capacidad) {
        vector = (int*)realloc(vector, sizeof(int) * (capacidad + incremento));
        capacidad += incremento;
    }
    memmove(&vector[pos + 1], &vector[pos], sizeof(int) * (n - pos));
    vector[pos] = val;
    n++;
}

void ListaContigua::eliminar(int pos)
{
    if (capacidad - incremento > n) { // si sobra el espacio
        vector = (int*)realloc(vector, sizeof(int) * (capacidad - incremento)); // lo hace más pequeños
        capacidad -= incremento;
    }
    memmove(&vector[pos], &vector[pos + 1], sizeof(int) * (n - pos));
    n--;
}

void ListaContigua::modificar(int pos, int val)
{
    vector[pos] = val;
}

bool ListaContigua::estaLlena()
{
    return n == capacidad;
}

int ListaContigua::elemento(int pos)
{
    return vector[pos];
}

void ListaContigua::imprimir()
{
    for (int i = 0; i < n; i++)
        std::cout << vector[i] << " ";
    std::cout << std::endl;
}

ListaContigua::~ListaContigua()
{
    delete[] vector;
    n = capacidad = incremento = 0;
    vector = nullptr;
}
