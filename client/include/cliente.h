#ifndef _CLIENTE_H
#define _CLIENTE_H
//#include "../../common_src/include/socket.h"
//#include "../../common_src/include/thread.h"
#include "protected_queue.h"
#include "comandos/comando.h"
#include <SDL2/SDL.h>

class Cliente {
private:
    //Socket socket;
    ProtectedQueue<Comando *> &cola_eventos;
public:
    Cliente(ProtectedQueue<Comando *> &cola_eventos, const char *host, const char *server_port);

    ~Cliente();

    void run();
};

#endif
