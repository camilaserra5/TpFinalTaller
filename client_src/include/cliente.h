#ifndef _CLIENTE_H
#define _CLIENTE_H

#include "../common_src/thread.h"

class Cliente: public Thread {
    public:
      Cliente(const std::queue<STD_Event>& cola_eventos);
      ~Cliente();
      void run() override;
    private:
        std::queue<STD_Event> cola_eventos;
};

#endif
