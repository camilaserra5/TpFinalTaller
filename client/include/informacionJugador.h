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
          this->vida = new Label(200, 200, "PEPEEE", fuentes.getFont("info"), blanco, render);
          this->vida->setLabelText();
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
          this->vida->draw();
          //this->nivel.renderizar();
          //his->puntaje.renderizar();

      }

private:
        Label* vida;
        //Label nivel;
        //Label puntaje;


};

#endif
