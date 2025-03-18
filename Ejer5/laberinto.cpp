#include <iostream>
#define TAM 10
#define LEN 4
using namespace std;

int movX[LEN] = { -1, 0, 1, 0 };
int movY[LEN] = { 0, 1, 0, -1 };

void imprimirLaberinto(char** laberinto)
{
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++)
            cout << laberinto[i][j];
        cout << endl;
    }
}

bool buscarTesoro(char** laberinto, int x, int y, int& sol_x, int& sol_y) // encuentra el tesoro mediante un patrón de backtracking
{ // T(0) = 1, T(n) = 4*T(n-1) + 1 -> T(n) = (1/3) * (4^(n+1) - 1) = O(4^n)
    // M(1) = 1, M(n) = M(n-1) + 1 -> M(n) = n + 1 = O(n)
    int f = 0;

    do {
        int i = movX[f] + x; // posición eje x nueva
        int j = movY[f] + y; // posición eje y nueva

        if (i < TAM && j < TAM && i >= 0 && j >= 0 && laberinto[i][j] != '*' && laberinto[i][j] != 'X') { // se comprueba que se pueda hacer el movimiento
            if (laberinto[i][j] == '.') { // si es un hueco, se avanza
                laberinto[i][j] = 'X'; // se marca como posición recorrida
                if (!buscarTesoro(laberinto, i, j, sol_x, sol_y)) // si no hay éxito se cambia por hueco y se intenta por otro lado
                    laberinto[i][j] = '.';
                else
                    return true; // se devuelve true porque la solución fué encontrada
            }
            if (laberinto[i][j] == 'T') { // si se llega a la meta devuelve true
                sol_x = i, sol_y = j; // Se guarda la posición de la meta
                return true; // se devuelve true ya que se encontró la solución
            }
        }
        f++; // siguiente posición
    } while (f < LEN);
    return false; // si no se enceuntra nada en todas las iteraciones se devuelve false
}

int main()
{
    int i, j;
    int sol_x = -1, sol_y = -1;
    char** laberinto; // matriz de char

    // reservar memoria laberinto
    laberinto = new char*[TAM];
    for (i = 0; i < TAM; i++)
        laberinto[i] = new char[TAM];

    // introducir datos
    for (i = 0; i < TAM; i++)
        for (j = 0; j < TAM; j++)
            cin >> laberinto[i][j];

    // hacer búsqueda
    i = 0, j = 0;
    laberinto[i][j] = 'X'; // la posición inicial se marca
    if (buscarTesoro(laberinto, i, j, sol_x, sol_y)) {
        imprimirLaberinto(laberinto);
        cout << "ENCONTRADO " << sol_x << " " << sol_y << endl;
    } else
        cout << "INALCANZABLE" << endl;

    // liberar memoria
    for (i = 0; i < TAM; i++)
        delete[] laberinto[i];

    delete[] laberinto;
}
