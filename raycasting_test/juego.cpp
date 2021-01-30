#include "juego.h"

#define EXITO 0
#define TAMANIO_FILA 20
#define TAMANIO_COLUMNA 20
#define LARGO_PROYECTOR ANCHO_CANVAS
#define ANCHO_PROYECTOR 20
#define WOODEN_WALL_ROOT "../../editor/resources/wall2.jpg"
#define BLUE_STONE_WALL_ROOT "../../editor/resources/wall1.jpg"
#define GRAY_STONE_WALL_ROOT "../../editor/resources/wall3.jpg"

#include "SDL2/SDL_ttf.h"
#include <SDL2/SDL.h>

Juego::Juego(const std::string &titulo, int ancho, int alto, bool fullscreen, int idJugador, Jugador& jugador): jugador(jugador) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == EXITO) {


        if (TTF_Init() == -1) {
            printf("Failed to init TTF\n");
            exit(1);
        }

        this->ventana = new Ventana(titulo, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ancho, alto, flags);
        this->modelo = new Modelo(this->ventana, idJugador);
        modelo->inicializar();
        this->texturaInferior = new Textura("../../client/resources/images/ParteInferior.png",
                                            this->ventana->obtener_render());
        this->corriendo = true;
    } else {
        this->corriendo = false;
    }
}

void Juego::run() {
  Map mapa(20,20);
    try {
        this->clean();
        this->renderizar();
        this->raycasting(mapa,this->jugador);
        this->actualizar(/*1*/);
//deberia ir antes que renderizar para que se dibuje atras del mapa
        this->jugador.rotar(0.5 * acos(0.0));
    } catch (...) {
        this->corriendo = false;
    }

}

void Juego::actualizar(/*temporal int idArma*/) {
    this->ventana->actualizar();
}

void Juego::renderizar() {
    this->ventana->renderizar(this->texturaInferior);
    this->modelo->renderizar();
}

Juego::~Juego() {}

void Juego::clean() {
    this->ventana->limpiar();
    //this->corriendo = false;
}

void Juego::raycasting(Map &mapaa, Jugador &jugador) {

// x = fila / y = columna

  int mapa[TAMANIO_FILA][TAMANIO_COLUMNA] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                       /*1*/  {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                      /*2*/   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                     /*3*/    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    /*4*/     {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                   /*5*/      {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                                  /*6*/       {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                                  /*7*/       {1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1},
                                  /*8*/       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  /*9*/       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  /*10*/      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  /*11*/      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                /*12*/        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                            /*13*/            {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
                            /*14*/            {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    /*15*/    {1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    /*16*/    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                      /*17*/  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                      /*18*/  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                      /*19*/  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                            /* 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 */
                                            };
            SDL_Renderer *render = this->ventana->obtener_render();

            Textura* wall = new Textura(GRAY_STONE_WALL_ROOT,render);
            double rangoDeVista = 2 * acos(0.0) / 3;//60 grados
            unsigned int alturaParedProyectada = 0;
            int ladoCelda = ANCHO_CANVAS/TAMANIO_FILA;
            double anguloPorStripe = rangoDeVista / ANCHO_CANVAS;
            double anguloJugador = jugador.getAnguloDeVista();
            double anguloRayo = anguloJugador - (rangoDeVista / 2);
            Posicion& posJugador = jugador.getPosicion();

            for (int i = ANCHO_CANVAS - 1; i >= 0; i--) {
                double distancia = 0;
                int drawStart,drawEnd;
                Rayo rayo(rangoDeVista, ladoCelda, LARGO_PROYECTOR, anguloRayo,posJugador);
                rayo.verificarInterseccion(mapa,distancia,jugador);
                alturaParedProyectada = (ladoCelda / distancia) * rayo.getDistanciaProyector();

                //  if (alturaParedProyectada > 600){
                  //    drawStart = 600 - 1;
                  //    drawEnd = 0;
                //  }else{
                    drawStart = floor((ANCHO_CANVAS / 2) - (alturaParedProyectada / 2)) - 20;
                    drawEnd = drawStart + alturaParedProyectada - 20;
            //      }
                  SDL_Rect wallDimension;
                  wallDimension.x = rayo.getOffset() % 64;
                  wallDimension.y = 0;
                  wallDimension.w = 1;
                  wallDimension.h = alturaParedProyectada;

                  SDL_Rect wallDest;
                  wallDest.x = i;
                  wallDest.y = drawStart;
                  wallDest.w = 1;
                  wallDest.h = drawEnd - drawStart;
                  wall->renderizar(&wallDimension,wallDest);
                  this->ventana->actualizar();

                  std::chrono::milliseconds duration(20);
                  std::this_thread::sleep_for(duration);
                  anguloRayo += anguloPorStripe;
            }
            //SDL_SetRenderDrawColor(render, 157, 97, 70, 255);// deberia estar en atualizar
            delete wall;
}
