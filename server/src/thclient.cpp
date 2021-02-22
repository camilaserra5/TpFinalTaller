#include "../include/thclient.h"
#include "socket.h"
#include <string>
#include <utility>
#include <socket_error.h>
#include "comandos/crearPartida.h"
#include "comandos/unirseAPartida.h"

#define BUF_TAM 50
#define ERROR -1
#define SOCKET_CERRADO 0

ThClient::ThClient(Socket &&un_socket, std::string rutaMapas,
                   std::map<std::string, std::string> &mapas, int id) :
        protocolo(new Protocolo(std::move(un_socket))),
        rutaMapas(std::move(rutaMapas)),
        mapas(mapas),
        keep_talking(true),
        is_running(true),
        id(id) {}

Comando *ThClient::obtenerComandoInicial(std::vector<char> partidas) {
    this->protocolo->enviar(partidas);
    std::vector<char> serializado = this->protocolo->recibir();
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    char number[4];
    memcpy(number, sub.data(), 4);
    auto buf = (uint32_t *) number;
    int idAccion = ntohl(*buf);
    std::string nombre_partida;

    if (idAccion == static_cast<int>(Accion::unirseAPartida)) {
        std::cout << "UNIRSE" << std::endl;
        auto unirseAPartida = new UnirseAPartida();
        unirseAPartida->deserializar(serializado);
        return unirseAPartida;
    }
    if (idAccion == static_cast<int>(Accion::crearPartida)) {
        std::cout << "CREAR" << std::endl;
        auto crearPartida = new CrearPartida();
        crearPartida->deserializar(serializado);
        return crearPartida;
    }
    isDead = true;
    return nullptr;
}

void ThClient::enviarIdJugador() {
    std::vector<char> ret(4);
    unsigned int size = htonl(this->id);
    memcpy(ret.data(), &size, 4);
    this->protocolo->enviar(ret);
}

void ThClient::agregarColaEventos(ProtectedQueue<Comando *> &cola_comandos) {
    this->enviador = new Server_Event_Sender(protocolo);
    this->recibidor = new Server_Event_Receiver(cola_comandos, protocolo);
}

ThClient::~ThClient() {
    delete this->protocolo;
    delete this->enviador;
    delete this->recibidor;
}

void ThClient::stop() {
    if (this->enviador->estaCorriendo()) {
        this->enviador->cerrar();
        this->enviador->join();

    } else if (this->recibidor->estaCorriendo()) {
        this->recibidor->cerrar();
        this->recibidor->join();
    }
    isDead = true;
}

bool ThClient::is_dead() {
    if (isDead)
        return true;
    try {
        if (this->enviador != nullptr && this->recibidor != nullptr) {
            return !this->enviador->estaCorriendo() || !this->recibidor->estaCorriendo();
        }
    } catch (...) {
        std::cerr << "error " << std::endl;
    }
    return false;
}

void ThClient::enviar_actualizaciones(std::vector<Actualizacion *> actualizaciones) {
    this->enviador->enviar_actualizaciones(actualizaciones);
}

void ThClient::run() {
    try {
        std::chrono::milliseconds duration(100);
        std::this_thread::sleep_for(duration);
        std::vector<char> empece(4);
        unsigned int size = htonl(static_cast<int>(Accion::empezoPartida));
        memcpy(empece.data(), &size, 4);
        this->protocolo->enviar(empece);
        std::this_thread::sleep_for(duration);
        this->enviador->start();
        this->recibidor->start();
    } catch (SocketError &e) {
        isDead = true;
        if (this->enviador->estaCorriendo()) {
            this->enviador->cerrar();
        } else if (this->recibidor->estaCorriendo()) {
            this->recibidor->cerrar();
        }
    }

}
