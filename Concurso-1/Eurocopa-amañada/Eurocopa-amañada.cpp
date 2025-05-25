#include <iostream>
using namespace std;

char calcular_ganador(char* equipos, int n, int ronda)
{
    if (n == 1) { // base case - un solo equipo
        return equipos[0];
    }

    int mitad = n / 2;
    char ganador1 = calcular_ganador(equipos, mitad, ronda + 1);
    char ganador2 = calcular_ganador(equipos + mitad, mitad, ronda + 1);

    char ganador;
    if (ronda % 2 == 0)
        ganador = ganador1;
    else
        ganador = ganador2;

    cout << "Ronda " << ronda << " Ganador " << ganador << endl;
    return ganador;
}

int main()
{
    int n;
    cin >> n;
    char* equipos = new char[n + 1];
    for (int i = 0; i < n; i++) {
        equipos[i] = 'A' + i;
    }
    equipos[n] = '\0';

    calcular_ganador(equipos, n, 0);

    delete[] equipos; // liberar memoria
    return 0; // avisar que el programa ha finalizado correctamente
}
