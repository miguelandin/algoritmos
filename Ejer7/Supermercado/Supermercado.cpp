#include "Supermercado.h"
#include <iostream>
#define assertdomjudge(x)                  \
    if (!(x)) {                            \
        std::cout << "ERROR" << std::endl; \
        exit(0);                           \
    }

Supermercado::Supermercado(int n) // T(n) = O(1), M(n) = O(n)
{
    assertdomjudge(n > 0); // por lo menos una caja

    n_cajas = n; // si inicializa el número de cajas a n
    cajas = new Cola[n]; // se reserva la memoria de las cajas
}

void Supermercado::nuevoUsuario(int n, int id) // T(n) = M(n) = O(1)
{
    assertdomjudge(n >= 0 && n < n_cajas); // n tiene que estar dentro de cajas

    cajas[n].encolar(id); // se encola en la caja n con su id
}

void Supermercado::cerrarCaja(int n) // T(n) = O(n), M(n) = O(1)
{
    assertdomjudge(n >= 0 && n < n_cajas); // n tiene que estar dentro de cajas

    int id, i = 0;

    while (!cajas[n].estaVacia()) { // mientras no esté vacía
        if (i == n_cajas) // si i llega al límite, vuelve a 0
            i = 0;

        if (i != n && !cajas[i].estaVacia()) { // no es la nuestra y está vacía
            id = cajas[n].desencolar(); // el primero deja la cola de la caja n
            cajas[i].encolar(id); // y se encola en la caja i
        }
        i++;
    }
}

int Supermercado::atenderUsuario(int n) // T(n) = M(n) = O(1)
{
    assertdomjudge(n >= 0 && n < n_cajas); // n tiene que estar dentro de cajas

    return cajas[n].desencolar();
}

bool Supermercado::cajaVacia(int n) // T(n) = M(n) = O(1)
{
    assertdomjudge(n >= 0 && n < n_cajas); // n tiene que estar dentro de cajas

    return cajas[n].estaVacia();
}
