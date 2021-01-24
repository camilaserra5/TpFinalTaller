#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <iostream>
#include "objetosJuego.h"
#include <sstream>

class ISerializable {
public:
    virtual std::stringstream serializar() = 0;

    virtual void deserializar(/*std::stringstream secuencia*/) = 0;

    virtual ~ISerializable() {}
};

#endif
