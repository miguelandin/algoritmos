class Nodo {
public:
    int num;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(int num)
    {
        this->num = num;
        siguiente = nullptr;
        anterior = nullptr;
    }
};
