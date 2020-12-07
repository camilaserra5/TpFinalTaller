#include "../include/ataque.h"

Ataque::Ataque(int &destinox, int &destinoy):
          destinox(destinox),
          destinoy(destinoy){
            this.danio = 10;
          }

Ataque::~Ataque(){}


void Ataque::estrategia(Mapa &mapa){
    if (mapa(destinox,destinoy) == JUGADOR){
        mapa(destinox,destinoy).recibirAtaque(danio);
    }
    std::cout << "ataco pium pium\n";
}
