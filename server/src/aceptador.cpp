#include "../include/aceptador.h"
#include "socket_error_aceptar.h"
#include "../include/thclient.h"
#include <utility>
#include <algorithm>
#include <vector>
#include "../include/manejadorPartidas.h"

Aceptador::Aceptador(Socket &un_socket, std::string rutaMapas, std::map<std::string, std::string> mapas,ConfiguracionPartida configuracion):
        socket_listener(un_socket), rutaMapas(rutaMapas), mapas(mapas), configuracionPartida(configuracion){}

static void liberar_terminados(std::vector<ThClient *> &clientes) {
    try {
        std::vector<ThClient *> temp;
        std::vector<ThClient *>::iterator iterador_clientes = clientes.begin();
        while (iterador_clientes != clientes.end()) {
            if ((*iterador_clientes)->is_dead()) {
                (*iterador_clientes)->join();
                //delete (*iterador_clientes);
            } else {
                temp.push_back(*iterador_clientes);
            }
            ++iterador_clientes;
        }
        clientes.swap(temp);
    } catch (...) {
        std::cerr << "error";
    }
}

void Aceptador::run() {
    ManejadorPartidas manejadorPartidas(this->rutaMapas, this->mapas,this->configuracionPartida);
    bool socket_es_valido = true;
    while (socket_es_valido) {
        try {
            std::cerr << "estoy en acpetador\n";
            Socket peer = this->socket_listener.aceptar();
            clientes.push_back(new ThClient(std::move(peer), this->rutaMapas,
                                            this->mapas, this->obtenerIdParaJugador()));

            manejadorPartidas.cerrarPartidas();
            manejadorPartidas.nuevoCliente(clientes.back());
            liberar_terminados(clientes);
        } catch (SocketErrorAceptar &exc) {
            socket_es_valido = false;
        }
    }
    this->socket_listener.cerrar();
    this->cerrar();
}

void Aceptador::cerrar() {
    for (std::size_t i = 0; i < clientes.size(); i++) {
        clientes.at(i)->stop();
        clientes.at(i)->join();
        delete (clientes.at(i));
    }
}

int Aceptador::obtenerIdParaJugador() {
    int id = this->generadorDeId;
    this->generadorDeId += 1;
    return id;
}
