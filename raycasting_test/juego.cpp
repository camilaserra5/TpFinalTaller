#include "juego.h"
#include "rayo.h"
#include "map.h"
#include <iostream>
#include <thread>


#define EXITO 0

#define ANCHO_CANVAS 800
#define ALTURA_CANVAS 320
#define TAMANIO_FILA 20
#define TAMANIO_COLUMNA 20
#define LARGO_PROYECTOR ANCHO_CANVAS
#define ANCHO_PROYECTOR 20


void Juego::inicializar(const char *titulo, int xpos, int ypos, int ancho, int alto, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == EXITO) {
        this->ventana = SDL_CreateWindow(titulo, xpos, ypos, ancho, alto, flags);
        this->render = SDL_CreateRenderer(this->ventana, -1, 0);
        SDL_SetRenderDrawColor(this->render, 157, 97, 70, 255);
        SDL_RenderClear(this->render);
        this->corriendo = true;
    } else {
        this->corriendo = false;
    }
    this->texturaInferior = new Textura("../../client_src/resources/images/ParteInferior.png", this->render);
    ObjetoJuego* enemigo = new ObjetoJuego("../../client_src/resources/images/Guard.png", this->render, /*50, 50,*/0,0,78,78/*100,100*/);//poner constantes
    this->objetos.push_back(enemigo);
}

void Juego::handleEvents() {
    SDL_Event evento;
    SDL_PollEvent(&evento);
    switch (evento.type) {
        case SDL_QUIT:
            this->corriendo = false;
            break;
        default:
            break;
    }
}

void Juego::actualizar() {
    this->objetos.front()->actualizar();
}

void Juego::renderizar() {
    SDL_RenderClear(this->render);
    Lienzo posiciontexturaini(0, 0, 800, 40);
    Lienzo posiciontexturadest(0, 562, 800, 40);
    this->texturaInferior->renderizar(this->render, posiciontexturaini, posiciontexturadest);
    this->objetos.front()->renderizar();

    SDL_RenderDrawPoint(this->render, 400, 300); //Renders on middle of screen.
    SDL_RenderPresent(this->render);
}

void Juego::clean() {
    SDL_DestroyWindow(this->ventana);
    SDL_DestroyRenderer(this->render);
    SDL_Quit();
}

void Juego::raycasting(/*Map &mapa,Jugador &jugador*/){

  int mapa[TAMANIO_FILA][TAMANIO_COLUMNA] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                              {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                              {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                              {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                              {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                              {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                              {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                              {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                              {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                              {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                              {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                              {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                              {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                              {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                              {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                              {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                              {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                              {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                              {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                              {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                            };

            float posJugadorX, posJugadorY, alturaJugador;
            float anguloDeVista = 2 * acos(0.0) / 3;
            float anguloJugador = 2 * acos(0.0) / 3;
            int alturaParedProyectada = 0;
            int ladoCelda = ANCHO_CANVAS/TAMANIO_FILA - 10;//el -10 va para q dibuje alfo razzonable
            float anguloBarrido = 0;
            float anguloPorStripe = anguloDeVista / ANCHO_CANVAS;

            for (int i = 0; i <= ANCHO_CANVAS; i++) {
                Rayo rayo(anguloDeVista, ladoCelda, LARGO_PROYECTOR, anguloBarrido);
                float distancia = 0;
                if (rayo.verificarInterseccionHorizontal(mapa, distancia, anguloJugador)) {
                    alturaParedProyectada = (ladoCelda / distancia) * rayo.getDistanciaProyector();
                    std::cout << "la altura es: " << alturaParedProyectada << "\n";
                } else if (rayo.verificarInterseccionVertical(mapa, distancia, anguloJugador)) {
                    alturaParedProyectada = (ladoCelda / distancia) * rayo.getDistanciaProyector();
                    std::cout << "la altura es: " << alturaParedProyectada << "\n";
                }

                  double drawStart = round((ANCHO_CANVAS / 2) - (alturaParedProyectada / 2)) - 20;
                  double drawEnd = drawStart + alturaParedProyectada - 20;
                  SDL_RenderPresent(this->render);

                  SDL_SetRenderDrawColor(this->render, 255, 255, 255, SDL_ALPHA_OPAQUE);
                  SDL_RenderDrawLine(this->render, i, drawStart,i, drawEnd);

                  std::chrono::milliseconds duration(10);
                  std::this_thread::sleep_for(duration);//sin esto se vuelve loco
              anguloBarrido += anguloPorStripe;
            }
            SDL_SetRenderDrawColor(this->render, 157, 97, 70, 255);// deberia estar en atualizar

            SDL_RenderClear(this->render);

}
