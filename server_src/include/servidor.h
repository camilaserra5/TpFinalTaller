#ifndef _SERVIDOR_H
#define _SERVIDOR_H
#include "../common_src/include/thread.h"
#include <SDL2/SDL.h>
#include "../common_src/include/protected_queue.h"

class Servidor : public Thread {
      public:
            Servidor(ProtectedQueue& cola_eventos);
            ~Servidor();
            void run() override;
      private:
            ProtectedQueue& cola_eventos;
};

#endif
