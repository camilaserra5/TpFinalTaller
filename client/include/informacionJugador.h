#ifndef _INFORMACION_JUGADOR_H
#define _INFORMACION_JUGADOR_H

#include "ventana.h"
#include "texto.h"

class InfoJugador{
public:

      InfoJugador(Ventana& ventana, int vida, int nivel, int puntaje){
          this->vida = Texto(ventana, vida);
          this->nivel = Texto(ventana, nivel);
          this->puntaje = Texto(ventana, puntaje);
      }
      ~InfoJugador();
      void renderizar(){
        /*
          this->vida.renderizar();
          this->nivel.renderizar();
          his->puntaje.renderizar();
          */
      }

private:
        Texto vida;
        Texto nivel;
        Texto puntaje;


};

#endif
