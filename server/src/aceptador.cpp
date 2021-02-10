#include "../include/aceptador.h"
#include <utility>
#include <vector>
#include "socket_error_aceptar.h"

Aceptador::Aceptador(Socket &un_socket, ManejadorPartidas *manejadorPartidas) :
        socket_listener(un_socket), manejadorPartidas(manejadorPartidas) {}

static void liberar_terminados(std::vector<ThClient *> &clientes) {
    std::vector<ThClient *> temp;
    std::vector<ThClient *>::iterator iterador_clientes = clientes.begin();
    while (iterador_clientes != clientes.end()) {
        if ((*iterador_clientes)->is_dead()) {
            (*iterador_clientes)->join();
            delete (*iterador_clientes);
        } else {
            temp.push_back(*iterador_clientes);
        }
        ++iterador_clientes;
    }
    clientes.swap(temp);
}

void Aceptador::run() {
    bool socket_es_valido = true;
    while (socket_es_valido) {
        try {
            std::cerr << "acepto cliente";
            Socket peer = this->socket_listener.aceptar();
            std::cerr << "agrego cliente";
            clientes.push_back(new ThClient(std::move(peer), this->manejadorPartidas));
            clientes.back()->start();
            liberar_terminados(clientes);
        } catch (SocketErrorAceptar &exc) {
            socket_es_valido = false;
        }
    }
    this->cerrar();
}

void Aceptador::cerrar() {
  this->socket_listener.cerrar();
    for (std::size_t i = 0; i < clientes.size(); i++) {
        clientes.at(i)->stop();
        clientes.at(i)->join();
        delete (clientes.at(i));
    }
}
