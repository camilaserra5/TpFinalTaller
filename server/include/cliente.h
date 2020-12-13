#ifndef _CLIENTE_H
#define _CLIENTE_H

#include "thread.h"
#include "protected_queue.h"
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
