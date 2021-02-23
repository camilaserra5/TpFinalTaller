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
#include "configuracionPartida.h"

class Partida : public Thread, public ISerializable {
public:
    /*
      * creara la partida dejandola valida para uso
      * los parametros deben estar inicializados
    */
    Partida(Map&& mapa, int cant_jugadores, ConfiguracionPartida configuracion);
    /*
      * liberara la partida con sus recrusos
    */
    ~Partida();
    /*
      * ejecutara la partida procesando comandos y enviando actualizaciones
    */
    void run() override;
    /*
      * agrega un cliente a la partida
    */
    void agregarCliente(std::string &nombreJugador, ThClient *cliente);
    /*
      * devuelve true si ya empezo la partida
    */
    bool yaArranco();


    void finalizarClientes();
    /*
      * devuelve true si termino la partida
    */
    bool terminoPartida();
    /*
      * devuelve la cola de comandos
    */
    ProtectedQueue<Comando *> &obtenerColaEventos();

    /*
      * lanza los hilos de los jugadores jugadores
    */
    void lanzarJugadores();
    /*
      * lanza el cntador de la partida
    */
    void lanzarContadorTiempoPartida();

    void borrarClientes();
    /*
      * serializa la partida y devuelve la inforacion de ella
    */
    std::vector<char> serializar();
    /*
      * deserialza la artida dejandola en sus valores correspondientes
    */
    void deserializar(std::vector<char> &serializado) {}
    /*
      * envia las actualizaciones a todos los clientes
    */
    void enviar_actualizaciones(std::vector<Actualizacion *> actualizaciones);
    /*
      * actualiza el contador de la partida
    */
    void actualizarContador();

    void joinClientes();

    /*
      * frena a la partida
    */
    void stop();


private:
    /*
      * procesa los comandos de la cola protegida y los ejecuta
    */
    void procesar_comandos(EstadoJuego &estadoJuego);

    ProtectedQueue<Comando *> cola_comandos;
    //BlockingQueue<Actualizacion *> cola_actualizaciones;
    EstadoJuego estadoJuego;
    int cantJugadoresPosibles;
    int cantJugadoresAgregados = 0;
    std::atomic<bool> sigue_corriendo;
    std::atomic<bool> arrancoPartida;
    std::map<int, ThClient *> clientes;
    std::vector<Actualizacion *> ultAct;
    //JugadorLua jugadorLua;
    /*
      * genera comandos del jugador lua
    */
    void generarComandosLua(JugadorLua &jugadorLua);
};

#endif
