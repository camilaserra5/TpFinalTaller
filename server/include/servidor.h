#ifndef _SERVIDOR_H
#define _SERVIDOR_H

#include <map>
#include "thread.h"
#include "protected_queue.h"
#include "actualizaciones/actualizacion.h"
#include "comandos/comando.h"
#include "map.h"
#include "estadoJuego.h"
#include "jugador.h"
#include "iserializable.h"
#include <atomic>
#include "jugadorLua.h"
#include "parser.h"
#include <string>
#include "socket.h"

class Servidor {
private:
    Socket socket;
    Parser &parser;
public:
    Servidor(Parser &parser);

<<<<<<< HEAD
    ProtectedQueue<Comando *> cola_comandos;
    //BlockingQueue<Actualizacion *> cola_actualizaciones;
    EstadoJuego estadoJuego;
    int cantJugadoresPosibles;
    int cantJugadoresAgregados = 0;
    std::atomic<bool> sigue_corriendo;
    std::atomic<bool> arrancoPartida;
    int generadorDeId = 100;
    std::map<int, ManejadorCliente*> clientes;
    //JugadorLua jugadorLua;
    void verificarClientes();
=======
    void correr();
>>>>>>> 0fc9e59f0849ab6be23f77097005aecaf12a9b57

    ~Servidor();
};

#endif /*SERVIDOR_H*/
