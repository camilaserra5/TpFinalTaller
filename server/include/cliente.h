#ifndef _CLIENTE_H
#define _CLIENTE_H

#include "thread.h"
#include "protected_queue.h"
#include "comando.h"
#include <string>

class Cliente : public Thread {
public:

    Cliente(ProtectedQueue<Comando*> &cola_eventos,ProtectedQueue<Actualizacion*>& actualizaciones, std::string& nombre);


    ~Cliente();

    void run() override;

private:
    ProtectedQueue<Comando*> &cola_comandos;
    ProtectedQueue<Actualizacion*> &cola_actualizaciones;
    std::string nombre;
};

#endif
