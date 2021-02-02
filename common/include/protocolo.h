#ifndef _PROTOCOLO_H
#define _PROTOCOLO_H


#include "socket.h"

#include "comandos/ataque.h"
#include "comandos/movimiento.h"
#include <iostream>

#define TAMANIO 100

class Protocolo {
public:
    Protocolo(Socket socket) : socket(std::move(socket)) {}

    ~Protocolo() {};

    void enviar(std::stringstream &informacion) {
        std::string buffer = informacion.str();
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

    Comando *deserializarComando(std::stringstream &informacion) {

        if (informacion.str()[0] == static_cast<int>(Accion::ataque)) {
            // verificar temas de los bytes;
            // byte 1 tipo de accion , byte 2 id jugador, byte 3 tipo de ivimiento;
            return new Ataque(informacion.str()[1]);
        } else {
            Accion accion;
            if (informacion.str()[2] == static_cast<int>(Accion::rotarDerecha)) {
                accion = Accion::rotarDerecha;
            } else if (informacion.str()[2] == static_cast<int>(Accion::rotarIzquierda)) {
                accion = Accion::rotarIzquierda;
            } else if (informacion.str()[2] == static_cast<int>(Accion::moverArriba)) {
                accion = Accion::moverArriba;
            } else {
                accion = Accion::moverAbajo;
            }
            int id = informacion.str()[1];
            return new Movimiento(id, accion);
        }
    }

private:
    Socket socket;
};

#endif
