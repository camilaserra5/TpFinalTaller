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
    Server_Event_Sender *enviador;
    Server_Event_Receiver *recibidor;
    int id;

    void procesar_pedido();

public:
    ThClient(Socket &&un_socket, std::string rutaMapas,
             std::map<std::string, std::string> &mapas, int id);

    Comando *obtenerComandoInicial(std::vector<char> info);

    void enviarIdJugador();

    void agregarColaEventos(ProtectedQueue<Comando *> &cola_comandos);

    void run() override;

    bool is_dead();

    void stop();

    int getId() {
        return this->id;
    }

    void enviar_actualizaciones(std::vector<Actualizacion *> actualizaciones);

    ~ThClient();
};

#endif /*THCLIENT_H*/
