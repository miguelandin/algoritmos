#include "Agenda.h"
#include "assertdomjudge.h"

Agenda::Agenda(int capacidad) // T(n) = M(n) = O(n)
{
    assertdomjudge(capacidad > 0); // capacidad tiene que ser natural

    this->capacidad = capacidad; // se guarda la capacidad de la tabla
    n = 0; // numero actual de elementos a 0
    /* se reserva memoria de los atributos */
    nombres = new string[capacidad];
    telefonos = new long[capacidad];
    borradas = new bool[capacidad](); // los inicializa a false (no eliminado)

    vacias = new bool[capacidad]; // los inicializa a true (vacio)
    for (int i = 0; i < capacidad; i++)
        vacias[i] = true;
}

Agenda::~Agenda() // T(n) = M(n) = O(1)
{
    delete[] nombres;
    delete[] telefonos;
    delete[] vacias;
}

int Agenda::obtenerPosicion(long clave) // T(n) = M(n) = O(1)
{
    return clave % capacidad;
}

int Agenda::buscarContacto(long telefono) // T(n) = O(n), M(n) = 1
{
    int res = -1; // -1 por defecto por si no se encuentra
    int pos = obtenerPosicion(telefono); // obtenemos la posicion que debería
    bool termina = false;

    while (!termina) {
        if (!vacias[pos] && telefonos[pos] == telefono) { // si lo encuentra
            res = pos; // se guarda el resultado
            termina = true; // termina el bucle
        } else if (vacias[pos] && !borradas[pos] || pos == capacidad) // el limite
            termina = true; // no se ha encontrado, termina el bucle
        else
            pos++;
    }

    return res;
}

int Agenda::buscarHueco(long telefono) // T(n) = O(n), M(n) = O(1)
{
    int res = -1;
    int pos = obtenerPosicion(telefono);
    bool encontrado = false;

    while (!encontrado && pos < capacidad) { // mientras no se encuentre o pase
        if (vacias[pos]) { // si no está ocupada se guarda el resultado
            res = pos;
            encontrado = true;
        } else
            pos++;
    }

    return res;
}

bool Agenda::isLlena() // T(n) = M(n) = O(1)
{
    return n == capacidad;
}

bool Agenda::existeContacto(long telefono)
{
    if (buscarContacto(telefono) == -1) // si es -1 es que no se encontró
        return false;
    else // en otro caso es que se encontró el contacto -> existe
        return true;
}

string Agenda::getContacto(long telefono) // T(n) = O(n), M(n) = O(1)
{
    int pos = buscarContacto(telefono); // se obtiene la posicion del contacto
    assertdomjudge(pos != -1); // comprueba que exista

    return nombres[pos]; // devuelve el nombre
}

void Agenda::introducirContacto(long telefono, string contacto) // T(n) = O(n), M(n) = O(1)
{
    int pos = buscarHueco(telefono); // se obtiene la posicion de un hueco
    assertdomjudge(pos != -1); // comprueba que se encontró

    telefonos[pos] = telefono; // ponemos el telefono
    nombres[pos] = contacto; // ponemos el nombre
    vacias[pos] = false; // ponemos ocupada

    n++; // aumenta el numero de elementos
}

void Agenda::eliminarContacto(long telefono) // T(n) = O(n), M(n) = O(1)
{
    int pos = buscarContacto(telefono); // busca la posicion del contacto

    assertdomjudge(pos != -1); // comprueba que se encontró

    vacias[pos] = true; // pasa a estar vacio
    borradas[pos] = true; // pasa a estar marcada como eliminada

    n--; // disminuye el numero de elementos
}
