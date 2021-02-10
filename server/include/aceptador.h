#ifndef ACEPTADOR_H
#define ACEPTADOR_H

#include <string>
#include <vector>

#include "thread.h"

#include "socket.h"
#include "thclient.h"
#include "manejadorPartidas.h"

class Aceptador : public Thread {
private:
    Socket &socket_listener;
    ManejadorPartidas *manejadorPartidas;
    std::vector<ThClient *> clientes;

public:
    Aceptador(Socket &un_socket, ManejadorPartidas *manejadorPartidas);

    /*
     * Aceptara los clientes que quieren conectarse al servidor.
     * Los insertará en un vector e ira procesando cada uno.
     * Se limpiara este vector los cliente finalizados
     * cada vez que se conecte un nuevo cliente
     */
    void run() override;

    void cerrar();

    ~Aceptador() {}
};

#endif /*ACEPTADOR_H*/
