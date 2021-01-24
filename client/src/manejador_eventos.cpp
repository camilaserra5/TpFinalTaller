#include "../include/manejador_eventos.h"
#include "../include/player.h"

#include "comandos/movimiento.h"
#include <iostream>

ManejadorEventos::ManejadorEventos(int idJugador, BlockingQueue<Comando*>& eventos):
    idJugador(idJugador),
    eventos(eventos),
    corriendo(true){}

ManejadorEventos::~ManejadorEventos(){}

void ManejadorEventos::run(){
    SDL_Event evento;
    while(this->corriendo){

        if (SDL_PollEvent(&evento)){;
              detectarEventos(evento);
          }
          std::chrono::milliseconds duration(1000);
          std::this_thread::sleep_for(duration);
    }
}

void ManejadorEventos::crearMovimiento(Accion direccion){
    Comando* movimiento = new Movimiento(this->idJugador, direccion);
    this->eventos.push(movimiento);
}
void ManejadorEventos::detectarEventos(SDL_Event& evento){
      switch (evento.type) {
          case SDL_KEYDOWN:
              std::cout << "tecla preionada\n";
              switch( evento.key.keysym.sym ){
                  // aca mandariamos la informacion o crearimos el evento;
                      case SDLK_LEFT:         // x, y, vida, angulo;

                          crearMovimiento(Accion::moverIzquierda);
                        //  player.settear_estado(-1, 0, 100, 50); // esto es para probar que se cambia el estado
                                                                // y se renderiza la imagen;
                            std::cout << "me muevo a izquierda\n";
                          break;
                      case SDLK_RIGHT:
                          crearMovimiento(Accion::moverDerecha);
                        //  player.settear_estado(1, 0, 100, 50);
                        std::cout << "me muevo a derecha\n";
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
              }
              break;
          case SDL_KEYUP:
              std::cout << "tecla despresionada\n";
              break;
          case SDL_QUIT:
              this->corriendo = false;
              break;
          default:
              break;
      }
}

void ManejadorEventos::stop(){
    this->corriendo = false;
}
