#include "Agenda.h"
#include "assertdomjudge.h"

Agenda::Agenda(int capacidad)
{
    assertdomjudge(capacidad > 0); // capacidad tiene que ser natural
    this->capacidad = capacidad; // se guarda la capacidad de la tabla
    n = 0; // número de listas a cero
    tabla = new ListaEnlazada[capacidad]; // se reserva memoria para la tabla
}

int Agenda::obtenerPosicion(long clave) // T(n) = M(n) = O(1)
{
    return clave % capacidad; // método hashing
}

bool Agenda::existeContacto(long telefono) // T(n) = O(n), M(n) = O(1)
{
    Contacto buscar; // creamos la variable contacto con el telefono para
    buscar.telefono = telefono; // poder usar la función buscar

    /* buscamos en la lista de la posicion que dé la función hash */
    if (tabla[obtenerPosicion(telefono)].buscar(buscar) == -1)
        return false;
    else
        return true;
}

string Agenda::getContacto(long telefono) // T(n) = O(n), M(n) = O(1)
{
    Contacto buscar; // creamos la variable contacto con el telefono para
    buscar.telefono = telefono; // poder usar la función buscar

    int pos_tabla = obtenerPosicion(telefono); // obtenemos posicion de tabla
    int pos_lista = tabla[pos_tabla].buscar(buscar); // obtenemos pos de lista

    assertdomjudge(pos_lista != -1); // comprueba que exista

    return tabla[pos_tabla].getValor(pos_lista).nombre; // devuelve el nombre
}

void Agenda::introducirContacto(long telefono, string nuevo) // T(n) = O(n)
{ // M(n) = O(1)
    /* Creamos el contacto */
    Contacto nuevoC;
    nuevoC.nombre = nuevo;
    nuevoC.telefono = telefono;

    int pos = obtenerPosicion(telefono); // obtenemos posicion de tabla
    tabla[pos].insertar(0, nuevoC); // inserta al principio de la lista
}

void Agenda::eliminarContacto(long telefono) // T(n) = O(n), M(n) = O(1)
{
    Contacto buscar; // creamos la variable contacto con el telefono para
    buscar.telefono = telefono; // poder usar la función buscar

    int pos_tabla = obtenerPosicion(telefono); // obtenemos posicion de tabla
    int pos_lista = tabla[pos_tabla].buscar(buscar); // obtenemos pos de lista

    assertdomjudge(pos_lista != -1); // comprueba que exista

    tabla[pos_tabla].eliminar(pos_lista); // elimina el elemento
}

Agenda::~Agenda()
{
    delete[] tabla;
}
