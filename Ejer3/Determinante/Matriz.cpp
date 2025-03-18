#include "Matriz.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#define assertdomjudge(x)                  \
    if (!(x)) {                            \
        std::cout << "ERROR" << std::endl; \
        exit(0);                           \
    }

// Asignacion de matrices
Matriz::Matriz() // constructor por defecto
{
    this->n_filas = 0;
    this->n_columnas = 0;
    this->matriz = nullptr;
}

Matriz::Matriz(int n_filas, int n_columnas)
{
    this->n_filas = n_filas;
    this->n_columnas = n_columnas;

    matriz = new double*[this->n_filas]; // reserva memoria a la matriz
    for (int i = 0; i < this->n_filas; i++)
        matriz[i] = new double[this->n_columnas];
}

Matriz::Matriz(const Matriz& copia)
{
    this->n_filas = copia.n_filas;
    this->n_columnas = copia.n_columnas;

    matriz = new double*[this->n_filas];
    for (int f = 0; f < this->n_filas; f++) {
        matriz[f] = new double[this->n_columnas]; // reserva memoria

        for (int c = 0; c < this->n_columnas; c++)
            matriz[f][c] = copia.matriz[f][c]; // copia valores
    }
}

Matriz::~Matriz() // destructor
{
    for (int i = 0; i < this->n_filas; i++)
        delete[] matriz[i]; // elimina las columnas
    delete[] matriz; // elimina las filas
}

Matriz Matriz::operator+(const Matriz& m) const // operador de suma
{
    Matriz res(n_filas, n_columnas);

    if (n_filas != m.n_filas || n_columnas != m.n_columnas) // comprueba que sean del mismo tamaño
        printf("Las matrices deben de tener mismo tamaño");
    else {
        for (int f = 0; f < n_filas; f++)
            for (int c = 0; c < n_columnas; c++)
                res.matriz[f][c] = this->matriz[f][c] + m.matriz[f][c]; // hace la suma con la matriz original y la que se introduce
    }
    return res;
}

Matriz Matriz::operator-(const Matriz& m) const // operador de resta
{
    Matriz res(n_filas, n_columnas);

    if (n_filas != m.n_filas || n_columnas != m.n_columnas) // comprueba que sean del mismo tamaño
        printf("Las matrices deben de tener mismo tamaño");
    else {
        for (int f = 0; f < n_filas; f++)
            for (int c = 0; c < n_columnas; c++)
                res.matriz[f][c] = this->matriz[f][c] - m.matriz[f][c]; // hace la resta con la matriz original y la que se introduce
    }
    return res;
}

Matriz Matriz::operator*(const double escalar) const // multiplica todos los valores de la matriz por un escalar
{
    Matriz res(n_filas, n_columnas);
    for (int f = 0; f < n_filas; f++)
        for (int c = 0; c < n_columnas; c++)
            res.matriz[f][c] = this->matriz[f][c] * escalar;

    return res;
}

Matriz Matriz::operator*(const Matriz& m) const // producto de matrices
{
    Matriz res(n_filas, m.n_columnas); // numero de filas del primer operando y numero de columnas del segundo operando
    if (n_columnas == m.n_filas) // comprueba que se pueda hacer la operación
    {
        for (int f = 0; f < n_filas; f++)
            for (int c = 0; c < m.n_columnas; c++)
                for (int k = 0; k < m.n_columnas; k++)
                    res.matriz[f][c] += matriz[f][k] * m.matriz[k][c]; // suma a la matriz resultado el producto de fil * col
    }

    return res;
}

Matriz Matriz::calcularTraspuesta() const // calcula la traspuesta de la matriz
{
    Matriz res(n_columnas, n_filas); // crea resultado alternando las filas y columnas
    for (int f = 0; f < n_filas; f++)
        for (int c = 0; c < n_columnas; c++)
            res.matriz[c][f] = matriz[f][c];

    return res;
}

bool Matriz::esSimetrica() const
{
    bool res = true;

    int f = 0, c = 0;
    while (res && f < n_filas) {
        while (res && c < n_columnas) {
            if (matriz[f][c] != matriz[c][f]) // tiene que ser igual que su traspuesta
                res = false;
            else
                c++;
        }

        f++;
        c = 0;
    }

    return res;
}

double Matriz::obtenerMaximo() const
{
    double max = matriz[0][0];

    for (int f = 0; f < n_filas; f++)
        for (int c = 0; c < n_columnas; c++)
            if (max < matriz[f][c])
                max = matriz[f][c];

    return max;
}

double Matriz::obtenerMinimo() const
{
    double min = matriz[0][0];

    for (int f = 0; f < n_filas; f++)
        for (int c = 0; c < n_columnas; c++)
            if (min > matriz[f][c])
                min = matriz[f][c];

    return min;
}

Matriz& Matriz::operator=(const Matriz& m)
{
    if (matriz != NULL) {
        for (int i = 0; i < n_filas; i++)
            delete[] matriz[i];

        delete[] matriz;
        matriz = NULL;
    }

    this->n_filas = m.n_filas;
    this->n_columnas = m.n_columnas;
    this->matriz = NULL;
    if (n_filas > 0 && n_columnas > 0) {
        matriz = new double*[n_filas];

        for (int i = 0; i < n_filas; i++) {
            matriz[i] = new double[n_columnas];
            for (int j = 0; j < n_columnas; j++)
                matriz[i][j] = m.matriz[i][j];
        }
    }

    return (*this);
}

// Leer matriz
void Matriz::rellenarManual()
{
    double elemento;
    for (int i = 0; i < n_filas; i++) {
        cout << "Fila " << i << endl;
        for (int j = 0; j < n_columnas; j++) {
            cout << "Elemento " << j << endl;
            cin >> elemento;
            matriz[i][j] = elemento;
        }
        cout << endl;
    }
}

// Rellenar Matriz Aleatoria
void Matriz::rellenarAleatorio(long seed)
{
    srand(seed);
    for (int i = 0; i < n_filas; i++)
        for (int j = 0; j < n_columnas; j++)
            matriz[i][j] = rand();
}

// Imprimir Matriz
void Matriz::mostrarMatriz()
{
    for (int i = 0; i < n_filas; i++) {
        for (int j = 0; j < n_columnas; j++)
            cout << matriz[i][j] << " ";
        cout << endl;
    }
}

double Matriz::calcularDeterminante() const // t(1) = 1, t(0) = 1, t(n) = n*t(n-1) + O(n^2) -> t(n) = ∑k=1 n (k!/n!*O(k2)) = O(n!)
{ // S(n) = S(n-1) + O(n²), S(0) = 1 -> S(n) = ∑k=2 n (O(k2)) = O(n³)
    if (n_filas != n_columnas) { // precondicion, tiene que ser cuadrada
        std::cout << "ERROR";
        return 0;
    }

    if (n_filas == 1) { // caso base 0, por si quedara un solo elemento suelto
        return matriz[0][0];
    }

    if (n_filas == 2) { // caso base, es una matriz 2x2
        return matriz[0][0] * matriz[1][1] - matriz[0][1] * matriz[1][0]; // se calcula directamente
    }

    double det = 0; // se crea el double determinante para guardar el resultado
    for (int col = 0; col < n_columnas; ++col) { // primero se itera por las columnas que estamos escluyendo
        Matriz submatriz(n_filas - 1, n_columnas - 1); // se crea una sub matriz por cada columna que se quite
        for (int i = 1; i < n_filas; ++i) { // se inicializa en 1 ya que la primera fila no se copia
            int subcol = 0; // se crea el entero sub col para iterar en nuestra submatriz
            for (int j = 0; j < n_columnas; ++j) { // se itera por cada columna
                if (j == col) // se salta la columna que no queremos copiar
                    continue;
                submatriz.matriz[i - 1][subcol] = matriz[i][j]; // se copian los valores
                ++subcol;
            }
        }
        double subdet = submatriz.calcularDeterminante(); // se calcula el valor del subdeterminante
        det += (col % 2 == 0 ? 1 : -1) * matriz[0][col] * subdet; // se suman o restan los valores obtenidos dependiendo de si son pare o impares
    }
    return det;
}
