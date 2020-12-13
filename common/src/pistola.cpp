#include "../include/pistola.h"


Pistola::Pistola() :
        danio(10),
        precision(10),
        probalidad_acierto(10) {}

Pistola::~Pistola() {}

// conviene mandarle coordenadas de yo jugador??
// or ahora devuelve danio de ataque
int Pistola::atacar() {
    return this->danio;
}
