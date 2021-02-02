#include "../include/manejador_eventos.h"
#include "../include/player.h"

#include "comandos/movimiento.h"
#include "comandos/ataque.h"
#include "comandos/aperturaDePuerta.h"
#include <iostream>

ManejadorEventos::ManejadorEventos(int& idJugador, BlockingQueue<Comando*>& eventos):
    idJugador(idJugador),
    eventos(eventos),
    corriendo(true),
    sonidoAmbiente("../resources/sonidos/wolfenstein-3d-title-theme.wav"){}

ManejadorEventos::~ManejadorEventos(){}

void ManejadorEventos::run(){
    SDL_Event evento;
    while(this->corriendo){

        if (SDL_PollEvent(&evento)){;
              detectarEventos(evento);
          }
          std::chrono::milliseconds duration(100);
          std::this_thread::sleep_for(duration);
    }
}

void ManejadorEventos::crearMovimiento(Accion direccion){
    Comando* movimiento = new Movimiento(this->idJugador, direccion);
    this->eventos.push(movimiento);
}

void ManejadorEventos::crearAtaque(){
    Comando* ataque = new Ataque(this->idJugador);
    this->eventos.push(ataque);
}

void ManejadorEventos::crearAperturaDePuerta(){
    Comando* apertura = new AperturaDePuerta(this->idJugador);
    this->eventos.push(apertura);
}

void ManejadorEventos::detectarEventos(SDL_Event& evento){
      switch (evento.type) {
          case SDL_KEYDOWN:
              std::cout << "tecla preionada\n";
              switch( evento.key.keysym.sym ){
                  // aca mandariamos la informacion o crearimos el evento;
                      case SDLK_LEFT:         // x, y, vida, angulo;

                          crearMovimiento(Accion::rotarIzquierda);
                        //  player.settear_estado(-1, 0, 100, 50); // esto es para probar que se cambia el estado
                                                                // y se renderiza la imagen;
                            std::cout << "me roto a izquierda\n";
                          break;
                      case SDLK_RIGHT:
                          crearMovimiento(Accion::rotarDerecha);
                        //  player.settear_estado(1, 0, 100, 50);
                        std::cout << "me roto a derecha\n";
                          break;
                      case SDLK_UP:
                          crearMovimiento(Accion::moverArriba);
                        //  player.settear_estado(0, 1, 100, 50);
                        std::cout << "me muevo arriba\n";
                          break;
                      case SDLK_DOWN:
                          crearMovimiento(Accion::moverAbajo);
                        //  player.settear_estado(0, -1, 100, 50);
                        std::cout << "me muevo abajo\n";
                          break;
                      case SDLK_SPACE:
                          sonidoAmbiente.play(100);
                        std::cout << "ESPACIO\n";
                          break;
                      case SDLK_PERIOD: //tecla "."
                        crearAtaque();
                        break;
              }
              break;
          case SDL_KEYUP:
              std::cout << "tecla despresionada\n";
              if (evento.key.keysym.sym == SDLK_PERIOD){
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

void ManejadorEventos::stop(){
    this->corriendo = false;
}

bool ManejadorEventos::esta_vivo() {
    return this->corriendo;
}
