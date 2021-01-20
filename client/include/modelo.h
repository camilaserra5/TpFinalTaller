#ifndef _MODELO_H
#define _MODELO_H

#include "ventana.h"
#include "player.h"
#include <map>

class Modelo{
    public:
          Modelo(Ventana* ventana, int idJugador);
          ~Modelo();
          void inicializar(); // viene los datos todos los jugadores?
          void renderizar();
    private:
            Ventana* ventana;
            int idJugador;
            std::map<int, Player*> jugadores;
            // mapa de entidades dibujables;

};

#endif
