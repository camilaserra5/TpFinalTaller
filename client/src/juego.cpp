#include "../include/juego.h"
#include <config.h>
#include <algorithm>

#define EXITO 0
#define LARGO_PROYECTOR ANCHO_CANVAS
#define ANCHO_PROYECTOR 20


#define BLUE_WALL IMGS_DIR BLUE_WALL_IMG
#define GREY_WALL IMGS_DIR GREY_WALL_IMG
#define WOOD_WALL IMGS_DIR WOOD_WALL_IMG
#define DOOR IMGS_DIR DOOR_IMG
#define KEY_DOOR IMGS_DIR KEYDOOR_IMG
#define RANGO_DE_VISTA 1.047197551
#define TIEMPO_CLIENTE 60
#define ALTURA_IMAGEN_INFERIOR 20
#define ANCHO_SPRITE 64

#define LOWER_TEXTURE_ROOT IMGS_DIR INFERIOR_IMG


Juego::Juego(Ventana &ventana, Modelo &modelo) : ventana(ventana), modelo(modelo) {
    SDL_Renderer *render = this->ventana.obtener_render();

    this->corriendo = true;
    Textura *t1 = new Textura(BLUE_WALL, render);
    Textura *t2 = new Textura(GREY_WALL, render);
    Textura *t3 = new Textura(WOOD_WALL, render);
    Textura *t4 = new Textura(KEY_DOOR, render);
    Textura *t5 = new Textura(DOOR, render);

    this->texturas.insert({TYPE_WALL, t1});
    this->texturas.insert({TYPE_WALL_2, t2});
    this->texturas.insert({TYPE_WALL_3, t3});
    this->texturas.insert({TYPE_KEY_DOOR, t4});
    this->texturas.insert({TYPE_DOOR, t5});
    this->texturas.insert({TYPE_FAKE_WALL, t3});
}

void Juego::eventos() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                this->cerrar();
            default:
                break;
        }
    }
}

void Juego::run() {
    while (this->corriendo) {
        try {
            auto inicio = std::chrono::high_resolution_clock::now();
            this->modelo.procesarActualizaciones();
            this->clean();
            this->raycasting(this->modelo.obtenerMapa(), this->modelo.getPlayer());
            if (this->corriendo) this->renderizar();
            this->actualizar();
            auto final = std::chrono::high_resolution_clock::now();
            auto delta = final - inicio;
            long tardanza = delta.count();
            if (tardanza >= TIEMPO_CLIENTE) {
                tardanza = TIEMPO_CLIENTE;
            }
            std::chrono::milliseconds duration(TIEMPO_CLIENTE - tardanza);
            std::this_thread::sleep_for(duration);
        } catch (std::exception &exc) {
            std::cout << exc.what() << std::endl;
            this->corriendo = false;
        } catch (...){
            this->corriendo = false;
        }
    }
    this->cerrar();
}

void Juego::actualizar() {
    this->modelo.actualizar();
    this->ventana.actualizar();
}

void Juego::renderizar() {
    this->modelo.renderizar();
}

Juego::~Juego() {
    std::map<int, Textura *>::iterator i;
    for (i = texturas.begin(); i != texturas.end(); ++i) {
        delete i->second;
    }
}

void Juego::cerrar() {
  if (this->corriendo){
    this->corriendo = false;
    this->ventana.cerrar();
    }
}

void Juego::clean() {
    this->ventana.limpiar();
}

void Juego::raycasting(Map &mapa, Player &jugador) {
    Posicion &posJugador = jugador.getPosicion();
    SDL_Renderer *render = this->ventana.obtener_render();
    int ladoCelda = mapa.getLadoCelda();
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
    std::reverse(zbuffer.begin(), zbuffer.end());
}

void Juego::renderizarPared(SDL_Renderer *render, Rayo &rayo, int &posCanvas, unsigned int &alturaParedProyectada) {
    Textura *wall = verificarTextura(render, rayo.getTipoPared());
    if (!wall) return;
    int drawStart, drawEnd;
    drawStart = floor((ANCHO_CANVAS / 2) - (alturaParedProyectada / 2)) - ALTURA_IMAGEN_INFERIOR;
    drawEnd = drawStart + alturaParedProyectada;
    if (alturaParedProyectada > ALTURA_CANVAS) {
        drawStart = 0;
        drawEnd = ALTURA_CANVAS - 1;
    }
    SDL_Rect wallDimension, wallDest;
    wallDimension.x = rayo.getOffset() % ANCHO_SPRITE;
    wallDimension.y = 0;
    wallDimension.w = 1;
    wallDimension.h = alturaParedProyectada;

    wallDest.x = posCanvas;
    wallDest.y = drawStart;
    wallDest.w = 1;
    wallDest.h = drawEnd - drawStart;

    wall->renderizar(&wallDimension, wallDest, 0, NULL);
}

Textura *Juego::verificarTextura(SDL_Renderer *render, int &tipoDePared) {
    try {
        return this->texturas.at(tipoDePared);
    } catch (...) {
        return nullptr;
    }
}
