#include "../include/manejador_eventos.h"
#include "../include/player.h"

#include "comandos/movimiento.h"
#include "comandos/ataque.h"
#include "comandos/aperturaDePuerta.h"
#include "comandos/cambioDeArma.h"
#include <iostream>

ManejadorEventos::ManejadorEventos(int &idJugador, BlockingQueue<Comando *> &eventos) :
        idJugador(idJugador),
        eventos(eventos),
        corriendo(true),
        sonidoAmbiente("../../client/resources/sonidos/wolfenstein-3d-title-theme.wav") {}

ManejadorEventos::~ManejadorEventos() {}

void ManejadorEventos::run() {
    SDL_Event evento;
    while (this->corriendo) {

        if (SDL_PollEvent(&evento)) { 
            detectarEventos(evento);
        }
        std::chrono::milliseconds duration(100);
        std::this_thread::sleep_for(duration);
    }
}

void ManejadorEventos::crearMovimiento(Accion direccion) {
    Comando *movimiento = new Movimiento(this->idJugador, direccion);
    this->eventos.push(movimiento);
    //delete movimiento;
}

void ManejadorEventos::crearAtaque() {
    Comando *ataque = new Ataque(this->idJugador);
    this->eventos.push(ataque);
    //delete ataque;
}

void ManejadorEventos::crearAperturaDePuerta() {
    Comando *apertura = new AperturaDePuerta(this->idJugador);
    this->eventos.push(apertura);
    //delete apertura;
}

void ManejadorEventos::crearCambioDeArma() {
    Comando *cambio = new CambioDeArma(this->idJugador);
    this->eventos.push(cambio);
    //delete apertura;
}

void ManejadorEventos::detectarEventos(SDL_Event &evento) {
    switch (evento.type) {
        case SDL_KEYDOWN:
            switch (evento.key.keysym.sym) {
                // aca mandariamos la informacion o crearimos el evento;
                case SDLK_LEFT:         // x, y, vida, angulo;
                    crearMovimiento(Accion::rotarIzquierda);
                    break;
                case SDLK_RIGHT:
                    crearMovimiento(Accion::rotarDerecha);
                    break;
                case SDLK_UP:
                    crearMovimiento(Accion::moverArriba);
                    break;
                case SDLK_DOWN:
                    crearMovimiento(Accion::moverAbajo);
                    break;
                case SDLK_m:
                    sonidoAmbiente.play(100);
                    break;
                case SDLK_PERIOD:
                    crearAtaque();
                    break;
                case SDLK_a:
                    crearCambioDeArma();
                    break;
            }
            break;
        case SDL_KEYUP:
            if (evento.key.keysym.sym == SDLK_PERIOD) {
                // dejo de disparar;
            }
            break;
        case SDL_QUIT:
            this->stop();
            break;
        case SDLK_SPACE:
            crearAperturaDePuerta();
            break;
        default:
            break;
    }
}

void ManejadorEventos::stop() {
    this->corriendo = false;
}

bool ManejadorEventos::esta_vivo() {
    return this->corriendo;
}
