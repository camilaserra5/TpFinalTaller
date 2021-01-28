#ifndef _INFORMACION_JUGADOR_H
#define _INFORMACION_JUGADOR_H


#include "label.h"
#include "fonts.h"

class InfoJugador{
public:

      InfoJugador(SDL_Renderer* render, int vida, int nivel, int puntaje){
          Fonts fuentes;
          fuentes.addFont("info", "../resources/fonts/wolfenstein.ttf", 60);
          SDL_Color blanco = {255, 255, 255, 255};
          std::string vidainfo = std::to_string(vida);
          std::string nivelinfo = std::to_string(nivel);
          std::string puntajeinfo = std::to_string(puntaje);
          //Label label(500, 0, vidainfo, fuentes.getFont("info"), blanco, render);
          this->vida = new Label(400, 400, "PEPEEE", fuentes.getFont("info"), blanco, render);
          this->nivel = new Label(600, 600, nivelinfo, fuentes.getFont("info"), blanco, render);
          this->puntaje = new Label(500, 600, puntajeinfo, fuentes.getFont("info"), blanco, render);
          //this->nivel = Texto(ventana, nivel);
          //this->puntaje = Texto(ventana, puntaje);
      }
      ~InfoJugador(){}
      void actualizarDatosJugador(int vida, int nivel, int puntaje){
          std::string vidainfo = std::to_string(vida);
          std::string nivelinfo = std::to_string(nivel);
          std::string puntajeinfo = std::to_string(puntaje);
          //this->vida->actualizarTexto(vidainfo);
      }
      void renderizar(){
          this->vida->setLabelText();
          this->vida->draw();
          this->nivel->setLabelText();
          this->nivel->draw();
          this->puntaje->setLabelText();
          this->puntaje->draw();

      }

private:
        Label* vida;
        Label* nivel;
        Label* puntaje;


};

#endif
