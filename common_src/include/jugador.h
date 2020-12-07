#ifndef _JUGADOR_H
#define _JUGADOR_H
#include <vector>

class Jugador{
      public:
            Jugador();
            ~Jugador();
            void moverse(int &posx, int &posy);
            void actualizar_vida(int &vidaActualizada);
            void agregar_item();
            void agregar_arma(Arma* arma);
      private:
            int vida;
            int posx, posy;
            std::vector<Arma*> armas;
            int municiones;
            int puntaje;
};

#endif
