#ifndef _PROTOCOLO_H
#define _PROTOCOLO_H


#include "socket.h"

#include "comandos/ataque.h"
#include "comandos/movimiento.h"
#include "comandos/aperturaDePuerta.h"
#include <iostream>

#define TAMANIO 100

class Protocolo {
public:
    Protocolo(Socket socket) : socket(std::move(socket)) {}

    ~Protocolo() {};

    void enviar(std::vector<char> &informacion) {
        std::string buffer(informacion.begin(), informacion.end());
        socket.enviar(buffer.c_str(), buffer.size());
    }

    std::stringstream recibir_aux() {
        char buffer[TAMANIO];
        std::stringstream informacion;
        int cant_recibidos = socket.recibir(buffer, TAMANIO);
        while (cant_recibidos > 0) {
            informacion.write(buffer, cant_recibidos);
            cant_recibidos = socket.recibir(buffer, TAMANIO);
        }
        return informacion;
    }

    std::vector<char> recibir() {
        std::string someString = recibir_aux().str();
        std::vector<char> informacion(someString.begin(), someString.end());
        return informacion;
    }

    Comando *deserializarComando(std::vector<char> &informacion) {

        if (informacion[1] == static_cast<int>(Accion::ataque)) {

            return new Ataque((int)informacion[0]);
        } else if (informacion[1] == static_cast<int>(Accion::aperturaDePuerta)){
            return new AperturaDePuerta((int)informacion[0]);
        } else {
            Accion accion;
            if (informacion[1] == static_cast<int>(Accion::rotarDerecha)) {
                accion = Accion::rotarDerecha;
            } else if (informacion[1] == static_cast<int>(Accion::rotarIzquierda)) {
                accion = Accion::rotarIzquierda;
            } else if (informacion[1] == static_cast<int>(Accion::moverArriba)) {
                accion = Accion::moverArriba;
            } else {
                accion = Accion::moverAbajo;
            }
            int id = (int)informacion[0];
            return new Movimiento(id, accion);
        }
    }

private:
    Socket socket;
};

#endif
