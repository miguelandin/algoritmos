#ifndef MATRIZ_H
#define MATRIZ_H

using namespace std;

class Matriz {
private:
    double** matriz; // puntero a una matriz bidimensional

    int n_filas;
    int n_columnas;

public:
    Matriz(); // contructor por defecto

    Matriz(int n_filas, int n_columnas); // constructor con parámetros

    Matriz(const Matriz& copia); // copia una matriz

    ~Matriz(); // destructor

    Matriz operator+(const Matriz& m) const; // suma

    Matriz operator-(const Matriz& m) const; // resta

    Matriz operator*(const double escalar) const; // producto escalar

    Matriz operator*(const Matriz& m) const; // producto sobre una matriz

    Matriz calcularTraspuesta() const; // calcula la traspuesta

    bool esSimetrica() const; // comprueba si es simétrica comparandola con su traspuesta

    double obtenerMaximo() const; // obitnene el valor mas grande

    double obtenerMinimo() const; // obtiene el valor mas pequeño

    /* Realiza la asignación entre dos objetos de la clase Matriz. Crea una nueva matriz  con el resultado.
               Parámetro: la matriz que se va a asignar
               Retorno: una nueva matriz con la matriz pasada como parámetro.
               Precondicion: Ninguno.
               Complejidad Temporal: O(n_filas*n_columnas)
               Complejidad Espacial: O(n_filas*n_columnas)


    */

    Matriz& operator=(const Matriz& m);

    /* Permite rellenar todos los elementos de la matriz del objeto actual preguntando al usuario
               Parámetro: Ninguno
               Retorno: Ninguno
               Precondicion: La matriz no debe estar vacía
               Complejidad Temporal: O(n_filas*n_columnas)
               Complejidad Espacial: O(1)


    */

    void rellenarManual();

    /* Permite rellenar todos los elementos de la matriz del objeto actual de forma aleatoria
               Parámetro: semilla que se utiliza para el generador aleatorio
               Retorno: Ninguno
               Precondicion: La matriz no debe estar vacía
               Complejidad Temporal: O(n_filas*n_columnas)
               Complejidad Espacial: O(1)


    */

    void rellenarAleatorio(long seed);

    /* Imprime por pantalla todos los elementos de la matriz del objeto actual
               Parámetro: Ninguno
               Retorno: Ninguno
               Precondicion: La matriz no debe estar vacía
               Complejidad Temporal: O(n_filas*n_columnas)
               Complejidad Espacial: O(1)


    */

    void mostrarMatriz();

    double calcularDeterminante() const;
};

#endif // MATRIZ_H
