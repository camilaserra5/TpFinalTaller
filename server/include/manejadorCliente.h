#ifndef _MANEJADOR_CLIENTES_H
#define _MANEJADOR_CLIENTES_H

#include "server_event_sender.h"
#include "server_event_receiver.h"


class ManejadorCliente{
public:
    ManejadorCliente(BlockingQueue<Actualizacion *> &actualizaciones, ProtectedQueue<Comando *> &comandos, Protocolo* protocolo, int& id){
        this->enviador =  new Server_Event_Sender(actualizaciones, protocolo);
        this->recibidor = new Server_Event_Receiver(comandos, protocolo);
        this->id = id;//no lo necesita porq se settea
    }
    ~ManejadorCliente(){

    }
    void run(){
        this->enviador->start();
        this->recibidor->start();
    }
    void settearId(int& id){
        this->id = id;
    }
    void join(){
      this->enviador->join();
      this->recibidor->join();
    }
private:
    Server_Event_Sender* enviador;
    Server_Event_Receiver* recibidor;
    int id;
};

#endif
