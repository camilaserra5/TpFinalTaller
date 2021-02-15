#include "../include/juego.h"

#define EXITO 0
#define LARGO_PROYECTOR ANCHO_CANVAS
#define ANCHO_PROYECTOR 20
#define BLUE_WALL "../../editor/resources/blue-wall.jpg"
#define GREY_WALL "../../editor/resources/grey-wall.jpg"
#define WOOD_WALL "../../editor/resources/wood-wall.jpg"
#define DOOR "../../editor/resources/door.jpg"
#define KEYDOOR "../../editor/resources/keydoor.jpg"
#define RANGO_DE_VISTA 1.047197551

#define LOWER_TEXTURE_ROOT "../../client/resources/images/ParteInferior.png"


Juego::Juego(Ventana &ventana, Modelo &modelo) : ventana(ventana), modelo(modelo) {
    SDL_Renderer *render = this->ventana.obtener_render();

    this->texturaInferior = new Textura(LOWER_TEXTURE_ROOT, render);
    this->corriendo = true;
    Textura *t1 = new Textura(BLUE_WALL, render);
    Textura *t2 = new Textura(WOOD_WALL, render);
    Textura *t3 = new Textura(GREY_WALL, render);
    Textura *t4 = new Textura(KEYDOOR, render);
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
                exit(0);
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
            this->eventos();
            this->raycasting(this->modelo.obtenerMapa(), this->modelo.getPlayer());
            this->renderizar();
            this->actualizar();
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

void Juego::actualizar() {
    this->ventana.actualizar();
    this->modelo.actualizar();
}

void Juego::renderizar() {
    this->modelo.renderizar();
    this->ventana.renderizar(this->texturaInferior);
}

Juego::~Juego() {
    delete this->texturaInferior;
    std::map<int, Textura *>::iterator i;
    for (i = texturas.begin(); i != texturas.end(); ++i) {
        delete i->second;
    }
}

void Juego::cerrar() {
    this->corriendo = false;
    this->ventana.cerrar();
};

void Juego::clean() {
    this->ventana.limpiar();
}

void Juego::raycasting(Map &mapa, Player &jugador) {
    Posicion &posJugador = jugador.getPosicion();
    SDL_Renderer *render = this->ventana.obtener_render();
    int ladoCelda = 80;// ANCHO_CANVAS / mapa.getRowSize();
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
    drawStart = floor((ANCHO_CANVAS / 2) - (alturaParedProyectada / 2)) - 20;
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
}

Textura *Juego::verificarTextura(SDL_Renderer *render, int &tipoDePared) {
    return this->texturas.at(tipoDePared);
}
