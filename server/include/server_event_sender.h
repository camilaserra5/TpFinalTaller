#ifndef _SERVER_EVENT_SENDER_H
#define _SERVER_EVENT_SENDER_H


#include "thread.h"
#include "blocking_queue.h"
#include "socket.h"
#include "actualizaciones/actualizacion.h"
#include "protocolo.h"
#include <atomic>


class Server_Event_Sender : public Thread {
public:
    /*
      * creara la clase server event sender dejandola valida para uso
      * sus parametros deben estar inicalizados
    */
    Server_Event_Sender(Protocolo *protocolo) : protocolo(protocolo), corriendo(true) {}
    /*
      * liberara la clase con sus recursos
    */
    ~Server_Event_Sender() {}
    /*
      * sacara de la cola de actualizaciones una actualizacion , la serializara
      * y la mandara por medio del Protocolo
    */
    void run() override;
    /*
      * cierra el protocolo
    */
    void cerrar();
    /*
      * enviara las actualizaciones por medio del protocolo
    */
    void enviar_actualizaciones(std::vector<Actualizacion *> act);
    /*
      * devuelve true si esta corriendo
    */
    bool estaCorriendo();

private:
    BlockingQueue<Actualizacion *> actualizaciones;
    Protocolo *protocolo;
    std::atomic<bool> corriendo;
};

#endif
