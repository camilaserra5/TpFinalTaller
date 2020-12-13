#ifndef _CLIENTE_H
#define _CLIENTE_H

#include "thread.h"
#include "protected_queue.h"
#include "comando.h"
#include <string>

class Cliente : public Thread {
public:
<<<<<<< HEAD
    Cliente(ProtectedQueue &cola_eventos, std::string& nombre);
=======
    Cliente(ProtectedQueue<Comando*> &cola_eventos, std::string& nombre);
>>>>>>> 7632d0ff7eb3384ad4fd780f34707e0a0d05d0fe

    ~Cliente();

    void run() override;

private:
    ProtectedQueue<Comando*> &cola_comandos;
    std::string nombre;
};

#endif
