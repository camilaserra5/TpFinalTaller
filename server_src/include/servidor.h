#ifndef _SERVIDOR_H
#define _SERVIDOR_H
#include "thread.h"
#include "protected_queue.h"
#include "comando.h"

class Servidor : public Thread {
      public:
            Servidor(ProtectedQueue& cola_comandos);
            ~Servidor();
            void run() override;
      private:
            ProtectedQueue& cola_comandos;
};

#endif
