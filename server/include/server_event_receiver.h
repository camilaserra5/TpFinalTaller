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
    Server_Event_Receiver(ProtectedQueue<Comando *> &comandos, Protocolo *protocolo) :
            comandos(comandos), protocolo(protocolo), corriendo(true) {}

    ~Server_Event_Receiver() {
    /*  bool termine = false;
       while (!termine) {
           try {
               Comando *comando = comandos.obtener_dato();
               if (comando != NULL) delete comando;
           } catch (const std::exception &exception) {
               termine = true;
           }
       }*/
    }

    void run() override;

    void cerrar();

    bool estaCorriendo();


private:
    ProtectedQueue<Comando *> &comandos;
    Protocolo *protocolo;
    std::atomic<bool> corriendo;

};

#endif
