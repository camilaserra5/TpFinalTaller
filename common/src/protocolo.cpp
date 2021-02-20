#include "../include/protocolo.h"

Protocolo::Protocolo(Socket socket) : socket(std::move(socket)) {}

Protocolo::~Protocolo() {};


void Protocolo::enviar(std::vector<char> &informacion) {
    unsigned int size = htonl(informacion.size());
    char number_str[4];
    memcpy(number_str, &size, 4);
    socket.enviar(number_str, 4);
    std::string buffer(informacion.begin(), informacion.end());
    socket.enviar(buffer.c_str(), buffer.size());
    //std::cout << "termine de enviar";
}

std::vector<char> Protocolo::recibir_aux() {
  char length_str[4];
  socket.recibir(length_str, 4);

  unsigned int *buf = (unsigned int *) length_str;
  unsigned int length = ntohl(*buf);
  std::vector<char> informacion(length);

  //informacion.resize(length);
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
    buf = (uint32_t *) number;
    idx+=4;
    int idJugador = ntohl(*buf);
    sub = std::vector<char>(&informacion[idx], &informacion[idx + 4]);
    memcpy(number, sub.data(), 4);
    buf = (uint32_t *) number;
    int idAccion = ntohl(*buf);

    if (idAccion == static_cast<int>(Accion::ataque)) {
      //  std::cerr << "COMANDO ATAQUE\n";
        return new Ataque(idJugador);
    } else if (idAccion == static_cast<int>(Accion::aperturaDePuerta)) {
      //  std::cerr << "COMANDO ABRIR PUERTA\n";
        return new AperturaDePuerta(idJugador);
    } else if(idAccion == static_cast<int>(Accion::cambioDeArma)){
        //std::cerr << "COMANDO CAMBIO DE ARMA";
        return new CambioDeArma(idJugador);
    } else {
        Accion accion;
        if (idAccion == static_cast<int>(Accion::rotarDerecha)) {
        //  std::cerr << "COMANDO ROT DERECHA\n";
            accion = Accion::rotarDerecha;
        } else if (idAccion == static_cast<int>(Accion::rotarIzquierda)) {
        //  std::cerr << "COMANDO ROT izq\n";

            accion = Accion::rotarIzquierda;
        } else if (idAccion == static_cast<int>(Accion::moverArriba)) {
        //  std::cerr << "COMANDO mov arr\n";

            accion = Accion::moverArriba;
        } else {
        //  std::cerr << "COMANDO mov abajo num: " << idAccion << "\n";

            accion = Accion::moverAbajo;
        }
        return new Movimiento(idJugador, accion);
    }
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
        return new Balas(posicion, 0, idTipo);
    } else if (idTipo == ObjetosJuego::obtenerTipoPorNombre("comida").getType()) {
        return new Comida(posicion, idTipo);
    } else if (idTipo == ObjetosJuego::obtenerTipoPorNombre("kitsMedicos").getType()) {
        return new KitsMedicos(posicion, idTipo);
    } else if (idTipo == ObjetosJuego::obtenerTipoPorNombre("llave").getType()) {
        return new Llave(posicion, idTipo);
    } else if (idTipo == ObjetosJuego::obtenerTipoPorNombre("sangre").getType()) {
        return new Sangre(posicion, idTipo);
    } else if (idTipo == ObjetosJuego::obtenerTipoPorNombre("tesoro").getType()) {
        return new Tesoro(idTipo, ObjetosJuego::obtenerTipoPorNombre("tesoro"), 0, posicion);
    }
    return NULL;//CHEQUEAR ESTE NULL EN LA FUNCION Q LLAMA A ESTA FUNCION
}


void Protocolo::cerrar() {
    this->socket.cerrar();
}
