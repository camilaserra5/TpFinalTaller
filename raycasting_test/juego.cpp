#include "juego.h"

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
  Map mapa = yamlToMap;
    try {
        this->clean();
        this->renderizar();

        this->raycasting(mapa,this->jugador);
        this->actualizar(/*1*/);
//deberia ir antes que renderizar para que se dibuje atras del mapa
        this->jugador.rotar(1);
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


void Juego::raycasting(Map &mapa, Player &jugador) {
    Posicion &posJugador = jugador.getPosicion();
    SDL_Renderer *render = this->ventana.obtener_render();
    int ladoCelda = ANCHO_CANVAS / TAMANIO_FILA;
    double anguloPorStripe = RANGO_DE_VISTA / ANCHO_CANVAS;
    double anguloJugador = jugador.getAnguloDeVista();
    double anguloRayo = anguloJugador - (RANGO_DE_VISTA / 2);

    std::vector<double> &zbuffer = this->modelo.getZBuffer();
    for (int i = ANCHO_CANVAS - 1; i >= 0; i--) {
        double distancia = 0;
        Rayo rayo(RANGO_DE_VISTA, ladoCelda, LARGO_PROYECTOR, anguloRayo, posJugador);
        rayo.verificarInterseccion(mapa, distancia, jugador);
        zbuffer.push_back(distancia);
        unsigned int alturaParedProyectada = 0;
        alturaParedProyectada = (ladoCelda / distancia) * rayo.getDistanciaProyector();
        renderizarPared(render, rayo, i, alturaParedProyectada);
        anguloRayo += anguloPorStripe;
    }
}

void Juego::renderizarPared(SDL_Renderer *render, Rayo &rayo, int &posCanvas, unsigned int &alturaParedProyectada) {
    Textura *wall = verificarTextura(render, rayo.getTipoPared());
    int drawStart, drawEnd;
    drawStart = floor((ANCHO_CANVAS / 2) - (alturaParedProyectada / 2)) - 20;//cheuear ese ancho canvas
    drawEnd = drawStart + alturaParedProyectada;
    if (drawStart > ALTURA_CANVAS) {
        drawStart = 600 - 1;
        drawEnd = 0;
    }
    SDL_Rect wallDimension, wallDest;
    wallDimension.x = rayo.getOffset() % 64;
    wallDimension.y = 0;
    wallDimension.w = 1;
    wallDimension.h = alturaParedProyectada;

    wallDest.x = posCanvas;
    wallDest.y = drawStart;
    wallDest.w = 1;
    wallDest.h = drawEnd - drawStart;

    wall->renderizar(&wallDimension, wallDest, 0, NULL);
    delete wall;
}

Textura *Juego::verificarTextura(SDL_Renderer *render, int &tipoDePared) {
    //cambiar a mas especifico
    if (tipoDePared == TYPE_WALL) {
        return new Textura(BLUE_WALL, render);
    } else if (tipoDePared == TYPE_WALL_2) {
        return new Textura(WOOD_WALL, render);
    } else if (tipoDePared == TYPE_WALL_3) {
        return new Textura(GREY_WALL, render);
    } else {
        return new Textura(DOOR, render);
    }
}
