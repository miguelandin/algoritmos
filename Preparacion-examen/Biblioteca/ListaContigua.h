#include<iostream>

class ListaContigua{
    int * vector;
    int n, capacidad, incremento;
public:
    ListaContigua(int incremento);
    ~ListaContigua();
    bool estaLlena();
    int elemento(int pos);
    void modificar(int pos, int val);
    void insertar(int pos, int val);
    void eliminar(int pos);
    void imprimir();
};
