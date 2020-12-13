#ifndef _SERVIDOR_H
#define _SERVIDOR_H

#include <map>
#include "thread.h"
#include "protected_queue.h"
#include "comando.h"
#include "map.h"
#include "estadoJuego.h"
#include "jugador.h"

class Servidor : public Thread {
public:
    Servidor(ProtectedQueue<Comando*> &cola_comandos, Map &mapa);

    ~Servidor();

    void run() override;

private:
    ProtectedQueue<Comando*> &cola_comandos;
    std::map<int, Jugador> jugadores;
    EstadoJuego estadoJuego;

};

#endif
