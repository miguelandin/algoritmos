#include "Polinomio.h"
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

const int ITERACIONES = 10; // cuantos hijos crear

float Polinomio::obtenerAleatorioNormalEstandar()
{
    float suma = 0; // Suma de 12 variables aleatorias uniformes entre 0 y 1
    for (int i = 0; i < 12; i++)
        suma = suma + rand() / (float)RAND_MAX;
    return (suma - 6);
}

float Polinomio::obtenerRaizRecursivo(SolucionParcial padre)
{ // T(0) = ITERACIONES (10), T(n) = T(hijos > padre) + 10 -> T(n) ~ O(n²)
    // M(0) = 10, M(n) = M(x) + 10 -> M(n) ~ O(n²)
    SolucionParcial hijos[ITERACIONES]; // array de hijos (10)
    bool seguir = false; // booleano para saber si seguir iterando o no

    /* Imprimimos el padre */
    cout << "Seleccionada" << endl;
    padre.imprimir();
    cout << "Mutaciones" << endl;

    /* Calculamos la mutación para cada hijo (10) y evaluamos */
    for (int i = 0; i < ITERACIONES; i++) {
        hijos[i].x = padre.x + obtenerAleatorioNormalEstandar();
        hijos[i].y = evaluar(hijos[i].x); // obtiene y
        hijos[i].imprimir(); // imprime la mutación
    }

    /* Una vez terminadas las mutaciones, elegimos el mejor hijo */
    for (int i = 0; i < ITERACIONES; i++)
        if (abs(hijos[i].y) < abs(padre.y)) { // se busca el más cercano a 0
            padre = hijos[i]; // el hijo pasa ser padre para la nueva generación
            seguir = true; // se ha encontrado un hijo -> seguimos
        }

    if (seguir) // Si se encontró un nuevo padre seguimos
        return obtenerRaizRecursivo(padre);
    else // si no, caso base, terminamos devolviendo la "x" del mejor candidato
        return padre.x;
}

Polinomio::Polinomio(int n, float* coeficientes) // constructor
{ // T(n) = M(n) = O(n+1)
    this->n = n; // se guarda el grado del polinomio
    this->coeficientes = new float[n + 1]; // reserva la memoria del vector

    for (int i = 0; i < n + 1; i++) // copia los valores para nuestro vector
        this->coeficientes[i] = coeficientes[i];
}

float Polinomio::evaluar(float x) // calcula el valor del polinomio según x
{ // T(n) = O(n+1), M(n) = O(1)
    float resultado = 0; // importante inicializar a 0

    for (int i = 0; i < n + 1; i++)
        resultado += coeficientes[i] * pow(x, i);

    return resultado;
}

float Polinomio::obtenerRaiz() // obtiene la raiz del polinomio
{ // T(n) = M(n) ~ O(n²)
    SolucionParcial inicial; // creamos una SolucionParcial inicial con x = 0
    inicial.x = 0;
    inicial.y = evaluar(inicial.x); // calculamos la y

    return obtenerRaizRecursivo(inicial); // obtenemos el resultado
}

Polinomio::~Polinomio()
{ // T(n) = M(n) = O(1)
    delete[] coeficientes; // libera la memoria del vector coeficientes
    coeficientes = nullptr; // el vector pasa a apuntar a null
    n = 0; // el grado pasa a ser 0
}
