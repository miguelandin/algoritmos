#include "Supermercado.h"
#include "assertdomjudge.h"

Supermercado::Supermercado(int n)
{
    assertdomjudge(n > 0); // por lo menos una caja

    n_cajas = n; // se establece el número de cajas
    cajas = new ColaPrioridad[n_cajas]; // reserva memoria para las cajas
}

void Supermercado::nuevoUsuario(int n, int id)
{
    assertdomjudge(n >= 0 && n < n_cajas); // n dentro de las cajas

    cajas[n].encolar(id); // encola en la caja n el id de el usuario
}

void Supermercado::cerrarCaja(int n)
{
    assertdomjudge(n >= 0 && n < n_cajas); // n dentro de las cajas

    int id, i = 0;

    while (!cajas[n].estaVacia()) { // mientras no esté vacía la caja
        if (i == n_cajas) // si i llega al límite, vuelve a 0
            i = 0;

        if (i != n && !cajas[i].estaVacia()) { // no es la nuestra y está vacía
            id = cajas[n].desencolar(); // el primero deja la cola de la caja n
            cajas[i].encolar(id); // y se encola en la caja i
        }
        i++;
    }
}

int Supermercado::atenderUsuario(int n)
{
    assertdomjudge(n >= 0 && n < n_cajas); // n dentro de las cajas

    return cajas[n].desencolar();
}

bool Supermercado::cajaVacia(int n)
{
    assertdomjudge(n>=0&&n<n_cajas);// n dentro de las cajas

    return cajas[n].estaVacia();
}
