#pragma once

class ListaContigua {
    int* vector; // puntero a un array de entero

    int n; // numero de elementos almacenados

    int capacidad; // máximo número de elementos posible

    int incremento; // numero de posiciones que se incremete o decrementa

public:
    ListaContigua(int incremento);

    int getValor(int posicion);

    void setValor(int posicion, int nuevoValor);

    int getN();

    int getCapacidad();

    void insertar(int posicion, int nuevoValor);

    void eliminar(int posicion);

    void concatenar(ListaContigua* listaAConcatenar);

    int buscar(int elementoABuscar);

    ~ListaContigua();
};
