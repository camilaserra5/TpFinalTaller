#ifndef _SERVIDOR_H
#define _SERVIDOR_H
#include "../common_src/include/thread.h"
#include <SDL2/SDL.h>
#include <queue>

class Servidor : public Thread {
      public:
            Servidor(const std::queue<SDL_Event>& cola_eventos);
            ~Servidor();
            void run() override;
      private:
            std::queue<SDL_Event> cola_eventos;
};

#endif
