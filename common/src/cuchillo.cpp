#include "../include/cuchillo.h"


Cuchillo::Cuchillo() :
        danio(10) {}

Cuchillo::~Cuchillo() {}

int Cuchillo::atacar() {
    return this->danio;
}
