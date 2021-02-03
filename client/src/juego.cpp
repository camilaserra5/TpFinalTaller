#include "../include/juego.h"

#define EXITO 0
#define TAMANIO_FILA 20
#define TAMANIO_COLUMNA 20
#define LARGO_PROYECTOR ANCHO_CANVAS
#define ANCHO_PROYECTOR 20
#define WOODEN_WALL_ROOT "../../editor/resources/wall2.jpg"
#define BLUE_STONE_WALL_ROOT "../../editor/resources/wall1.jpg"
#define GRAY_STONE_WALL_ROOT "../../editor/resources/wall3.jpg"
#define PUERTA_ROOT "../../editor/resources/puerta.png"

#include "SDL2/SDL_ttf.h"
#include <SDL2/SDL.h>
#include "../include/musica.h"
#include "../include/audio.h"


#define LOWER_TEXTURE_ROOT "../../client/resources/images/ParteInferior.png"
#define MUSICA_FONDO "../../client/resources/sonidos/musiquita.wav"

Juego::Juego(const std::string &titulo, int ancho, int alto, bool fullscreen, int idJugador) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == EXITO) {


        if (TTF_Init() == -1) {
            printf("Failed to init TTF\n");
            exit(1);
        }
        Audio audio;
        Musica ambient_music = Musica(MUSICA_FONDO);
        ambient_music.play(-1);

        this->ventana = new Ventana(titulo, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ancho, alto, flags);
        this->modelo = new Modelo(this->ventana, idJugador);
        modelo->inicializar();
        this->texturaInferior = new Textura(LOWER_TEXTURE_ROOT,
                                            this->ventana->obtener_render());
        this->corriendo = true;
    } else {
        this->corriendo = false;
    }
}

void Juego::run() {
  Map mapa (20,20);
    while(this->corriendo){
        try {
              this->clean();
            //  this->raycasting(mapa,this->modelo->getPlayer());
              this->renderizar();
              this->actualizar(/*1*/);
              std::chrono::milliseconds duration(100);
              std::this_thread::sleep_for(duration);
        } catch (...) {
            this->corriendo = false;
        }
    }

}

void Juego::actualizar(/*temporal int idArma*/) {
    this->ventana->actualizar();
    this->modelo->actualizar();
}

void Juego::renderizar() {
    this->ventana->renderizar(this->texturaInferior);
    this->modelo->renderizar();
}

Juego::~Juego() {}

void Juego::cerrar(){
    this->corriendo = false;
    this->ventana->cerrar();
};
void Juego::clean() {
    this->ventana->limpiar();
  //  this->corriendo = false;
}

void Juego::raycasting(Map &mapaa, Player &jugador) {

// x = fila / y = columna

  int mapa[TAMANIO_FILA][TAMANIO_COLUMNA] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                       /*1*/  {1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1},
                                      /*2*/   {1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
                                     /*3*/    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    /*4*/     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                   /*5*/      {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  /*6*/       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  /*7*/       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  /*8*/       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  /*9*/       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                  /*10*/      {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                                  /*11*/      {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                                /*12*/        {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                            /*13*/            {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                            /*14*/            {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                                    /*15*/    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    /*16*/    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                      /*17*/  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                      /*18*/  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                      /*19*/  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                            /* 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 */
                                            };
            SDL_Renderer *render = this->ventana->obtener_render();
            Textura* wall = new Textura(GRAY_STONE_WALL_ROOT,render);
            Posicion& posJugador = jugador.getPosicion();

            /*******PARAMETROS DE RAYCASTING********/
            double rangoDeVista = 2 * acos(0.0) / 3;//60 grados
            int ladoCelda = ANCHO_CANVAS/TAMANIO_FILA;
            double anguloPorStripe = rangoDeVista / ANCHO_CANVAS;
            double anguloJugador = jugador.getAnguloDeVista();
            double anguloRayo = anguloJugador - (rangoDeVista / 2);
            SDL_Rect wallDimension,wallDest;

            std::vector<double>& zbuffer = this->modelo->getZBuffer();
            for (int i = ANCHO_CANVAS - 1; i >= 0; i--) {
                unsigned int alturaParedProyectada = 0;
                double distancia = 0;
                int drawStart,drawEnd;
                Rayo rayo(rangoDeVista, ladoCelda, LARGO_PROYECTOR, anguloRayo,posJugador);
                rayo.verificarInterseccion(mapa,distancia,jugador);
                alturaParedProyectada = (ladoCelda / distancia) * rayo.getDistanciaProyector();
                zbuffer.push_back(distancia);
                drawStart = floor((ANCHO_CANVAS / 2) - (alturaParedProyectada / 2)) - 20;//cheuear ese ancho canvas
                drawEnd = drawStart + alturaParedProyectada - 20;
                if (drawStart > ALTURA_CANVAS){
                    drawStart = 600 - 1;
                    drawEnd = 0;
                }
                wallDimension.x = rayo.getOffset() % 64;
                wallDimension.y = 0;
                wallDimension.w = 1;
                wallDimension.h = alturaParedProyectada;

                wallDest.x = i;
                wallDest.y = drawStart;
                wallDest.w = 1;
                wallDest.h = drawEnd - drawStart;

                wall->renderizar(&wallDimension,wallDest, 0,NULL);
              //  this->ventana->actualizar();

                std::chrono::milliseconds duration(20);
                std::this_thread::sleep_for(duration);
                anguloRayo += anguloPorStripe;
            }
            delete wall;
}
