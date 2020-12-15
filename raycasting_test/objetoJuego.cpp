#include "objetoJuego.h"

ObjetoJuego::ObjetoJuego(const char* rutaimg, SDL_Renderer* render, int x, int y, int ancho, int alto) :
    xpos(x),
    ypos(y),
    alto(alto),
    ancho(ancho),
    render(render){
        this->textura = new Textura(rutaimg, render);
}

void ObjetoJuego::actualizar(){
    this->xpos++; //POR AHORA
    this->ypos++; //POR AHORA
    this->ancho= this->ancho * 2;
    this->alto = this->alto * 2;
}

void ObjetoJuego::renderizar() {
    Lienzo lienzosrc(0,0,30,30);
    Lienzo lienzodest(this->xpos, this->ypos, this->ancho, this->alto);
    this->textura->renderizar(this->render, (lienzosrc), (lienzodest));
}
