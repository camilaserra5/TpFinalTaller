#include "../include/cliente.h"
#include "../../common_src/include/socket.h"


Cliente::Cliente(ProtectedQueue& cola_eventos, const char* host, const char* server_port):
    cola_eventos(cola_eventos), socket(host, server_port){}

Cliente::~Cliente(){}

void Cliente::run(){
    Comando* evento;
    //ACA IRIA UN HANDLER EVENT
    this->cola_eventos.aniadir_comando(evento);
    //SE VAN AÑADIENDO, SE ENVIAN Y SE ACTUALIZA.
    //LO QUE RECIBA DE LA ACTUALIZACION HAY QUE DIBUJARLO.

}
