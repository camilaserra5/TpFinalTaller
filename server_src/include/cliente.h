#ifndef _CLIENTE_H
#define _CLIENTE_H

#include "../common_src/include/thread.h"
#include "../common_src/include/protected_queue.h"
#include <SDL2/SDL.h>

class Cliente: public Thread {
    public:
      Cliente(ProtectedQueue& cola_eventos);
      ~Cliente();
      void run() override;
    private:
        ProtectedQueue& cola_comandos;
};

#endif
