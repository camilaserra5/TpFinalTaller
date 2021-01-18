#ifndef _CLIENTE_H
#define _CLIENTE_H
//#include "../../common_src/include/socket.h"
//#include "../../common_src/include/thread.h"
#include "protected_queue.h"
#include "blocking_queue.h"
#include "comandos/comando.h"
#include <SDL2/SDL.h>
#include <actualizacion.h>

class Cliente {

public:
    Cliente(const char *host, const char *server_port);

    ~Cliente();

    void run();

private:
    Socket socket;

};

#endif
