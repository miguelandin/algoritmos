#include "assertdomjudge.h"
#include "lista-adyacencia.h"
#include <iostream>

using namespace std;

bool esRojiBlanco(ListaAdyacencia* vector, int vertices);

int main()
{
    int vertices, aristas;

    // Procesar múltiples casos hasta que vertices sea 0
    while (cin >> vertices && vertices != 0) {
        cin >> aristas;

        ListaAdyacencia* vector = new ListaAdyacencia[vertices];

        // Introducir los valores del grafo
        for (int i = 0; i < aristas; i++) {
            int from, to;
            cin >> from >> to;
            assertdomjudge(from >= 0 && from < vertices && to >= 0 && to < vertices);
            vector[from].insertar(to); // inserta relación entre nodos "from" y "to"
            vector[to].insertar(from); // es no dirigido, a sí que se repite
        }

        // Comprobar si es esRojiBlanco
        if (esRojiBlanco(vector, vertices))
            cout << "SI" << endl;
        else
            cout << "NO" << endl;

        // Liberar memoria
        delete[] vector;
    }

    return 0;
}

bool esRojiBlanco(ListaAdyacencia* vector, int vertices) // comprueba si el grafo esRojiBlanco
{ //T(n) = O(vertices + aristas), M(n) = O(vertices)
    if (vertices == 0)
        return true;

    int* color = new int[vertices]; // creamos un vector para almacenar colores
    for (int i = 0; i < vertices; i++) { // inicializamos
        color[i] = -1; // -1 significa no coloreado
    }

    /* Creamos una cola para recorrer el grafo */
    int* cola = new int[vertices];
    int frente = 0;
    int final = 0;

    for (int i = 0; i < vertices; i++) {
        if (color[i] == -1) { // si no está coloreado
            color[i] = 0; // Lo coloreamos con el primer color (0)
            cola[final++] = i; // lo añadimos a la cola

            while (frente < final) { // Mientras la cola no esté vacía
                int u = cola[frente++]; // sacamos el primer vértice

                Nodo* actual = vector[u].getLista(); // obtenemos sus vecinos
                while (actual != nullptr) {
                    int v = actual->valor; // vecino actual

                    if (color[v] == -1) { // si no está coloreado
                        color[v] = 1 - color[u]; // color opuesto al acutal
                        cola[final++] = v; // "push"
                        // Verificar que no excedamos el tamaño de la cola
                    } else if (color[v] == color[u]) { // conflicto de colores
                        delete[] color;
                        delete[] cola;
                        return false; // no esRojiBlanco
                    }
                    actual = actual->siguiente; // itera al siguiente vecino
                }
            }
        }
    }

    delete[] color;
    delete[] cola;
    return true; // si llega hasta aquí -> esRojiBlanco
}
