#include "ColaPrioridad.h"
#include "assertdomjudge.h"

ColaPrioridad::ColaPrioridad() { } // T(n) = M(n) = O(1)

void ColaPrioridad::encolar(int num) // T(n) = O(log n), M(n) = O(1)

{
    vector.insertarAlFinal(num); // insertar al final
    int pos = vector.getN() - 1; // posición del nuevo elemento

    /* mientras no sea la raíz y sea menor que su padre */
    while (pos > 0 && vector.getValor(pos) < vector.getValor((pos - 1) / 2)) {
        /* intercambiar con el padre */
        int padre = (pos - 1) / 2;
        int temp = vector.getValor(padre);
        vector.setValor(padre, vector.getValor(pos));
        vector.setValor(pos, temp);

        pos = padre; // Moverse a la posición del padre
    }
}

int ColaPrioridad::desencolar() // T(n) = O(log n), M(n) = O(1)
{
    assertdomjudge(!estaVacia());

    int valorRoot = vector.getValor(0); // guardar el valor del root

    if (vector.getN() == 1) { // caso de un solo elemento
        vector.eliminarAlFinal();
        return valorRoot;
    }

    /* reemplazar el root con el último elemento */
    int ultimo = vector.getValor(vector.getN() - 1);
    vector.setValor(0, ultimo);
    vector.eliminarAlFinal();

    /* reestructurar si aún hay elementos */
    if (!estaVacia()) {
        reestructurar();
    }

    return valorRoot;
}

bool ColaPrioridad::estaVacia() // T(n) = M(n) = O(1)
{
    return vector.getN() == 0;
}

void ColaPrioridad::reestructurar() // T(n) = O(log n), M(n) = O(1)
{
    int pos = 0;
    int n = vector.getN();

    while (true) {
        int hijoIzq = 2 * pos + 1;
        int hijoDer = 2 * pos + 2;
        int menor = pos;

        /* encontrar el menor entre padre e hijos */
        if (hijoIzq < n && vector.getValor(hijoIzq) < vector.getValor(menor)) {
            menor = hijoIzq;
        }
        if (hijoDer < n && vector.getValor(hijoDer) < vector.getValor(menor)) {
            menor = hijoDer;
        }

        /* si el padre es el menor, termina */
        if (menor == pos) {
            break;
        }

        /* intercambiar con el hijo menor */
        int temp = vector.getValor(pos);
        vector.setValor(pos, vector.getValor(menor));
        vector.setValor(menor, temp);

        pos = menor; // Continuar con la posición del hijo
    }
}
