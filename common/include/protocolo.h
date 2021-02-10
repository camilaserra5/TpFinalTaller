#ifndef _PROTOCOLO_H
#define _PROTOCOLO_H


#include "socket.h"

#include "comandos/ataque.h"
#include "comandos/movimiento.h"
#include "comandos/aperturaDePuerta.h"
#include <iostream>
#include <netinet/in.h>
#include <cstring>

#define TAMANIO 100

class Protocolo {
public:
    Protocolo(Socket socket);

    ~Protocolo();


    void enviar(std::vector<char> &informacion);

    std::vector<char> recibir_aux();

    std::vector<char> recibir();

    Comando *deserializarComando(std::vector<char> &informacion);

    Item *deserializarItem(std::vector<char> &informacion);

    void cerrar();


private:
    Socket socket;
};

#endif
