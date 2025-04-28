#include <iostream>

int calculaMax(int* pilas, int n_pilas, int v_min);
void eliminar(int* pilas, int& n_pilas, int pos); // Cambia n_pilas a referencia

int main() {
    int casos = 0; // número de casos de prueba
    std::cin >> casos; // inserta el número de casos

    for (int i = 0; i < casos; i++) {
        int n_pilas; // número de pilas
        std::cin >> n_pilas; // inserta el número de pilas

        int v_min; // voltaje mínimo para que funcione un coche
        std::cin >> v_min;

        int* pilas = new int[n_pilas]; // array que contiene los voltajes de cada pila

        for (int j = 0; j < n_pilas; j++) { // Cambia 'i' por 'j'
            int voltaje; // voltaje de cada pila
            std::cin >> voltaje;
            pilas[j] = voltaje; // se inserta el voltaje en el array
        }

        std::cout << calculaMax(pilas, n_pilas, v_min) << std::endl; // muestra por consola el máximo de coches posible
        delete[] pilas; // libera memoria
    }
    return 0;
}

int calculaMax(int* pilas, int n_pilas, int v_min) {
    int coches = 0; // número de coches cargables

    for (int i = 0; i < n_pilas; i++) {
        for (int j = 0; j < n_pilas; j++) {
            if (i == j) continue; // saltar si son la misma pila

            int v_acumulado = pilas[i] + pilas[j]; // suma de voltajes de las dos pilas

            if (v_acumulado >= v_min) {
                coches++; // se puede cargar un coche
                eliminar(pilas, n_pilas, i); // elimina la pila i
                eliminar(pilas, n_pilas, j > i ? j - 1 : j); // elimina la pila j (ajusta el índice)
                break; // salir del bucle interno, ya que se ha cargado un coche
            }
        }
    }

    return coches;
}

void eliminar(int* pilas, int& n_pilas, int pos) {
    for (int i = pos; i < n_pilas - 1; i++) {
        pilas[i] = pilas[i + 1]; // mueve a la izquierda
    }
    n_pilas--; // decrementa el número de pilas
}

