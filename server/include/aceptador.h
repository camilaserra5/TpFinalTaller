#ifndef ACEPTADOR_H
#define ACEPTADOR_H

#include <string>
#include <vector>
#include "thread.h"
#include "socket.h"
#include "../include/thclient.h"

class Aceptador : public Thread {
private:
    Socket &socket_listener;
    std::vector<ThClient *> clientes;
    std::string rutaMapas;
    std::map<std::string, std::string> mapas;
    ProtectedQueue<Comando *> cola_comandos;
    int generadorDeId = 100;

    int obtenerIdParaJugador();

public:
    Aceptador(Socket &un_socket, std::string rutaMapas, std::map<std::string, std::string> mapas);

    void run() override;

    void cerrar();

    ~Aceptador() { this->join(); }
};

#endif /*ACEPTADOR_H*/
