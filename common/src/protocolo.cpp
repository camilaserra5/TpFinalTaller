#include "../include/protocolo.h"

Protocolo::Protocolo(Socket socket) : socket(std::move(socket)) {}

Protocolo::~Protocolo() {}

void Protocolo::enviar(std::vector<char> &informacion) {
    unsigned int size = htonl(informacion.size());
    char number_str[4];
    memcpy(number_str, &size, 4);
    socket.enviar(number_str, 4);
    std::string buffer(informacion.begin(), informacion.end());
    socket.enviar(buffer.c_str(), buffer.size());
}

std::vector<char> Protocolo::recibir_aux() {
    char length_str[4];
    socket.recibir(length_str, 4);

    unsigned int *buf = (unsigned int *) length_str;
    unsigned int length = ntohl(*buf);
    std::vector<char> informacion(length);

    socket.recibir(informacion.data(), length);
    return informacion;
}

std::vector<char> Protocolo::recibir() {
    std::vector<char> informacion = recibir_aux();
    return informacion;
}

Comando *Protocolo::deserializarComando(std::vector<char> &informacion) {
    std::vector<char> sub(4);
    int idx = 0;
    char number[4];
    sub = std::vector<char>(&informacion[idx], &informacion[idx + 4]);
    memcpy(number, sub.data(), 4);
    uint32_t *buf = (uint32_t *) number;
    idx += 4;
    int idJugador = ntohl(*buf);
    sub = std::vector<char>(&informacion[idx], &informacion[idx + 4]);
    memcpy(number, sub.data(), 4);
    buf = (uint32_t *) number;
    int idAccion = ntohl(*buf);
    if (idAccion == static_cast<int>(Accion::ataque)) {
        return new Ataque(idJugador);
    } else if (idAccion == static_cast<int>(Accion::aperturaDePuerta)) {
        return new AperturaDePuerta(idJugador);
    } else if (idAccion == static_cast<int>(Accion::cambioDeArma)) {
        return new CambioDeArma(idJugador);
    } else if (idAccion == static_cast<int>(Accion::rotarDerecha)) {
        return new Movimiento(idJugador, Accion::rotarDerecha);
    } else if (idAccion == static_cast<int>(Accion::rotarIzquierda)) {
        return new Movimiento(idJugador, Accion::rotarIzquierda);
    } else if (idAccion == static_cast<int>(Accion::moverArriba)) {
        return new Movimiento(idJugador, Accion::moverArriba);
    } else if (idAccion == static_cast<int>(Accion::moverAbajo)) {
        return new Movimiento(idJugador, Accion::moverAbajo);
    }
    return nullptr;
}


Item *Protocolo::deserializarItem(std::vector<char> &informacion) {
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&informacion[idx], &informacion[idx + 4]);
    char number[4];
    memcpy(number, sub.data(), 4);
    uint32_t *buf = (uint32_t *) number;
    int idTipo = ntohl(*buf);

    Posicion posicion;
    std::vector<char> posicionSerializado(informacion.begin() + 4,
                                          informacion.end());
    posicion.deserializar(posicionSerializado);
    if (idTipo == ObjetosJuego::obtenerTipoPorNombre("balas").getType()) {
        return new Balas(posicion, 0, idTipo,0);
    } else if (idTipo == ObjetosJuego::obtenerTipoPorNombre("comida").getType()) {
        return new Comida(posicion, idTipo,0,0);
    } else if (idTipo == ObjetosJuego::obtenerTipoPorNombre("kitsMedicos").getType()) {
        return new KitsMedicos(posicion, idTipo,0,0);
    } else if (idTipo == ObjetosJuego::obtenerTipoPorNombre("llave").getType()) {
        return new Llave(posicion, idTipo);
    } else if (idTipo == ObjetosJuego::obtenerTipoPorNombre("sangre").getType()) {
        return new Sangre(posicion, idTipo,0,0);
    } else if (idTipo == ObjetosJuego::obtenerTipoPorNombre("tesoro").getType()) {
        return new Tesoro(idTipo, ObjetosJuego::obtenerTipoPorNombre("tesoro"), 0, posicion);
    }
    return NULL;
}


void Protocolo::cerrar() {
    this->socket.cerrar();
}
