#include <string>

using namespace std;

// Tabla hash que guarda los nombres de los estudiantes de una universidad
class Agenda {

protected:
    int capacidad; // Capacidad de la tabla. Permanece invariante a lo largo de la vida del objeto
    int n; // número actual de elementos
    // Vectores que guardarán la información de la tabla hash
    string* nombres; // Vector con los nombres de los contactos
    bool* vacias; // Vector con los flags que indican si una posición está vacía (true) o no (false). Si esta vacia, tiene basura.
    bool* borradas; // indica que posiciones han sido eliminadas
    long* telefonos; // Vector con los telefonos de los contactos

    // Método de hashing
    int obtenerPosicion(long telefono);

public:
    // Constructor
    Agenda(int capacidad);

    // Comprueba si un contacto está o no en la tabla hash
    bool existeContacto(long telefono);

    // Obtiene un contacto (su nombre) a partir de su telefono
    string getContacto(long telefono);

    // Inserta un contacto en la tabla
    void introducirContacto(long telefono, string contacto);

    // Elimina un contacto de la tabla
    void eliminarContacto(long telefono);

    // Imprime toda la tabla hash. Viola el principio de separación entre interfaz y modelo
    void imprimir();

    //Obtiene la posición real de un contacto en la tabla
    int buscarContacto(long telefono);

    //Busca el hueco adecuado para meter el contacto
    int buscarHueco(long telefono);

    //indica si ha llegado la tabla a su máxima capacidad
    bool isLlena();
    // Destructor
    ~Agenda();
};
