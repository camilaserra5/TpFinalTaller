#ifndef THCLIENT_H
#define THCLIENT_H

#include <sstream>
#include <atomic>
#include "thread.h"
#include "socket.h"
#include "protocolo.h"
#include <map>
#include "server_event_receiver.h"
#include "server_event_sender.h"

class ThClient : public Thread {
private:
    Protocolo *protocolo;
    std::string rutaMapas;
    std::map<std::string, std::string> &mapas;
    std::atomic<bool> keep_talking;
    std::atomic<bool> is_running;
    Server_Event_Sender *enviador = NULL;
    Server_Event_Receiver *recibidor = NULL;
    int id;
    bool isDead = false;

    void procesar_pedido();

public:
    /*
      * CReara la clase thclient dejandola valia para uso
      * sus parametros deben ser valido y estar inicializados
    */
    ThClient(Socket &&un_socket, std::string rutaMapas,
             std::map<std::string, std::string> &mapas, int id);
    /*
      * devuelve el comando inical si se trata de un crear partida o
      * unirse a una partida
    */
    Comando *obtenerComandoInicial(std::vector<char> info);

    /*
      * envia el en -1 al jugador por medio del protocolo
    */
    void enviarError();

    /*
      * envia el id del juagdor por medio del protocolo
    */
    void enviarIdJugador();
    /*
      * agrega la cola de eventos
    */
    void agregarColaEventos(ProtectedQueue<Comando *> &cola_comandos);
    /*
      * lanza los dos hilos de enviador y recibidor
    */
    void run() override;
    /*
      * devuelve true si el hilo sigue corriendo o false en caso contrario
    */
    bool is_dead();
    /*
      * frena al cliente
    */
    void stop();
    /*
      * devuelve el id del cliente que le asigno el servior
    */
    int getId() {
        return this->id;
    }
    /*
      * envia las actualizaciones al enviador
    */
    void enviar_actualizaciones(std::vector<Actualizacion *> actualizaciones);

    ~ThClient();
};

#endif /*THCLIENT_H*/
