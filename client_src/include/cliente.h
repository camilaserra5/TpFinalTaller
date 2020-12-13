#ifndef _CLIENTE_H
#define _CLIENTE_H
#include "socket.h"

#include "thread.h"
#include "protected_queue.h"
#include <SDL2/SDL.h>

class Cliente: public Thread {
    private:
        Socket socket;
        ProtectedQueue& cola_eventos;
    public:
        Cliente(ProtectedQueue& cola_eventos, const char* host, const char* server_port);
        ~Cliente();
        void run() override;
};

#endif
