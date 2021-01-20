#include "../include/objetoJuego.h"

ObjetoJuego::ObjetoJuego(const char *rutaimg, SDL_Renderer *render, int x, int y, int ancho, int alto) :
        xpos(x),
        ypos(y),
        alto(alto),
        ancho(ancho),
        render(render) {
    this->textura = new Textura(rutaimg, render);
}

void ObjetoJuego::actualizar(int posx, int posy) {
    this->xpos = posx;
    this->ypos = posy;
    this->ancho = this->ancho;
    this->alto = this->alto;
}

void ObjetoJuego::renderizar() {
    Lienzo lienzosrc(0, 0, 30, 30);
    Lienzo lienzodest(this->xpos, this->ypos, this->ancho, this->alto);
    this->textura->renderizar(this->render, (lienzosrc), (lienzodest));
}
