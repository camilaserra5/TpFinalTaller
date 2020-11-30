#ifndef _CLIENTE_H
#define _CLIENTE_H

#include "../common_src/include/thread.h"
#include <queue>
#include <SDL2/SDL.h>

class Cliente: public Thread {
    public:
      Cliente(const std::queue<SDL_Event>& cola_eventos);
      ~Cliente();
      void run() override;
    private:
        std::queue<SDL_Event> cola_eventos;
};

#endif
