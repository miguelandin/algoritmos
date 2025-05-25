#include "Nodo.h"

class Circulo {
    int n;
    Nodo* principio;

public:
    Circulo();
    ~Circulo();
    Nodo * getPrincipio();
    int getN();
    void encolar(int num);
    void eliminar(Nodo* eliminar);
};
