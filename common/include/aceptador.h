#ifndef ACEPTADOR_H
#define ACEPTADOR_H

#include <string>
#include <vector>

#include "thread.h"

#include "socket.h"
#include "thclient.h"

class Aceptador : public Thread {
private:
    Socket &socket_listener;
    std::vector<ThClient *> clientes;

public:
    Aceptador(Socket &un_socket);

    /*
     * Aceptara los clientes que quieren conectarse al servidor.
     * Los insertará en un vector e ira procesando cada uno.
     * Se limpiara este vector los cliente finalizados
     * cada vez que se conecte un nuevo cliente
     */
    void run() override;

    void cerrar();

    ~Aceptador() { this->join(); }
};

#endif /*ACEPTADOR_H*/
