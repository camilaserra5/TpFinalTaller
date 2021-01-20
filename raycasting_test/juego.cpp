#include "juego.h"
#include "rayo.h"
#include <iostream>
#include <thread>


#define EXITO 0
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
    this->texturaInferior = new Textura("../../client/resources/images/ParteInferior.png", this->render);
    ObjetoJuego *enemigo = new ObjetoJuego("../../client/resources/images/Guard.png", this->render,  /*50, 50,*/0, 0,
                                           78, 78/*100,100*/);
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

/*
void Juego::handleEvents(Player& player) {
    SDL_Event evento;
    while (SDL_PollEvent(&evento)){

      switch (evento.type) {
        case SDL_KEYDOWN:
            std::cout << "tecla preionada\n";
            switch( evento.key.keysym.sym ){
                // aca mandariamos la informacion o crearimos el evento;
                    case SDLK_LEFT:         // x, y, vida, angulo;
                        player.settear_estado(-1, 0, 100, 50); // esto es para probar que se cambia el estado
                                                              // y se renderiza la imagen;
                        break;
                    case SDLK_RIGHT:
                        player.settear_estado(1, 0, 100, 50);
                        break;
                    case SDLK_UP:
                        player.settear_estado(0, 1, 100, 50);
                        break;
                    case SDLK_DOWN:
                        player.settear_estado(0, -1, 100, 50);
                        break;
                    default:
                        break;
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
*/
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

void Juego::raycasting(Map &mapaa,Jugador &jugador){

// x = fila / y = columna

  int mapa[TAMANIO_FILA][TAMANIO_COLUMNA] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                       /*1*/  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                      /*2*/   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                     /*3*/    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    /*4*/     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                   /*5*/      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  /*6*/       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  /*7*/       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  /*8*/       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  /*9*/       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  /*10*/      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  /*11*/      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
                                /*12*/        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
                            /*13*/            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
                            /*14*/            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
                                    /*15*/    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
                                    /*16*/    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                      /*17*/  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                      /*18*/  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                      /*19*/  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                            /* 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 */
                                            };

            float rangoDeVista = 2 * acos(0.0) / 3;//60 grados
            unsigned int alturaParedProyectada = 0;
            int ladoCelda = ANCHO_CANVAS/TAMANIO_FILA;//el -10 va para q dibuje alfo razzonable
            float anguloPorStripe = rangoDeVista / ANCHO_CANVAS;
            float anguloJugador = jugador.getAnguloDeVista();
            float anguloRayo = anguloJugador - (rangoDeVista / 2);

            for (int i = ANCHO_CANVAS - 1; i >= 0; i--) {
                float distancia = 0;
                Rayo rayo(rangoDeVista, ladoCelda, LARGO_PROYECTOR, anguloRayo);

                if (rayo.verificarInterseccion(mapa,distancia,jugador)){
                  alturaParedProyectada = (ladoCelda / distancia) * rayo.getDistanciaProyector();
                }
                  double drawStart = floor((ANCHO_CANVAS / 2) - (alturaParedProyectada / 2)) - 20;
                  double drawEnd = drawStart + alturaParedProyectada - 20;

                  SDL_RenderPresent(this->render);
                  SDL_SetRenderDrawColor(this->render, 255, 255, 255, SDL_ALPHA_OPAQUE);
                  SDL_RenderDrawLine(this->render, i, drawStart,i, drawEnd);

                  std::chrono::milliseconds duration(10);
                  std::this_thread::sleep_for(duration);

                  anguloRayo += anguloPorStripe;
            }
            std::cout << "==================termina=========================\n";
            SDL_SetRenderDrawColor(this->render, 157, 97, 70, 255);// deberia estar en atualizar

            SDL_RenderClear(this->render);

}
