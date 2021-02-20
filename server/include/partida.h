#ifndef PARTIDA_H
#define PARTIDA_H

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
#include "../include/thclient.h"

class Partida : public Thread, public ISerializable {
public:
    Partida(Map mapa, int cant_jugadores);

    ~Partida();

    void run() override;

    void agregarCliente(std::string &nombreJugador, ThClient *cliente);

    bool yaArranco();

    bool terminoPartida();

    ProtectedQueue<Comando *> &obtenerColaEventos();

    //  BlockingQueue<Actualizacion *> &obtenerColaActualizaciones();

    void lanzarJugadores();

    void lanzarContadorTiempoPartida();

    void borrarClientes();

    std::vector<char> serializar();

    void deserializar(std::vector<char> &serializado) {}

    void enviar_actualizaciones(std::vector<Actualizacion *> actualizaciones);

    void actualizarContador();

    void joinClientes();


private:
    void procesar_comandos(EstadoJuego &estadoJuego);

    ProtectedQueue<Comando *> cola_comandos;
    //BlockingQueue<Actualizacion *> cola_actualizaciones;
    EstadoJuego estadoJuego;
    int cantJugadoresPosibles;
    int cantJugadoresAgregados = 0;
    std::atomic<bool> sigue_corriendo;
    std::atomic<bool> arrancoPartida;
    std::map<int, ThClient *> clientes;
    //JugadorLua jugadorLua;

    void generarComandosLua(JugadorLua &jugadorLua);
};

#endif
