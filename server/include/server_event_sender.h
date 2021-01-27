#ifndef _SERVER_EVENT_SENDER_H
#define _SERVER_EVENT_SENDER_H


#include "thread.h"
#include "blocking_queue.h"
#include "socket.h"
#include "actualizacion.h"
#include "protocolo.h"


class Server_Event_Sender : public Thread{
    public:
        Server_Event_Sender(BlockingQueue<Actualizacion*>& actualizaciones, Socket& socket):
            actualizaciones(actualizaciones), protocolo(std::move(socket)), corriendo(true){}

        ~Server_Event_Sender(){}

        void run() override;

        void cerrar(){
            this->corriendo = false;
        }
    private:
        BlockingQueue<Actualizacion*>& actualizaciones;
        Protocolo protocolo;
        bool corriendo; // deberian ser atomic??
};

#endif
