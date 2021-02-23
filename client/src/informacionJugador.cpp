#include <iostream>
#include "../include/informacionJugador.h"
#include <config.h>

#define LOWER_TEXTURE_ROOT IMGS_DIR INFERIOR_IMG
#define FONT FONTS_DIR NOUGAT_FONT
#define RUTA_SONIDO_CANION SOUNDS_DIR MUERTE

InfoJugador::InfoJugador(SDL_Renderer *render, int vida, int nivel, int puntaje,
                         int cantVidas, int balas) : musica(MUERTE) {
    Fonts fuentes;
    fuentes.addFont("info", FONT, 35);
    SDL_Color blanco = {255, 255, 255, 255};
    std::string vidainfo = std::to_string(vida);
    std::string nivelinfo = std::to_string(nivel);
    std::string puntajeinfo = std::to_string(puntaje);
    std::string cantVidasinfo = std::to_string(cantVidas);
    std::string balasinfo = std::to_string(balas);
    this->vida = new Label(450, 570, vidainfo, fuentes.getFont("info"), blanco, render);
    this->nivel = new Label(50, 570, nivelinfo, fuentes.getFont("info"), blanco, render);
    this->puntaje = new Label(150, 570, puntajeinfo, fuentes.getFont("info"), blanco, render);
    this->cantVidas = new Label(270, 570, cantVidasinfo, fuentes.getFont("info"), blanco, render);
    this->balas = new Label(550, 570, balasinfo, fuentes.getFont("info"), blanco, render);
    this->texturaInferior = new Textura(LOWER_TEXTURE_ROOT, render);
    this->murio = false;
}

InfoJugador::~InfoJugador() {
    delete this->vida;
    delete this->nivel;
    delete this->puntaje;
    delete this->cantVidas;
    delete this->balas;
}

void InfoJugador::actualizarDatosJugador(int vida, int nivel, int puntaje, int cantVidas,
                                         int balas) {
    if (cantVidas < std::stoi(this->cantVidas->getTexto().c_str())){
        this->murio = true;
    }
    std::string vidainfo = std::to_string(vida);
    std::string nivelinfo = std::to_string(nivel);
    std::string puntajeinfo = std::to_string(puntaje);
    std::string cantVidasinfo = std::to_string(cantVidas);
    std::string balasinfo = std::to_string(balas);
    this->vida->actualizarTexto(vidainfo);
    this->nivel->actualizarTexto(nivelinfo);
    this->puntaje->actualizarTexto(puntajeinfo);
    this->cantVidas->actualizarTexto(cantVidasinfo);
    this->balas->actualizarTexto(balasinfo);
}

void InfoJugador::renderizar() {
    SDL_Rect posiciontexturadest{0, 550, 800, 60};
    texturaInferior->renderizar(NULL, posiciontexturadest, 0, NULL);
    this->vida->setLabelText();
    this->nivel->setLabelText();
    this->puntaje->setLabelText();
    this->cantVidas->setLabelText();
    this->balas->setLabelText();
    this->vida->draw();
    this->nivel->draw();
    this->puntaje->draw();
    this->cantVidas->draw();
    this->balas->draw();
    if (this->murio){
        this->musica.play(2);
    }
}

int InfoJugador::getPuntaje() {
    return this->puntaje->getTexto();
}
