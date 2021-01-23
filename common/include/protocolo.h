#ifndef _PROTOCOLO_H
#define _PROTOCOLO_H


#include "socket.h"
#include "comando.h"
#include <iostream>

class Protocolo{
    public:
        Protocolo(Socket& socket): socket(socket){}
        ~Protocolo();
        void enviar(Comando& comando){
            std::stringstream informacion = comando.serializar();
            // socket.send(informacion);
        }
        void recibir();

    private:
          Socket& socket;
};

#endif
