#ifndef _CLIENTE_H
#define _CLIENTE_H

#include "thread.h"
#include "protected_queue.h"
#include "actualizaciones/actualizacion.h"
#include "comandos/comando.h"
#include <string>
/***************************BORRARRRRR****************************/
class Cliente : public Thread {
public:

    Cliente(ProtectedQueue<Comando *> &cola_eventos, ProtectedQueue<Actualizacion *> &actualizaciones,
            std::string &nombre);

    void actualizar(const Actualizacion *actualizacion);

    ~Cliente();

    void run() override;

private:
    ProtectedQueue<Comando *> &cola_comandos;
    ProtectedQueue<Actualizacion *> &cola_actualizaciones;
    std::string nombre;
    int id;
};

#endif
