#include "Agenda.h"
#include "assertdomjudge.h"

Agenda::Agenda(int capacidad) // T(n) = M(n) = O(1)
{
    assertdomjudge(capacidad > 0); // capacidad tiene que ser natural

    this->capacidad = capacidad; // se guarda la capacidad de la tabla
    /* se reserva memoria de los atributos */
    nombres = new string[capacidad];
    telefonos = new long[capacidad];
    ocupada = new bool[capacidad](); // los inicializa a false (vacio)
}

Agenda::~Agenda() // T(n) = M(n) = O(1)
{
    delete[] nombres;
    delete[] telefonos;
    delete[] ocupada;
}

int Agenda::obtenerPosicion(long clave) // T(n) = M(n) = O(1)
{
    return clave % capacidad;
}

bool Agenda::existeContacto(long telefono) // T(n) = M(n) = O(1)
{
    int pos = obtenerPosicion(telefono); // obtiene la pos de la clave
    return (ocupada[pos] && telefonos[pos] == telefono); // está y misma clave
}

string Agenda::getContacto(long telefono) // T(n) = M(n) = O(1)
{
    assertdomjudge(existeContacto(telefono)); // comprueba que exista

    return nombres[obtenerPosicion(telefono)]; // se obtiene el contacto
}

void Agenda::introducirContacto(long telefono, string contacto) // T(n)=M(n)=O(1)
{
    int pos = obtenerPosicion(telefono); // obtenemos su posición

    assertdomjudge(ocupada[pos] == false); // comprueba que haya hueco

    telefonos[pos] = telefono; // ponemos el telefono
    nombres[pos] = contacto; // ponemos el nombre
    ocupada[pos] = true; // ponemos ocupada
}

void Agenda::eliminarContacto(long telefono) // T(n) = M(n) = O(1)
{
    assertdomjudge(existeContacto(telefono)); // comprueba que exista

    ocupada[obtenerPosicion(telefono)] = false; // pasa a estar vacía
}
