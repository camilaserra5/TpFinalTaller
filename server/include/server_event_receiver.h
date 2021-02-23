#ifndef _SERVER_EVENT_RECEIVER
#define _SERVER_EVENT_RECEIVER

#include "thread.h"
#include "protected_queue.h"
#include "socket.h"
#include "comandos/comando.h"
#include "protocolo.h"
#include <atomic>

class Server_Event_Receiver : public Thread {
public:
    /*
      * CReara la clase server Event Receiver dejandola valida para uso
      * los parametros deben estar inicializados
    */
    Server_Event_Receiver(ProtectedQueue<Comando *> &comandos, Protocolo *protocolo) :
            comandos(comandos), protocolo(protocolo), corriendo(true) {}

    ~Server_Event_Receiver() {
    /*  for (int i = 0; i < this->comandos.size(); i++){
        Comando* c = comandos.obtener_dato();
        delete c;
      }*/
    }
    /*
      * recibiera la informacion por medio del protocolo y metera el comando
      * en la cola de comandos
    */
    void run() override;
    /*
      * cerrara el protocolo
    */
    void cerrar();
    /*
      *devuelve true si sigue corriendo
    */
    bool estaCorriendo();


private:
    ProtectedQueue<Comando *> &comandos;
    Protocolo *protocolo;
    std::atomic<bool> corriendo;

};

#endif
