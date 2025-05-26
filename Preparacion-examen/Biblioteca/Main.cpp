#include "ListaContigua.h"

int main()
{
    ListaContigua lista(2);
    for (int i = 0; i < 10; i++)
        lista.insertar(i, i);
    lista.imprimir();

    lista.eliminar(3);
    lista.imprimir();

    lista.eliminar(5);
    lista.imprimir();

    lista.insertar(7, 12);
    lista.imprimir();

    lista.insertar(9, 20);
    lista.imprimir();

    if (lista.estaLlena())
        std::cout << "Llena" << std::endl;
}
