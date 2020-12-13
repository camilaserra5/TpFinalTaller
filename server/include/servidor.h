#ifndef _SERVIDOR_H
#define _SERVIDOR_H

#include <map>
#include "thread.h"
#include "protected_queue.h"
#include "comando.h"
#include "map.h"
#include "estadoJuego.h"
#include "jugador.h"
#include "cliente.h"

class Servidor : public Thread {
public:
    Servidor(ProtectedQueue<Comando*> &cola_comandos, Map &mapa, int cant_jugadores);

    void agregarCliente(std::string& nombreJugador, Cliente& cliente);

    ~Servidor();

    void run() override;
    void agregarCliente(std::string& nombreJugador, Cliente& cliente);
    bool yaArranco();
    bool terminoPartida();
    ProtectedQueue& obtenerColaEventos(); 

private:
    ProtectedQueue<Comando*> &cola_comandos;
    std::map<int, Jugador> jugadores;
    EstadoJuego estadoJuego;
    int cant_jugadores;
    bool sigue_corriendo;

};

#endif
