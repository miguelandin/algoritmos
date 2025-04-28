#include <iostream>
using namespace std;

char calcular_ganador(char* equipos, int n, int ronda)
{
    
}

int main()
{
    int n;
    cin >> n;
    char* equipos = new char[n + 1];
    for (int i = 0; i < n; i++)
        equipos[i] = 'A' + i;
    equipos[n] = 0;
    calcular_ganador(equipos, n, 0);
}
