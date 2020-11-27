#ifndef _SERVIDOR_H
#define _SERVIDOR_H
#include "../common_src/thread.h"

class Servidor : public Thread {
      public:
            Servidor(const &std::queue<STD_Event> cola_eventos);
            ~Servidor();
            void run() override;
      private:
            std::queue<STD_Event> cola_eventos;
};

#endif
