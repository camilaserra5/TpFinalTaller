#ifndef _SERVIDOR_H
#define _SERVIDOR_H

#include <map>
#include "thread.h"
#include "protected_queue.h"
#include "actualizacion.h"
#include "comandos/comando.h"
#include "map.h"
#include "estadoJuego.h"
#include "jugador.h"
#include "old_cliente.h"
#include "iserializable.h"
#include <atomic>

class Servidor : public Thread, public ISerializable {
public:
    Servidor(Map *mapa, int cant_jugadores);

    ~Servidor();

    void run() override;

    void agregarCliente(std::string &nombreJugador);

    bool yaArranco();

    bool terminoPartida();

    ProtectedQueue<Comando *> &obtenerColaEventos();

    ProtectedQueue<Actualizacion *> &obtenerColaActualizaciones();

    void lanzarJugadores();

    void lanzarContadorTiempoPartida();

    void borrarClientes();

    std::vector<char> serializar();/* {
        std::vector<char> informacion;
        std::vector<char> cantJugadoresAct = numberToCharArray(this->jugadores.size());
        informacion.insert(informacion.end(), cantJugadoresAct.begin(), cantJugadoresAct.end());
        std::vector<char> cantJugadores = numberToCharArray(cant_jugadores);
        informacion.insert(informacion.end(), cantJugadores.begin(), cantJugadores.end());
        return informacion;
    }*/

    void deserializar(std::vector<char> &serializado) {
    }

    void enviar_actualizaciones(ProtectedQueue<Actualizacion *> &actualizaciones);

    void actualizarContador();

    int obtenerIdParaJugador();


private:
    void procesar_comandos(ProtectedQueue<Comando *> &cola_comandos, EstadoJuego &estadoJuego);

    ProtectedQueue<Comando *> cola_comandos;
    ProtectedQueue<Actualizacion *> cola_actualizaciones;
    EstadoJuego estadoJuego;
    int cantJugadoresPosibles;
<<<<<<< HEAD
    int cantidadJugadoresAgregados = 0;
=======
    int cantJugadoresAgregados = 0;
>>>>>>> e1006ad355652f36caef7c2f544ab1ece5f754bc
    std::atomic<bool> sigue_corriendo;
    std::atomic<bool> arrancoPartida;
    int generadorDeId = 100;
};

#endif
