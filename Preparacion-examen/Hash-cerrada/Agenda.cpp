#include "Agenda.h"

Agenda::Agenda(int capacidad)
{
    this->capacidad = capacidad;
    n = 0;
    telefonos = new long[capacidad];
    nombres = new string[capacidad];
    vacias = new bool[capacidad];
    borradas = new bool[capacidad];

    for (int i = 0; i < capacidad; i++) {
        vacias[i] = true;
        borradas[i] = false;
    }
}

int Agenda::obtenerPosicion(long telefono)
{
    return telefono % capacidad;
}

int Agenda::buscarContacto(long telefono)
{
    int pos = obtenerPosicion(telefono); // obtiene la pos hash
    int res = -1; // se inicializa el resultado a -1 por si noo
    bool encontrado = false;

    while (!encontrado) {
        if (!vacias[pos] && telefonos[pos] == telefono) {
            res = pos;
            encontrado = true;
        }
        if (vacias[pos] && !borradas[pos] || pos == capacidad)
            encontrado = true;
        pos++;
    }

    return res;
}

int Agenda::buscarHueco(long telefono)
{
    int pos = obtenerPosicion(telefono);
    int res = -1;
    bool encontrado = false;

    while (!encontrado && pos != capacidad) {
        if (vacias[pos]) {
            res = pos;
            encontrado = true;
        } else
            pos++;
    }
    return res;
}

bool Agenda::isLlena()
{
    return capacidad == n;
}

bool Agenda::existeContacto(long telefono)
{
    return buscarContacto(telefono) != -1;
}

string Agenda::getContacto(long telefono)
{
    int pos = buscarContacto(telefono);
    if (pos == -1)
        return "No encontrado";
    else
        return nombres[pos];
}

void Agenda::introducirContacto(long telefono, string contacto)
{
    int pos = buscarHueco(telefono);
    if (pos != -1) {
        telefonos[pos] = telefono;
        nombres[pos] = contacto;
        vacias[pos] = false;
        n++;
    }
}

void Agenda::eliminarContacto(long telefono)
{
    int pos = buscarContacto(telefono);
    if (pos != -1) {
        borradas[pos] = true;
        vacias[pos] = true;
        n--;
    }
}
void Agenda::imprimir()
{
    for (int i = 0; i < capacidad; i++) {
        cout << nombres[i] << " " << telefonos[i] << " " << vacias[i] << " " << borradas[i] << endl;
    }
}

Agenda::~Agenda(){
    delete[] nombres;
    delete[] telefonos;
    delete[] vacias;
    delete[] borradas;
    n = 0;
}
