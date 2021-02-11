#ifndef ACTUALIZACION_H
#define ACTUALIZACION_H

#include "estadoJuego.h"
#include <list>
#include "iserializable.h"
#include "ranking.h"

class Actualizacion : public ISerializable {
public:
    Actualizacion();

    ~Actualizacion();

    virtual int obtenerId() = 0;

private:
};

#endif
