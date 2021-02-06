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
#define RANGO_DE_VISTA 1.047197551


#define LOWER_TEXTURE_ROOT "../../client/resources/images/ParteInferior.png"


Juego::Juego(Ventana &ventana, Modelo &modelo) : ventana(ventana), modelo(modelo) {

    this->modelo.inicializar();
    this->texturaInferior = new Textura(LOWER_TEXTURE_ROOT,
                                        this->ventana.obtener_render());
    this->corriendo = true;
}

void Juego::eventos() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
                this->corriendo = false;
                break;

            default:
                break;

        }
    }
}

void Juego::run() {
    Map mapa(20, 20);
    while (this->corriendo) {
        try {
            auto inicio = std::chrono::high_resolution_clock::now();
            this->clean();
            this->eventos();
            this->raycasting(mapa, this->modelo.getPlayer());
            this->renderizar();
            this->actualizar(/*1*/);
            auto final = std::chrono::high_resolution_clock::now();
            auto delta = final - inicio;
            long tardanza = delta.count();
            if (tardanza >= 60) {
                tardanza = 60;
            }
            std::chrono::milliseconds duration(60 - tardanza);
            std::this_thread::sleep_for(duration);
        } catch (std::exception &exc) {
            std::cout << exc.what() << std::endl;
            this->corriendo = false;
        }
    }
    this->cerrar();

}

void Juego::actualizar(/*temporal int idArma*/) {
    this->ventana.actualizar();
    this->modelo.actualizar();
}

void Juego::renderizar() {
    this->modelo.renderizar();
    this->ventana.renderizar(this->texturaInferior);
}

Juego::~Juego() {
    delete this->texturaInferior;
}

void Juego::cerrar() {
    this->corriendo = false;
    this->ventana.cerrar();
};

void Juego::clean() {
    this->ventana.limpiar();
    //  this->corriendo = false;
}

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
        return new Textura(WOODEN_WALL_ROOT, render);
    } else if (tipoDePared == TYPE_DOOR) {
        return new Textura(PUERTA_ROOT, render);
    } else {
        return new Textura(GRAY_STONE_WALL_ROOT, render);
    }
}
