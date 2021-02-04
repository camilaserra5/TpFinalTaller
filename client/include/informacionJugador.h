#ifndef _INFORMACION_JUGADOR_H
#define _INFORMACION_JUGADOR_H


#include "label.h"
#include "fonts.h"

class InfoJugador {
public:

    InfoJugador(SDL_Renderer *render, int vida, int nivel, int puntaje,
                int cantVidas, int balas);/* {
        Fonts fuentes;
        fuentes.addFont("info", "../../resources/fuentes/Nougat.ttf", 35);
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
    }*/

    ~InfoJugador();/* {
        delete this->vida;
        delete this->nivel;
        delete this->puntaje;
        delete this->cantVidas;
        delete this->balas;
    }*/

    void actualizarDatosJugador(int vida, int nivel, int puntaje, int cantVidas,
                                int balas);/* {
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
    }*/

    void renderizar();/* {
        this->vida->setLabelText();
        this->vida->draw();
        this->nivel->setLabelText();
        this->nivel->draw();
        this->puntaje->setLabelText();
        this->puntaje->draw();
        this->cantVidas->setLabelText();
        this->cantVidas->draw();
        this->balas->setLabelText();
        this->balas->draw();
    }*/

    int getPuntaje();/*{
        this->puntaje->getTexto();
    }*/
private:
    Label *vida;
    Label *nivel;
    Label *puntaje;
    Label *cantVidas;
    Label *balas;


};

#endif
