#ifndef _PISTOLA_H
#define _PISTOLA_H

#include "arma.h"

class Pistola : public Arma {
public:
    Pistola();

    ~Pistola();

    int atacar() override;

private:
    int danio; //  aleatorio rand(1,10)?
    int precision;
    int probalidad_acierto;
};

#endif
