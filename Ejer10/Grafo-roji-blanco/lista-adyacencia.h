#include "Nodo.h"

class ListaAdyacencia {
    Nodo* lista; // principio de la lista
    int n; // numero de aristas

public:
    ListaAdyacencia();
    ~ListaAdyacencia();

    void insertar(int valor);
    Nodo* getLista() const { return lista; }
    int getN() const { return n; }
};
