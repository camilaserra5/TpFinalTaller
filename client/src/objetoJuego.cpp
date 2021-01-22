#include "../include/objetoJuego.h"

ObjetoJuego::ObjetoJuego(const char *rutaimg, SDL_Renderer *render, int ancho, int alto) :
        alto(alto),
        ancho(ancho),
        render(render) {
    this->textura = new Textura(rutaimg, render);
}


void ObjetoJuego::renderizar(int posx, int posy, int angulo) {
    Lienzo lienzosrc(0, 0, 30, 30);
    Lienzo lienzodest(posx, posy, this->ancho, this->alto);
    this->textura->renderizar(this->render, (lienzosrc), (lienzodest));
}
