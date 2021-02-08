#include "../include/thclient.h"
#include "socket.h"
#include <string>
#include <utility>
#include "comandos/crearPartida.h"
#include "comandos/unirseAPartida.h"

#define BUF_TAM 50
#define ERROR -1
#define SOCKET_CERRADO 0

ThClient::ThClient(Socket &&un_socket, ManejadorPartidas *manejadorDePartidas) :
        protocolo(new Protocolo(std::move(un_socket))),
        keep_talking(true),
        is_running(true),
        manejadorDePartidas(manejadorDePartidas) {}

ThClient::~ThClient() {
    this->join();
}

void ThClient::stop() {
    this->keep_talking = false;
    this->protocolo->cerrar();
}

void ThClient::procesar_pedido() {
    std::vector<char> serializado = this->protocolo->recibir();
    int idJugador = -1;
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    char number[4];
    memcpy(number, sub.data(), 4);
    uint32_t *buf = (uint32_t *) number;
    int idAccion = ntohl(*buf);
    std::string nombre_partida;

    if (idAccion == static_cast<int>(Accion::unirseAPartida)) {
        std::cout << "UNIRSE" << std::endl;
        UnirseAPartida unirseAPartida;
        unirseAPartida.deserializar(serializado);
        idJugador = this->manejadorDePartidas->agregarClienteAPartida(unirseAPartida.getNombreJugador(),
                                                                      unirseAPartida.getNombrePartida(), this->protocolo);
    } else {
        std::cout << "CREAR" << std::endl;
        CrearPartida crearPartida;
        crearPartida.deserializar(serializado);
        idJugador = this->manejadorDePartidas->crearPartida(crearPartida.getNombreJugador(),
                                                            crearPartida.getCantJugadores(),
                                                            crearPartida.getNombrePartida(),
                                                            crearPartida.getRutaArchivo(),
                                                            this->protocolo);
    }
    std::vector<char> ret(4);
    unsigned int size = htonl(idJugador);
    memcpy(ret.data(), &size, 4);
    protocolo->enviar(ret);

}

bool ThClient::is_dead() {
    return !this->is_running;
}

void ThClient::run() {
    std::cerr << "envio partidas\n";
    std::vector<char> partidas = this->manejadorDePartidas->serializar();
    for (int i = 0; i < partidas.size(); i++) {
        std::cerr << partidas[i];
    }
    std::cerr << "\nfin envio partidas";
    //  reinterpret_cast<char *>(partidas.data()), partidas.size()
    this->protocolo->enviar(partidas);
    procesar_pedido();
    while (this->keep_talking) {

/*
        std::string mensaje = this->mensaje_cliente.str();
        if (mensaje.size() != 0) {
            mensaje.erase(mensaje.size() - 1);
        }


        this->keep_talking = false;*/
        //  this->keep_talking = false;
    }
    this->stop();
}
