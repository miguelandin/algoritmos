#include"Agenda.h"

int main(){
    Agenda agenda(25);
    
    agenda.introducirContacto(123123321, "mike");
    agenda.introducirContacto(756232490, "boniatez");
    agenda.introducirContacto(555444333, "Jhon Pork");
    agenda.introducirContacto(333123984, "Tralalero");
    agenda.introducirContacto(111666111, "Ouran");

    agenda.imprimir();

    agenda.eliminarContacto(123123321);
    agenda.imprimir();
    if(agenda.existeContacto(123123321))
        cout<<"Encontrado"<<endl;
    agenda.introducirContacto(123321321, "mike2");
    agenda.imprimir();
}
