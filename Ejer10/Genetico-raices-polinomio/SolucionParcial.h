#include <iostream>
#include <iomanip>
using namespace std;

// Representa una solución parcial del problema de optimización genética
class SolucionParcial {
 public:
  float x; // Posición del hijo
  float y; // Valor del hijo
  void imprimir()
  {
    cout<<setprecision(5)<<"("<<x<<","<<y<<")"<<endl;
  }
  
};
